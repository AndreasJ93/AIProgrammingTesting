#pragma once
#include <stdint.h>

class WeaponBase
{
public:
	WeaponBase() {};
	virtual ~WeaponBase();
	virtual uint16_t Damage() { return damage; };
	virtual bool Fire(); //Returns false if firing failed (out of ammo?)
	virtual void Reload();
	virtual bool ReloadingDone() {
		return roundsToReloadFinished == 0 ? true : false;
	};
	virtual uint16_t CurrentAmmo() { return currentAmmo; }; //Return the current ammo
	virtual float Accuracy() { return accuracy; }; //Return the accuracy of the weapon
protected:
	uint16_t damage;
	uint16_t currentAmmo;
	uint16_t maxAmmo;
	uint8_t reloadTime;
	uint8_t roundsToReloadFinished;
	float accuracy;
private:
};