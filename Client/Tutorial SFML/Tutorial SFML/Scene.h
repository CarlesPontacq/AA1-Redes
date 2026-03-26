#pragma once
//#include "Object.h"
#include <vector>
//#include "Spawner.h"

class Scene
{/*
protected:
	std::vector<Object*> ui;
	std::vector<Object*> objects;

public:
	Scene() = default;
	virtual void OnEnter() = 0;
	virtual void OnExit()
	{
		SPAWN.ClearSpawnedObjects();
		for (Object* o : objects)
			delete o;
		objects.clear();

		SPAWN.ClearSpawnedUIObjects();
		for (Object* u : ui)
			delete u;
		ui.clear();

	};
	virtual void Update()
	{
		//Destruction
		for (int i = objects.size() - 1; i >= 0; i--)
		{
			if (objects[i]->IsPendingDestroy())
			{
				delete objects[i];
				objects.erase(objects.begin() + i);
			}
		}
		//Creation
		while (SPAWN.GetSpawnedObjectsCount() > 0)
		{
			objects.push_back(SPAWN.GetSpawnedObject());
		}

		while (SPAWN.GetSpawnedUIObjectsCount() > 0)
		{
			ui.push_back(SPAWN.GetSpawnedUIObject());
		}
		//Update
		for (Object* o : objects)
			o->Update();

		for (Object* u : ui)
			u->Update();
		//Update physics

		for (int i = 0; i < objects.size(); i++)
		{
			for (int j = i + 1; j < objects.size(); j++)
			{
				if (objects[i]->GetRigidBody()->CheckCollision(objects[j]->GetRigidBody()))
				{
					objects[i]->OnCollisionEnter(objects[j]);
					objects[j]->OnCollisionEnter(objects[i]);
				}
			}
		}
	}

	virtual void Render()
	{
		for (Object* o : objects)
			o->Render();
		for (Object* u : ui)
			u->Render();
	};*/
};