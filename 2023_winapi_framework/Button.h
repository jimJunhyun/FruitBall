#pragma once
#include "Object.h"
#include "Texture.h"

class Scene;

class Button :
    public Object
{
public:
    Button(void(*_action)(), wstring _text, Scene* level = nullptr);
    ~Button();

public:
    void Update() override;
    void Render(HDC _dc) override;
    void SetText(wstring str) { m_sText = str; }

private:
    void(*m_pAction)();
    wstring m_sText;
    Texture* m_pTex;
};