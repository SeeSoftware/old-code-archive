#include "SpriteBatch.h"

namespace GESFML {

	SpriteBatch::SpriteBatch()
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}


	void SpriteBatch::createSprite(long long unsigned id) {
		_sprites[id] = sf::Sprite();
	}

	void SpriteBatch::createSprite(long long unsigned id, int x, int y, int xs, int ys) {
		sf::Sprite sprite;
		sprite.setPosition(x, y);
		_tools.setSizeInPixel(sprite, xs, ys);
		_sprites[id] = sprite;
	}

	void SpriteBatch::createSprite(long long unsigned id, int x, int y, int xs, int ys, sf::Texture &texture) {
		
		sf::Sprite sprite;
		sprite.setTexture(texture);
		_tools.setSizeInPixel(sprite, xs, ys);
		sprite.setPosition(x, y);

		_sprites[id] = sprite;
	}

	sf::Vector2f SpriteBatch::getPosition(long long unsigned id) {
		return _sprites[id].getPosition();
	}

	sf::Vector2f SpriteBatch::getScale(long long unsigned id) {
		return _sprites[id].getScale();
	}

	sf::Vector2f SpriteBatch::getScaleInPixel(long long unsigned id)
	{
		sf::Vector2f tmp_v;
		tmp_v = getScale(id);
		const sf::Texture *tmp_t;
		tmp_t = getTexture(id);
		return sf::Vector2f(tmp_v.x * tmp_t->getSize().x, tmp_v.y * tmp_t->getSize().y);
	}

	float SpriteBatch::getRotation(long long unsigned id) {
		return _sprites[id].getRotation();
	}

	const sf::Texture *SpriteBatch::getTexture(long long unsigned id) {
		const sf::Texture *tmp;
		tmp = _sprites[id].getTexture();
		return tmp;
	}
	sf::Color SpriteBatch::getColor(long long unsigned id) {
		return _sprites[id].getColor();
	}

	void SpriteBatch::setPosition(long long unsigned id, int x, int y) {
		_sprites[id].setPosition(x, y);
	}

	void SpriteBatch::setTexture(long long unsigned id, sf::Texture &texture) {
		_sprites[id].setTexture(texture);
	}

	void SpriteBatch::setScale(long long unsigned id, int x, int y) {
		_sprites[id].setScale(x, y);
	}

	void SpriteBatch::setScaleInPixel(long long unsigned id, int x, int y) {
		_tools.setSizeInPixel(_sprites[id], x, y);
	}

	void SpriteBatch::setRotation(long long unsigned id, float rotation) {
		_sprites[id].setRotation(rotation);
	}

	void SpriteBatch::setColor(long long unsigned id,sf::Color color) {
		_sprites[id].setColor(color);
	}

	void SpriteBatch::move(long long unsigned id, int x, int y) {
		setPosition(id, getPosition(id).x + x, getPosition(id).y + y);
	}

	void SpriteBatch::scale(long long unsigned id, int x, int y) {
		setScale(id, getScale(id).x + x, getScale(id).y + y);
	}

	void SpriteBatch::scaleInPixel(long long unsigned id, int x, int y) {
		setScaleInPixel(id, getScaleInPixel(id).x + x, getScaleInPixel(id).y + y);
	}

	void SpriteBatch::rotatate(long long unsigned id, int rot) {
		setRotation(id, getRotation(id) + rot);
	}

	void SpriteBatch::setSprite(long long unsigned id, sf::Sprite sprite) {
		_sprites[id] = sprite;
	}

	sf::Sprite SpriteBatch::getSprite(long long unsigned id) {
		return _sprites[id];
	}

	long long unsigned SpriteBatch::getSize() {
		return _sprites.size();
	}
	void SpriteBatch::deleteAll() {
		_sprites.clear();
	}
	void SpriteBatch::deleteSprite(long long unsigned id) {
		_sprites.erase(id);
	}

	void SpriteBatch::changeDrawOrder(long long unsigned id, long long unsigned toid) {
		sf::Sprite tmp;
		tmp = _sprites[toid];

		_sprites[toid] = _sprites[id];
		_sprites[id] = tmp;

	}

}