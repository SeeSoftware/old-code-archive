#pragma once

#include "Human.h"
#include <GE2D/InputManager.h>
#include <GE2D/Camera2D.h>
#include "Bullet.h"

class Gun;

class Player : public Human
{
public:
    Player();
    ~Player();

    void init(float speed, glm::vec2 pos, GE2D::InputManager* inputManager, GE2D::Camera2D* camera, std::vector<Bullet>* bullets);

    void addGun(Gun* gun);

    void update(const std::vector<std::string>& levelData,
                std::vector<Human*>& humans,
                std::vector<Zombie*>& zombies) override;
private:
	GE2D::InputManager* _inputManager;

    std::vector<Gun*> _guns;
    int _currentGunIndex;

	GE2D::Camera2D* _camera;
    std::vector<Bullet>* _bullets;

};

