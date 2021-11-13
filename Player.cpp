#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
Player::Player()
{
    // ��������� � ���������� �������� 
    m_Speed = 100;
    CurrentFrame = 0;

    PlayerImage.loadFromFile("texturePac.png");
    PlayerImage.createMaskFromColor(Color(255, 0, 255));

    PlayerTexture.loadFromImage(PlayerImage);//�������� � ���� ������ Image (�����������)

    PlayerSprite.setTexture(PlayerTexture);//������� � ���� ������ Texture (��������)
    PlayerSprite.setTextureRect(IntRect(4, 72, 51, 51));
    PlayerSprite.setPosition(50, 25);//������ ��������� ���������� ��������� �������

    int vec_null[2] = { 0,0 };
    memcpy(&vector, &vec_null, sizeof(vec_null));
    // ������������� ��������� ������� ���� � ��������
    m_Position.x = 100;
    m_Position.y = 100;

} 

// ������ ��������� ������ ��������� ��� ������� draw()
Sprite Player::getSprite()
{
    return PlayerSprite;
}

void Player::moveLeft()
{
    int vec_null[2] = { -1,0};
    memcpy(&vector, &vec_null, sizeof(vec_null));
    PlayerSprite.setTextureRect(IntRect(392 + 64 * (int(CurrentFrame) / 1), 72, 52, 52));
}

void Player::moveRight()
{
    int vec_null[2] = { 1,0};
    memcpy(&vector, &vec_null, sizeof(vec_null));
    PlayerSprite.setTextureRect(IntRect(132 + 64 * (int(CurrentFrame) / 1), 72, 52, 52));
}

void Player::moveUp()
{
    int vec_null[2] = { 0,-1 };
    memcpy(&vector, &vec_null, sizeof(vec_null));
    PlayerSprite.setTextureRect(IntRect(4+64*(int(CurrentFrame)/1), 72, 52, 52));
}

void Player::moveDown()
{
    int vec_null[2] = { 0,1 };
    memcpy(&vector, &vec_null, sizeof(vec_null));
    PlayerSprite.setTextureRect(IntRect(260 + 64 * (int(CurrentFrame) / 1), 72, 52, 52));
}


// ������� �� ��������� ����������������� ����� � ���� �����,
// ���������� ������� � ��������
void Player::update(float elapsedTime)
{
    if (vector[0] != 0)
        m_Position.x += m_Speed * vector[0] * elapsedTime;
    else
        m_Position.y += m_Speed * vector[1] * elapsedTime;
    int vec_null[2] = { 0,0 };
    memcpy(&vector, &vec_null, sizeof(vec_null));
    if (CurrentFrame > 2) CurrentFrame -= 2;
    CurrentFrame += elapsedTime* animSpeed;
    // ������ �������� ������ �� ����� �������
    PlayerSprite.setPosition(m_Position);

}