#include "BasicWeapon.h"

BasicWeapon::BasicWeapon(uint16_t damage, uint16_t maxAmmo, uint8_t reloadTime, float accuracy)
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