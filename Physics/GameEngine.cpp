#include "GameEngine.h"
#include <iostream>


std::vector<GameObject*> GameEngine::objects;
std::vector<CollisionData> GameEngine::collisionDataVec;
 
int GameEngine::oldTimeSinceStart = 0;
int GameEngine::newTimeSinceStart = 0;


 void GameEngine::UpdateGame()
{
	 oldTimeSinceStart = newTimeSinceStart;
	 newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);

	 CollisionData info;

	 float deltaTime = (newTimeSinceStart - oldTimeSinceStart);
	 deltaTime /= 1000.f;


	 /*
	 Broad Phase 
	  I probably not gonna have enough time to implement this but I think it's worth to leave my idea for it here
	  it is very simple broad phase as it divides area into only 4 sub-areas but with a few more if statments could be more complex


	  O      |		O
         1   |	2
	  O------A------O
	     3   |	4
	  O      |      O


	 get a vec3 point in the middle to separate area into 4 squares (lets can the point A, and O are the holes)
	 
	 need for vectors<> for objects, one for every sub-area
	 + function that will update where object belongs when it is moved

	 Logic is:
	 compare A.position to objects position. Only in 2D at the moment
	 (r = radius, or half of the sides lenght)

	 1. check if it is in the middle so belong to more than one zone

	 if (objPos.x + r >= A.x && objPos.x - r <= A.x){
		obj is in the middle
	 }

	 if (objPos.z + r >= A.z && objPos.z -r <= A.z)
	 {
		is in the middle-middle like A
	 }
	 else if (objPoz.z + r > A.z && objPos.z - r > A.z){
		add to zone 1 and 2
	 } else {
	 add to 3, 4
	 }


	 if (objPos.z + r >= A.z && Pos.Z -r <= A.z){
		if (objPos.x + r < A.x) -> add to 1, 3
		if (objPos.x - r < A.x) -> add to 2, 4
	 }

	 Cases then object belong to only one area
	 objPos.z - r > A.z && objPos.x + r < A.x  -> 1
	 objPos.z - r > A.z && objPos.x - r > A.x  -> 2
	 objPos.z + r < A.z && objPos.x + r < A.x  -> 3
	 objPos.z + r > A.z && objPos.x - r > A.x  -> 4
	 
	 
	 */



	 for (int i =0; i < objects.size()-1; i++) 
 	 {
		 for (int j = i; j < objects.size(); j++) 
		 {											  
			 if (objects[i]->colliderPtr != nullptr && objects[i] != objects[j])
			 {

				 if (objects[i]->colliderPtr->CollideCheck(objects[j]->colliderPtr, info)) 
				 {
					 info.obj1 = objects[i];
					 info.obj2 = objects[j];

					 collisionDataVec.push_back(info);
				 }
				 
			 }
		 }
	 }
	 float coEfficientOfRestitution = 0.8f;

	 // going through vector with collision pairs and applying impulse
	 if (collisionDataVec.size() > 0) 
	 {
		 for (int i = 0; i < collisionDataVec.size(); i++)
		 {
			 // resolve penetration here
			 if (collisionDataVec[i].penetrationDepth > 0) 
			 {
				 collisionDataVec[i].obj1->particlePtr->position = collisionDataVec[i].obj1->particlePtr->position + ((collisionDataVec[i].penetrationDepth / 2) * collisionDataVec[i].collisionNormal);
				 collisionDataVec[i].obj2->particlePtr->position = collisionDataVec[i].obj2->particlePtr->position + ((collisionDataVec[i].penetrationDepth / 2) * -collisionDataVec[i].collisionNormal);
			 }
			 
			
			 //std::cout << "Going through Vector" << std::endl;
			 glm::vec3 relativeVelocity = collisionDataVec[i].obj1->particlePtr->GetVelocity() - collisionDataVec[i].obj2->particlePtr->GetVelocity();

			 float impulse = (-1 * glm::dot(relativeVelocity, collisionDataVec[i].collisionNormal) * (1 + coEfficientOfRestitution))
				 / (glm::dot(collisionDataVec[i].collisionNormal, collisionDataVec[i].collisionNormal) * (1 / collisionDataVec[i].obj1->particlePtr->GetMass() + 1 / collisionDataVec[i].obj2->particlePtr->GetMass()));


			 glm::vec3 Va = collisionDataVec[i].obj1->particlePtr->GetVelocity() + (impulse / collisionDataVec[i].obj1->particlePtr->GetMass()) * collisionDataVec[i].collisionNormal;

			 glm::vec3 Vb = collisionDataVec[i].obj2->particlePtr->GetVelocity() - (impulse / collisionDataVec[i].obj2->particlePtr->GetMass()) * collisionDataVec[i].collisionNormal;

			 
			 if (collisionDataVec[i].obj1->particlePtr->GetMass() != 0) 
			 {
				collisionDataVec[i].obj1->particlePtr->SetVelocity(Va);
			 }
			 if (collisionDataVec[i].obj2->particlePtr->GetMass() != 0)
			 {
				 collisionDataVec[i].obj2->particlePtr->SetVelocity(Vb);
			 }


		 }
	 }
	 


	 for (int i = 0; i < objects.size(); ++i)
	 {
		 objects[i]->Update(deltaTime);
	 }

	 collisionDataVec.clear();

	 glutPostRedisplay();

}

 void GameEngine::DrawGame()
{

	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 glEnable(GL_DEPTH_TEST);
	 glLoadIdentity();

	 // Position the objects for viewing.
	 gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	 for (int i = 0; i < objects.size(); ++i)
	 {
		 objects[i]->Draw();
	 }

	 glutSwapBuffers();

}

 void GameEngine::CleanupEngine()
{
	 for (int i = 0; i < objects.size(); ++i)
	 {
		 delete objects[i];
	 }
}

