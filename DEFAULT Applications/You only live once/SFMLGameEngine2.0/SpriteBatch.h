#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "HelperFunctions.h"
#include "Window.h"
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include "ContactListener.h"


namespace GESFML
{

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void initWorld(b2Vec2 gravity, int iterations, int timestepfps, bool doSleep);
		void createSprite(long long id, float x, float y, float w, float h, const sf::Texture &texture, sf::Color color, float rotation = 0);
		void createPhysicSpriteBox(long long id, float x, float y, float w, float h, bool dynamic, float density, float friction, float bounce, const sf::Texture &texture, sf::Color color, float rotation = 0);
		void createPhysicSpriteCircle(long long id, float x, float y, float diameter, bool dynamic, float density, float friction, float bounce, const sf::Texture &texture, sf::Color color);
		//void createPhysicSpriteFixtureBoxAddToBody(long long id, float localx, float localy, float w, float h, float density, float friction, float bounce, const sf::Texture &texture, sf::Color color, float rotation = 0);
		//void createPhysicSpriteFixtureCircleAddToBody(long long id, float localx, float localy, float diameter, float density, float friction, float bounce, const sf::Texture &texture, sf::Color color);
		void createSpriteShadow(long long id, float shadowOffsetX, float shadowOffsetY, int alpha);
		void createPhysicSpriteShadow(long long id, float shadowOffsetX, float shadowOffsetY, int alpha);
		void createRevoluteJoint(long long firstBodyid, long long secondBodyid, b2Vec2 localAnchorA, b2Vec2 localAnchorB, bool collideConnected, float baseangle);
		void createRevoluteJointAngLimit(long long firstBodyid, long long secondBodyid, b2Vec2 localAnchorA, b2Vec2 localAnchorB, bool collideConnected, float baseangle, float upperAngleLimit, float lowerAngleLimit);
		void createRevoluteJointMotor(long long firstBodyid, long long secondBodyid, b2Vec2 localAnchorA, b2Vec2 localAnchorB, bool collideConnected, float baseangle, float MotorSpeed, float MaxMotorRotationSpeed);
		void deleteSprite(long long id);
		void deleteShadow(long long id);
		void deletePhysicSprite(long long id);
		void deletePhysicShadow(long long id);
		void deletePhysicSpriteRevoluteJoint(long long id);
		void drawPhysicSprites(Window &window);
		void drawShadowSprites(Window &window);
		void drawSprites(Window &window);
		void drawSprite(long long id, Window &window);
		void drawPhysicSprite(long long id, Window &window);
		void drawShadowSprite(long long id, Window &window);
		void drawAllFast(Window &window, bool spriteOnFront = false);
		void drawAll(Window &window);
		void setSpriteColor(long long id, sf::Color color = sf::Color());
		void setSpritePosition(long long id, float x, float y);
		void setSpritePosition(long long id, sf::Vector2f pos);
		void addSpritePosition(long long id, sf::Vector2f pos);
		void setSpriteScale(long long id, float xScale, float yScale);
		void setSpriteSize(long long id, float w, float h);
		void setSpriteSize(long long id, sf::Vector2f size);
		void setSpriteTexture(long long id, const sf::Texture &texture);
		void setSpriteRotation(long long id, float rotation = 0);
		void addSpriteRotation(long long id, float rotation = 0);
		void setSpriteShadowOffset(long long id, float offsetX, float offsetY);
		void setSpriteShadowColor(long long id, sf::Color color);
		void setSpriteShadowTexture(long long id, const sf::Texture &texture);
		void setSpriteOrigin(long long id, sf::Vector2f origin);
		void setSpriteOriginMiddle(long long id);
		void restoreSpriteShadowTexture(long long id);
		//void swapSprites(long long idfrom, long long idto);
		//void replaceSprites(long long idfrom, long long idto);
		void setSpriteUserDataNum(long long id, long double data);
		void setSpriteUserDataStr(long long id, std::string data);
		void setSpriteUserDataStr2(long long id, std::string data);
		void deleteSpriteUserDataNum(long long id);
		void deleteSpriteUserDataStr(long long id);
		void deleteSpriteUserDataStr2(long long id);
		sf::Color getSpriteColor(long long id);
		sf::Vector2f getSpritePosition(long long id);
		sf::Vector2f getSpriteScale(long long id);
		sf::Vector2f getSpriteSize(long long id);
		const sf::Texture *getSpriteTexture(long long id);
		sf::Sprite &getSprite(long long id);
		sf::Sprite &getShadowSprite(long long id);
		float getSpriteRotation(long long id);
		sf::Vector2f getSpriteOrigin(long long id);
		sf::Color getSpriteShadowColor(long long id);
		const sf::Texture *getSpriteShadowTexture(long long id);
		long double getSpriteUserDataNum(long long id);
		std::string getSpriteUserDataStr(long long id);
		std::string getSpriteUserDataStr2(long long id);
		long long getSpriteCountUserDataNum(long double data);
		long long getSpriteCountUserDataStr(std::string data);
		long long getSpriteCountUserDataStr2(std::string data);
		bool isExistingSprite(long long id);
		///order 0 = on bottom;
		///order 1 = ontop of bottom but behind physic sprites;
		///order 2 = ontop of physic sprites but behind on top;
		///order 3 = on top;
		///order >3 = dont draw;
		void setSpriteDrawOrder(long long id, int order);
		int getSpriteDrawOrder(long long id);
		bool testPointSprite(long long id, float x, float y);
		long long textPointSpriteId(long long id, float x, float y);
		//---------------------------------------------------------------
		void createText(long long id, float x, float y, float wScale, float hScale, float characterSize, sf::Font &font, std::string text, sf::Color color, float rotation = 0);
		void setText(long long id, std::string text);
		void setTextStyle(long long id, sf::Uint32 style);
		void setTextPosition(long long id, sf::Vector2f pos);
		void setTextRotaion(long long id, float rotation);
		void setTextScale(long long id, sf::Vector2f scale);
		void setTextFont(long long id, sf::Font &font);
		void setTextCharacterSize(long long id, float size);
		void addTextPosition(long long id, sf::Vector2f pos);
		void setTextColor(long long id, sf::Color color);
		void setTextOrigin(long long id, sf::Vector2f origin);
		sf::Vector2f getTextPosition(long long id);
		sf::Text &getText(long long id);
		sf::Vector2f getTextOrigin(long long id);
		sf::Color getTextColor(long long id);
		float getTextCharacterSize(long long id);
		sf::Vector2f getTextScale(long long id);
		float getTextRotation(long long id);
		sf::Uint32 getTextStyle(long long id);
		std::string getTextString(long long id);
		const sf::Font *getTextFont(long long id);
		///order 0 = on bottom;
		///order 1 = ontop of bottom but behind physic sprites;
		///order 2 = ontop of physic sprites but behind on top;
		///order 3 = on top;
		///order >3 = dont draw;
		void setTextDrawOrder(long long id, int order);
		int getTextDrawOrder(long long id);
		//---------------------------------------------------------------
		void setPhysicSpriteColor(long long id, sf::Color color = sf::Color());
		void setPhysicSpritePosition(long long id, float x, float y);
		void setPhysicSpritePosition(long long id, sf::Vector2f pos);
		void setPhysicSpritePosition(long long id, b2Vec2 pos);
		void addPhysicSpritePosition(long long id, sf::Vector2f pos);
		void setPhysicSpriteSizeBox(long long id, float w, float h);
		void setPhysicSpriteSizeCircle(long long id, float diameter);
		void setPhysicSpriteTexture(long long id, const sf::Texture &texture);
		void setPhysicSpriteOrigin(long long id, sf::Vector2f origin);
		void setPhysicSpriteOriginMiddle(long long id);
		void setPhysicSpriteRotation(long long id, float rotation = 0);
		void addPhysicSpriteRotation(long long id, float rotation = 0);
		void setPhysicSpriteShadowOffset(long long id, float offsetX, float offsetY);
		void setPhysicSpriteShadowColor(long long id, sf::Color color);
		void setPhysicSpriteShadowTexture(long long id, const sf::Texture &texture);
		void restorePhysicSpriteShadowTexture(long long id);
		//void swapPhysicSprites(long long idfrom, long long idto);
		//void replacePhysicSprites(long long idfrom, long long idto);
		void setPhysicSpriteUserDataNum(long long id, long double data);
		void setPhysicSpriteUserDataStr(long long id, std::string data);
		void setPhysicSpriteUserDataStr2(long long id, std::string data);
		void deletePhysicSpriteUserDataNum(long long id);
		void deletePhysicSpriteUserDataStr(long long id);
		void deletePhysicSpriteUserDataStr2(long long id);
		sf::Color getPhysicSpriteColor(long long id);
		sf::Vector2f getPhysicSpritePosition(long long id);
		sf::Vector2f getPhysicSpriteScale(long long id);
		sf::Vector2f getPhysicSpriteSize(long long id);
		const sf::Texture *getPhysicSpriteTexture(long long id);
		float getPhysicSpriteRotation(long long id);
		sf::Color getPhysicSpriteShadowColor(long long id);
		const sf::Texture *getPhysicSpriteShadowTexture(long long id);
		sf::Vector2f getPhysicSpriteOrigin(long long id);
		long double getPhysicSpriteUserDataNum(long long id);
		std::string getPhysicSpriteUserDataStr(long long id);
		std::string getPhysicSpriteUserDataStr2(long long id);
		b2Vec2 getPhysicSpriteVelocity(long long id);
		float getPhysicSpriteAngVelocity(long long id);
		b2Body *getPhysicSpriteBody(long long id);
		sf::Sprite &getPhysicSprite(long long id);
		sf::Sprite &getPhyiscShadowSprite(long long id);
		long long getPhysicSpriteCountUserDataNum(long double data);
		long long getPhysicSpriteCountUserDataStr(std::string data);
		long long getPhysicSpriteCountUserDataStr2(std::string data);
		void freezePhysicSprite(long long id, bool freezed);
		bool isCollidingPhysicSprite(long long id);
		bool isCollidingPhysicSpriteExceptIds(long long id,std::vector<long long> idsToExcept);
		bool isCollidingPhysicSpriteExceptUserDataNum(long long id, std::vector<long double> dataToExcept);
		bool isCollidingPhysicSpriteExceptUserDataStr(long long id, std::vector<std::string> dataToExcept);
		bool isCollidingPhysicSpriteExceptUserDataStr2(long long id, std::vector<std::string> dataToExcept);
		long long isCollidingPhysicSpriteExceptIdsCount(long long id, std::vector<long long> idsToExcept);
		long long isCollidingPhysicSpriteExceptUserDataNumCount(long long id, std::vector<long double> dataToExcept);
		long long isCollidingPhysicSpriteExceptUserDataStrCount(long long id, std::vector<std::string> dataToExcept);
		long long isCollidingPhysicSpriteExceptUserDataStr2Count(long long id, std::vector<std::string> dataToExcept);
		std::vector<long long> getAllCollidersIdPhysicSprite(long long id);
		bool isCollidingWithPhysicSprite(long long id, long long collidingId);
		bool testPointPhysicSprite(float x, float y);
		long long testPointIdPhyiscSprite(float x, float y);
		void setPhysicSpriteVelocity(long long id, b2Vec2 velocity);
		void setPhysicSpriteAngularVelocity(long long id, float angVelocity);
		void addPhysicSpriteVelocity(long long id, b2Vec2 velocity);
		void addPhysicSpriteAngularVelocity(long long id, float angVelocity);
		void setPhysicSpriteFriction(long long id, float friction);
		void setPhysicSpriteDensity(long long id, float density);
		void setPhysicSpriteMass(long long id, float mass);
		void setPhysicSpriteBounce(long long id, float bounce);
		void updatePhysicSprite(long long id);
		void updateAllPhysicSprites();
		void worldStep();
		bool isPhysicSpriteDynamic(long long id);
		bool getPhysicSpriteShapeType(long long id);
		void applyForcePhysicSprite(long long id, b2Vec2 direction, b2Vec2 point);
		void applyImpusePhysicSprite(long long id, b2Vec2 direction, b2Vec2 point);
		void applyAngularForcePhysicSprite(long long id, float force);
		void applyAngularImpusePhysicSprite(long long id, float impule);
		b2Vec2 getPhysicSpriteWorldPoint(long long id, b2Vec2 localPoint);
		b2Vec2 getPhysicSpriteLocalPoint(long long id, b2Vec2 worldPoint);
		bool isExistingPhysicSprite(long long id);
		void setSensorPhysicSprite(long long id, bool sensor);
		std::map<long long, sf::Sprite>& getSpriteShadowBatch();
		std::map<long long, sf::Sprite>& getSpriteBatch();
		std::map<long long, sf::Sprite>& getPhysicSpriteShadowBatch();
		std::map<long long, sf::Sprite>& getPhysicSpriteBatch();
		std::unordered_map<long long, b2Body*>& getBodyBatch();
		std::unordered_map<long long, b2RevoluteJoint*>& getRevoluteJointBatch();
		std::unordered_map<long long, bool>& getPhysicSpriteShapeTypes();
		std::unordered_map<long long, std::vector<long long>>& getPhysicSpriteCollisionIdsBatch();
		b2World *getWorld();

