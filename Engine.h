#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <sstream>
#include "Player.h"
#include "Enemy.h"
#include "Explosion.h"
using namespace sf;
using namespace std;
class Engine
{
private:

    RenderWindow m_Window;

    Sprite MainSprite;
    Texture MainTexture;
    Vector2f border;
    Image MainImage;


    Image GameIm;
    Sprite GameSpr;
    Texture GameTex;

    Image OverIm;
    Sprite OverSpr;
    Texture OverTex;

    Font font;
    Text text;

    Player m_Player;
    vector<Enemy> Enemys;
    vector<Explosion> Explosions;

    int ExplCount = 0;

    float EnemyTimer = 0;
    int spawnEnemyCooldown = 0.5;
    int enemysCount = 0;
    int enemysMax = 5;
    int score = 0;


    void spawnEnemys();
    void input();
    void update(float dtAsSeconds);
    void draw();
    void collision();

    bool GameOver = false;

public:
    Engine();
    void start();
};
