#include "bullet.h"

Bullet::Bullet()
{
	bulletXpos = 0;
	bulletYpos = 0;
	bulletVelY = BULLET_VEL;

	bulletCollider.w = BULLET_WIDTH;
	bulletCollider.h = BULLET_HEIGHT;

	isDestroyed = false;
}

Bullet::~Bullet()
{

}

void Bullet::fire()
{
	bulletYpos -= bulletVelY;
	bulletCollider.x = bulletXpos;
	bulletCollider.y = bulletYpos;

	if ((bulletYpos < 0) || (bulletYpos + Bullet::BULLET_HEIGHT > globals::SCREEN_HEIGHT))
	{
		isDestroyed = true;
	}
}

int Bullet::getBulletXpos() {
	return Bullet::bulletXpos;
}

int Bullet::getBulletYpos() {
	return Bullet::bulletYpos;
}