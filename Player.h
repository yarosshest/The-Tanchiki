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

    // ������� Player
    Vector2f m_Position;
    Vector2f vectorMove;
    string orientation;

    vector<Bullet> Bullets;

    // ��������� ������ Sprite
    Image PlayerImage;
    Texture PlayerTexture;
    Sprite PlayerSprite;

    float CurrentFrame = 0;
    int XP = 1;
    float m_Speed = 100;
    float animSpeed = 50;
    float cooldown = 0.5;
    float cooldown_timer = cooldown;

    // �������� ������
public:
    // ����������� Player � ������������
    Player();

    vector<Bullet>getBullets();

    void moveLeft();

    void moveRight();

    void moveUp();

    void moveDown();

    void Fire();

    void draw(RenderWindow* win);

    // ��� ������� ����� ���������� �� ������ ����
    void update(float elapsedTime);

};