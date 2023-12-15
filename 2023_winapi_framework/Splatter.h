#pragma once
#include "Object.h"

class Texture;
class Scene;

class Splatter
	: public Object
{
public:
	Splatter(Scene* level);
	~Splatter();

	void Update() override;
	void Render(HDC dc) override;

private:
	Vec2 initScale;
	float curScale;
	float lifetime;
	float shrinkStartTime = 0.1f;
	Texture* myTex;
};

