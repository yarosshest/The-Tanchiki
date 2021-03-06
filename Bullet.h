#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;
class Bullet
{

private:
	Vector2f vector;


	Image BulletImage;
	Texture BulletTexture;
	Sprite BulletSprite;

	int speed = 120;

public:

	Vector2f Position;
	Vector2f size;
	int id;
	int damage = 1;
	Bullet(string orientation, Vector2f getPosition, int getId);
	void update(float elapsedTime);
	void draw(RenderWindow* win);
};