	private:
		std::map<long long, sf::Sprite> _shadowBatch;
		std::map<long long, sf::Sprite> _physicShadowBatch;
		std::unordered_map<long long, sf::Vector2f> _shadowOffsets;
		std::unordered_map<long long, sf::Vector2f> _physicShadowOffsets;
		std::map<long long, sf::Sprite> _spriteBatch;
		std::map<long long, sf::Sprite> _physicSpriteBatch;
		std::unordered_map<long long, b2Body*> _bodyBatch;
		std::unordered_map<long long, std::vector<long long>> _collisionIds;
		std::unordered_map<long long, b2RevoluteJoint*> _revoluteJointBatch;
		std::unordered_map<long long, long long> _revoluteJointData;
		std::unordered_map<long long, long double> _spriteUserDataNum;
		std::unordered_map<long long, std::string > _spriteUserDataString;
		std::unordered_map<long long, std::string> _spriteUserDataString2;
		std::unordered_map<long long, long double> _physicSpriteUserDataNum;
		std::unordered_map<long long, std::string > _physicSpriteUserDataString;
		std::unordered_map<long long, std::string> _physicSpriteUserDataString2;
		std::unordered_map<long long, bool> _physicSpriteShapeType;
		std::unordered_map<long long, int> _drawOrder;
		std::unordered_map<long long, int> _drawOrderText;
		std::map<long long, sf::Text> _textBatch;
		

		HelperFunctions _helperFunc;
		ContactListener *_contactInstance;
		b2World* _world;
		b2Vec2 _gravity = b2Vec2(0, 9.8f);
		float _size = 30;
		bool _doSleep = true;
		int _iterations = 10;
		float _timestep = 1.0f / 60.0f;


	};


}

