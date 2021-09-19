#include "Game.h"
#include <Box2D\Box2D.h>
#include <iostream>
#include <time.h>
#include <GESFML\Entity.h>

//#include "Block.h"
#include <vector>

Game::Game()
{
	
}


Game::~Game()
{
}


void Game::run() {
	init(1280, 720);
	gameloop();

}


void Game::init(int width, int height) {

	_width = width;
	_height = height;
	//create the window
	_window.create(sf::VideoMode(width, height), "2DMinecraft");
	_physEnt.initWorld(b2Vec2(0, 64), 60, 25, true);
	//setting the framerate limit
	_window.setFramerateLimit(60);
	_window.setVerticalSyncEnabled(true);
	// setting the bg color
	_bgColor = sf::Color(0, 128, 255);
	//init the camera
	_camera.setSize(width, height);
	_camera.setCenter(width / 2, height / 2);
	_camera.zoom(0.3);
	//loading the basic textures
	_textureAtlas.loadFromFile("Resources/Textures/Minecraft_textures.png");
	_playerTexture.loadFromFile("Resources/Textures/player.png");

	//init names

	_blocks_names[0] = "Gravel";
	_blocks_names[1] = "Stone";
	_blocks_names[2] = "Dirt";
	_blocks_names[3] = "Grass";
	_blocks_names[4] = "Wood Planks";
	_blocks_names[5] = "Half Steps";
	_blocks_names[6] = "Stone";
	_blocks_names[7] = "Bricks";
	_blocks_names[8] = "TNT";
	_blocks_names[16] = "Cobblestone";
	_blocks_names[17] = "Bedrock";
	_blocks_names[18] = "Sand";
	_blocks_names[19] = "Gravel";
	_blocks_names[20] = "Log";
	_blocks_names[22] = "Ironblock";
	_blocks_names[23] = "Goldblock";
	_blocks_names[24] = "Diamondblock";
	_blocks_names[32] = "Goldore";
	_blocks_names[33] = "Ironore";
	_blocks_names[34] = "Coalore";
	_blocks_names[35] = "Bookshelf";
	_blocks_names[36] = "Mossy Cobblestone";
	_blocks_names[37] = "Obsidian";
	_blocks_names[44] = "Oven";
	_blocks_names[48] = "Sponge";
	_blocks_names[49] = "Glass";
	_blocks_names[50] = "Diamondore";
	_blocks_names[51] = "Redstoneore";
	_blocks_names[52] = "Leaves";
	_blocks_names[60] = "Workbench";
	_blocks_names[64] = "Wool";
	_blocks_names[65] = "Spawner";
	_blocks_names[67] = "Ice";
	_blocks_names[68] = "SnowGrass";
	_blocks_names[66] = "Snowblock";
	_blocks_names[74] = "Noteblock";
	_blocks_names[103] = "Netherrack";
	_blocks_names[104] = "Soulsand";
	_blocks_names[105] = "Glowstone";
	_blocks_names[109] = "Stone";
	_blocks_names[113] = "Blackwool";
	_blocks_names[114] = "Graywool";
	_blocks_names[116] = "Log";
	_blocks_names[117] = "Log";
	_blocks_names[119] = "Pumpkin";
	_blocks_names[129] = "Redwool";
	_blocks_names[130] = "Pinkwool";
	_blocks_names[144] = "lapislazuli block";
	_blocks_names[145] = "Greenwool";
	_blocks_names[146] = "Lightgreen wool";
	_blocks_names[160] = "lapislazuli ore";

	_blocks_names[161] = "Brownwool";
	_blocks_names[162] = "Yellowool";
	_blocks_names[177] = "Bluewool";
	_blocks_names[178] = "Lightblue wool";
	_blocks_names[192] = "Sandstone";
	_blocks_names[193] = "Purplewool";
	_blocks_names[194] = "Lightpurple wool";
	_blocks_names[209] = "Cynanwool";
	_blocks_names[210] = "Orangewool";
	_blocks_names[225] = "Lightgray wool";

	_blocks_id[1] = 0;
	_blocks_id[2] =1;
	_blocks_id[3] =2;
	_blocks_id[4] =3;
	_blocks_id[5] =4;
	_blocks_id[6] =5;
	_blocks_id[7] =6;
	_blocks_id[8] =7;
	_blocks_id[9] =8;
	_blocks_id[10] =16;
	_blocks_id[11] =17;
	_blocks_id[12] =18;
	_blocks_id[13] =19;
	_blocks_id[14] =20;
	_blocks_id[15] =22;
	_blocks_id[16] =23;
	_blocks_id[17] =24;
	_blocks_id[18] =32;
	_blocks_id[19] =33;
	_blocks_id[20] =34;
	_blocks_id[21] =35;
	_blocks_id[22] =36;
	_blocks_id[23] =37;
	_blocks_id[24] =44;
	_blocks_id[25] =48;
	_blocks_id[26] =49;
	_blocks_id[27] =50;
	_blocks_id[28] =51;
	_blocks_id[29] =52;
	_blocks_id[30] =60;
	_blocks_id[31] =64;
	_blocks_id[32] =65;
	_blocks_id[33] =67;
	_blocks_id[34] =68;
	_blocks_id[35] =66;
	_blocks_id[36] =74;
	_blocks_id[37] =103;
	_blocks_id[38] =104;
	_blocks_id[39] =105;
	_blocks_id[40] =109;
	_blocks_id[41] =113;
	_blocks_id[42] =114;
	_blocks_id[43] =116;
	_blocks_id[44] =117;
	_blocks_id[45] =119;
	_blocks_id[46] =129;
	_blocks_id[47] =130;
	_blocks_id[48] =144;
	_blocks_id[49] =145;
	_blocks_id[50] =146;
	_blocks_id[51] =160;

	_blocks_id[52] =161;
	_blocks_id[53] =162;
	_blocks_id[54] =177;
	_blocks_id[55] =178;
	_blocks_id[56] =192;
	_blocks_id[57] =193;
	_blocks_id[58] =194;
	_blocks_id[59] =209;
	_blocks_id[60] =210;
	_blocks_id[61] =225;

	_font.loadFromFile("Resources/Fonts/Minecraft.ttf");
	_selectionText.setFont(_font);
	_selectionText.setCharacterSize(120);
	_selectionText.setScale(sf::Vector2f(0.1, 0.1));
	
	_gui.createSprite(1, 0,0, _textureAtlas.getSize().x * 25 / 16, _textureAtlas.getSize().y * 25 / 16, _textureAtlas);
	sf::Sprite tmp;
	tmp = _gui.getSprite(1);
	tmp.setTextureRect(sf::IntRect(0 % 16 * 16, 0 / 16 * 16, 16, 16));
	_gui.setSprite(1, tmp);

	_gui.createSprite(2, 0, 0, _textureAtlas.getSize().x * 25 / 16, _textureAtlas.getSize().y * 25 / 16, _textureAtlas);

	tmp = _gui.getSprite(2);
	tmp.setTextureRect(sf::IntRect(0 % 16 * 16, 0 / 16 * 16, 16, 16));
	_gui.setSprite(2, tmp);

	_gui.setColor(2, sf::Color(255, 255, 255, 64));

	_selectionText.setString(_blocks_names[_selectedBlock - 1]);


	// init music
	_buffer.loadFromFile("Resources/Sound/Sound.wav");
	_music.setBuffer(_buffer);
	_music.setLoop(true);

	//seting id to one
	_id = 10000000;

	//_physEnt.addRect(100000, 50, 50, 50, 50, true, Textures);

//generateChunk(0, 10, 50, 50);
//occlusion();
}


