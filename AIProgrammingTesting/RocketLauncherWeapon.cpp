#include "RocketLauncherWeapon.h"

RocketLauncherWeapon::RocketLauncherWeapon()
{
	this->maxAmmo = this->currentAmmo = 1;
	this->reloadTime = 4;
	this->roundsToReloadFinished = 0;

	this->damage = 100;
	this->damageDevisor = 1500;
	this->damageDecayExponent = 2.0f;
	this->damageDecayShift = 0;

	this->accuracy = 0.50;
	this->accuracyDecayExponent = 2.0;
	this->accuracyDevisor = 30000;
	this->accuracyDecayShift = 50;
}

RocketLauncherWeapon::~RocketLauncherWeapon()
{
}
