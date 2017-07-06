#include "Entity.h"
#include "BasicWeapon.h"
#include "AutomaticWeapon.h"
#include "PistolWeapon.h"
#include "RocketLauncherWeapon.h"
#include "ShotgunWeapon.h"

Entity::Entity(float life, float positionX, float positionY) {
	this->life = life;
	this->positionX = positionX;
	this->positionY = positionY;

	switch (rand() % 4)
	{
	case 0:
		equipedWeapon = new AutomaticWeapon();
		break;
	case 1:
		equipedWeapon = new PistolWeapon();
		break;
	case 2:
		equipedWeapon = new RocketLauncherWeapon();
		break;
	case 3:
		equipedWeapon = new ShotgunWeapon();
		break;
	}
	accuracyModifier = (rand() % 5) / 100.0f;
}
float Entity::GetLife()
{
	return life;
}
void Entity::MovePositionX(float distance)
{
	positionX += distance;
}
void Entity::MovePositionY(float distance)
{
	positionY += distance;
}
;
float Entity::PositionX()
{
	return positionX;
};
float Entity::PositionY()
{
	return positionY;
};
void Entity::Heal(uint16_t damageToHeal)
{
	life += damageToHeal;
};
bool Entity::Fire()
{
	return equipedWeapon->Fire();
};
void Entity::Reload()
{
	equipedWeapon->Reload();
}
bool Entity::Reloading()
{
	return equipedWeapon->ReloadingDone();
};
float Entity::Accuracy(float distanceToTarget)
{
	return equipedWeapon->Accuracy(distanceToTarget) + accuracyModifier;
};
float Entity::Damage(float distanceToTarget)
{
	return equipedWeapon->Damage(distanceToTarget);
}
WeaponBase* Entity::EquipedWeapon()
{
	return equipedWeapon;
};
std::vector<WeaponBase*> &Entity::GetAllWeapons()
{
	return weapons;
};
void Entity::TakeDamage(float damage) {
	if (life - damage < 0)
		life = 0;
	else
		life -= damage;
}