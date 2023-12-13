#pragma once // ¤¾¤§¤¡¤§
#define SINGLE(type)			\
private:						\
	type() {}					\
	~type(){}					\
public:							\
	static type* GetInst()		\
	{							\
		static type m_pInst;	\
		return &m_pInst;		\
	}
#define WINDOW_CLASS_NAME L"FRUITBALL"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720 
#define RECT_RENDER(posx, posy, scalex, scaley, hdc) Rectangle(hdc, (int)(posx-scalex/2), (int)(posy-scaley/2), (int)(posx+scalex/2), (int)(posy+scaley/2))
#define RECT_RENDER_WITHRECT(rect, hdc) Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom)
#define ELLIPSE_RENDER(posx, posy, scalex, scaley, hdc) Ellipse(hdc, (int)(posx-scalex/2), (int)(posy-scaley/2), (int)(posx+scalex/2), (int)(posy+scaley/2))
#define TRANSPARENTBLT_INPOS(hdc, sdc, texture) TransparentBlt(hdc, GetPos().x, GetPos().y, GetScale().x, GetScale().y, sdc, 0, 0, texture->GetWidth(), texture->GetHeight(), RGB(255, 0, 255))

#define IS_CLICK(posx, posy, scalex, scaley, mousex, mousey)                \
       (int)(posx-scalex/2) <= mousex && (int)(posy-scaley/2) <= mousey        \
    && (int)(posx+scalex/2) >= mousex && (int)(posy+scaley/2) >= mousey        \


#define RECT_MAKE(posx, posy, scalex, scaley) {posx-scalex/2, posy-scaley/2, posx+scalex/2, posy+scaley/2}
#define fDT TimeMgr::GetInst()->GetDT()
#define KEY_CHECK(key, state) KeyMgr::GetInst()->GetKey(key) == state
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define KEY_UP(key) KEY_CHECK(key, KEY_STATE::UP)
#define KEY_DOWN(key) KEY_CHECK(key, KEY_STATE::DOWN)
#define KEY_PRESS(key) KEY_CHECK(key, KEY_STATE::PRESS)

#define GETMOUSEPOSITION() KeyMgr::GetInst()->GetMousePos()

#define DRAGTHRESHOLD 75

#define PI 3.14
#define RAD2DEG 180 / PI
#define DEG2RAD PI / 180
#define FRUITLIFETIME 10.0f