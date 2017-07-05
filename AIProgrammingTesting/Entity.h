#pragma once

#include "WeaponBase.h"
#include "BasicWeapon.h"
#include <vector>
class Entity
{
private:
	float life;
	float accuracyModifier;
	float positionX;
	float positionY;
	std::vector<WeaponBase*> weapons;
	WeaponBase* equipedWeapon;
public:
	Entity(float life, float position, float positionY);
	float GetLife();
	float PositionX();
	float PositionY();
	void Heal(uint16_t damageToHeal);
	bool Fire();
	void Reload();
	bool Reloading();
	float Accuracy(float distanceToTarget);
	float Damage(float distanceToTarget);
	WeaponBase* EquipedWeapon();
	std::vector<WeaponBase*> &GetAllWeapons();
	void TakeDamage(float damage);
};