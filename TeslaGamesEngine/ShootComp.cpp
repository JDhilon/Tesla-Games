#include "ShootComp.h"
ShootComp::ShootComp() {}
ShootComp::ShootComp(int am): ammo(am)  {}
ShootComp::~ShootComp() {};

double ShootComp::getBulletSpeed() {
	return bullet_speed;
}

double ShootComp::getBulletDir() {
	return bullet_direction;

}

void ShootComp::SetBulletDirection(double h) {
	bullet_direction = h;

	return;
}

void ShootComp::SetBulletSpeed(double h) {
	bullet_speed = h;

	return;
}

void ShootComp::fire() {


	if (ammo <= 0) {
		//std::cout << "Out of ammo" << std::endl;
	}
	else {
		ammo = ammo - 1;
	}
	return;
}

void ShootComp::Tick(float deltaTime) {}