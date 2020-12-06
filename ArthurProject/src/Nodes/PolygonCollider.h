#pragma once
#include "Node.h"
#include "core/Body.h"
#include "core/Shape.h"
#include "core/Collision.h"
#include "core/Manifold.h"

struct ColliderMaterial
{
	float Density = 0.3f;
	float Bouncyness = 0.2f;
	float DynamicFriction = 0.2f;
	float StaticFriction = 0.2f;

	ColliderMaterial()
	{

	}

	ColliderMaterial(float aDensity, float aBouncyness, float aDynamicFriction, float aStaticFriction)
		: Density(aDensity), Bouncyness(aBouncyness), DynamicFriction(aDynamicFriction), StaticFriction(aStaticFriction)
	{

	}

	static ColliderMaterial Rock()
	{
		return ColliderMaterial(0.6f, 0.1f, 0.4f, 0.6f);
	}

	static ColliderMaterial Wood()
	{
		return ColliderMaterial(0.3f, 0.2f, 0.2f, 0.4f);
	}
	static ColliderMaterial Metal()
	{
		return ColliderMaterial(1.2f, 0.05f, 0.1f, 0.3f);
	}
	static ColliderMaterial BouncyBall()
	{
		return ColliderMaterial(0.3f, 0.8f, 0.1f, 0.15f);
	}
	static ColliderMaterial SuperBall()
	{
		return ColliderMaterial(0.3f, 0.95f, 0.1f, 0.15f);
	}
	static ColliderMaterial Pillow()
	{
		return ColliderMaterial(0.1f, 0.2f, 0.8f, 1.f);
	}
	static ColliderMaterial Static()
	{
		return ColliderMaterial(0.f, 0.4f, 0.2f, 0.4f);
	}
};

class PolygonCollider :
	public Node
{
public:
	PolygonCollider(const sf::Vector2f& aPosition, const std::string& aName, int aVertexCount, sf::Vector2f* someVertices, const ColliderMaterial& aColMat = ColliderMaterial::Wood());
	PolygonCollider(const sf::Vector2f& aPosition, const std::string& aName, int aVertexCount, float aRadius, const ColliderMaterial& aColMat = ColliderMaterial::Wood());
	void OnStart() override;
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
	void SetPosition(const sf::Vector2f& aPos) override;
	void SetStatic(bool aFlag);
	void SetColMat(ColliderMaterial aColMat);
	void FreezeRotation(bool aFlag);
	void SetRotation(float aValue);
	float GetRotation();
	void AddVelocity(const sf::Vector2f& aVal);
	sf::Vector2f GetVelocity();
	void SetVelocity(const sf::Vector2f& aVal);
	Body* GetBody();


private:
	int myVertexCount;
	bool myRotationFrozenFlag;
protected:
	ColliderMaterial myColMat;
	Body* myBody;


};

