#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;

class Engine
{
private:

    RenderWindow m_Window;

    Sprite MainSprite;
    Texture MainTexture;

    Image MainImage;

    Player m_Player;

    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    Engine();
    void start();
};
