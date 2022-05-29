#include "Player.h"


void Player::Draw()
{
	glPushMatrix();
	glColor3f(1, 1.f, 1);
	glTranslatef( particlePtr->position.x, particlePtr->position.y, particlePtr->position.z);
	glutSolidSphere(radius, 10, 10);
	glPopMatrix();

	
	colliderPtr->Draw();
	//sphereColliderPtr->Draw(glm::vec3(particlePtr->position.x, particlePtr->position.y, particlePtr->position.z), 0.5f);


	glColor3f(1.f, 1.f, 1.f);
	glm::vec3 vel = particlePtr->GetVelocity();
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0); //0, 0, 0 is used here as I assume you have a glTranslatef line above, so 0, 0, 0 puts us at the center of the object now
	glVertex3f(vel.x, vel.y, vel.z);
	glEnd();
}



void Player::Update(float deltaTime) 
{
	particlePtr->ResetForces();

	if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		particlePtr->AddForce(glm::vec3(0.f, 1.5f, 0.f));
	if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		particlePtr->AddForce(glm::vec3(0.f, -1.5f, 0.f));
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		particlePtr->AddForce(glm::vec3(1.5f, 0.f, 0.f));
	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		particlePtr->AddForce(glm::vec3(-1.5f, 0.f, 0.f));

	particlePtr->Update(deltaTime);

	colliderPtr->SetPosition(particlePtr->position); // so that collider follows player obj

}

glm::vec3 Player::GetPosition()
{
	return glm::vec3(particlePtr->position.x, particlePtr->position.y, particlePtr->position.z);
}

float Player::GetRadius()
{
	return radius;
}

Player::~Player()
{
}
