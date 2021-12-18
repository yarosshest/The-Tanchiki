#include "Player.h"
Player::Player()
{
    PlayerImage.loadFromFile("texturePac.png");
    PlayerImage.createMaskFromColor(Color(255, 0, 255));

    PlayerTexture.loadFromImage(PlayerImage);

    PlayerSprite.setTexture(PlayerTexture);
    PlayerSprite.setTextureRect(IntRect(4, 72, 51, 51));

    size.x = 51;
    size.y = 51;

    vectorMove.x = 0;
    vectorMove.y = 0;

    m_Position.x = 400;
    m_Position.y = 400;
}


void Player::moveLeft()
{
    vectorMove.x = -1;
    vectorMove.y = 0;
    orientation = "Left";
    PlayerSprite.setTextureRect(IntRect(392 + 64 * (int(CurrentFrame) / 1), 72, 52, 52));
}

void Player::moveRight()
{
    vectorMove.x = 1;
    vectorMove.y = 0;
    orientation = "Right";
    PlayerSprite.setTextureRect(IntRect(132 + 64 * (int(CurrentFrame) / 1), 72, 52, 52));
}

void Player::moveUp()
{
    vectorMove.x = 0;
    vectorMove.y = -1;
    orientation = "Up";
    PlayerSprite.setTextureRect(IntRect(4+64*(int(CurrentFrame)/1), 72, 52, 52));
}

void Player::moveDown()
{
    vectorMove.x = 0;
    vectorMove.y = 1;
    orientation = "Down";
    PlayerSprite.setTextureRect(IntRect(260 + 64 * (int(CurrentFrame) / 1), 72, 52, 52));
}

void Player::Fire()
{
    Vector2f b_Position;
    if (cooldown_timer >= cooldown)
    {
        if (orientation == "Up")
        {
            b_Position.x = m_Position.x + 20;
            b_Position.y = m_Position.y;
        }
        else if (orientation == "Down")
        {
            b_Position.x = m_Position.x + 20;
            b_Position.y = m_Position.y + 52;
        }
        else if (orientation == "Left")
        {
            b_Position.x = m_Position.x - 16;
            b_Position.y = m_Position.y + 20;
        }
        else if (orientation == "Right")
        {
            b_Position.x = m_Position.x + 52;
            b_Position.y = m_Position.y + 20;
        }


        Bullet bullet(orientation, b_Position, bulletCount);
        bulletCount++;
        Bullets.push_back(bullet);
        cooldown_timer = 0;
    }

}

void Player::draw(RenderWindow* win)
{
    PlayerSprite.setTexture(PlayerTexture);
    (*win).draw(PlayerSprite);
    for (int i = 0; i < Bullets.size(); i++)
         Bullets[i].draw(win);
}


bool isCollisionPlayer(Vector2f pos1, Vector2f size1, Vector2f pos2, Vector2f size2)
{

    if ((pos1.y > (pos2.y + size2.y)) || ((pos1.y + size1.y) < pos2.y) || ((pos1.x + size1.x) < pos2.x) || (pos1.x > (pos2.x + size2.x)))
        return false;
    else
        return true;
}

// Двигаем на основании пользовательского ввода в этом кадре,
// прошедшего времени и скорости
void Player::update(float elapsedTime, vector<Vector2f> posBord, vector<Vector2f> posSize)
{

    Vector2f predPos;
    bool move = true;
    predPos.x = m_Position.x + m_Speed * vectorMove.x * elapsedTime;
    predPos.y = m_Position.y + m_Speed * vectorMove.y * elapsedTime;
    for (int i = 0; i < posBord.size(); i++)
        if (isCollisionPlayer(predPos, size, posBord[i], posSize[i]))
            move = false;

    if (move)
        m_Position = predPos;

    vectorMove.x = 0;
    vectorMove.y = 0;

    for (int i = 0; i < Bullets.size(); i++)
        Bullets[i].update(elapsedTime);


    CurrentFrame += elapsedTime * animSpeed;
    if (CurrentFrame > 2) CurrentFrame = 0;

    if (cooldown_timer < cooldown) cooldown_timer += elapsedTime;

    PlayerSprite.setPosition(m_Position);

}