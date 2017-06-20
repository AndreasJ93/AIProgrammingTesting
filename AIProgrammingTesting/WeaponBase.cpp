#include "WeaponBase.h"

WeaponBase::~WeaponBase()
{
	//Empty
}

float WeaponBase::Damage(float distanceToTarget)
{
	return damage - (pow(distanceToTarget, damageDecayExponent) / damageDevisor);
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
	return accuracy - (pow(distanceToTarget, accuracyDecayExponent) / accuracyDevisor);
}

