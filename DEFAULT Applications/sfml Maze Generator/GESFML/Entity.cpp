#include "Entity.h"

namespace GESFML {

	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
	}



	void Entity::setTexture(Texture texture) {
		_texture = texture;
		_textureSize.x = texture.getTexture().getSize().x;
		_textureSize.y = texture.getTexture().getSize().y;
		_sprite.setTexture(texture.getTexture());
	}
	void Entity::setScale(int x, int y) {
		_sprite.setScale(x / _textureSize.x, y / _textureSize.y);
		_scale.x = x;
		_scale.y = y;
	}
	void Entity::setPosition(int x, int y) {
		_sprite.setPosition(x, y);
		_pos = sf::Vector2f(x, y);
	}
	void Entity::setRotation(int rot) {
		_sprite.setRotation(rot);
		_rot = rot;
	}
	void Entity::setPosScale(int xpos, int ypos, int xsize, int ysize) {
		setPosition(xpos, ypos);
		setScale(xsize, ysize);

	}

	void Entity::move(int x, int y) {
		setPosition(getPosition().x + x, getPosition().y + y);
	}
	void Entity::scale(int x, int y) {
		setScale(getScale().x + x, getScale().y + y);
	}
	void Entity::rotate(int rot) {
		setRotation(getRotation()+rot);
	}
}