#include "Engine.h"
#include <math.h>
Engine::Engine()
{
    border.x = 700;
    border.y = 700;
    m_Window.create(VideoMode(border.x, border.y), "The Tanchiki");
   

    Player m_Player;
}

int selfRand(int Max)
{
    return rand() % Max;
}

bool condSpawn(Vector2f pos1, Vector2f pos2, double dest)
{
    double res;
    res = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
    if (res >= dest) return true; else false;
}

void Engine::spawnEnemys()
{
    if (Enemys.size() < enemysMax)
    {
        Vector2f pos;
        bool flag;
        do
        {
            flag = true;
            pos.x = selfRand(border.x - 60);
            pos.y = selfRand(border.y - 60);

            if (!condSpawn(m_Player.m_Position, pos, 85)) flag = false;
            for (int i = 0; i < Enemys.size(); i++)
                if (!condSpawn(Enemys[i].Position, pos, 85)) flag = false;
        } while (!flag);

        Enemy en(enemysCount, pos);
        enemysCount++;
        Enemys.push_back(en);
    }
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
        collision();
        draw();
    }
}

void Engine::update(float dtAsSeconds)
{
    m_Player.update(dtAsSeconds);


    for (int i = 0; i < Enemys.size(); i++)
        Enemys[i].update(dtAsSeconds);

    EnemyTimer += dtAsSeconds;
    if (EnemyTimer >= spawnEnemyCooldown)
    {
        spawnEnemys();
        spawnEnemyCooldown = 0;
    }

    for (int i = 0; i < Explosions.size(); i++)
        Explosions[i].update(dtAsSeconds);

}

void Engine::draw()
{
    // Стираем предыдущий кадр
    m_Window.clear();

    m_Player.draw(&m_Window);

    for (int i = 0; i < Enemys.size(); i++)
        Enemys[i].draw(&m_Window);

    for (int i = 0; i < Explosions.size(); i++)
        Explosions[i].draw(&m_Window);


    Image testImage;
    testImage.loadFromFile("texturePac.png");
    testImage.createMaskFromColor(Color(255, 0, 255));

    Texture testTexture;
    testTexture.loadFromImage(testImage);

    Sprite testSprite;
    testSprite.setTexture(testTexture);
    testSprite.setTextureRect(IntRect(512, 0, 64, 64));

    testSprite.setPosition(100,100);
    m_Window.draw(testSprite);


    m_Window.display();
}

bool isCollision(Vector2f pos1, Vector2f size1, Vector2f pos2, Vector2f size2)
{

    if ((pos1.y  > (pos2.y + size2.y)) || ((pos1.y + size1.y) < pos2.y) || ((pos1.x + size1.x) < pos2.x) || (pos1.x > (pos2.x + size2.x)))
        return false;
    else
        return true;
}

void Engine::collision()
{
    if (m_Player.m_Position.x + m_Player.size.x > border.x) m_Player.m_Position.x = border.x - m_Player.size.x;
    if (m_Player.m_Position.y + m_Player.size.y > border.y) m_Player.m_Position.y = border.y - m_Player.size.y;
    if (m_Player.m_Position.x < 0) m_Player.m_Position.x = 0;
    if (m_Player.m_Position.y < 0) m_Player.m_Position.y = 0;

    for (int i = 0; i < m_Player.Bullets.size(); i++)
    {
        Bullet bul = m_Player.Bullets[i];
        bool flag = false;
        if (bul.Position.x + bul.size.x > border.x) flag = true;
        else if (bul.Position.y + bul.size.y > border.y) flag = true;
        else if (bul.Position.x < 0) flag = true;
        else if (bul.Position.y < 0) flag = true;

        for (int i = 0; i < Enemys.size(); i++)
            if (isCollision(Enemys[i].Position, Enemys[i].size, bul.Position, bul.size))
            {
                flag = true;
                enemysCount++;
                Explosion ex(Enemys[i].Position);
                Explosions.push_back(ex);
                Enemys.erase(Enemys.begin() + i);
            }

        if (flag)m_Player.Bullets.erase(m_Player.Bullets.begin() + i);
    }

    for(int i =0; i < Explosions.size();i++)
        if (Explosions[i].done) Explosions.erase(Explosions.begin() + i);
}