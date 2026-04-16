#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "RigidBody.h"
#include "Transform.h"
#include "TimeManager.h"

class Object
{
private:
	bool isPendingDestroy = false;


protected:
	sf::Sprite* sprite;
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
		delete sprite;
	}

	virtual void Render(sf::RenderTarget& window)
	{
		window.draw(*sprite);
	}

	virtual void Update()
	{
		if (physics != nullptr)
			physics->Update();

		// Poner la lógica de actualizar la posición/tamaño/orientación del sprite respecto al transform
		//sprite->Update();
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
