#pragma once
#include <stdint.h>
#include <cmath>

/*

	The "weapon formula" below is taken from "Behavioural Mathematics for Game AI"

*/

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
	uint16_t currentAmmo;				//The current ammo
	uint16_t maxAmmo;					//The max ammo for the weapon
	uint8_t reloadTime;					//The time it takes to reload
	uint8_t roundsToReloadFinished;		//How many rounds there's left before the reload is finished

	uint16_t damage;					//Damage/shot
	uint16_t damageDevisor;				//How "quickly" the damage wears off (higher number -> slower decay)
	float damageDecayExponent;			//How the distance is modified for the damage wears off
	uint16_t damageDecayShift;			//Move the "highest possible damage" point to a further range (snipers, for instance)

	float accuracy;						//Base accuracy
	float accuracyDecayExponent;		//How the distance is modified for the accuracy decay
	uint16_t accuracyDevisor;			//How "quickly" the accuracy wears off (higher number -> slower decay)
	uint16_t accuracyDecayShift;			//Move the "highest possible accuracy" to another distance than 0
private:
};