#include "Collider.h"
#include <iostream>


Collider::Collider(glm::vec3 _position, int _id)
{
	id = _id;
	position = _position;
}

void Collider::Draw()
{
}

float Collider::GetRadius()
{
	return 0.0f;
}

void Collider::SetPosition(glm::vec3 newPos)
{
	position = newPos;
}


/*

AABB
boxA.min > boxB.max

if (boxA.max >= boxB.min && boxB.max >= boxA.min on dimention 1)
{
	if (boxA.max >= boxB.min && boxB.max >= boxA.min on dimention 2)
	{
		if (boxA.max >= boxB.min && boxB.max >= boxA.min on dimention 3)
		{
			// all true -> collision
			if any is false than there is no collision
		}
	}
}












*/


