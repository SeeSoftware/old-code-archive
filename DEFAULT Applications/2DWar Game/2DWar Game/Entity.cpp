#include "Entity.h"

Entity::Entity(GESFML::SpriteBatch &spriteBatch)
{
	_spriteBatch = spriteBatch;
}

Entity::Entity()
{
	_texture = GESFML::HelperFunctions::createBlankTexture(64, 64, sf::Color());
	_pos = GESFML::Vector2D();
	_size = GESFML::Vector2D();
	_color = GESFML::Color(255, 255, 255);
	_id = findNextFreeId();
}

Entity::Entity(GESFML::Color color)
{
	_texture = GESFML::HelperFunctions::createBlankTexture(64, 64, color.getSfColor());
	_pos = GESFML::Vector2D();
	_size = GESFML::Vector2D();
	_color = color;
	_id = findNextFreeId();
}


Entity::~Entity()
{
	if (_spriteBatch.isExistingPhysicSprite(_id))
	{
		_spriteBatch.deletePhysicSprite(_id);
	}
}


Entity::Entity(float x, float y, float w, float h)
{
	_texture = GESFML::HelperFunctions::createBlankTexture(w, h, sf::Color());
	_pos = GESFML::Vector2D(x, y);
	_size = GESFML::Vector2D(w, h);
	_color = GESFML::Color(255,255,255);
	_id = findNextFreeId();
}

Entity::Entity(float x, float y, float w, float h, GESFML::Color color)
{
_texture = GESFML::HelperFunctions::createBlankTexture(64, 64, color.getSfColor());
_pos = GESFML::Vector2D(x, y);
_size = GESFML::Vector2D(w, h);
_color = color;
_id = findNextFreeId();
}

Entity::Entity(float x, float y, float w, float h, sf::Texture &texture)
{
	_texture = texture;
	_pos = GESFML::Vector2D(x, y);
	_size = GESFML::Vector2D(w, h);
	_color = GESFML::Color(255,255,255);
	_id = findNextFreeId();
}
Entity::Entity(GESFML::Vector2D pos, GESFML::Vector2D size, sf::Texture &texture)
{
	_texture = texture;
	_pos = pos;
	_size = size;
	_color = GESFML::Color(255, 255, 255);
	_id = findNextFreeId();
}
Entity::Entity(GESFML::Vector2D pos, GESFML::Vector2D size, GESFML::Color color)
{
	_texture = GESFML::HelperFunctions::createBlankTexture(64, 64, color.getSfColor());
	_pos = pos;
	_size = size;
	_color = GESFML::Color(255, 255, 255);
	_id = findNextFreeId();
}
Entity::Entity(GESFML::Vector2D pos, GESFML::Vector2D size, GESFML::Color color, std::string type, std::string key, long double value)
{
	_texture = GESFML::HelperFunctions::createBlankTexture(64, 64, color.getSfColor());
	_pos = pos;
	_size = size;
	_color = GESFML::Color(255, 255, 255);
	_id = findNextFreeId();
	_key = key;
	_type = type;
	_value = value;
	
	
}
Entity::Entity(float x, float y, float w, float h, GESFML::Color color, std::string type, std::string key, long double value)
{
	_texture = GESFML::HelperFunctions::createBlankTexture(64, 64, color.getSfColor());
	_pos = GESFML::Vector2D(x,y);
	_size = GESFML::Vector2D(w,h);
	_color = GESFML::Color(255, 255, 255);
	_id = findNextFreeId();
	_key = key;
	_type = type;
	_value = value;
	_id = findNextFreeId();
}
Entity::Entity(float x, float y, float w, float h, sf::Texture &texture, std::string type, std::string key, long double value)
{
	_texture = texture;
	_pos = GESFML::Vector2D(x,y);
	_size = GESFML::Vector2D(w, h);
	_color = GESFML::Color(255, 255, 255);
	_id = findNextFreeId();
	_key = key;
	_type = type;
	_value = value;
	_id = findNextFreeId();
}
Entity::Entity(GESFML::Vector2D pos, GESFML::Vector2D size, sf::Texture &texture, std::string type, std::string key, long double value)
{
	_texture = texture;
	_pos = pos;
	_size = size;
	_color = GESFML::Color(255, 255, 255);
	_id = findNextFreeId();
	_key = key;
	_type = type;
	_value = value;
	_id = findNextFreeId();
}


