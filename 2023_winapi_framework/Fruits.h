#pragma once
#include "Object.h"
class Texture;
class Fruits :
	public Object
{
public:
	Fruits(FRUITS type, float scale = 0.3f, Scene* level = nullptr) : Object(level)
	{
		Init(type, scale);
	}
	~Fruits();

	void Init(FRUITS type, float scale = 0.3f);


	void Update() override;
	void Render(HDC _dc) override;

	virtual void EnterCollision(Collider* _pOther, std::shared_ptr<CollisionInfo> info) override;
	virtual void ExitCollision(Collider* _pOther) override;

public:
	
	const FRUITS& GetType() const { return fruitMode; }

private:

	FRUITS fruitMode;

	Texture* myTexture;

	float lifeTime;
};

