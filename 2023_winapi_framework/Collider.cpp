#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "SelectGDI.h"
UINT Collider::m_sNextID = 0;
Collider::Collider()
	: m_pOwner(nullptr)
	, m_vScale(Vec2(40.f,40.f))
	, m_ID(m_sNextID++)
	, m_check(0)
	, m_vFinalPos{}
	, type {COLLIDER_TYPE::RECTANGLE}
{
	//Collider a, b;
	//a = b;
}

Collider::Collider(const Collider& _origin)
	: m_pOwner(nullptr)
	, m_vScale(_origin.m_vScale)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_ID(m_sNextID++)
	, m_check(0)
	, m_vFinalPos{}
	, type {COLLIDER_TYPE::RECTANGLE}
{
}

Collider::~Collider()
{}

void Collider::Render(HDC _dc)
{
	//Core::GetInst()->GetPen(PEN_TYPE::GREEN);
	//Core::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW);
	//SelectObject();
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (m_check)
		ePen = PEN_TYPE::RED;
	SelectGDI pen(_dc, ePen);
	SelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);
	switch (type)
	{
	case COLLIDER_TYPE::RECTANGLE:
		RECT_RENDER(m_vFinalPos.x, m_vFinalPos.y, m_vScale.x, m_vScale.y, _dc);
		break;
	case COLLIDER_TYPE::CIRCLE:
		ELLIPSE_RENDER(m_vFinalPos.x, m_vFinalPos.y, m_vScale.x, m_vScale.y, _dc);
		break;
	}
	
	
}


void Collider::EnterCollision(Collider* _pOther, std::shared_ptr<CollisionInfo> info)
{


 	++m_check;
	m_pOwner->EnterCollision(_pOther, info);

}

void Collider::ExitCollision(Collider* _pOther)


{

	--m_check;
	m_pOwner->ExitCollision(_pOther);

}

void Collider::StayCollision(Collider* _pOther, std::shared_ptr<CollisionInfo> info)


{

	m_pOwner->StayCollision(_pOther, info);

}

const RECT& Collider::GetRect()
{
	return { (long)(m_pOwner->GetPos().x + m_vOffsetPos.x), (long)(m_pOwner->GetPos().y + m_vOffsetPos.y) ,(long)(m_pOwner->GetPos().x + m_vOffsetPos.x + m_vScale.x), (long)(m_pOwner->GetPos().y + m_vOffsetPos.y + m_vScale.y) };
}

void Collider::FinalUpdate()
{
	// Object위치를 따라가야 하는거야.
	Vec2 vObjPos = m_pOwner->GetPos();
	m_vFinalPos = vObjPos + m_vOffsetPos;
}

