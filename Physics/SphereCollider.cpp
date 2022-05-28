#include "SphereCollider.h"
#include <iostream>

void SphereCollider::Draw()
{
	glPushMatrix();
	glColor3f(1.f, 0.f, 1.0f); 
	glTranslatef(position.x, position.y, position.z);
	glutWireSphere(radius, 10, 10);
	glPopMatrix();

}
/*
id list
1 = Sphere
2 = AABB
3 = Plane
*/

bool SphereCollider::CollideCheck(Collider* collider2, CollisionData& collisionInfo)  
{
	if (collider2->id == 1) // collider 2 is sphere
	{
		if (glm::distance(position, collider2->position) <= (GetRadius() + collider2->GetRadius()))
		{
			// collision = true
			std::cout << "Colliding " << std::endl;

			collisionInfo.penetrationDepth = abs(GetRadius() + collider2->GetRadius()) - glm::distance(position, collider2->position);
			collisionInfo.collisionNormal = glm::normalize(position - collider2->position);
			collisionInfo.collisionPoint = collisionInfo.collisionNormal * radius;

			return true;
		}
	}
	else if (collider2->id == 2)
	{
		// Sphere - AABB collision

		glm::vec3 minA, maxA, collisionPoint;
		// AABB min and max
		minA = collider2->position - glm::vec3(collider2->GetRadius(), collider2->GetRadius(), collider2->GetRadius());
		maxA = collider2->position + glm::vec3(collider2->GetRadius(), collider2->GetRadius(), collider2->GetRadius());

		collisionPoint = position;

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
		if (glm::distance(collisionPoint, position) <= radius)
		{
			std::cout << "Colliding AABB - Sphere" << std::endl;

			collisionInfo.penetrationDepth = abs(GetRadius() + collider2->GetRadius()) - glm::distance(position, collider2->position);
			collisionInfo.collisionNormal = glm::normalize(collider2->position - position);
			collisionInfo.collisionPoint = collisionPoint;
			return true;
		}


		return false;

	}
	else if (collider2->id == 3) // Plane
	{

		return collider2->CollideCheck(this, collisionInfo);
		/*glm::vec3 posToPos = collider2->position - position;

		float distance = glm::dot(posToPos, planeNormal);

		glm::vec3 closestPoint = collider2->position - planeNormal * distance;

		if (glm::distance(closestPoint, collider2->position) - collider2->GetRadius() <= collider2->GetRadius())
		{
			collisionInfo.penetrationDepth = abs(glm::distance(closestPoint, collider2->position) - collider2->GetRadius());
			collisionInfo.collisionNormal = glm::normalize(closestPoint - collider2->position);
			collisionInfo.collisionPoint = closestPoint;

			return true;
		}
		return false;*/
	}


}


float SphereCollider::DotProduct(glm::vec3 a, glm::vec3 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * a.z);

}

glm::vec3 SphereCollider::CrossProduct(glm::vec3 a, glm::vec3 b)
{
	glm::vec3 result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;

	return result;
}

float SphereCollider::GetRadius()
{
	return radius;
}



