#include "Engine.h"
int main()
{

    Engine engine;


    RenderWindow Window(sf::VideoMode(800, 800), "The Tanchiki");

    Clock clock;

    while (Window.isOpen())
    {
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();
        }
        // Перезапускаем таймер и записываем отмеренное время в dt
        Time dt = clock.restart();

        float dtAsSeconds = dt.asSeconds();

        engine.input();
        engine.update(dtAsSeconds);

        Window.clear();

        Window.draw(engine.m_Player.getSprite());

        Window.display();
    }
	return 0;
}