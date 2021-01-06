#include "Scene.h"
#include "TimeTracker.h"

b2World Scene::myB2World = b2World(b2Vec2(0.0f, 10.0f));

Scene::Scene() : Node(sf::Vector2f(0, 0), "Scene")
{
	myView = Window::CurrentWindow->GetRawWindow()->getDefaultView();
}
void Scene::OnUpdate()
{
	myB2World.Step(TimeTracker::GetDeltaTime(), velocityIterations, positionIterations);
	Node::OnUpdate();
}
void Scene::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->setView(myView);
	Node::OnRender(aWindow);
	if (myGroundVerts.size() != 0) 
	{
		for (int j = 0; j < myGroundVerts.size(); j++) 
		{
			int vCount = myGroundVerts[j].size() + 1;
			sf::VertexArray tempVArr(sf::PrimitiveType::LineStrip, vCount);
			for (int i = 0; i < vCount; i++)
			{
				sf::Vector2f tempPos = myGroundVerts[j][i % (vCount - 1)];
				tempVArr[i].position = tempPos;
				tempVArr[i].color = sf::Color::White;
			}
			aWindow->draw(tempVArr);
		}
	}
}

void Scene::SetView(sf::View aView)
{
	myView = aView;
}

b2Body* Scene::AddPolygon(const b2PolygonShape aShape, const float& aDensity)
{
	b2BodyDef tempDef;
	tempDef.type = b2_dynamicBody;
	tempDef.fixedRotation = true;

	b2Body* tempBody = myB2World.CreateBody(&tempDef);
	tempBody->CreateFixture(&aShape, aDensity);

	return tempBody;
}


double angle_degree(double x1, double y1, double x2, double y2, double x3,
    double y3)
{
    double value;
    double x;
    double y;

    x = (x3 - x2) * (x1 - x2) + (y3 - y2) * (y1 - y2);

    y = (x3 - x2) * (y1 - y2) - (y3 - y2) * (x1 - x2);

    if (x == 0.0 && y == 0.0)
    {
        value = 0.0;
    }
    else
    {
        value = atan2(y, x);

        if (value < 0.0)
        {
            value = value + 2.0 * b2_pi;
        }
        value = 180.0 * value / b2_pi;
    }

    return value;
}

double polygon_area(const std::vector<sf::Vector2f>& someVertices)
{
    double area;
    int i;
    int im1;

    area = 0.0;
    im1 = someVertices.size() - 1;
    for (i = 0; i < someVertices.size(); i++)
    {
        area = area + someVertices[im1].x * someVertices[i].y - someVertices[i].x * someVertices[im1].y;
        im1 = i;
    }
    area = 0.5 * area;

    return area;
}

double triangle_area(double xa, double ya, double xb, double yb, double xc, double yc)
{
    return 0.5 * ((xb - xa) * (yc - ya) - (xc - xa) * (yb - ya));
}

bool in_cone(int im1, int ip1, const std::vector<sf::Vector2f>& someVertices, int prev_node[], int next_node[])
{
    int i;
    int im2;
    double t1;
    double t2;
    double t3;
    double t4;
    double t5;
    bool value;

    im2 = prev_node[im1];
    i = next_node[im1];

    t1 = triangle_area(someVertices[im1].x, someVertices[im1].y, someVertices[i].x, someVertices[i].y, someVertices[im2].x, someVertices[im2].y);

    if (0.0 <= t1)
    {
        t2 = triangle_area(someVertices[im1].x, someVertices[im1].y, someVertices[ip1].x, someVertices[ip1].y, someVertices[im2].x, someVertices[im2].y);
        t3 = triangle_area(someVertices[ip1].x, someVertices[ip1].y, someVertices[im1].x, someVertices[im1].y, someVertices[i].x, someVertices[i].y);
        value = ((0.0 < t2) && (0.0 < t3));
    }
    else
    {
        t4 = triangle_area(someVertices[im1].x, someVertices[im1].y, someVertices[ip1].x, someVertices[ip1].y, someVertices[i].x, someVertices[i].y);
        t5 = triangle_area(someVertices[ip1].x, someVertices[ip1].y, someVertices[im1].x, someVertices[im1].y, someVertices[im2].x, someVertices[im2].y);
        value = !((0.0 <= t4) && (0.0 <= t5));
    }
    return value;
}

bool collinear(double xa, double ya, double xb, double yb, double xc, double yc)
{
    double area;
    const double r8_eps = 2.220446049250313E-016;
    double side_ab_sq;
    double side_bc_sq;
    double side_ca_sq;
    double side_max_sq;
    bool value;

    area = triangle_area(xa, ya, xb, yb, xc, yc);

    side_ab_sq = pow(xa - xb, 2) + pow(ya - yb, 2);
    side_bc_sq = pow(xb - xc, 2) + pow(yb - yc, 2);
    side_ca_sq = pow(xc - xa, 2) + pow(yc - ya, 2);

    side_max_sq = std::max(side_ab_sq, std::max(side_bc_sq, side_ca_sq));

    if (side_max_sq <= r8_eps)
    {
        value = true;
    }
    else if (2.0 * fabs(area) <= r8_eps * side_max_sq)
    {
        value = true;
    }
    else
    {
        value = false;
    }

    return value;
}


