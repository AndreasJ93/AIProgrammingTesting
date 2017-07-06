#include "ShotgunWeapon.h"

ShotgunWeapon::ShotgunWeapon()
{
	this->maxAmmo = this->currentAmmo = 5;
	this->reloadTime = 2;
	this->roundsToReloadFinished = 0;

	this->damage = 50;
	this->damageDevisor = 100;
	this->damageDecayExponent = 2.1f;
	this->damageDecayShift = 0;

	this->accuracy = 0.95;
	this->accuracyDecayExponent = 2.5;
	this->accuracyDevisor = 15000;
	this->accuracyDecayShift = 0;
}

ShotgunWeapon::~ShotgunWeapon()
{
}