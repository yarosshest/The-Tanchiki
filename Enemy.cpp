#include "Enemy.h"

Enemy::Enemy(int getId, Vector2f pos)
{
    id = getId;

    EnemyImage.loadFromFile("texturePac.png");
    EnemyImage.createMaskFromColor(Color(255, 0, 255));

    EnemyTexture.loadFromImage(EnemyImage);

    EnemySprite.setTexture(EnemyTexture);
    EnemySprite.setTextureRect(IntRect(4, 516, 52, 60));

    size.x = 52;
    size.y = 60;

    vectorMove.x = 0;
    vectorMove.y = 0;

    Position.x = pos.x;
    Position.y = pos.y;

    orientation = "Up";
}

void Enemy::draw(RenderWindow* win)
{
    EnemySprite.setTexture(EnemyTexture);
    (*win).draw(EnemySprite);
    for (int i = 0; i < Bullets.size(); i++)
        Bullets[i].draw(win);
}

void Enemy::Move()
{
    if (orientation == "Up")
    {
        vectorMove.x = 0;
        vectorMove.y = -1;
        EnemySprite.setTextureRect(IntRect(4 + 64 * (int(CurrentFrame) / 1), 516, 52, 60));
    }
    else if (orientation == "Down")
    {
        vectorMove.x = 0;
        vectorMove.y = 1;
        EnemySprite.setTextureRect(IntRect(260 + 64 * (int(CurrentFrame) / 1), 512, 52, 60));
    }
    else if (orientation == "Left")
    {
        vectorMove.x = -1;
        vectorMove.y = 0;
        EnemySprite.setTextureRect(IntRect(388 + 64 * (int(CurrentFrame) / 1), 520, 60, 52));
    }
    else if (orientation == "Right")
    {
        vectorMove.x = 1;
        vectorMove.y = 0;
        EnemySprite.setTextureRect(IntRect(129 + 64 * (int(CurrentFrame) / 1), 520, 60, 52));
    }
}

void Enemy::turn(Vector2f posP, Vector2f sizeP)
{
    if(abs(posP.x - Position.x) < abs(posP.y - Position.y))
        if (posP.y < Position.y)
        {
            orientation = "Up";
            size.x = 52;
            size.y = 60;
            EnemySprite.setTextureRect(IntRect(4 + 64 * (int(CurrentFrame) / 1), 516, 52, 60));
        }
        else
        {
            orientation = "Down";
            size.x = 52;
            size.y = 60;
            EnemySprite.setTextureRect(IntRect(260 + 64 * (int(CurrentFrame) / 1), 512, 52, 60));
        }
    else
        if (posP.x < Position.x)
        {
            orientation = "Left";
            size.x = 60;
            size.y = 52;
            EnemySprite.setTextureRect(IntRect(388 + 64 * (int(CurrentFrame) / 1), 520, 60, 52));
        }
        else
        {
            orientation = "Right";
            size.x = 60;
            size.y = 52;
            EnemySprite.setTextureRect(IntRect(129 + 64 * (int(CurrentFrame) / 1), 520, 60, 52));
        }
}



void Enemy::update(float elapsedTime , Vector2f posP, Vector2f sizeP)
{
    Move();
    Position.x += Speed * vectorMove.x * elapsedTime;
    Position.y += Speed * vectorMove.y * elapsedTime;

    EnemySprite.setPosition(Position);
    CurrentFrame += elapsedTime * animSpeed;
    if (CurrentFrame > 2) CurrentFrame = 0;
    if (cooldown_timer < cooldown) cooldown_timer += elapsedTime;
    if (cooldown_timer >= cooldown) Fire(posP, sizeP);

    for (int i = 0; i < Bullets.size(); i++)
        Bullets[i].update(elapsedTime);

    turn(posP, sizeP);
}






void Enemy::Fire(Vector2f posP, Vector2f sizeP)
{
    if ((orientation == "Up")&&(Position.y > posP.y)&&((Position.x+size.x /2)<=(posP.x+ sizeP.x)) && ((Position.x + size.x / 2) >= posP.x))
    {
        Vector2f b_Position;
        b_Position.x = Position.x + 20;
        b_Position.y = Position.y- 16;
        Bullet bullet(orientation, b_Position, bulletCount);
        bulletCount++;
        Bullets.push_back(bullet);
        cooldown_timer = 0;
    }
    else if ((orientation == "Down") && (Position.y < posP.y) && ((Position.x + size.x / 2) <= (posP.x + sizeP.x)) && ((Position.x + size.x / 2) >= posP.x))
    {
        Vector2f b_Position;
        b_Position.x = Position.x + 20;
        b_Position.y = Position.y + size.y;
        Bullet bullet(orientation, b_Position, bulletCount);
        bulletCount++;
        Bullets.push_back(bullet);
        cooldown_timer = 0;
    }
    else if ((orientation == "Left") && (Position.x > posP.x) && ((Position.y + size.y / 2) <= (posP.y + sizeP.y)) && ((Position.y + size.y / 2) >= posP.y))
    {
        Vector2f b_Position;
        b_Position.x = Position.x - 16;
        b_Position.y = Position.y + 20;
        Bullet bullet(orientation, b_Position, bulletCount);
        bulletCount++;
        Bullets.push_back(bullet);
        cooldown_timer = 0;
    }
    else if ((orientation == "Right") && (Position.x < posP.x) && ((Position.y + size.y / 2) <= (posP.y + sizeP.y)) && ((Position.y + size.y / 2) >= posP.y))
    {
        Vector2f b_Position;
        b_Position.x = Position.x + size.x;
        b_Position.y = Position.y + 20;
        Bullet bullet(orientation, b_Position, bulletCount);
        bulletCount++;
        Bullets.push_back(bullet);
        cooldown_timer = 0;
    }
}
