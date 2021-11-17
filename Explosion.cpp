#include "Explosion.h"

Explosion::Explosion(Vector2f getPos)
{
	Position.x = getPos.x;
	Position.y = getPos.y;

    ExplImage.loadFromFile("texturePac.png");
    ExplImage.createMaskFromColor(Color(255, 0, 255));

    ExplTexture.loadFromImage(ExplImage);

    ExplSprite.setTexture(ExplTexture);
    ExplSprite.setTextureRect(IntRect(512, 0, 64, 64));

    ExplSprite.setPosition(Position);
}

void Explosion::draw(RenderWindow* win)
{
    ExplSprite.setTexture(ExplTexture);
    (*win).draw(ExplSprite);
}

void Explosion::update(float elapsedTime)
{
    CurrentFrame += elapsedTime * animSpeed;
    if (CurrentFrame > 3) done = true;

    ExplSprite.setTextureRect(IntRect(512 + 64 * (int(CurrentFrame) / 1), 0, 64, 64));

    ExplSprite.setPosition(Position);
}
