#pragma once
class Collider;
class Animator;
class CollisionInfo;
class Object
{
public:
	Object();
	virtual ~Object();
//public:	// 크기, 위치
	//POINT m_ptPos;
	//POINT m_ptScale;
public:
	virtual void Update();
	virtual void FinalUpdate() final;
	virtual void Render(HDC _dc);
	virtual void EnterCollision(Collider* _pOther, CollisionInfo* info);
	virtual void ExitCollision(Collider* _pOther);
	virtual void StayCollision(Collider* _pOther);
	void Component_Render(HDC _dc);
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetVelocity(Vec2 val) { m_vVelocity = val; }
	const Vec2& GetPos() const { return m_vPos; }
	const Vec2& GetScale() const { return m_vScale; }
	const Vec2& GetVelocity()  { return m_vVelocity * velMod; }
	const float GetVelocityPower();
	Collider* GetCollider() const 
	{ return m_pCollider; }
	Animator* GetAnimator()
	{
		return m_pAnimator;
	}
	const wstring& GetName() const { return m_strName; }
	void SetName(wstring _name) { m_strName = _name; }
	bool GetIsDead() const { return !m_IsAlive; }
protected:
	void SetDead() { m_IsAlive = false; }
	friend class EventMgr;
public:
	void CreateCollider(COLLIDER_TYPE type);
	void CreateAnimator();
private:
	Vec2 m_vPos; // 위치
	Vec2 m_vScale; // 크기
	Vec2 m_vVelocity; 
	Vec2 velMod;
	Collider* m_pCollider;
	wstring m_strName; // 이름.
	bool m_IsAlive;
	Animator* m_pAnimator;
};