void Game::gameloop() {
	sf::Clock FpsClock;
	// textures
	srand(floor(time(NULL)*1000));
	// init the player
	_player.init(sf::Vector2f(_width /2 +rand()%5000-2500, _height / 2 - 300), _playerTexture, _physEnt._world);

	

	// generating chunks
	for (int i = -8; i < 8;i++) {

		_chunkBatch[i + 8] = Chunk(i * 16, -120, 16, 32, _textureAtlas, _physEnt._world);
	}


	//_gui.createSprite(1, 200, 200, 50, 50, test);

	// gameloop
	while (_window.isOpen())
	{
		// famerate
		float Framerate = 1.0f / FpsClock.getElapsedTime().asSeconds();

		FpsClock.restart();

		std::cout << Framerate << "\n";
		_player.move(sf::Vector2f(0, 0));
		//updating the world and entities 
		_player.update();
		_physEnt.updateAll();
		_physEnt.updateWorld();

		for (int i = 0;i < 16; i++) {
			for (auto& x : _chunkBatch[i].getDestroyList()) {
				_physEnt._world->DestroyBody(_chunkBatch[i].getBody(x.second));
				_chunkBatch[i].destroyEnt(x.second);

			}
			_chunkBatch[i].clearDestroyList();
		}

		//checking for inputs

		// setting the view and clear the screen
		_window.setView(_camera);

		input();

		_window.clear(_bgColor);
		//drawing all sprites
		for (int i = 0;i < 32; i++) {
			for (auto& x : _chunkBatch[i].getEntities()) {
				_window.draw(x.second.getSprite());
			}
		}

		_window.draw(_player.getSprite());

		for (auto& x : _physEnt.getSpriteBatch().getSprites()) {
			_window.draw(x.second);
		}


		for (auto& x : _gui.getSprites()) {
			_window.draw(x.second);
		}

		_window.draw(_selectionText);

		//displaying the window
		_window.display();
	}

}

