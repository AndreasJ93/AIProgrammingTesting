#pragma once

#include "WeaponBase.h"
#include "BasicWeapon.h"
#include <vector>
class Entity
{
private:
	uint16_t life;
	float accuracyModifier;
	std::vector<WeaponBase*> weapons;
	WeaponBase* equipedWeapon;
public:
	Entity(uint16_t life) {
		this->life = life;
		for (int i = 0; i < 3; i++)
		{
			weapons.push_back(new BasicWeapon(
				rand() % 25 + 15 * rand() % (5 + 1),
				rand() % 7 + 2,
				rand() % 12 + 2,
				0.75f));
		}
		equipedWeapon = weapons[0];
		accuracyModifier = 0;//(rand() % 5) / 100.0f;
	}
	uint16_t GetLife() { return life; };
	void Heal(uint16_t damageToHeal) { life += damageToHeal; };
	bool Fire() { return equipedWeapon->Fire(); };
	void Reload() { equipedWeapon->Reload(); }
	bool Reloading() { return equipedWeapon->ReloadingDone(); };
	float Accuracy() { return equipedWeapon->Accuracy() + accuracyModifier; };
	WeaponBase* EquipedWeapon() { return equipedWeapon; };
	std::vector<WeaponBase*> &GetAllWeapons() { return weapons; };
	void TakeDamage(uint16_t damage) {
		if (life - damage < 0)
			life = 0;
		else
			life -= damage;
	}
};