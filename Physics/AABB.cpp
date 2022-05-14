#include "AABB.h"
#include <iostream>

bool AABB::CollideCheck(Collider* collider2, CollisionData& collisionInfo)
{
	if (collider2->id == 1) // collider 2 is sphere
		// so AABB and Sphere
	{
		
		glm::vec3 minA, maxA, collisionPoint;
		// AABB min and max
		minA = position - glm::vec3((width / 2), (height / 2), (length / 2));
		maxA = position + glm::vec3(width / 2, height / 2, (length / 2));

		// Sphere
		collisionPoint = collider2->position;

		// clamp values -> determin where is sphere compared to AABB and get collision point
		// X axis
		if (collisionPoint.x < minA.x) 
		{
			collisionPoint.x = minA.x;
		}
		if (collisionPoint.x > maxA.x) 
		{
			collisionPoint.x = maxA.x;
		}
		// Y axis
		if (collisionPoint.y < minA.y)
		{
			collisionPoint.y = minA.y;
		}
		if (collisionPoint.y > maxA.y)
		{
			collisionPoint.y = maxA.y;
		}
		// Z axis
		if (collisionPoint.z < minA.z)
		{
			collisionPoint.z = minA.z;
		}
		if (collisionPoint.z > maxA.z)
		{
			collisionPoint.z = maxA.z;
		}

		// actual check for collision
		if (glm::distance(collisionPoint, collider2->position) <= collider2->GetRadius()) 
		{
			std::cout << "Colliding AABB - Sphere" << std::endl;

			collisionInfo.penetrationDepth = (GetRadius() + collider2->GetRadius()) - glm::distance(position, collider2->position);
			collisionInfo.collisionNormal = glm::normalize(position - collider2->position);
			collisionInfo.collisionPoint = collisionPoint;
			return true;
		}


		return false;
	}
	else if (collider2->id == 2)
	{
		// minA and maxA are of 1st object
		// B stuff is of 2nd one
		glm::vec3 minA, minB, maxA, maxB;
		minA = position - glm::vec3((width / 2), (height / 2), (length / 2));
		maxA = position + glm::vec3(width / 2,  height / 2, (length / 2));

		minB = collider2->position - glm::vec3(collider2->GetRadius(), collider2->GetRadius(), collider2->GetRadius());
		maxB = collider2->position + glm::vec3(collider2->GetRadius(), collider2->GetRadius(), collider2->GetRadius());

		// should include z axis? add width/2 lenght/2 and height/2 


		//glm::dot(maxA, glm::vec3(0,1,0))
		if ((glm::dot(maxA, glm::vec3(1,0,0)) > glm::dot(minB, glm::vec3(1,0,0))) && (glm::dot(maxB, glm::vec3(1,0,0)) > glm::dot(minA, glm::vec3(1,0,0))) )
		{
			//std::cout << "x axis collide" << std::endl;
			if (glm::dot(maxA, glm::vec3(0, 1, 0)) > glm::dot(minB, glm::vec3(0, 1, 0)) && glm::dot(maxB, glm::vec3(0, 1, 0)) > glm::dot(minA, glm::vec3(0, 1, 0)))
			{
				//std::cout << "y axis collide" << std::endl;
				if (glm::dot(maxA, glm::vec3(0, 0, 1)) > glm::dot(minB, glm::vec3(0, 0, 1)) && glm::dot(maxB, glm::vec3(0, 0, 1)) > glm::dot(minA, glm::vec3(0, 0, 1)))
				{
					collisionInfo.penetrationDepth = (GetRadius() + collider2->GetRadius()) - glm::distance(position, collider2->position);
					collisionInfo.collisionNormal = glm::normalize(position - collider2->position);
					collisionInfo.collisionPoint = glm::vec3((position.x - collider2->position.x)/2, (position.y - collider2->position.y) / 2, (position.y - collider2->position.y) / 2);

					//std::cout << "z axis collide" << std::endl;
					std::cout << "Colliding AABB" << std::endl;

					return true;
				}
			
			}
		}
		//maxA > minB&& maxB > minA



	}
	else if (collider2->id == 3)
	{
		return collider2->CollideCheck(this, collisionInfo);
	}

	return false;

}

void AABB::Draw()
{
	glPushMatrix();
	glColor3f(1.f, 0.f, 1.0f);
	glTranslatef(position.x, position.y, position.z);
	glutWireCube(width+0.01f);
	glPopMatrix();
}

void AABB::SetPosition(glm::vec3 newPos)
{
	position = newPos;

}

float AABB::GetRadius()
{
	return height / 2;
	// could retu rn dimentions as vec3 (like in constructor) but i'm going to use cubes only to make it testing easier
}
