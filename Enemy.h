#pragma once
#include "vector"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Enemy
{
private:
    Vector2f vectorMove;
    string orientation;

    Image EnemyImage;
    Texture EnemyTexture;
    Sprite EnemySprite;

    int bulletCount = 0;

    float CurrentFrame = 0;
    int XP = 1;
    float Speed = 100;
    float animSpeed = 50;
    float cooldown = 0.5;
    float cooldown_timer = cooldown;
public:
    Vector2f Position;
    Vector2f size;
    vector<Bullet> Bullets;


	int id;
	Enemy(int getId, Vector2f pos);

    void draw(RenderWindow* win);

    void update(float elapsedTime);
};

