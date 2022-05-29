#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include "Collider.h"

class SphereCollider : public Collider
{

private:
	float radius;
public:
	void Draw();
	bool CollideCheck(Collider* collider2, CollisionData& collisionInfo);
	SphereCollider(glm::vec3 _pos, float _radius) :Collider(_pos, 1) 
	{
		radius = _radius;
	};

	// made for fun
	float DotProduct(glm::vec3 x, glm::vec3 y);
	glm::vec3 CrossProduct(glm::vec3 x, glm::vec3 y);

	float GetRadius();




};

