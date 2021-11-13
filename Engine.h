#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;

class Engine
{
private:

    RenderWindow m_Window;

    // ��������� ������ � �������� ��� ����
    Sprite m_BackgroundSprite;
    Texture m_BackgroundTexture;

public:
    // ����������� ������
    Player m_Player;
    void input();
    void update(float dtAsSeconds);
    Engine();

};
