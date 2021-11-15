#include "Engine.h"

Engine::Engine()
{
    m_Window.create(VideoMode(800, 800), "The Tanchiki");
   

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
    if (Keyboard::isKeyPressed(Keyboard::Space))
        m_Player.Fire();
}


void Engine::start()
{
    // Расчет времени
    Clock clock;

    while (m_Window.isOpen())
    {
        // Перезапускаем таймер и записываем отмеренное время в dt
        Time dt = clock.restart();

        float dtAsSeconds = dt.asSeconds();

        update(dtAsSeconds);
        input();
        draw();
    }
}

void Engine::update(float dtAsSeconds)
{
    m_Player.update(dtAsSeconds);
}

void Engine::draw()
{
    // Стираем предыдущий кадр
    m_Window.clear();

    m_Player.draw(&m_Window);

    Image testImage;
    testImage.loadFromFile("texturePac.png");
    testImage.createMaskFromColor(Color(255, 0, 255));

    Texture testTexture;
    testTexture.loadFromImage(testImage);

    Sprite testSprite;
    testSprite.setTexture(testTexture);
    testSprite.setTextureRect(IntRect(193, 0, 12, 16));

    testSprite.setPosition(100, 100);

    m_Window.draw(testSprite);


    m_Window.display();
}