bool l4_xor(bool l1, bool l2)
{
    bool value;
    bool value1;
    bool value2;

    value1 = (l1 && (!l2));
    value2 = ((!l1) && l2);

    value = (value1 || value2);

    return value;
}

bool intersect_prop(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd)
{
    double t1;
    double t2;
    double t3;
    double t4;
    bool value;
    bool value1;
    bool value2;
    bool value3;
    bool value4;

    if (collinear(xa, ya, xb, yb, xc, yc))
    {
        value = false;
    }
    else if (collinear(xa, ya, xb, yb, xd, yd))
    {
        value = false;
    }
    else if (collinear(xc, yc, xd, yd, xa, ya))
    {
        value = false;
    }
    else if (collinear(xc, yc, xd, yd, xb, yb))
    {
        value = false;
    }
    else
    {
        t1 = triangle_area(xa, ya, xb, yb, xc, yc);
        t2 = triangle_area(xa, ya, xb, yb, xd, yd);
        t3 = triangle_area(xc, yc, xd, yd, xa, ya);
        t4 = triangle_area(xc, yc, xd, yd, xb, yb);

        value1 = (0.0 < t1);
        value2 = (0.0 < t2);
        value3 = (0.0 < t3);
        value4 = (0.0 < t4);

        value = (l4_xor(value1, value2)) && (l4_xor(value3, value4));
    }
    return value;
}

bool between(double xa, double ya, double xb, double yb, double xc, double yc)
{
    bool value;
    double xmax;
    double xmin;
    double ymax;
    double ymin;

    if (!collinear(xa, ya, xb, yb, xc, yc))
    {
        value = false;
    }
    else if (fabs(ya - yb) < fabs(xa - xb))
    {
        xmax = std::max(xa, xb);
        xmin = std::min(xa, xb);
        value = (xmin <= xc && xc <= xmax);
    }
    else
    {
        ymax = std::max(ya, yb);
        ymin = std::min(ya, yb);
        value = (ymin <= yc && yc <= ymax);
    }

    return value;
}

bool intersect(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd)
{
    bool value;

    if (intersect_prop(xa, ya, xb, yb, xc, yc, xd, yd))
    {
        value = true;
    }
    else if (between(xa, ya, xb, yb, xc, yc))
    {
        value = true;
    }
    else if (between(xa, ya, xb, yb, xd, yd))
    {
        value = true;
    }
    else if (between(xc, yc, xd, yd, xa, ya))
    {
        value = true;
    }
    else if (between(xc, yc, xd, yd, xb, yb))
    {
        value = true;
    }
    else
    {
        value = false;
    }
    return value;
}

bool diagonalie(int im1, int ip1, const std::vector<sf::Vector2f>& someVertices, int next_node[])
{
    int first;
    int j;
    int jp1;
    bool value;
    bool value2;

    first = im1;
    j = first;
    jp1 = next_node[first];

    value = true;
    //
    //  For each edge VERTEX(J):VERTEX(JP1) of the polygon:
    //
    while (1)
    {
        //
        //  Skip any edge that includes vertex IM1 or IP1.
        //
        if (j == im1 || j == ip1 || jp1 == im1 || jp1 == ip1)
        {
        }
        else
        {
            value2 = intersect(someVertices[im1].x, someVertices[im1].y, someVertices[ip1].x, someVertices[ip1].y, 
                someVertices[j].x, someVertices[j].y, someVertices[jp1].x, someVertices[jp1].y);

            if (value2)
            {
                value = false;
                break;
            }
        }
        j = jp1;
        jp1 = next_node[j];

        if (j == first)
        {
            break;
        }
    }

    return value;
}

bool diagonal(int im1, int ip1, const std::vector<sf::Vector2f>& someVertices, int prev_node[], int next_node[])
{
    bool value;
    bool value1;
    bool value2;
    bool value3;

    value1 = in_cone(im1, ip1, someVertices, prev_node, next_node);
    value2 = in_cone(ip1, im1, someVertices, prev_node, next_node);
    value3 = diagonalie(im1, ip1, someVertices, next_node);

    value = (value1 && value2 && value3);

    return value;
}

