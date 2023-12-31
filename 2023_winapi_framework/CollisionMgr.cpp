#include "pch.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "Object.h"
#include "Scene.h"
#include "Collider.h"
#include "CollisionInfo.h"
void CollisionMgr::Update()
{
	for (UINT Row = 0; Row < (UINT)OBJECT_GROUP::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)OBJECT_GROUP::END; ++Col)
		{
			if (m_arrCheck[Row] & (1 << Col))
			{
				CollisionGroupUpdate((OBJECT_GROUP)Row, (OBJECT_GROUP)Col);
			}
		}
	}
}
void CollisionMgr::CollisionGroupUpdate(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight)
{
	std::shared_ptr<Scene> pCurScene = SceneMgr::GetInst()->GetCurScene();
	const vector<Object*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<Object*>& vecRight = pCurScene->GetGroupObject(_eRight);
	// 충돌 검사를 해보자.
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 충돌체가 없는 경우
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (vecRight[j]->GetCollider() == nullptr || vecRight[j]->GetCollider() == vecLeft[i]->GetCollider())
				continue;
			Collider* pLeftCol = vecLeft[i]->GetCollider();
			Collider* pRightCol = vecRight[j]->GetCollider();
			COLLIDER_ID colID;
			colID.left_ID = pLeftCol->GetID();
			colID.right_ID = pRightCol->GetID();

			// 찾아라.
			auto iter = m_mapColInfo.find(colID.ID);
			// 없어용
			if (iter == m_mapColInfo.end())
			{
				// 넣어라
				m_mapColInfo.insert({ colID.ID, false });
				// 넣은거 잡아라.
				iter = m_mapColInfo.find(colID.ID);
			}
			std::shared_ptr<CollisionInfo> info = std::make_shared<CollisionInfo>(pLeftCol, pRightCol);
			// 충돌하네?
			if (IsCollision(pLeftCol, pRightCol, info))
			{
				// 이전에도 충돌 중
				if (iter->second)
				{
					// 둘중 하나 삭제 예정이라면
					if (vecLeft[i]->GetIsDead() || vecRight[j]->GetIsDead())
					{
						pLeftCol->ExitCollision(pRightCol);
						pRightCol->ExitCollision(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->StayCollision(pRightCol, info);
						pRightCol->StayCollision(pLeftCol, info);
					}
				}
				// 이전에 충돌x
				else
				{
					pLeftCol->EnterCollision(pRightCol, info);
					pRightCol->EnterCollision(pLeftCol, info);
					iter->second = true;
				}
			}
			// 안하네?
			else
			{
				if (iter->second)
				{
					pLeftCol->ExitCollision(pRightCol);
					pRightCol->ExitCollision(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionMgr::IsCollision(Collider* _pLeft, Collider* _pRight, std::shared_ptr<CollisionInfo> outCol)
{
	if (_pLeft->GetType() == _pRight->GetType()) {
		if (_pLeft->GetType() == COLLIDER_TYPE::RECTANGLE) {
			RECT tmps;
			bool res = IntersectRect(&tmps, &(_pLeft->GetRect()), &(_pRight->GetRect()));
			if (res)
				outCol->SetPos(Vec2((tmps.left + tmps.right), (tmps.top + tmps.bottom)));

			return res;
		}
		else {
			Vec2 leftPos = _pLeft->GetFinalPos();
			Vec2 rightPos = _pRight->GetFinalPos();
			Vec2 posDiff = (leftPos - rightPos);
			float dist = posDiff.Length();
			float angleRad = acos(posDiff.Dotproduct(Vec2(0, 1)) / (posDiff.Length()));
			float angleDeg = angleRad * RAD2DEG;
			if (dist <= (_pLeft->GetScale().x + _pRight->GetScale().x)) {
				outCol->SetPos((rightPos + leftPos) * 0.5f);
				return true;
			}
			return false;
		}
	}

	Collider* circle;
	Collider* rectangle;

	if (_pLeft->GetType() == COLLIDER_TYPE::CIRCLE) {
		circle = _pLeft;
		rectangle = _pRight;
	}
	else {
		circle = _pRight;
		rectangle = _pLeft;
	}

	Vec2 closestPoint = Vec2(circle->GetFinalPos());
	Vec2 circlePoint = circle->GetFinalPos();
	float cx = circle->GetFinalPos().x;
	float cy = circle->GetFinalPos().y;
	float rx = rectangle->GetFinalPos().x;
	float ry = rectangle->GetFinalPos().y;
	float rw = rectangle->GetScale().x;
	float rh = rectangle->GetScale().y;
	if (cx < rx)
		closestPoint.x = rx;
	else if (cx > rx + rw)
		closestPoint.x = rx + rw;

	if (cy < ry)
		closestPoint.y = ry;
	else if (cy > ry + rh)
		closestPoint.y = ry + rh;

	float distBetween = (circlePoint - closestPoint).Length();
	if (distBetween >= circle->GetScale().x)
		outCol->SetPos(closestPoint);
	return distBetween >= circle->GetScale().x;
}

void CollisionMgr::CheckGroup(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight)
{
	// 작은쪽을 행으로 씁시다.
	UINT Row = (UINT)_eLeft;
	UINT Col = (UINT)_eRight;
	Row = min(Row, Col);

	//// 비트 연산
	// 체크가 되어있다면
	if (m_arrCheck[Row] & (1 << Col))
	{
		m_arrCheck[Row] &= ~(1 << Col);
	}
	// 체크가 안되어있다면r
	else
	{
		m_arrCheck[Row] |= (1 << Col);
	}
}

void CollisionMgr::CheckReset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)(OBJECT_GROUP::END));
}

