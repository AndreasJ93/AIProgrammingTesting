#include "WeaponBase.h"
#include <math.h>

WeaponBase::~WeaponBase()
{
	//Empty
}

float WeaponBase::Damage(float distanceToTarget)
{
	return std::fmaxf(0, damage - (pow(distanceToTarget - damageDecayShift, damageDecayExponent) / damageDevisor));
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
	return std::fmaxf(0, accuracy - (pow(distanceToTarget - accuracyDecayShift, accuracyDecayExponent) / accuracyDevisor));
}