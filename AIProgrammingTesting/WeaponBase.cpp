#include "WeaponBase.h"

WeaponBase::~WeaponBase()
{
	//Empty
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