void Game::input() {
	sf::Event event;
	sf::Sprite tmpsp;
	sf::Vector2f pos;
	if (_window.pollEvent(event)) {
		switch (event.type) {
			// looking for inputs
		case sf::Event::Closed:
			_window.close();
			break;

		case sf::Event::KeyPressed:
			_ioManager.pressKey(event.key.code);



			break;
		case sf::Event::KeyReleased:
			_ioManager.releaseKey(event.key.code);
			break;
		case sf::Event::MouseButtonPressed:
			_ioMouse.pressKey(event.mouseButton.button);

			if (_ioMouse.getKey(sf::Mouse::Button::Right)) {
				sf::Vector2f pos = _lastmousepos;
				pos = _window.mapPixelToCoords((sf::Vector2i)pos);

				int chunk = getChunk(pos);

				if (!_player.getEntity().getBody()->GetFixtureList()->TestPoint(b2Vec2(pos.x, pos.y))) {



					

							Block tmp;
							pos.x += 25 / 2;
							pos.y += 25 / 2;



							tmp.create(floor(pos.x / 25), floor(pos.y / 25), _blocks_id[_selectedBlock], _textureAtlas, _physEnt._world);


							_chunkBatch[chunk].insertBlock(tmp, _textureAtlas);
							if (_blocks_id[_selectedBlock] == 52) {
								int index;
								GESFML::Entity ent = _chunkBatch[chunk].getEntity(floor(pos.x / 25), floor(pos.y / 25), index);
								if (ent.getUserData() == 52) {
									_chunkBatch[chunk].setColor(index, sf::Color(0, 255, 0, 255));
								}
							}
							else {
								int index;
								GESFML::Entity ent = _chunkBatch[chunk].getEntity(floor(pos.x / 25), floor(pos.y / 25), index);
								if (ent.getUserData() == 52) {
									_chunkBatch[chunk].setColor(index, sf::Color(0, 255, 0, 255));
								}
							}

				}


			}

			if (_ioMouse.getKey(sf::Mouse::Button::Left)) {
				sf::Vector2f pos = _lastmousepos;
				pos = _window.mapPixelToCoords((sf::Vector2i)pos);

				int chunk = getChunk(pos);


				pos.x += 25 / 2;
				pos.y += 25 / 2;

				_chunkBatch[chunk].removeBlock(floor(pos.x / 25), floor(pos.y / 25));



				_player.update();
			}


			break;
		case sf::Event::MouseButtonReleased:
			_ioMouse.releaseKey(event.mouseButton.button);
			break;
		case sf::Event::MouseMoved:
			_lastmousepos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);

			pos = _lastmousepos;
			pos = _window.mapPixelToCoords((sf::Vector2i)pos);

			pos.x += 12.5;
			pos.y += 12.5;


			_gui.setPosition(2, floor(pos.x/25)*25-12.5, floor(pos.y/25)*25-12.5);

			break;

		default:
			break;
		}




	}
	// mouse


	//IO manaergers
	if (_ioManager.getKey(sf::Keyboard::A)) {

		sf::Vector2f pos = _player.getPosition() + sf::Vector2f(0, 23.02);

		int chunk = getChunk(pos);
		int index;

		pos.x += 25 / 2;
		pos.y += 25 / 2;

		if (_chunkBatch[chunk].getEntity(floor(pos.x / 25), floor(pos.y / 25), index).getSprite().getOrigin() != sf::Vector2f(0, 0)) {

				_player.getEntity().getBody()->SetLinearVelocity(b2Vec2(-70, _player.getEntity().getBody()->GetLinearVelocity().y));
				_player.getEntity().getBody()->SetLinearVelocity(b2Vec2(_player.getEntity().getBody()->GetLinearVelocity().x, _player.getEntity().getBody()->GetLinearVelocity().y - 1.1));

		}
		else {
			_player.move(sf::Vector2f(-2000, _player.getEntity().getBody()->GetLinearVelocity().y));
		}


	}else if (_ioManager.getKey(sf::Keyboard::D)) {

		sf::Vector2f pos = _player.getPosition() + sf::Vector2f(0, 23.02);

		int chunk = getChunk(pos);
		int index;

		pos.x += 25 / 2;
		pos.y += 25 / 2;

		if (_chunkBatch[chunk].getEntity(floor(pos.x / 25), floor(pos.y / 25), index).getSprite().getOrigin() != sf::Vector2f(0, 0)) {

				_player.getEntity().getBody()->SetLinearVelocity(b2Vec2(70, _player.getEntity().getBody()->GetLinearVelocity().y));
				_player.getEntity().getBody()->SetLinearVelocity(b2Vec2(_player.getEntity().getBody()->GetLinearVelocity().x, _player.getEntity().getBody()->GetLinearVelocity().y - 1.1));
		}
		else {
			_player.move(sf::Vector2f(2000, _player.getEntity().getBody()->GetLinearVelocity().y));
		}
		
	}
	else {
		sf::Vector2f pos = _player.getPosition() + sf::Vector2f(0, 23.02);

		int chunk = getChunk(pos);
		int index;

		pos.x += 25 / 2;
		pos.y += 25 / 2;
		

		if (_chunkBatch[chunk].getEntity(floor(pos.x / 25), floor(pos.y / 25), index).getSprite().getOrigin() != sf::Vector2f(0, 0)) {
			_player.getEntity().getBody()->SetLinearVelocity(b2Vec2(0, _player.getEntity().getBody()->GetLinearVelocity().y));
		}
	}
	if (_ioManager.getKey(sf::Keyboard::P)) {

		_music.play();
	}
	if (_ioManager.getKey(sf::Keyboard::O)) {
		_music.stop();
	}

	if (_ioManager.getKey(sf::Keyboard::Space)) {


			sf::Vector2f pos = _player.getPosition() + sf::Vector2f(0, 25);

			int chunk = getChunk(pos);
			int index;

			pos.x += 25 / 2;
			pos.y += 25 / 2;


			if (_chunkBatch[chunk].getEntity(floor(pos.x / 25), floor(pos.y / 25), index).getSprite().getOrigin() != sf::Vector2f(0, 0)) {
				_player.getEntity().getBody()->SetLinearVelocity(b2Vec2(_player.getEntity().getBody()->GetLinearVelocity().x, -70));
			}
		}

	if(_ioManager.getKey(sf::Keyboard::Num1))
	{
		_tmp++;
		
		if (_tmp == 1) {
			if (_selectedBlock == 1) {
				_selectedBlock = 62;
			}
			_selectedBlock--;
			_selectedBlock %= 62;

			_selectionText.setString(_blocks_names[_blocks_id[_selectedBlock]]);

			tmpsp = _gui.getSprite(1);
			tmpsp.setTextureRect(sf::IntRect(_blocks_id[_selectedBlock] % 16 * 16, _blocks_id[_selectedBlock] / 16 * 16, 16, 16));
			_gui.setSprite(1, tmpsp);


			tmpsp = _gui.getSprite(2);
			tmpsp.setTextureRect(sf::IntRect(_blocks_id[_selectedBlock] % 16 * 16, _blocks_id[_selectedBlock] / 16 * 16, 16, 16));
			_gui.setSprite(2, tmpsp);
		}
	
	}
	else 	if (_ioManager.getKey(sf::Keyboard::Num2))
	{
		_tmp++;

		if (_tmp == 1) {
			if(_selectedBlock == 61) {
				_selectedBlock = 0;
			}
			_selectedBlock++;
			_selectedBlock %= 62;

			_selectionText.setString(_blocks_names[_blocks_id[_selectedBlock]]);

			tmpsp = _gui.getSprite(1);
			tmpsp.setTextureRect(sf::IntRect(_blocks_id[_selectedBlock] % 16 * 16, _blocks_id[_selectedBlock] / 16 * 16, 16, 16));
			_gui.setSprite(1, tmpsp);

			tmpsp = _gui.getSprite(2);
			tmpsp.setTextureRect(sf::IntRect(_blocks_id[_selectedBlock] % 16 * 16, _blocks_id[_selectedBlock] / 16 * 16, 16, 16));
			_gui.setSprite(2, tmpsp);
		}

	}
	
	else{ _tmp = 0; }


	//calculating the pitch
	float pitch;
	pitch = (_player.getEntity().getBody()->GetLinearVelocity().x + _player.getEntity().getBody()->GetLinearVelocity().y);
	if (pitch < 0) {
		pitch*=-1;
	}

	//seting the pitch
	_music.setPitch(pitch / 100);
	_camera.setCenter(_player.getPosition());

	pos = sf::Vector2f(10,110);
	pos = _window.mapPixelToCoords((sf::Vector2i)pos);

	_selectionText.setPosition(pos);

	pos = sf::Vector2f(20, 20);
	pos = _window.mapPixelToCoords((sf::Vector2i)pos);

	_gui.setPosition(1, (float)pos.x,(float)pos.y);

}
/*
void Game::generateChunk(int x, int y, int w, int h)
{


	for (int y2 = y; y2 < h;y2++) {
		for (int x2 = x; x2 < w;x2++) {
			_id++;
			if (y2 == y) {
				_physEnt.addRect(_id, x2 * 50, y2 * 50, 50, 50, false, _grassTexture);
				srand(time(NULL) + _id);
				int rnd = rand() % 100;

				if (rnd > 50) {
					_physEnt.addRect(_id, x2 * 50, y2 * 50, 50, 50, false, _dirtTexture);
					_id++;
					_physEnt.addRect(_id, x2 * 50, (y2-1) * 50, 50, 50, false, _grassTexture);
					
					srand(time(NULL) + _id*5);
					int rnd = rand() % 60;

					if (rnd > 50) {
						
						_physEnt.addRect(_id, x2 * 50, (y2-1) * 50, 50, 50, false, _dirtTexture);
						_id++;
						_physEnt.addRect(_id, x2 * 50, (y2 - 2) * 50, 50, 50, false, _grassTexture);
					}


				}
			}
			else if(y2-y>1 || y2-y < 3){
				_physEnt.addRect(_id, x2 * 50, y2 * 50, 50, 50, false, _dirtTexture);
			}
			if(y2-y>3) {
				_physEnt.addRect(_id, x2 * 50, y2 * 50, 50, 50, false, _stoneTexture);

			}
			if (y2 - y == 3) {
				srand(time(NULL)+_id);
				int rnd = rand()%100;

				if (rnd > 50) {
					_physEnt.addRect(_id, x2 * 50, y2 * 50, 50, 50, false, _stoneTexture);
				}


			}

		}
	}
}

void Game::occlusion() {
	for (auto& x : _physEnt.getSpriteBatch().getSprites()) {
		sf::Vector2i tmp = _window.mapCoordsToPixel(_physEnt.getSpriteBatch().getPosition(x.first));
		int id = x.first;
		

		if (tmp.x < (0 - _physEnt.getSpriteBatch().getScaleInPixel(id).x)){
			_renderBatch.deleteSprite(id);
			continue;
		}else if (tmp.x > (_width + _physEnt.getSpriteBatch().getScaleInPixel(id).x)) {
			_renderBatch.deleteSprite(id);
			continue;
		}

		if (tmp.y < (0 - _physEnt.getSpriteBatch().getScaleInPixel(id).y)) {
			_renderBatch.deleteSprite(id);
			continue;
		}
		else if (tmp.y >(_height + _physEnt.getSpriteBatch().getScaleInPixel(id).y)) {
			_renderBatch.deleteSprite(id);
			continue;
		}

		_renderBatch.setSprite(x.first, _physEnt.getSpriteBatch().getSprite(id));

	}
	*/
//}

int Game::getChunk(sf::Vector2f pos) {
	//getting the chunk on the cursor
	pos.x += 25/2;
	pos.y += 25 / 2;
	for (auto &x : _chunkBatch){
		if (x.second.isInChunk(pos)) {
			return x.first;
		}
	}
	return -1;
}