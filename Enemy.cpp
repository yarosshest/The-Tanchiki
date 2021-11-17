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
}

void Enemy::draw(RenderWindow* win)
{
    EnemySprite.setTexture(EnemyTexture);
    (*win).draw(EnemySprite);
    /*for (int i = 0; i < Bullets.size(); i++)
        Bullets[i].draw(win);*/
}

void Enemy::update(float elapsedTime)
{
    EnemySprite.setPosition(Position);
}
