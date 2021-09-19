#pragma once
#include <SFML\Graphics.hpp>
#include <SFMLGameEngine2.0\SpriteBatch.h>
#include <SFMLGameEngine2.0\HelperFunctions.h>
#include <SFMLGameEngine2.0\Color.h>
#include <SFMLGameEngine2.0\Vector2D.h>
#include <string>
#include <unordered_map>

class Entity
{
public:
	Entity();
	Entity(GESFML::SpriteBatch &spriteBatch);
	Entity(GESFML::Color color);
	Entity(float x, float y, float w, float h);
	Entity(float x, float y, float w, float h, GESFML::Color color);
	Entity(float x, float y, float w, float h, sf::Texture &texture);
	Entity(GESFML::Vector2D pos, GESFML::Vector2D size, sf::Texture &texture);
	Entity(GESFML::Vector2D pos, GESFML::Vector2D size, GESFML::Color color);
	Entity(GESFML::Vector2D pos, GESFML::Vector2D size, GESFML::Color color, std::string type, std::string key, long double value);
	Entity(float x, float y, float w, float h, GESFML::Color color, std::string type, std::string key, long double value);
	Entity(float x, float y, float w, float h, sf::Texture &texture, std::string type, std::string key, long double value);
	Entity(GESFML::Vector2D pos, GESFML::Vector2D size, sf::Texture &texture, std::string type, std::string key, long double value);
	~Entity();

	long long findNextFreeId();
	void setSpriteBatch(GESFML::SpriteBatch &batch);
	void setPos(GESFML::Vector2D pos);
	void setPos(float x, float y);
	void setRotation(float rot);
	void setSize(GESFML::Vector2D size);
	void setSize(float w, float h);
	void setColor(GESFML::Color color);
	void setColor(int r, int g, int b);
	void setColor(int r, int g, int b, int a);
	void setTexture(sf::Texture &texture);
	void spawn(bool Circle, float density, float friction, float bounce, bool dynamic);
	void setInitFunction(void (*function)(long long,GESFML::Vector2D , GESFML::Vector2D , GESFML::Color, sf::Texture , bool,bool,float,float, float, std::string, std::string, long double, float));
	void setDestroyFunction(void (*function)(long long,std::string ));
	void setType(std::string type);
	void setKey(std::string key);
	void setValue(long double value);
	long long getBatchId();
	float getRotation();
	GESFML::Color getColor();
	GESFML::Vector2D getSize();
	GESFML::Vector2D getPos();
	sf::Texture &getTexture();
	


private:

	void (*_InitFunc)(long long, GESFML::Vector2D, GESFML::Vector2D, GESFML::Color, sf::Texture, bool,bool, float, float, float, std::string, std::string, long double, float) = nullptr;
	void (*_DeleteFunc)(long long,std::string) = nullptr;

	sf::Texture _texture;
	GESFML::SpriteBatch _spriteBatch;
	long long _id =-1;
	//bool generated = false;
	GESFML::Color _color;
	GESFML::Vector2D _size;
	std::unordered_map<std::string, std::string> _stringTable;
	std::unordered_map<std::string, double> _numTable;
	GESFML::Vector2D _pos;

	float _density;
	float _friction;
	float _bounce;
	float _rotation;
	bool _dynamic;
	bool _isCircle = false;

	std::string _type;
	std::string _key;
	long double _value;

};

