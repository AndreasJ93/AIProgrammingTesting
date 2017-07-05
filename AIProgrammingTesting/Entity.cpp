#include "Entity.h"

Entity::Entity(float life, float positionX, float positionY) {
	this->life = life;
	this->positionX = positionX;
	this->positionY = positionY;

	equipedWeapon = new BasicWeapon(100, 5, 2, 1, 1, 1, 1, 1);
	accuracyModifier = 0;//(rand() % 5) / 100.0f;
}
float Entity::GetLife()
{
	return life;
};
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