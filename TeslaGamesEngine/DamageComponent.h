#pragma once

#include "Component.h"

/*
* DamageComponent class inherits fron Component class, representing the damage that the bound object can cause
*/

class DamageComponent : public Component
{
public:
	DamageComponent();
	DamageComponent(double d);
	~DamageComponent();

	double GetDamage();
	void SetDamage(double d);
	void Tick(float deltaTime);

private:
	double localDamage;
};

