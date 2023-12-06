#pragma once
#include "Object.h"
#include "Texture.h"

class Button :
    public Object
{
public:
    Button(void(*_action)(), wstring _text);
    ~Button();

public:
    void Update() override;
    void Render(HDC _dc) override;
    //void EnterCollision(Collider* _pOther);
    void SetText(wstring str) { m_sText = str; }

public:

private:
    void(*m_pAction)();
    wstring m_sText;
    Texture* m_pTex;
};