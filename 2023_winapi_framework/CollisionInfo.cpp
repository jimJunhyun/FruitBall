#include "pch.h"
#include "CollisionInfo.h"
#include "Collider.h"

CollisionInfo::CollisionInfo(Collider* left, Collider* right)
{
	lft = left;
	rht = right;
}

CollisionInfo::~CollisionInfo()
{
}

Vec2 CollisionInfo::GetCollideNormal(Collider* relativeTo)
{
	Vec2 pos = relativeTo->GetFinalPos();
	return (point - pos).Normalized();
}

