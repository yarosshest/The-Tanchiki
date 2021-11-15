#include "Bullet.h"


void Bullet::update(float elapsedTime)
{
    Position.x += speed * vector.x * elapsedTime;
    Position.y += speed * vector.y * elapsedTime;

    BulletSprite.setPosition(Position);
}

Bullet::Bullet(string orientation , Vector2f getPosition)
{
    BulletImage.loadFromFile("texturePac.png");
    BulletImage.createMaskFromColor(Color(255, 0, 255));

    BulletTexture.loadFromImage(BulletImage);

    BulletSprite.setTexture(BulletTexture);
    Position = getPosition;

    if (orientation == "Up")
    {
        BulletSprite.setTextureRect(IntRect(192, 0, 12, 16));
        vector.x = 0;
        vector.y = -1;
    }
    else if (orientation == "Down")
    {
        BulletSprite.setTextureRect(IntRect(192, 32, 12, 16));
        vector.x = 0;
        vector.y = 1;
    }
    else if (orientation == "Left")
    {
        BulletSprite.setTextureRect(IntRect(224, 0, 16, 12));
        vector.x = -1;
        vector.y = 0;
    }
    else if (orientation == "Right")
    {
        BulletSprite.setTextureRect(IntRect(224, 32, 16, 12));
        vector.x = 1;
        vector.y = 0;
    }


    BulletSprite.setPosition(Position);
}

void Bullet::draw(RenderWindow* win)
{
    //Без этого ломается спрайт
    BulletSprite.setTexture(BulletTexture);

    (*win).draw(BulletSprite);
}
