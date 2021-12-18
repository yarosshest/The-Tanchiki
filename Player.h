#pragma once
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "vector"

using namespace sf;
using namespace std;

class Player
{
private:

    // Позиция Player
    Vector2f vectorMove;
    string orientation;

    // Объявляем объект Sprite
    Image PlayerImage;
    Texture PlayerTexture;
    Sprite PlayerSprite;

    int bulletCount = 0;

    float CurrentFrame = 0;
    float m_Speed = 100;
    float animSpeed = 50;
    float cooldown = 0.5;
    float cooldown_timer = cooldown;

    // Открытые методы
public:
    Vector2f m_Position;
    Vector2f size;
    vector<Bullet> Bullets;
    int XP = 20;

    // Настраиваем Player в конструкторе
    Player();

    void moveLeft();

    void moveRight();

    void moveUp();

    void moveDown();

    void Fire();

    void draw(RenderWindow* win);

    // Эта функция будет вызываться на каждый кадр
    void update(float elapsedTime, vector<Vector2f> posBord, vector<Vector2f> posSize);

};