#include "Cube.h"

Cube::Cube(glm::vec3 position): GameObject(position)
{
	colliderPtr = new AABB(glm::vec3(particlePtr->position.x, particlePtr->position.y, particlePtr->position.z), glm::vec3(1,1,1));
	pos = position;
}

Cube::~Cube()
{
}

void Cube::Draw()
{

	glPushMatrix();
	glTranslatef(particlePtr->position.x, particlePtr->position.y, particlePtr->position.z);
	glColor3f(0.0, 1.0, 0.5);
	glutSolidCube(1.0f);
	glPopMatrix();

}

void Cube::Update(float deltaTime)
{

	particlePtr->ResetForces();
	//particlePtr->AddForce(glm::vec3(0.0f, -1.0f, 0.0f) * particlePtr->GetMass()); // gravity

	particlePtr->Update(deltaTime);
	colliderPtr->SetPosition(particlePtr->position);
}