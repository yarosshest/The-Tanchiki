#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
    // Все private переменные могут быть доступны только внутри объекта
private:

    // Позиция Player
    Vector2f m_Position;

    // Объявляем объект Sprite
    Sprite PlayerSprite;

    // Добавляем текстуру
    Texture PlayerTexture;

    Image PlayerImage;

    float CurrentFrame;


    float animSpeed = 20;

    // переменные для отслеживания направления движения
    int vector[2];

    // Скорость Боба в пикселях в секунду
    float m_Speed;

    // Открытые методы
public:

    // Настраиваем Player в конструкторе
    Player();

    // Для отправки спрайта в главную функцию
    Sprite getSprite();

    // Для движения Боба
    void moveLeft();

    void moveRight();

    void moveUp();

    void moveDown();

    // Эта функция будет вызываться на каждый кадр
    void update(float elapsedTime);

};