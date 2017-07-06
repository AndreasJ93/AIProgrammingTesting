#include "BasicWeapon.h"

BasicWeapon::BasicWeapon(uint16_t damage, uint16_t maxAmmo, uint8_t reloadTime, float accuracy, uint16_t damageDevisor, float damageDecayExponent, float accuracyDecayExponent, uint16_t accuracyDevisor)
{
	this->maxAmmo = this->currentAmmo = maxAmmo;
	this->reloadTime = reloadTime;
	this->roundsToReloadFinished = 0;

	this->damage = damage;
	this->damageDevisor = damageDevisor;
	this->damageDecayExponent = damageDecayExponent;
	this->damageDecayShift = 0;

	this->accuracy = accuracy;
	this->accuracyDecayExponent = accuracyDecayExponent;
	this->accuracyDevisor = accuracyDevisor;
	this->accuracyDecayShift = 0;
}

BasicWeapon::~BasicWeapon()
{
}