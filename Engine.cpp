#include "Engine.h"
Engine::Engine()
{
    border.x = 700;
    border.y = 700;
    m_Window.create(VideoMode(border.x, border.y), "The Tanchiki");
   
    GameIm.loadFromFile("texturePac.png");
    GameIm.createMaskFromColor(Color(255, 0, 255));

    GameTex.loadFromImage(GameIm);

    GameSpr.setTexture(GameTex);
    GameSpr.setTextureRect(IntRect(520, 128, 495, 112));

    OverIm.loadFromFile("texturePac.png");
    OverIm.createMaskFromColor(Color(255, 0, 255));

    OverTex.loadFromImage(OverIm);

    OverSpr.setTexture(OverTex);
    OverSpr.setTextureRect(IntRect(520, 336, 495, 112));

    GameSpr.setPosition(100, 100);
    OverSpr.setPosition(100, 212 + 30);


    font.loadFromFile("DatcubBold.ttf");
    Text textN("dfgdgd", font);
    textN.setCharacterSize(30);
    textN.setStyle(Text::Bold);
    textN.setFillColor(Color::Yellow);
    text = textN;


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
        if (!GameOver)
        {
            sf::Event event;
            while (m_Window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    // Close window button clicked.
                    m_Window.close();
                }
            }
            // Перезапускаем таймер и записываем отмеренное время в dt
            Time dt = clock.restart();

            float dtAsSeconds = dt.asSeconds();

            update(dtAsSeconds);
            input();
            collision();
            draw();
        }
        else
        {
            input();
            draw();
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    m_Player.update(dtAsSeconds);

    for (int i = 0; i < Enemys.size(); i++)
        Enemys[i].update(dtAsSeconds,m_Player.m_Position, m_Player.size);

    EnemyTimer += dtAsSeconds;
    if (EnemyTimer >= spawnEnemyCooldown)
    {
        spawnEnemys();
        spawnEnemyCooldown = 0;
    }

    for (int i = 0; i < Explosions.size(); i++)
        Explosions[i].update(dtAsSeconds);
    if (m_Player.XP <= 0) GameOver = true;
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

    ostringstream playerHealthString, gameScoreString;    // объявили переменную здоровья и времени
    playerHealthString << m_Player.XP;
    gameScoreString << score;
    text.setString("Health: " + playerHealthString.str() + "\nScore: " + gameScoreString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()
    text.setPosition(150, 20);//задаем позицию текста, отступая от центра камеры
    m_Window.draw(text);//рисую этот текст

    if (GameOver)
    {
        m_Window.draw(GameSpr);
        m_Window.draw(OverSpr);
    }

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

        for (int j = 0; j < Enemys.size(); j++)
            if (isCollision(Enemys[j].Position, Enemys[j].size, bul.Position, bul.size))
            {
                flag = true;
                Explosion ex(Enemys[j].Position);
                Explosions.push_back(ex);
                for (int k = 0; k < Enemys.size(); k++)
                    if (Enemys[j].id == Enemys[k].id)
                        Enemys.erase(Enemys.begin() + j);
                score++;
            }

        if (flag)m_Player.Bullets.erase(m_Player.Bullets.begin() + i);
    }

    for (int i = 0; i < Enemys.size(); i++)
        for (int j = 0; j < Enemys[i].Bullets.size(); j++)
        {
            Bullet bul = Enemys[i].Bullets[j];
            bool flag = false;
            if (bul.Position.x + bul.size.x > border.x) flag = true;
            else if (bul.Position.y + bul.size.y > border.y) flag = true;
            else if (bul.Position.x < 0) flag = true;
            else if (bul.Position.y < 0) flag = true;

            if (isCollision(m_Player.m_Position, m_Player.size, bul.Position, bul.size))
            {
                Explosion ex(m_Player.m_Position);
                Explosions.push_back(ex);
                m_Player.XP -= bul.damage;
                flag = true;
            }

            if (flag)Enemys[i].Bullets.erase(Enemys[i].Bullets.begin() + j);
        }

    for (int i = 0; i < Enemys.size(); i++)
    {
        for (int k = i; k < Enemys.size(); k++)
            for (int j = 0; j < Enemys[i].Bullets.size(); j++)
            {
                Bullet bul = Enemys[i].Bullets[j];
                if (isCollision(Enemys[k].Position, Enemys[k].size, bul.Position, bul.size))
                {
                    Explosion ex(Enemys[k].Position);
                    Explosions.push_back(ex);
                    Enemys[i].Bullets.erase(Enemys[i].Bullets.begin() + j);
                    Enemys.erase(Enemys.begin() + k);
                }
            }

    }

    for(int i =0; i < Explosions.size();i++)
        if (Explosions[i].done) Explosions.erase(Explosions.begin() + i);
}