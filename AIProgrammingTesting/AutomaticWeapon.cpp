#include "AutomaticWeapon.h"

AutomaticWeapon::AutomaticWeapon()
{
	this->maxAmmo = this->currentAmmo = 30;
	this->reloadTime = 3;
	this->roundsToReloadFinished = 0;

	this->damage = 30;
	this->damageDevisor = 5000;
	this->damageDecayExponent = 2.0f;
	this->damageDecayShift = 0;

	this->accuracy = 0.80f;
	this->accuracyDecayExponent = 1.8f;
	this->accuracyDevisor = 50000;
	this->accuracyDecayShift = 0;
}

AutomaticWeapon::~AutomaticWeapon()
{
}