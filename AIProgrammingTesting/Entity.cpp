#include "Entity.h"
#include "BasicWeapon.h"
#include "AutomaticWeapon.h"
#include "PistolWeapon.h"
#include "RocketLauncherWeapon.h"
#include "ShotgunWeapon.h"

Entity::Entity(float life, float positionX, float positionY)
{
	this->life = life;
	this->positionX = uint16_t(floor(positionX));
	this->positionY = uint16_t(floor(positionY));

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

	default:
		equipedWeapon = new ShotgunWeapon();
		break;
	}
	accuracyModifier = (rand() % 5) / 100.0f;
}

Entity::~Entity()
{
	delete equipedWeapon;
}

float Entity::GetLife() const
{
	return life;
}

void Entity::MovePositionX(int distance)
{
	positionX += distance;
}

void Entity::MovePositionY(int distance)
{
	positionY += distance;
}
;

int Entity::PositionX() const
{
	return positionX;
};

int Entity::PositionY() const
{
	return positionY;
}

void Entity::SetPositionX(int position)
{
	positionX = position;
}

void Entity::SetPositionY(int position)
{
	positionY = position;
}

void Entity::Heal(uint16_t damageToHeal)
{
	life += damageToHeal;
};

bool Entity::Fire() const
{
	return equipedWeapon->Fire();
};

void Entity::Reload() const
{
	equipedWeapon->Reload();
}

bool Entity::Reloading() const
{
	return equipedWeapon->ReloadingDone();
};

float Entity::Accuracy(float distanceToTarget) const
{
	return equipedWeapon->Accuracy(distanceToTarget) + accuracyModifier;
};

float Entity::Damage(float distanceToTarget) const
{
	return equipedWeapon->Damage(distanceToTarget);
}

WeaponBase* Entity::EquipedWeapon() const
{
	return equipedWeapon;
};

std::vector<WeaponBase*>& Entity::GetAllWeapons()
{
	return weapons;
};

void Entity::TakeDamage(float damage)
{
	if (life - damage < 0)
		life = 0;
	else
		life -= damage;
}