void Scene::AddGround(const std::vector<sf::Vector2f>& someVertices)
{
    std::vector<sf::Vector2f> tempVertices = someVertices;
    tempVertices.push_back(sf::Vector2f(tempVertices.back().x, 1000));
    tempVertices.push_back(sf::Vector2f(tempVertices.front().x, 1000));
    double angle;
    const double angle_tol = 5.7E-05;
    double area;
    bool* ear;
    int i;
    int i0;
    int i1;
    int i2;
    int i3;
    int i4;
    int* next_node;
    int node;
    int node1;
    int node2;
    int node3;
    int node_m1;
    int* prev_node;
    int triangle_num;
    int* triangles;
    //
    //  We must have at least 3 vertices.
    //
    if (tempVertices.size() < 3)
    {
        return;
    }
    //
    //  Consecutive vertices cannot be equal.
    //
    node_m1 = tempVertices.size() - 1;
    for (node = 0; node < tempVertices.size(); node++)
    {
        if (tempVertices[node_m1].x == tempVertices[node].x && tempVertices[node_m1].y == tempVertices[node].y)
        {
            return;
        }
        node_m1 = node;
    }
    //
    //  No node can be the vertex of an angle less than 1 degree 
    //  in absolute value.
    //
    node1 = tempVertices.size() - 1;

    for (node2 = 0; node2 < tempVertices.size(); node2++)
    {
        node3 = ((node2 + 1) % tempVertices.size());

        angle = angle_degree(
            tempVertices[node1].x, tempVertices[node1].y,
            tempVertices[node2].x, tempVertices[node2].y,
            tempVertices[node3].x, tempVertices[node3].y);

        if (fabs(angle) <= angle_tol)
        {
            return;
        }
        node1 = node2;
    }
    //
    //  Area must be positive.
    //
    area = polygon_area(tempVertices);

    if (area <= 0.0)
    {
        return;
    }

    triangles = new int[3 * (tempVertices.size() - 2)];
    //
    //  PREV_NODE and NEXT_NODE point to the previous and next nodes.
    //
    prev_node = new int[tempVertices.size()];
    next_node = new int[tempVertices.size()];

    i = 0;
    prev_node[i] = tempVertices.size() - 1;
    next_node[i] = i + 1;

    for (i = 1; i < tempVertices.size() - 1; i++)
    {
        prev_node[i] = i - 1;
        next_node[i] = i + 1;
    }

    i = tempVertices.size() - 1;
    prev_node[i] = i - 1;
    next_node[i] = 0;
    //
    //  EAR indicates whether the node and its immediate neighbors form an ear
    //  that can be sliced off immediately.
    //
    ear = new bool[tempVertices.size()];
    for (i = 0; i < tempVertices.size(); i++)
    {
        ear[i] = diagonal(prev_node[i], next_node[i], tempVertices, prev_node, next_node);
    }

    triangle_num = 0;

    i2 = 0;

    while (triangle_num < tempVertices.size() - 3)
    {
        //
        //  If I2 is an ear, gather information necessary to carry out
        //  the slicing operation and subsequent "healing".
        //
        if (ear[i2])
        {
            i3 = next_node[i2];
            i4 = next_node[i3];
            i1 = prev_node[i2];
            i0 = prev_node[i1];
            //
            //  Make vertex I2 disappear.
            //
            next_node[i1] = i3;
            prev_node[i3] = i1;
            //
            //  Update the earity of I1 and I3, because I2 disappeared.
            //
            ear[i1] = diagonal(i0, i3, tempVertices, prev_node, next_node);
            ear[i3] = diagonal(i1, i4, tempVertices, prev_node, next_node);
            //
            //  Add the diagonal [I3, I1, I2] to the list.
            //
            triangles[0 + triangle_num * 3] = i3;
            triangles[1 + triangle_num * 3] = i1;
            triangles[2 + triangle_num * 3] = i2;
            triangle_num = triangle_num + 1;
        }
        //
        //  Try the next vertex.
        //
        i2 = next_node[i2];
    }
    //
    //  The last triangle is formed from the three remaining vertices.
    //
    i3 = next_node[i2];
    i1 = prev_node[i2];

    triangles[0 + triangle_num * 3] = i3;
    triangles[1 + triangle_num * 3] = i1;
    triangles[2 + triangle_num * 3] = i2;
    triangle_num = triangle_num + 1;
    //
    //  Free memory.
    //
    delete[] ear;
    delete[] next_node;
    delete[] prev_node;

	for (int i = 0; i < triangle_num * 3; i += 3)
	{
        std::cout << triangles[i] << std::endl;
		b2Vec2* tempTriangleVertices = new b2Vec2[3]; 
        myGroundVerts.push_back(std::vector<sf::Vector2f>());
        for (int j = 0; j < 3; j++) 
        {
            myGroundVerts.back().push_back(tempVertices[triangles[i + j]]);
            tempTriangleVertices[j] = b2Vec2(tempVertices[triangles[i + j]].x, tempVertices[triangles[i + j]].y);
        }
		b2PolygonShape tempShape;
		tempShape.Set(tempTriangleVertices, 3);
		AddPolygon(tempShape, 0);
	}
}




