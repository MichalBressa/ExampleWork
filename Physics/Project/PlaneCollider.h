#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include "Collider.h"

class PlaneCollider : public Collider
{
//http://gamedeveloperjourney.blogspot.com/2009/04/point-plane-collision-detection.html

public:
	PlaneCollider(glm::vec3 _position, glm::vec3 _direction) : Collider(_position, 3) 
	{
		planeDirection = _direction;
	}

	 bool CollideCheck(Collider* collider2, CollisionData& collisionInfo);
	 void Draw();
	 float GetRadius();
	 void SetPosition(glm::vec3 newPos);


private:
	glm::vec3 planeDirection;
};

