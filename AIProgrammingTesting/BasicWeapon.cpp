#include "BasicWeapon.h"

BasicWeapon::BasicWeapon(uint16_t damage, uint16_t maxAmmo, uint8_t reloadTime, float accuracy, uint16_t damageDevisor, float damageDecayExponent, float accuracyDecayExponent, uint16_t accuracyDevisor)
{
	this->damage = damage;
	this->maxAmmo = this->currentAmmo = maxAmmo;
	this->reloadTime = reloadTime;
	this->roundsToReloadFinished = 0;
	this->accuracy = accuracy;
}

BasicWeapon::~BasicWeapon()
{
}