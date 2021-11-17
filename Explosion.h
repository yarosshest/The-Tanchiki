#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Explosion
{
private:

	Image ExplImage;
	Texture ExplTexture;
	Sprite ExplSprite;

	float CurrentFrame = 0;
	float m_Speed = 100;
	float animSpeed = 5;
public:
	bool done = false;
	Vector2f Position;
	int id;

	Explosion(Vector2f getPos);
	void draw(RenderWindow* win);
	void update(float elapsedTime);
};