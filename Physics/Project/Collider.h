#pragma once
#include <glm/glm.hpp>
#include <vector>

class GameObject;
/*
id list
1 = Sphere
2 = AABB
3 = Plane
*/
struct CollisionData
{
	GameObject* obj1;
	GameObject* obj2;
	glm::vec3 collisionNormal;
	glm::vec3 collisionPoint;
	float penetrationDepth;
};

class Collider
{
public:
	int id;
	glm::vec3 position;
	Collider(glm::vec3 _position, int _id);

	virtual bool CollideCheck(Collider* collider2, CollisionData& collisionInfo) = 0;
	virtual void Draw();
	virtual float GetRadius();
	virtual void SetPosition(glm::vec3 newPos);



	//https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
	//http://buildnewgames.com/broad-phase-collision-detection/





	// For broad phase collision detection I might use Spatial Subdivision
	// Bins technique sounds ok to me

	/*
	IDEA

	each collider will have an int id (1 for sphere, 2 for smth else etc)
	All will call the same CollideCheck function that will recognise what colliders are using it
	and call coresponding method

	example 
	if sphere + sphere then id1 = 1, id2 = 1 call CollideCheck(sphere, sphere)

	*/




};

