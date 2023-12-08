#include "pch.h"
#include "Object.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "CollisionInfo.h"
#include "Scene.h"

Object::Object(Scene* scene)
	: m_pCollider(nullptr)
	, m_vPos{}
	, m_vScale{}
	, m_IsAlive(true)
	, m_pAnimator(nullptr)
	, m_vVelocity(0, 0)
	, bounciness(0.7)
	, colliding(nullptr)
	, level(scene)
{
}

Object::~Object()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
	if (nullptr != m_pAnimator)
		delete m_pAnimator;

}

void Object::CreateCollider(COLLIDER_TYPE type)
{
	m_pCollider = new Collider;
	m_pCollider->m_pOwner = this;
	m_pCollider->type = type;
}

void Object::CreateAnimator()
{
	m_pAnimator = new Animator;
	m_pAnimator->m_pOwner = this;
}

void Object::Update()
{
	if (m_vVelocity.Length() != 0) {
		Vec2 curVel = GetVelocity();
		m_vPos.x = m_vPos.x + curVel.x * GetMyDT();
		m_vPos.y = m_vPos.y + curVel.y * GetMyDT();
	}
}

void Object::FinalUpdate()
{
	if (m_pCollider)
		m_pCollider->FinalUpdate();
}

void Object::Render(HDC _dc)
{
	/*Vec2 vPos = m_obj.GetPos();
	Vec2 vScale = m_obj.GetScale();*/
	RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
	Component_Render(_dc);
}

void Object::EnterCollision(Collider* _pOther, std::shared_ptr<CollisionInfo> info)
{
	/*colliding = info;
	if (_pOther == nullptr || info == nullptr)
		return;
	Vec2 vel = _pOther->m_pOwner->GetVelocity();
	Vec2 myVel = GetVelocity();
	Vec2 v = (vel * (bounciness + 1) + (myVel * (1 - bounciness))) * 0.5f;
	SetVelocity(v);*/
}

void Object::ExitCollision(Collider* _pOther)
{
	colliding = nullptr;
}

void Object::StayCollision(Collider* _pOther, std::shared_ptr<CollisionInfo> info)
{
	/*colliding = info;
	if (_pOther == nullptr || info == nullptr)
		return;

	Vec2 vel = _pOther->m_pOwner->GetVelocity();
	Vec2 myVel = GetVelocity();
	SetVelocity((vel * (bounciness + 1) + (myVel * (1 - bounciness))) * 0.5f);*/


	/*Vec2 p = (colliding->GetCollidePoint());
	Vec2 curVel = GetVelocity();
	if ((p.x > GetPos().x) == (curVel.x >0) && (p.y > GetPos().y) == (curVel.y > 0)) {
		AddForce(info->GetCollideNormal(_pOther) * _pOther->m_pOwner->bounciness);
	}*/
}

void Object::Component_Render(HDC _dc)
{
	//if (colliding != nullptr) {
	//	RECT_RENDER(colliding->GetCollidePoint().x, colliding->GetCollidePoint().y, 25, 25, _dc);
	//	RECT_RENDER(colliding->GetCollidePoint().x - colliding->GetCollideNormal(GetCollider()).x * 25, colliding->GetCollidePoint().y - colliding->GetCollideNormal(GetCollider()).y * 25, 10, 10, _dc);
	//	//LineTo(_dc, colliding->GetCollidePoint().x - colliding->GetCollideNormal(GetCollider()).x, colliding->GetCollidePoint().y - colliding->GetCollideNormal(GetCollider()).y);
	//}
	if (nullptr != m_pCollider)
		m_pCollider->Render(_dc);
	if (nullptr != m_pAnimator)
		m_pAnimator->Render(_dc);

}

const float& Object::GetMyDT() const
{
	return fDT * level->GetTimescale();
}

const float& Object::GetUnscaledDT() const
{
	return fDT;
}
