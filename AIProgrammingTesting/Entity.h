#pragma once

#include "WeaponBase.h"
#include "BasicWeapon.h"
#include <vector>
class Entity
{
private:
	float life;
	float accuracyModifier;
	float position;
	std::vector<WeaponBase*> weapons;
	WeaponBase* equipedWeapon;
public:
	Entity(float life, float position) {
		this->life = life;
		this->position = position;
		for (int i = 0; i < 3; i++)
		{
			weapons.push_back(new BasicWeapon(
				rand() % 25 + 15 * rand() % (5 + 1),
				rand() % 7 + 2,
				rand() % 12 + 2,
				0.75f,
				2,
				2.5f,
				1.25f,
				1
			));
		}
		equipedWeapon = weapons[0];
		accuracyModifier = 0;//(rand() % 5) / 100.0f;
	}
	float GetLife() { return life; };
	float Position() { return position; };
	void Heal(uint16_t damageToHeal) { life += damageToHeal; };
	bool Fire() { return equipedWeapon->Fire(); };
	void Reload() { equipedWeapon->Reload(); }
	bool Reloading() { return equipedWeapon->ReloadingDone(); };
	float Accuracy(float distanceToTarget) { return equipedWeapon->Accuracy(distanceToTarget) + accuracyModifier; };
	float Damage(float distanceToTarget) { return equipedWeapon->Damage(distanceToTarget); }
	WeaponBase* EquipedWeapon() { return equipedWeapon; };
	std::vector<WeaponBase*> &GetAllWeapons() { return weapons; };
	void TakeDamage(float damage) {
		if (life - damage < 0)
			life = 0;
		else
			life -= damage;
	}
};