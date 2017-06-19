#pragma once
#include <stdint.h>
#include <cmath>

class WeaponBase
{
public:
	WeaponBase() {};
	virtual ~WeaponBase();
	virtual uint16_t Damage(float distanceToTarget) { return damage - (pow(distanceToTarget, damageDecayExponent) / damageDevisor); };
	virtual bool Fire(); //Returns false if firing failed (out of ammo?)
	virtual void Reload();
	virtual bool ReloadingDone() {
		return roundsToReloadFinished == 0 ? true : false;
	};
	virtual uint16_t CurrentAmmo() { return currentAmmo; }; //Return the current ammo
	virtual float Accuracy(float distanceToTarget) { return accuracy - (pow(distanceToTarget, accuracyDecayExponent) / accuracyDevisor); }; //Return the accuracy of the weapon
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