#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>

#include "Collider.h"


class AABB : public Collider
{
public:
	 bool CollideCheck(Collider* collider2, CollisionData& collisionInfo);
	 void Draw();
	 void SetPosition(glm::vec3 newPos);
	 float GetRadius();
	 //Collider(glm::vec3 _position, int _id);
	 AABB(glm::vec3 _position, glm::vec3 size) :Collider(_position, 2) 
	 {
		 height = size.y;
		 width = size.x;
		 length = size.z;
	 }

	 float height, width, length;
};

