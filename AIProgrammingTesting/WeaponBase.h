#pragma once
#include <stdint.h>
#include <cmath>

class WeaponBase
{
public:
	WeaponBase() {};
	virtual ~WeaponBase();
	virtual float Damage(float distanceToTarget);
	virtual bool Fire(); //Returns false if firing failed (out of ammo?)
	virtual void Reload();
	virtual bool ReloadingDone();
	virtual uint16_t CurrentAmmo(); //Return the current ammo
	virtual float Accuracy(float distanceToTarget);
protected:
	uint16_t damage;
	uint16_t currentAmmo;
	uint16_t maxAmmo;
	uint8_t reloadTime;
	uint8_t roundsToReloadFinished;
	uint16_t damageDevisor;
	float damageDecayExponent;
	float accuracyDecayExponent;
	uint16_t accuracyDevisor;
	float accuracy;
private:
};