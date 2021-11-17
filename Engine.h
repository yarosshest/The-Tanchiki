#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Explosion.h"
using namespace sf;

class Engine
{
private:

    RenderWindow m_Window;

    Sprite MainSprite;
    Texture MainTexture;
    Vector2f border;
    Image MainImage;

    Player m_Player;
    vector<Enemy> Enemys;
    vector<Explosion> Explosions;
    int ExplCount = 0;

    float EnemyTimer = 0;
    int spawnEnemyCooldown = 0.5;
    int enemysCount = 0;
    int enemysMax = 1;


    void spawnEnemys();
    void input();
    void update(float dtAsSeconds);
    void draw();
    void collision();

public:
    Engine();
    void start();
};