long long Entity::findNextFreeId()
{
	for (long long i = 0;i < _spriteBatch.getPhysicSpriteBatch().size() + 1;i++)
	{
		if (!_spriteBatch.isExistingPhysicSprite(i))
		{
			return i;
		}
	}
}
void Entity::setPos(GESFML::Vector2D pos)
{
	_pos = pos;
	_spriteBatch.setPhysicSpritePosition(_id, pos.getSfVec());
}
void Entity::setPos(float x, float y)
{
	_pos = GESFML::Vector2D(x,y);
	_spriteBatch.setPhysicSpritePosition(_id, GESFML::Vector2D(x,y).getSfVec());
}
void Entity::setSize(GESFML::Vector2D size)
{
	_size = size;
	if (_isCircle)
	{
		_spriteBatch.setPhysicSpriteSizeCircle(_id, size.x);
	}
	else
	{
		_spriteBatch.setPhysicSpriteSizeBox(_id,size.x,size.y);
	}
}
void Entity::setSize(float w, float h)
{
	_size = GESFML::Vector2D(w, h);
	if (_isCircle)
	{
		_spriteBatch.setPhysicSpriteSizeCircle(_id, w);
	}
	else
	{
		_spriteBatch.setPhysicSpriteSizeBox(_id, w,h);
	}
}
void Entity::setColor(GESFML::Color color)
{
	_color = color;
	_spriteBatch.setPhysicSpriteColor(_id, color.getSfColor());
}
void Entity::setColor(int r, int g, int b)
{
	_color = GESFML::Color(r,g,b);
	_spriteBatch.setPhysicSpriteColor(_id, GESFML::Color(r,g,b).getSfColor());
}
void Entity::setColor(int r, int g, int b, int a)
{
	_color = GESFML::Color(r, g, b,a);
	_spriteBatch.setPhysicSpriteColor(_id, GESFML::Color(r, g, b,a).getSfColor());
}
void Entity::setTexture(sf::Texture &texture)
{
	_texture = texture;
	_spriteBatch.setPhysicSpriteTexture(_id, texture);
}

void Entity::spawn(bool Circle, float density, float friction, float bounce, bool dynamic)
{
	_isCircle = Circle;
	_friction = friction;
	_density = density;
	_bounce = bounce;
	_dynamic = dynamic;
	if (_InitFunc != nullptr)
	{
		_InitFunc(_id, _pos, _size, _color, _texture, Circle,dynamic, density, friction, bounce, _type, _key, _value,_rotation);
	}
	else
	{
		if (_isCircle)
		{
			_spriteBatch.createPhysicSpriteCircle(_id, _pos.x, _pos.y, _size.x, dynamic, density, friction, bounce, _texture, _color.getSfColor());
		}
		else
		{
			_spriteBatch.createPhysicSpriteBox(_id, _pos.x, _pos.y, _size.x, _size.y, dynamic, density, friction, bounce, _texture, _color.getSfColor(), _rotation);
			_spriteBatch.setPhysicSpriteUserDataStr(_id, _type);
			_spriteBatch.setPhysicSpriteUserDataStr2(_id, _key);
			_spriteBatch.setPhysicSpriteUserDataNum(_id, _value);
		}
	}
}

void Entity::setRotation(float rot)
{
	_rotation = rot;
}

float Entity::getRotation()
{
	return _rotation;
}

void Entity::setInitFunction(void(*function)(long long, GESFML::Vector2D, GESFML::Vector2D, GESFML::Color, sf::Texture, bool,bool,float,float,float,std::string,std::string,long double,float))
{
	_InitFunc = function;
}

void Entity::setDestroyFunction(void (*function)(long long, std::string ))
{
	_DeleteFunc = function;
}

void Entity::setType(std::string type)
{
	_type = type;
	_spriteBatch.setPhysicSpriteUserDataStr(_id, type);
}

void Entity::setKey(std::string key)
{
	_key = key;
	_spriteBatch.setPhysicSpriteUserDataStr2(_id, key);
}

void Entity::setValue(long double value)
{
	_value = value;
	_spriteBatch.setPhysicSpriteUserDataNum(_id, value);
}

void Entity::setSpriteBatch(GESFML::SpriteBatch &batch)
{
	_spriteBatch = batch;
}

long long Entity::getBatchId()
{
	return _id;
}
GESFML::Color Entity::getColor()
{
	return _color;
}
GESFML::Vector2D Entity::getSize()
{
	return _size;
}
GESFML::Vector2D Entity::getPos()
{
	return _pos;
}

sf::Texture & Entity::getTexture()
{
	return _texture;
}
