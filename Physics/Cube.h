#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "GameObject.h"
#include "AABB.h"
class Cube : public GameObject
{

public:
	Cube(glm::vec3 position);
	~Cube();

	glm::vec3 GetPosition()
	{
		return glm::vec3(pos.x, pos.y, pos.z);
	}
	void Draw();
	void Update(float deltaTime);
private:
	glm::vec3 pos;




};

