#include "Chunk.h"
#include <iostream>


Chunk::Chunk()
{

}

Chunk::Chunk(int x, int y, int w, int h, sf::Texture &Textures, b2World *world) {
	
	generate(x, y, w, h, Textures, world);
}

Chunk::~Chunk()
{
}

void Chunk::generate(int x, int y, int w, int h,sf::Texture &Textures, b2World *world) {



	_world = world;
	_pos.x = x;
	_pos.y = y;
	_size.x = w;
	_size.y = h;
	Block tmp;
	y += 128;
	if (x < 0) {
		w = w - (-x);
	}
	else if (x>0) {
		w = w + x;
	}
	if (y < 0) {
		h = h - (-y);
	}
	else if (y>0) {
		h = h + y;
	}

	
	for (int y2 = y; y2 < h;y2++) {
		for (int x2 = x; x2 < w;x2++) {
			id++;
			if (y2 == y) {
				tmp.create(x2, y2, 3, Textures, world);
				_entities[id] = tmp.getEntity();
				srand(time(NULL) + id);
				int rnd = rand() % 100;
				//long unsigned rnd = _tools.xorshf96() % 80;

				if (rnd > 50) {
					_world->DestroyBody(_entities[id].getBody());
					tmp.create(x2, y2, 2, Textures, world);
					_entities[id] = tmp.getEntity();
					id++;
					tmp.create(x2, y2 - 1, 3, Textures, world);
					_entities[id] = tmp.getEntity();

					srand(time(NULL) + id * 5);
					int rnd = rand() % 80;
					//long unsigned rnd = _tools.xorshf96() % 70;

					if (rnd > 50) {
						_world->DestroyBody(_entities[id].getBody());
						tmp.create(x2, y2 - 1, 2, Textures, world);
						_entities[id] = tmp.getEntity();
						id++;
						tmp.create(x2, y2 - 2, 3, Textures, world);
						_entities[id] = tmp.getEntity();
					}


				}
				else {

					rnd = _tools.xorshf96() % 100;

					if (rnd > 90) {
						if (x2 - x > 1 & x2 - x < w - x - 2) {

							id++;
							tmp.create(x2, y2 - 1, 20, Textures, world);
							_entities[id] = tmp.getEntity();
							id++;
							tmp.create(x2, y2 - 2, 20, Textures, world);
							_entities[id] = tmp.getEntity();
							id++;
							tmp.create(x2, y2 - 3, 20, Textures, world);
							_entities[id] = tmp.getEntity();
							id++;
							tmp.create(x2, y2 - 4, 20, Textures, world);
							_entities[id] = tmp.getEntity();
							id++;
							tmp.create(x2, y2 - 5, 52, Textures, world);
							_entities[id] = tmp.getEntity();
							_entities[id].setColor(sf::Color(0, 255, 0, 255));
							id++;
							tmp.create(x2 + 1, y2 - 4, 52, Textures, world);
							_entities[id] = tmp.getEntity();
							_entities[id].setColor(sf::Color(0, 255, 0, 255));
							id++;
							tmp.create(x2 - 1, y2 - 4, 52, Textures, world);
							_entities[id] = tmp.getEntity();
							_entities[id].setColor(sf::Color(0, 255, 0, 255));
							id++;
							tmp.create(x2 - 1, y2 - 3, 52, Textures, world);
							_entities[id] = tmp.getEntity();
							_entities[id].setColor(sf::Color(0, 255, 0, 255));
							id++;
							tmp.create(x2 + 1, y2 - 3, 52, Textures, world);
							_entities[id] = tmp.getEntity();
							_entities[id].setColor(sf::Color(0, 255, 0, 255));
							id++;
							tmp.create(x2 + 2, y2 - 3, 52, Textures, world);
							_entities[id] = tmp.getEntity();
							_entities[id].setColor(sf::Color(0, 255, 0, 255));
							id++;
							tmp.create(x2 - 2, y2 - 3, 52, Textures, world);
							_entities[id] = tmp.getEntity();
							_entities[id].setColor(sf::Color(0, 255, 0, 255));
						}
					}

				}
			}
			else if (y2 - y>1 || y2 - y < 3) {
				tmp.create(x2, y2 , 2, Textures, world);
				_entities[id] = tmp.getEntity();
			}
			if (y2 - y>3) {
				_world->DestroyBody(_entities[id].getBody());
				tmp.create(x2, y2 , 1, Textures, world);
				_entities[id] = tmp.getEntity();

			}
			if (y2 - y == 3) {
				srand(time(NULL) + id);
				//int rnd = rand() % 100;
				long unsigned rnd = _tools.xorshf96() % 100;

				if (rnd > 50) {
					_world->DestroyBody(_entities[id].getBody());
					tmp.create(x2, y2 , 1, Textures, world);
					_entities[id] = tmp.getEntity();
				}


			}

		}
	}
}

void Chunk::insertBlock(Block block,sf::Texture &TextureAtlas) {
	if (isInChunk(sf::Vector2f(block.blockPosX * 25, block.blockPosY * 25))) {
		
		int index;
		if (getEntity(block.blockPosX, block.blockPosY,index).getSprite().getOrigin() == sf::Vector2f(0,0)) {

		
			id++;
			//_world->DestroyBody(_entities[id+1].getBody());
			_entities[id+1] = block.getEntity();
		}
		else {
			int userdata;
			userdata = (int)getEntity(block.blockPosX, block.blockPosY,index).getUserData();

			_world->DestroyBody(getBody(index));
			_entities.erase(index);

			id++;
			_world->DestroyBody(block.getEntity().getBody());
			block.create(block.blockPosX, block.blockPosY, userdata, TextureAtlas, _world);
			_entities[id + 1] = block.getEntity();


		}



	}
}

void Chunk::setColor(long long unsigned id, sf::Color color) {
	_entities[id].setColor(color);
}

void Chunk::removeBlock(int x, int y) {
	if (isInChunk(sf::Vector2f(x * 25, y * 25))) {
		int index;
		GESFML::Entity tmp =  getEntity(x, y,index);

		if (tmp.getSprite().getOrigin() != sf::Vector2f(0, 0)) {
			_destroyEntslist[index] = index;
			
		}
	}
}

void Chunk::destroyEnt(long long unsigned id) {
	_entities.erase(id);
}

b2Body *Chunk::getBody(long long unsigned id) {
	return _entities[id].getBody();
}

void Chunk::clearDestroyList() {
	_destroyEntslist.clear();
}

GESFML::Entity Chunk::getEntity(int x, int y, int &index) {
	if (isInChunk(sf::Vector2f(x * 25, y * 25))) {

		for (auto &ent : _entities) {
			sf::Vector2f pos = ent.second.getSprite().getPosition();
			pos.x += 25 / 2;
			pos.y += 25 / 2;
			pos.x /= 25;
			pos.y /= 25;

			//pos.x -= _pos.y;

			if (x == floor(pos.x)-7 & y == floor(pos.y)-7) {
				index = ent.first;
				return ent.second;

			}
		}
	
	}
	return GESFML::Entity();
}

bool Chunk::isInChunk(sf::Vector2f pos) {
 	if (pos.x/25 >= _pos.x & pos.y  / 25 >= _pos.y ) {
		if (pos.x / 25 <= (_pos.x+ _size.x) & pos.y / 25 <= (_pos.y + _size.y+128)) {
			return true;
		}
	}
	return false;
}