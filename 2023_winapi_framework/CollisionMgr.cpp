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
	// �浹 �˻縦 �غ���.
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// �浹ü�� ���� ���
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (vecRight[j]->GetCollider() == nullptr)
				continue;
			Collider* pLeftCol = vecLeft[i]->GetCollider();
			Collider* pRightCol = vecRight[j]->GetCollider();
			COLLIDER_ID colID;
			colID.left_ID = pLeftCol->GetID();
			colID.right_ID = pRightCol->GetID();

			// ã�ƶ�.
			auto iter = m_mapColInfo.find(colID.ID);
			// �����
			if (iter == m_mapColInfo.end())
			{
				// �־��
				m_mapColInfo.insert({ colID.ID, false });
				// ������ ��ƶ�.
				iter = m_mapColInfo.find(colID.ID);
			}
			// �浹�ϳ�?
			if (IsCollision(pLeftCol, pRightCol))
			{
				// �������� �浹 ��
				if (iter->second)
				{
					// ���� �ϳ� ���� �����̶��
					if(vecLeft[i]->GetIsDead() || vecRight[j]->GetIsDead())
					{
						pLeftCol->ExitCollision(pRightCol);
						pRightCol->ExitCollision(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->StayCollision(pRightCol);
						pRightCol->StayCollision(pLeftCol);
					}
				}
				// ������ �浹x
				else
				{
					CollisionInfo info(pLeftCol, pRightCol);
					pLeftCol->EnterCollision(pRightCol, &info);
					pRightCol->EnterCollision(pLeftCol, &info);
					iter->second = true;
				}
			}
			// ���ϳ�?
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

bool CollisionMgr::IsCollision(Collider* _pLeft, Collider* _pRight)
{
	if (_pLeft->GetType() == _pRight->GetType()) {
		if (_pLeft->GetType() == COLLIDER_TYPE::RECTANGLE) {
			RECT tmps;
			return IntersectRect(&tmps, &(_pLeft->GetRect()), &(_pRight->GetRect()));
		}
		else {
			Vec2 leftPos = _pLeft->GetFinalPos();
			Vec2 rightPos = _pRight->GetFinalPos();

			float dist = (leftPos - rightPos).Length();
			return (dist <= (_pLeft->GetScale().x + _pRight->GetScale().x));
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
	if (cx < rx)         closestPoint.x = rx;        // left edge
	else if (cx > rx + rw) closestPoint.x = rx + rw;     // right edge

	if (cy < ry)         closestPoint.y = ry;        // top edge
	else if (cy > ry + rh) closestPoint.y = ry + rh;     // bottom edge

	float distBetween = (circlePoint - closestPoint).Length();

	return distBetween >= circle->GetScale().x;
}

void CollisionMgr::CheckGroup(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight)
{
	// �������� ������ ���ô�.
	UINT Row = (UINT)_eLeft;
	UINT Col = (UINT)_eRight;
	Row = min(Row, Col);

	//// ��Ʈ ����
	// üũ�� �Ǿ��ִٸ�
	if (m_arrCheck[Row] & (1 << Col))
	{
		m_arrCheck[Row] &= ~(1 << Col);
	}
	// üũ�� �ȵǾ��ִٸ�r
	else
	{
		m_arrCheck[Row] |= (1 << Col);
	}
}

void CollisionMgr::CheckReset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)(OBJECT_GROUP::END));
}

