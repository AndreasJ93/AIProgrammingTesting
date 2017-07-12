#include "WeaponBase.h"
#include <math.h>

WeaponBase::WeaponBase()
{
	currentAmmo = 0;
	maxAmmo = 0;
	reloadTime = 0;
	roundsToReloadFinished = 0;

	damage = 0;
	damageDevisor = 0;
	damageDecayExponent = 0.0f;
	damageDecayShift = 0;

	accuracy = 0.0f;
	accuracyDecayExponent = 0.0f;
	accuracyDevisor = 0;
	accuracyDecayShift = 0;
}

WeaponBase::~WeaponBase()
{
	//Empty
}

float WeaponBase::Damage(float distanceToTarget)
{
	return fmaxf(0, damage - (powf(distanceToTarget - damageDecayShift, damageDecayExponent) / damageDevisor));
}

bool WeaponBase::Fire()
{
	if (currentAmmo)
	{
		currentAmmo--;
		return true;
	}
	return false;
}

void WeaponBase::Reload()
{
	if (roundsToReloadFinished)
	{
		//"Reloading"
		roundsToReloadFinished--;
		if (!roundsToReloadFinished)
			currentAmmo = maxAmmo;
	}
	else
	{
		//Starting reloading
		roundsToReloadFinished = reloadTime;
	}
}

bool WeaponBase::ReloadingDone()
{
	return roundsToReloadFinished == 0 ? true : false;
}

uint16_t WeaponBase::CurrentAmmo()
{
	return currentAmmo;
}

float WeaponBase::Accuracy(float distanceToTarget)
{
	return fmaxf(0, accuracy - (powf(distanceToTarget - accuracyDecayShift, accuracyDecayExponent) / accuracyDevisor));
}