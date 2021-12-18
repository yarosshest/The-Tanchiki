#pragma once
#include "vector"
#include "Bullet.h"
#include <math.h>
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
    float m_Speed = 15;
    float animSpeed = 10;
    float cooldown = 2;
    float cooldown_timer = cooldown;
public:
    Vector2f Position;
    Vector2f size;
    vector<Bullet> Bullets;


	int id;
	Enemy(int getId, Vector2f pos);

    void draw(RenderWindow* win);

    void Move();

    void turn(Vector2f posP, Vector2f sizeP);

    void update(float elapsedTime, Vector2f posP, Vector2f sizeP, vector<Vector2f> posBord, vector<Vector2f> posSize);

    void Fire(Vector2f posP, Vector2f sizeP);
};

