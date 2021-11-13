#include "Engine.h"
#include "Player.h"
Engine::Engine()
{
    Player m_Player;
}


void Engine::input()
{
    // Обрабатываем нажатие Escape
    if (Keyboard::isKeyPressed(Keyboard::Escape))
        m_Window.close();

    if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))))
        m_Player.moveLeft();
    if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) 
        m_Player.moveRight();
    if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) 
        m_Player.moveUp();
    if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))))
        m_Player.moveDown();
}

using namespace sf;

void Engine::update(float dtAsSeconds)
{
    m_Player.update(dtAsSeconds);
}