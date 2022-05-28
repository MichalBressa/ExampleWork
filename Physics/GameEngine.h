#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include "GameObject.h"

#include "Player.h"
#include "RigidBody2D.h"
#include "Particle.h"
#include "RotatingSquare.h"
#include "Sphere.h"
#include "Cube.h"
#include "SphereCollider.h"
#include "cubePlayer.h"
#include "Plane.h"


class GameEngine
{
private:
	    static std::vector<GameObject*> objects;	//	A way to storeand access created objects in the game world.
		static int oldTimeSinceStart;	//	To work out deltaTime in between updates.
		static int newTimeSinceStart;	//	To work out deltaTime in between updates.

		static void UpdateGame();	//	Update the objectsand work out deltaTime between frames.
		static void DrawGame();	//	The function to draw all objects to the screen.
		static void CleanupEngine();	//	Delete the objects afterwards.
		static void ResizeWindow(int w, int h);	//	The function to alter the window contents if the screen changes shape.
		
		
public:
	void InitEngine(int argc, char** argv, const char* windowTitle, int width, int height); 	//The function to set up / initialize Opengl and GLUT and the function to get things ready(but not run).
		void AddGameObject(GameObject*);	 //	A way to add objects to the game world.
		void StartEngine(); 	//	Start the game world.
		GameEngine();
		~GameEngine();
		static std::vector<CollisionData> collisionDataVec;

};