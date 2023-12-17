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
	, m_vPos{0, 0}
	, m_vScale{}
	, m_IsAlive(true)
	, m_pAnimator(nullptr)
	, m_vVelocity{0, 0}
	, bounciness(0.9)
	, colliding(nullptr)
{
	level = scene;
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
	RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
	Component_Render(_dc);
}


void Object::EnterCollision(Collider* _pOther, std::shared_ptr<CollisionInfo> info   )
{
	
}


void Object::ExitCollision(Collider* _pOther   )
{
	colliding = nullptr;
}


void Object::StayCollision(Collider* _pOther, std::shared_ptr<CollisionInfo> info   )
{
	
}

void Object::Component_Render(HDC _dc  )
{
	if (nullptr != m_pCollider)
		m_pCollider->Render(_dc);
	if (nullptr != m_pAnimator)
		m_pAnimator->Render(_dc);

}


const float Object::GetMyDT() const
{
	return fDT * level->GetTimescale();

}


const float Object::GetUnscaledDT() const
{
	return fDT;

}

