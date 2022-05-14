#include "Sphere.h"

Sphere::Sphere(glm::vec3 position, float _radius):GameObject(position)
{
	pos = position;
	radius = _radius;

	colliderPtr = new SphereCollider(glm::vec3(particlePtr->position.x, particlePtr->position.y, particlePtr->position.z), radius);

}

Sphere::~Sphere()
{
}

void Sphere::Update(float deltaTime)
{
	particlePtr->ResetForces();
	//particlePtr->AddForce(glm::vec3(0.0f, -1.0f, 0.0f) * particlePtr->GetMass()); // gravity

	particlePtr->Update(deltaTime);
	colliderPtr->SetPosition(particlePtr->position);
}

void Sphere::Draw()
{

	glPushMatrix();
	glTranslatef(particlePtr->position.x, particlePtr->position.y, particlePtr->position.z);
	glColor3f(0.0, 1.0, 0.0);
	glutSolidSphere(radius, 15, 15);
	glPopMatrix();

	colliderPtr->Draw();

	/*
	glColor3f(1.f, 1.f, 1.f);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0); //0, 0, 0 is used here as I assume you have a glTranslatef line above, so 0, 0, 0 puts us at the center of the object now
	glVertex3f(pos.x, pos.y, pos.z);
	glEnd();
*/
	//sphereColliderPtr->Draw(glm::vec3(pos.x, pos.y, pos.z), radius);
}

