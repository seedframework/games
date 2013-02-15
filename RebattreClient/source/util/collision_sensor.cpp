#include "collision_sensor.h"

#include "../scene/game_scene.h"

CollisionSensor::CollisionSensor()
	: pBody(NULL)
{
}

CollisionSensor::~CollisionSensor()
{
	gPhysicsManager->DestroyBody(pBody);
}

void CollisionSensor::Load(Seed::ISceneObject &metadata, void *userData)
{
	this->Load(metadata, false, NULL, userData);
}

void CollisionSensor::Load(Seed::ISceneObject &metadata, bool track, b2Vec2 *customSize, void *userData)
{
	pBody = gPhysicsManager->CreateStaticBody(&metadata, BodyType::SENSOR, track, customSize);
	pBody->GetFixtureList()->SetUserData(userData);
}

void CollisionSensor::Disable()
{
	pBody->GetFixtureList()->SetUserData(NULL);
}
