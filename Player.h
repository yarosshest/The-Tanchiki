#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
    // ��� private ���������� ����� ���� �������� ������ ������ �������
private:

    // ������� Player
    Vector2f m_Position;

    // ��������� ������ Sprite
    Sprite PlayerSprite;

    // ��������� ��������
    Texture PlayerTexture;

    Image PlayerImage;

    float CurrentFrame;


    float animSpeed = 20;

    // ���������� ��� ������������ ����������� ��������
    int vector[2];

    // �������� ���� � �������� � �������
    float m_Speed;

    // �������� ������
public:

    // ����������� Player � ������������
    Player();

    // ��� �������� ������� � ������� �������
    Sprite getSprite();

    // ��� �������� ����
    void moveLeft();

    void moveRight();

    void moveUp();

    void moveDown();

    // ��� ������� ����� ���������� �� ������ ����
    void update(float elapsedTime);

};