#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "GameObject.h"
#include "SphereCollider.h"
class Sphere : public GameObject
{
public:
	Sphere(glm::vec3 position, float _radius);
	~Sphere();


	void Update(float deltaTime);
	void Draw();
	glm::vec3 GetPosition()
	{
		return glm::vec3(pos.x, pos.y, pos.z);
	}

	float GetRadius() 
	{
		return radius;
	}

private:
	glm::vec3 pos;
	float radius;





};

