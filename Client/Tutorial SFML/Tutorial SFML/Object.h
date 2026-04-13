#pragma once
#include "RigidBody.h"
#include "Transform.h"
#include "ImageRenderer.h"
#include "AnimatedImageRenderer.h"
#include "TimeManager.h"

class Object
{
private:
	bool isPendingDestroy = false;


protected:
	Renderer* renderer = nullptr;
	Transform* transform;
	Rigidbody* physics;

public:
	Object()
	{
		transform = new Transform();
		physics = new Rigidbody(transform);
	};

	~Object()
	{
		delete transform;
		delete physics;
		delete renderer;
	}

	virtual void Render()
	{
		renderer->Render();
	}

	virtual void Update()
	{
		if (physics != nullptr)
			physics->Update();

		renderer->Update();
	}

	inline Transform* const GetTransform() { return transform; }
	Rigidbody* GetRigidBody() { return physics; }
	void SetTransform(Transform* t) { transform = t; };

	bool IsPendingDestroy() const { return isPendingDestroy; }
	virtual void Destroy() //virtual por la explosion
	{
		isPendingDestroy = true;
	}
	virtual void OnCollisionEnter(Object* other) {}
	virtual void SetOpacity(float opacity) { renderer->SetOpacity(opacity); }
};
