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
	float GetLife() const;
	void MovePositionX(int distance);
	void MovePositionY(int distance);
	int PositionX() const;
	int PositionY() const;
	void SetPositionX(int position);
	void SetPositionY(int position);
	void Heal(uint16_t damageToHeal);
	bool Fire() const;
	void Reload() const;
	bool Reloading() const;
	float Accuracy(float distanceToTarget) const;
	float Damage(float distanceToTarget) const;
	WeaponBase* EquipedWeapon() const;
	std::vector<WeaponBase*>& GetAllWeapons();
	void TakeDamage(float damage);
};
