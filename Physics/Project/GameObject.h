#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <map>
#include "Particle.h"
#include "Collider.h"
class GameObject
{

	public:
		GameObject();
		GameObject(glm::vec3);
		GameObject(float, glm::vec3);
		virtual ~GameObject();


		virtual void Draw() = 0;  // set it as pure virtual - can't instantiate, all children must heve thier own definition
		virtual void Update(float deltaTime);

		virtual glm::vec3 GetPosition();
		virtual float GetRadius();


		//maps for key input
		static std::map<char, bool> keys;
		static std::map<int, bool> specialKeys;
	
		//glm::vec3 pos;
		Collider* colliderPtr;
		Particle* particlePtr;
	

};

