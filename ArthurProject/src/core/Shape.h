/*
    Copyright (c) 2013 Randy Gaul http://RandyGaul.net
    This software is provided 'as-is', without any express or implied
    warranty. In no event will the authors be held liable for any damages
    arising from the use of this software.
    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:
      1. The origin of this software must not be misrepresented; you must not
         claim that you wrote the original software. If you use this software
         in a product, an acknowledgment in the product documentation would be
         appreciated but is not required.
      2. Altered source versions must be plainly marked as such, and must not be
         misrepresented as being the original software.
      3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SHAPE_H
#define SHAPE_H

#include "Body.h"

#define MaxPolyVertexCount 64

struct Shape
{
    enum Type
    {
        eCircle,
        ePoly,
        eCount
    };

    Shape() {}
    virtual Shape* Clone(void) const = 0;
    virtual void Initialize(void) = 0;
    virtual void ComputeMass(float density) = 0;
    virtual void SetOrient(float radians) = 0;
    virtual Type GetType(void) const = 0;

    Body* body;

    // For circle shape
    float radius;

    // For Polygon shape
    Mat2 u; // Orientation matrix from model to world
};

struct Circle : public Shape
{
    Circle(float r)
    {
        radius = r;
    }

    Shape* Clone(void) const
    {
        return new Circle(radius);
    }

    void Initialize(void)
    {
        ComputeMass(1.0f);
    }

    void ComputeMass(float density)
    {
        body->m = PI * radius * radius * density;
        body->im = (body->m) ? 1.0f / body->m : 0.0f;
        body->I = body->m * radius * radius;
        body->iI = (body->I) ? 1.0f / body->I : 0.0f;
    }

    void SetOrient(float radians)
    {
    }

    Type GetType(void) const
    {
        return eCircle;
    }
};

struct PolygonShape : public Shape
{
    void Initialize(void)
    {
        ComputeMass(1.0f);
    }

    Shape* Clone(void) const
    {
        PolygonShape* poly = new PolygonShape();
        poly->u = u;
        for (unsigned int i = 0; i < m_vertexCount; ++i)
        {
            poly->m_vertices[i] = m_vertices[i];
            poly->m_normals[i] = m_normals[i];
        }
        poly->m_vertexCount = m_vertexCount;
        return poly;
    }

    void ComputeMass(float density)
    {
        // Calculate centroid and moment of interia
        Vec2 c(0.0f, 0.0f); // centroid
        float area = 0.0f;
        float I = 0.0f;
        const float k_inv3 = 1.0f / 3.0f;

        for (unsigned int i1 = 0; i1 < m_vertexCount; ++i1)
        {
            // Triangle vertices, third vertex implied as (0, 0)
            Vec2 p1(m_vertices[i1]);
            unsigned int i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
            Vec2 p2(m_vertices[i2]);

            float D = Cross(p1, p2);
            float triangleArea = 0.5f * D;

            area += triangleArea;

            // Use area to weight the centroid average, not just vertex position
            c += triangleArea * k_inv3 * (p1 + p2);

            float intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
            float inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
            I += (0.25f * k_inv3 * D) * (intx2 + inty2);
        }

        c *= 1.0f / area;

        // Translate vertices to centroid (make the centroid (0, 0)
        // for the polygon in model space)
        // Not floatly necessary, but I like doing this anyway
        for (unsigned int i = 0; i < m_vertexCount; ++i)
            m_vertices[i] -= c;

        body->m = density * area;
        body->im = (body->m) ? 1.0f / body->m : 0.0f;
        body->I = I * density;
        body->iI = body->I ? 1.0f / body->I : 0.0f;
    }

    void SetOrient(float radians)
    {
        u.Set(radians);
    }

    Type GetType(void) const
    {
        return ePoly;
    }

    // Half width and half height
    void SetBox(float hw, float hh)
    {
        m_vertexCount = 4;
        m_vertices[0].Set(-hw, -hh);
        m_vertices[1].Set(hw, -hh);
        m_vertices[2].Set(hw, hh);
        m_vertices[3].Set(-hw, hh);
        m_normals[0].Set(0.0f, -1.0f);
        m_normals[1].Set(1.0f, 0.0f);
        m_normals[2].Set(0.0f, 1.0f);
        m_normals[3].Set(-1.0f, 0.0f);
    }

    void Set(Vec2* vertices, unsigned int count)
    {
        // No hulls with less than 3 vertices (ensure actual polygon)
        assert(count > 2 && count <= MaxPolyVertexCount);
        count = std::min((int)count, MaxPolyVertexCount);

        // Find the right most point on the hull
        int rightMost = 0;
        float highestXCoord = vertices[0].x;
        for (unsigned int i = 1; i < count; ++i)
        {
            float x = vertices[i].x;
            if (x > highestXCoord)
            {
                highestXCoord = x;
                rightMost = i;
            }

            // If matching x then take farthest negative y
            else if (x == highestXCoord)
                if (vertices[i].y < vertices[rightMost].y)
                    rightMost = i;
        }

        int hull[MaxPolyVertexCount];
        int outCount = 0;
        int indexHull = rightMost;

        for (;;)
        {
            hull[outCount] = indexHull;

            // Search for next index that wraps around the hull
            // by computing cross products to find the most counter-clockwise
            // vertex in the set, given the previos hull index
            int nextHullIndex = 0;
            for (int i = 1; i < (int)count; ++i)
            {
                // Skip if same coordinate as we need three unique
                // points in the set to perform a cross product
                if (nextHullIndex == indexHull)
                {
                    nextHullIndex = i;
                    continue;
                }

                // Cross every set of three unique vertices
                // Record each counter clockwise third vertex and add
                // to the output hull
                // See : http://www.oocities.org/pcgpe/math2d.html
                Vec2 e1 = vertices[nextHullIndex] - vertices[hull[outCount]];
                Vec2 e2 = vertices[i] - vertices[hull[outCount]];
                float c = Cross(e1, e2);
                if (c < 0.0f)
                    nextHullIndex = i;

                // Cross product is zero then e vectors are on same line
                // therefor want to record vertex farthest along that line
                if (c == 0.0f && e2.LenSqr() > e1.LenSqr())
                    nextHullIndex = i;
            }

            ++outCount;
            indexHull = nextHullIndex;

            // Conclude algorithm upon wrap-around
            if (nextHullIndex == rightMost)
            {
                m_vertexCount = outCount;
                break;
            }
        }

        // Copy vertices into shape's vertices
        for (unsigned int i = 0; i < m_vertexCount; ++i)
            m_vertices[i] = vertices[hull[i]];

        // Compute face normals
        for (unsigned int i1 = 0; i1 < m_vertexCount; ++i1)
        {
            unsigned int i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
            Vec2 face = m_vertices[i2] - m_vertices[i1];

            // Ensure no zero-length edges, because that's bad
            assert(face.LenSqr() > EPSILON * EPSILON);

            // Calculate normal with 2D cross product between vector and scalar
            m_normals[i1] = Vec2(face.y, -face.x);
            m_normals[i1].Normalize();
        }
    }

    // The extreme point along a direction within a polygon
    Vec2 GetSupport(const Vec2& dir)
    {
        float bestProjection = -FLT_MAX;
        Vec2 bestVertex;

        for (unsigned int i = 0; i < m_vertexCount; ++i)
        {
            Vec2 v = m_vertices[i];
            float projection = Dot(v, dir);

            if (projection > bestProjection)
            {
                bestVertex = v;
                bestProjection = projection;
            }
        }

        return bestVertex;
    }

    unsigned int m_vertexCount;
    Vec2 m_vertices[MaxPolyVertexCount];
    Vec2 m_normals[MaxPolyVertexCount];
};

#endif // SHAPE_H