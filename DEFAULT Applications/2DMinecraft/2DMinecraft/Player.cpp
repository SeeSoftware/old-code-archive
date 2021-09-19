#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}



Player::Player(sf::Vector2f position, sf::Texture &playerTexture, b2World *_world) {
	init(position, playerTexture, _world);
}


void Player::move(sf::Vector2f velocity) {
	_entity.getBody()->ApplyLinearImpulse(b2Vec2(velocity.x, velocity.y), _entity.getBody()->GetWorldCenter(), true);
}


void Player::init(sf::Vector2f position, sf::Texture &playerTexture, b2World *_world) {
	


	_entity.init(position.x, position.y, 22, 45, playerTexture,true, _world);
	_world->DestroyBody(_entity.getBody());
	_entity.initBody(position.x, position.y, 11, 45, true, _world);
	_entity.getBody()->SetFixedRotation(true);
	b2MassData *mass = new b2MassData();
	mass->mass = 1000;
	_entity.getBody()->SetMassData(mass);
	_entity.getBody()->SetLinearDamping(0);
}

void Player::update() {
	move(-sf::Vector2f(_entity.getBody()->GetLinearVelocity().x*3, _entity.getBody()->GetLinearVelocity().y*3));

	_entity.update();
}