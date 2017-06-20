#pragma once
#include "WeaponBase.h"
class BasicWeapon :
	public WeaponBase
{
public:
	BasicWeapon(uint16_t damage, uint16_t maxAmmo, uint8_t reloadTime,	
		float accuracy, uint16_t damageDevisor, float damageDecayExponent, 
		float accuracyDecayExponen,	uint16_t accuracyDevisor);
	~BasicWeapon();

private:
};
