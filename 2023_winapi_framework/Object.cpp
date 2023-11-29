#include "pch.h"
#include "Object.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "CollisionInfo.h"

Object::Object()
	: m_pCollider(nullptr)
	, m_vPos{}
	, m_vScale{}
	, m_IsAlive(true)
	, m_pAnimator(nullptr)
	, m_vVelocity(0, 0)
	, bounciness(0.7)
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
		m_vPos = m_vPos + curVel * fDT;
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

void Object::EnterCollision(Collider* _pOther, CollisionInfo* info)
{
	if (_pOther == nullptr || info == nullptr)
		return;
	Vec2 vel = _pOther->m_pOwner->GetVelocity();
	AddForce(info->GetCollideNormal(_pOther) * vel.Length() * 0.5f * _pOther->m_pOwner->bounciness);
}

void Object::ExitCollision(Collider* _pOther)
{
}

void Object::StayCollision(Collider* _pOther, CollisionInfo* info)
{
	if (_pOther == nullptr || info == nullptr)
		return;
	Vec2 vel = _pOther->m_pOwner->GetVelocity();
	AddForce(info->GetCollideNormal(_pOther) * 0.5f);
}

void Object::Component_Render(HDC _dc)
{
	if (nullptr != m_pCollider)
		m_pCollider->Render(_dc);
	if (nullptr != m_pAnimator)
		m_pAnimator->Render(_dc);

}