void GameEngine::InitEngine(int argc, char** argv, const char* windowTitle, int width, int height)
{
    glutInit(&argc, argv); //this is why we need to use argcand argv

    glutInitContextVersion(2, 0);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height); //changed to include the parameters
    glutInitWindowPosition(100, 100);
    glutCreateWindow(windowTitle); //changed to include the parameters

    glewExperimental = GL_TRUE;
    glewInit();

    glutDisplayFunc(DrawGame); //changed to include the GameEngine function
    glutReshapeFunc(ResizeWindow); //changed to include the GameEngine function
    glutIdleFunc(UpdateGame); //changed to include the GameEngine function


    glutKeyboardFunc([](unsigned char key, int x, int y)
        {
            GameObject::keys[key] = true;
            std::cout << "Key pressed: " << key << " : " << GameObject::specialKeys[key] << std::endl;
            //If we press escape, quit
                if (key == 27)
                {
                    //changed to include the GameEngine function - this function will have to be static!
                    CleanupEngine();
                    exit(0);
                }
                

        }
    );
    glutKeyboardUpFunc([](unsigned char key, int x, int y)
        {
            GameObject::specialKeys[key] = false;
            std::cout << "Key pressed: " << key << " : " << GameObject::specialKeys[key] << std::endl;
        }
    );

    glutSpecialFunc([](int key, int x, int y)
		{
			GameObject::specialKeys[key] = true;
			std::cout << "Key pressed: " << key << " : " << GameObject::specialKeys[key] << std::endl;

			if (GameObject::specialKeys[GLUT_KEY_UP] == true)
			{
				// do stuff
			}

			if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
			{
				// do stuff
			}

			if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
			{
				// do stuff
			}

			if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
			{
				// do stuff
			}
		}
	);
    glutSpecialUpFunc([]( int key, int x, int y)
		{
			GameObject::specialKeys[key] = false;
			std::cout << "Key pressed: " << key << " : " << GameObject::specialKeys[key] << std::endl;
		}
	);

}

void GameEngine::DeleteObject()
{
	/*
	auto it = std::find_if(objects.begin(), objects.end(), [&_name](const GameObject& obj) {return obj.name == _name; });

		if (it != objects.end())
		{
			// found element. it is an iterator to the first matching element.
			// if you really need the index, you can also get it:
			auto index = std::distance(objects.begin(), it);
		}
*/


}


void GameEngine::ResizeWindow(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void GameEngine::AddGameObject(GameObject* object)
{
	objects.push_back(object);
}

void GameEngine::StartEngine()
{
	glutMainLoop();
}

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}
