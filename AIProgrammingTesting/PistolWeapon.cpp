#include "PistolWeapon.h"

PistolWeapon::PistolWeapon()
{
	this->maxAmmo = this->currentAmmo = 12;
	this->reloadTime = 1;
	this->roundsToReloadFinished = 0;

	this->damage = 10;
	this->damageDevisor = 5000;
	this->damageDecayExponent = 2.2f;
	this->damageDecayShift = 0;

	this->accuracy = 0.70f;
	this->accuracyDecayExponent = 1.5f;
	this->accuracyDevisor = 3000;
	this->accuracyDecayShift = 0;
}

PistolWeapon::~PistolWeapon()
{
}