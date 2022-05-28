#include "Particle.h"
//#include <iostream>

void Particle::Update(float deltaTime)
{
	if (mass != 0) // plane will have mass = 0 -> block movement
	{
		acceleration = forceOnObj / mass;
		position = position + (velocity * deltaTime);
		velocity = velocity + (acceleration * deltaTime);

		velocity *= pow(0.8f, deltaTime);
	}
	
	//--------------------------------
	// change to Runge-Kutta method? ¦¦
	//--------------------------------

	//std::cout << "Acceleration: " << glm::to_string(acceleration) << std::endl;
}


Particle::Particle(float _mass, glm::vec3 _pos) 
{
	mass = _mass;
	position = _pos;

	acceleration = glm::vec3(0, 0, 0);
	velocity = glm::vec3(0, 0, 0);
	forceOnObj = glm::vec3(0, 0, 0);
}

Particle::~Particle()
{
}

void Particle::AddForce(glm::vec3 force) 
{
	forceOnObj += force;
}


void Particle::ResetForces()
{
	forceOnObj = glm::vec3(0, 0, 0);
}

float Particle::GetMass()
{
	return Particle::mass;
}

glm::vec3 Particle::GetVelocity()
{
	return velocity;
}

void Particle::SetVelocity(glm::vec3 _velocity)
{
	velocity = _velocity;
}
