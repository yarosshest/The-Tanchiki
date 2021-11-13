#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
Player::Player()
{
    // Вписываем в переменную скорость 
    m_Speed = 100;
    CurrentFrame = 0;

    PlayerImage.loadFromFile("texturePac.png");
    PlayerImage.createMaskFromColor(Color(255, 0, 255));

    PlayerTexture.loadFromImage(PlayerImage);//передаем в него объект Image (изображения)

    PlayerSprite.setTexture(PlayerTexture);//передаём в него объект Texture (текстуры)
    PlayerSprite.setTextureRect(IntRect(4, 72, 51, 51));
    PlayerSprite.setPosition(50, 25);//задаем начальные координаты появления спрайта

    int vec_null[2] = { 0,0 };
    memcpy(&vector, &vec_null, sizeof(vec_null));
    // Устанавливаем начальную позицию Боба в пикселях
    m_Position.x = 100;
    m_Position.y = 100;

} 

// Делаем приватный спрайт доступным для функции draw()
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


// Двигаем на основании пользовательского ввода в этом кадре,
// прошедшего времени и скорости
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
    // Теперь сдвигаем спрайт на новую позицию
    PlayerSprite.setPosition(m_Position);

}