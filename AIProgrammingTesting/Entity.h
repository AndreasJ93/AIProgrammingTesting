#pragma once

#include "WeaponBase.h"
#include <vector>
class Entity
{
private:
	float life;
	float accuracyModifier;
	int positionX;
	int positionY;
	std::vector<WeaponBase*> weapons;
	WeaponBase* equipedWeapon;
public:
	Entity(float life, float position, float positionY);
	~Entity();
	float GetLife();
	void MovePositionX(int distance);
	void MovePositionY(int distance);
	int PositionX();
	int PositionY();
	void SetPositionX(int position);
	void SetPositionY(int position);
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