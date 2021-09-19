#include "Bullet.h"
#include <GE2D\ResourceManager.h>


Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime)
{
	_lifeTime = lifeTime;
	_position = pos;
	_direction = dir;
	_speed = speed;
}


Bullet::~Bullet()
{
}



void Bullet::draw(GE2D::SpriteBatch& spriteBatch) {
	GE2D::Color color;
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GE2D::GLTexture texture = GE2D::ResourceManager::getTexture("Textures/jimmyjumppack/PNG/CharacterRight_Standing.png");
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30, 30);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);

}

bool Bullet::update() {

	_position += _direction * _speed;
	_lifeTime--;
	if (_lifeTime == 0) {

		return true;

	}
	return false;


}