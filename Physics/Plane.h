#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "GameObject.h"
#include "PlaneCollider.h"

class Plane : public GameObject
{
public :
	void Draw();  // set it as pure virtual - can't instantiate, all children must heve thier own definition
	void Update(float deltaTime);

	glm::vec3 GetPosition();
	float GetRadius();

	Plane(glm::vec3 _position, glm::vec3 _direction) : GameObject(0, _position)
	{
		colliderPtr = new PlaneCollider(glm::vec3(particlePtr->position), _direction);

	}


};

