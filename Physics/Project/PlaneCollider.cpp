#include "PlaneCollider.h"
#include <iostream>

bool PlaneCollider::CollideCheck(Collider* collider2, CollisionData& collisionInfo)
{
	float distance;

	if (collider2->id == 1) // collider 2 is sphere
	{
		glm::vec3 posToPos = collider2->position - position;
		
		distance = glm::dot(posToPos, planeDirection);

		glm::vec3 closestPoint = collider2->position - planeDirection * distance;

		if (glm::distance(closestPoint, collider2->position)  <= collider2->GetRadius()) 
		{
			collisionInfo.penetrationDepth = abs (glm::distance(closestPoint, collider2->position) - collider2->GetRadius());
			//collisionInfo.collisionNormal = glm::normalize(collider2->position - closestPoint); //planeDirection;
			// need velocity as collision normal -> but its not in the collider
			collisionInfo.collisionPoint = closestPoint;
			std::cout << "Colliding with sphere" << std::endl;
			return true;
		}
		return false;
		
	}
	else if (collider2->id == 2)	// AABB
	{
		// get closest point
		glm::vec3 posToPos = collider2->position - position;

		distance = glm::dot(posToPos, planeDirection);

		glm::vec3 closestPoint = collider2->position - planeDirection * distance;

		glm::vec3 minA, maxA, collisionPoint;
		minA = collider2->position - glm::vec3(collider2->GetRadius(), collider2->GetRadius(), collider2->GetRadius());
		maxA = collider2->position + glm::vec3(collider2->GetRadius(), collider2->GetRadius(), collider2->GetRadius());

		// clamp values -> determin where is plane compared to AABB and get collision point
		// X axis
		if (closestPoint.x < minA.x)
		{
			collisionPoint.x = minA.x;
		}
		if (closestPoint.x > maxA.x)
		{
			collisionPoint.x = maxA.x;
		}
		// Y axis
		if (closestPoint.y < minA.y)
		{
			collisionPoint.y = minA.y;
		}
		if (closestPoint.y > maxA.y)
		{
			collisionPoint.y = maxA.y;
		}
		// Z axis
		if (closestPoint.z < minA.z)
		{
			collisionPoint.z = minA.z;
		}
		if (closestPoint.z > maxA.z)
		{
			collisionPoint.z = maxA.z;
		}

		if (glm::distance(collisionPoint, closestPoint) <= 0) 
		{
			collisionInfo.penetrationDepth = abs(glm::distance(closestPoint, collider2->position) - collider2->GetRadius());
			collisionInfo.collisionNormal = planeDirection;
			collisionInfo.collisionPoint = closestPoint;
			std::cout << "Colliding with AABB" << std::endl;

			return true;
		}

		// not working 
		// alternatively can treat it as the sphere

		// https://gdbooks.gitbooks.io/3dcollisions/content/Chapter2/static_aabb_plane.html might be useful
	}

	return false;
}

void PlaneCollider::Draw()
{

}

float PlaneCollider::GetRadius()
{
	return 0.0f;
}

void PlaneCollider::SetPosition(glm::vec3 newPos)
{
	position = newPos;

}
