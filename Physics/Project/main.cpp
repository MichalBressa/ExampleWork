#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "GameEngine.h"
#include "GameObject.h"
#include "Collider.h"

#include <iostream>
#pragma comment(lib, "glew32.lib") 



//Create some objects
GameObject* cube = new Cube(glm::vec3(-1.5, 0, 0));
GameObject* cube2 = new Cube(glm::vec3(3, 3, 1));

GameObject* sphere1 = new Sphere(glm::vec3(-3, 0, 0), 0.5f);

GameObject* player1 = new Player(1.f, glm::vec3(3, 0, 0)); // controllable sphere 

GameObject* cubeplayer = new cubePlayer(1.f, glm::vec3(3, 0, 0)); // controllable cube

GameObject* rotating = new RotatingSquare(1.f, 1.f, glm::vec3(0, 0, 0)); // square that can be moved and rotated

SphereCollider* collider1 = new SphereCollider(glm::vec3(2, 0, 0),1.f);

GameObject* plane = new Plane(glm::vec3(0, -2, 0), glm::vec3(0, 1, 0));

//Create an instance of the game engine
GameEngine engine;





// Main routine.
int main(int argc, char** argv)
{
	//Initialize the engine
		engine.InitEngine(argc, argv, "GameEngine Window", 600, 600);

	//Add the objects to the engine
		engine.AddGameObject(cube);
		//engine.AddGameObject(cube2);
		//engine.AddGameObject(rotating);
		//engine.AddGameObject(plane);
		//engine.AddGameObject(sphere1);
		//engine.AddGameObject(cubeplayer);
		engine.AddGameObject(player1); // sphere player

	//causes the game loop to occur with functions like Drawing, Updating etc
		engine.StartEngine();

	return 0;
}
