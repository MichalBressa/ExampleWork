#include "Plane.h"

void Plane::Draw()
{
	glPushMatrix();
	glTranslatef(colliderPtr->position.x , colliderPtr->position.y , colliderPtr->position.z);
	glColor3f(0.0, 1.0, 0.5);
	glutSolidCube(.1f);
	glPopMatrix();


}

void Plane::Update(float deltaTime)
{
}

glm::vec3 Plane::GetPosition()
{
	return glm::vec3();
}

float Plane::GetRadius()
{
	return 0.0f;
}
