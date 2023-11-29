#pragma once
#include "Object.h"
class Texture;
class Fruits :
	public Object
{
public:
	Fruits(bool rottenMode, FRUITS type, float scale = 0.3f);
	~Fruits();

	void Init(bool rottenMode, FRUITS type, float scale = 0.3f);


	void Update() override;
	void Render(HDC _dc) override;

	virtual void EnterCollision(Collider* _pOther, CollisionInfo* info) override;
	virtual void ExitCollision(Collider* _pOther) override;

public:
	

private:
	bool rotten = false;

	FRUITS fruitMode;

	Texture* myTexture;


};

