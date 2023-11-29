#pragma once

class Collider;
class CollisionInfo
{
public:
	CollisionInfo(Collider* left, Collider* right);
	~CollisionInfo();

public:
	const Collider* GetLeftCol() const { return lft; }
	const Collider* GetRightCol() const { return rht; }

	const Vec2 GetCollidePoint() const { return point; }
	const Vec2 GetCollideNormal(Collider* relativeTo);

	void SetPos(Vec2 val) { point = val; }
private:
	Collider* lft;
	Collider* rht;

	Vec2 point;
};

