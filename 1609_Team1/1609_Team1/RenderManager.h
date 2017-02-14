#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <d2d1.h>			// Direct2D
#include <wincodec.h>		// IWICImaging
#include <wincodecsdk.h>	// IWICImaging
#include <dwrite.h>			// Text
#include <queue>
#include <map>
#include "Math.h"
#include "Common.h"
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "dwrite.lib")
using namespace D2D1;
using namespace std;

#define RENDER RenderManager::Instance()
//02-06 이승문
class IGraphics
{
public:
	virtual void Render(ID2D1RenderTarget* pRenderTarget) {}
};

class GText : public IGraphics
{
	IDWriteTextFormat* m_pFormat;
	wstring m_text;
	Vector m_pos;
	ColorF m_color;
	float m_size;

public:
	GText(IDWriteTextFormat* pFormat, wstring text, Vector pos
		, float size, ColorF color) : m_color(color)
	{
		m_pFormat = pFormat;
		m_text = text;
		m_pos = pos;
		m_size = size;
	}

	~GText() { RELEASE_OBJECT(m_pFormat); }

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		D2D1_RECT_F rect = RectF(m_pos.x, m_pos.y, m_pos.x + 500, m_pos.y);

		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);
		pRenderTarget->DrawTextW(m_text.c_str(), m_text.length(), m_pFormat, rect, pBrush);
		RELEASE_OBJECT(pBrush);
	}
};

class GLine : public IGraphics
{
	Vector m_start, m_end;
	ColorF m_color;
	float m_lineSize;

public:
	GLine(Vector start, Vector end, ColorF color, float lineSize) : m_color(color)
	{
		m_start = start;
		m_end = end;
		m_lineSize = lineSize;
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);

		D2D1_POINT_2F startPos = Point2F(m_start.x, m_start.y);
		D2D1_POINT_2F endPos = Point2F(m_end.x, m_end.y);
		pRenderTarget->DrawLine(startPos, endPos, pBrush, m_lineSize);

		RELEASE_OBJECT(pBrush);
	}
};

class GRect : public IGraphics
{
	Vector m_center, m_size;
	ColorF m_color;
	float m_lineSize;

public:
	GRect(Vector center, Vector size, ColorF color, float lineSize) : m_color(color)
	{
		m_center = center;
		m_size = size;
		m_lineSize = lineSize;
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);

		Vector leftTop = m_center - m_size * 0.5f;
		Vector rightBottom = m_center + m_size * 0.5f;
		D2D1_RECT_F rect = RectF(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);

		if (m_lineSize == 0) pRenderTarget->FillRectangle(rect, pBrush);
		else pRenderTarget->DrawRectangle(rect, pBrush, m_lineSize);

		RELEASE_OBJECT(pBrush);
	}
};

class GCircle : public IGraphics
{
	Vector m_center;
	float m_radius;
	ColorF m_color;
	float m_lineSize;

public:
	GCircle(Vector center, float radius, ColorF color, float lineSize) : m_color(color)
	{
		m_center = center;
		m_radius = radius;
		m_lineSize = lineSize;
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);

		D2D1_POINT_2F center = Point2F(m_center.x, m_center.y);
		D2D1_ELLIPSE ellipse = Ellipse(center, m_radius, m_radius);

		if (m_lineSize == 0) pRenderTarget->FillEllipse(ellipse, pBrush);
		else pRenderTarget->DrawEllipse(ellipse, pBrush, m_lineSize);

		RELEASE_OBJECT(pBrush);
	}
};


struct Text
{
	wstring str;
	wstring fontName;
	float x, y;
	ColorF color;
	int size;
	ALIGN_TYPE align;

	void Render(ID2D1RenderTarget* pRenderTarget, IDWriteFactory* pFactory)
	{
		IDWriteTextFormat* pFormat;
		pFactory->CreateTextFormat(fontName.c_str(), 0,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			size, L"ko", &pFormat
		);

		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(color, &pBrush);
		pRenderTarget->DrawTextW(str.c_str(), str.length(), pFormat,
			RectF(x, y, x + 300, y + 300), pBrush);
	}
};

struct GraphicsObject
{
	GRAPHICS_TYPE type;
	float x, y;
	float width, height;
	ColorF color;
	float lineSize;

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(color, &pBrush);

		switch (type)
		{
		case GRAPHICS_LINE:
			pRenderTarget->DrawLine(Point2F(x, y), Point2F(width, height), pBrush, lineSize); break;
		case GRAPHICS_RECT:
			if (lineSize == 0)
			{
				pRenderTarget->FillRectangle(RectF(x, y, x + width, y + height), pBrush);
				break;
			}
			else
			{
				pRenderTarget->DrawRectangle(RectF(x, y, x + width, y + height), pBrush, lineSize);
				break;
			}
		case GRAPHICS_CIRCLE:
			float radiusX = width * 0.5f;
			float radiusY = height * 0.5f;
			if (lineSize == 0)
			{
				pRenderTarget->FillEllipse(Ellipse(Point2F(x + radiusX, y + radiusY), radiusX, radiusY), pBrush);
				break;
			}
			else
			{
				pRenderTarget->DrawEllipse(Ellipse(Point2F(x + radiusX, y + radiusY), radiusX, radiusY), pBrush, lineSize);
				break;
			}
		}
	}
};

class Sprite
{
	ID2D1Bitmap* m_pImage;
	float m_x, m_y;
	float m_width;
	float m_height;
	float m_scale;
	float m_anchorX;
	float m_anchorY;
	int m_dir;

public:
	Sprite(ID2D1Bitmap* pImage, float scale = 1.0f,
		float anchorX = 0.5f, float anchorY = 0.5f)
	{
		m_pImage = pImage;
		m_width = pImage->GetSize().width;
		m_height = pImage->GetSize().height;
		m_scale = scale;
		m_anchorX = anchorX;
		m_anchorY = anchorY;
		m_dir = 1;
	}

	void SetPosition(float x, float y) { m_x = x; m_y = y; }
	void SetDirection(int dir) { m_dir = dir; }
	void SetSize(float w, float h) { m_width = w; m_height = h; }
	void SetScale(float scale) { m_scale = scale; }
	float GetLeftX() { return m_x - GetWidth() * m_anchorX; }
	float GetTopY() { return m_y - GetHeight() * m_anchorY; }
	float GetWidth() { return m_width * m_scale; }
	float GetHeight() { return m_height * m_scale; }
	float GetScale() { return m_scale; }

	void Render(ID2D1RenderTarget* pRenderTarget, float opacity = 1.0f)
	{
		Vector leftTop = Vector(GetLeftX(), GetTopY());
		Vector size = Vector(GetWidth(), GetHeight());

		// 스케일 적용
		pRenderTarget->SetTransform(Matrix3x2F::Scale(m_dir, 1.0f,
			Point2F(leftTop.x + size.x * 0.5f, leftTop.y + size.y * 0.5f)));

		// 비트맵 드로우
		pRenderTarget->DrawBitmap(m_pImage,
			RectF(leftTop.x, leftTop.y, leftTop.x + size.x, leftTop.y + size.y), opacity);

		// 스케일 초기화
		pRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
};

class Camera
{
	ID2D1BitmapRenderTarget* m_pBitmapTarget;
	Vector m_size;
	Vector m_center;
	float m_opacity;
	D2D1_RECT_F m_screenRect;
	Line m_LineCamera, m_LineLeft, m_LineRight;//	1. 카메라 중심선, 왼쪽, 오른쪽 선

	IDWriteFactory*			m_pDWriteFactory; // 텍스트 출력을 위한 팩토리


	//실제 미니맵에서의 플레이어 위치
	Line LineCenter;
	Line LineLeft;
	Line LineRight;

public:
	Camera(ID2D1BitmapRenderTarget* pBitmapTarget, float sizeX, float sizeY):
		m_LineCamera(Vector(CHARACTER_X, CHARACTER_Y), MATH->ToDirection(90) * SIGHT),
		m_LineLeft(Vector(CHARACTER_X, CHARACTER_Y), MATH->ToDirection(CAMERA_LEFT) * SIGHT),
		m_LineRight(Vector(CHARACTER_X, CHARACTER_Y), MATH->ToDirection(CAMERA_RIGHT) * SIGHT),
		LineCenter(Vector(VIEW_WIDTH-MINI_WIDTH/2, VIEW_HEIGHT), MATH->ToDirection(90) * MINI_WIDTH),
		LineLeft(Vector(VIEW_WIDTH - MINI_WIDTH / 2, VIEW_HEIGHT), MATH->ToDirection(CAMERA_LEFT) * MINI_WIDTH),
		LineRight(Vector(VIEW_WIDTH - MINI_WIDTH / 2, VIEW_HEIGHT), MATH->ToDirection(CAMERA_RIGHT) * MINI_WIDTH)
	{
		m_pBitmapTarget = pBitmapTarget;
		m_pBitmapTarget->BeginDraw();
		m_pBitmapTarget->Clear(ColorF(0, 0, 0, 0));
		m_pBitmapTarget->EndDraw();
		m_size = Vector(sizeX, sizeY);
		m_opacity = 1.0f;

		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(*m_pDWriteFactory),
			(IUnknown**)&m_pDWriteFactory);

		SetCenterPos(Vector(0, 0));
		SetScreenRect(0.0f, 0.0f, sizeX, sizeY);
	}

	Vector GetPos() { return m_center; }
	Vector GetLeftTop() { return m_center - m_size * 0.5f; }
	Vector GetRightBottom() { return m_center + m_size * 0.5f; }
	void SetOpacity(float opacity) { m_opacity = opacity; }
	void SetScreenRect(float x, float y, float width, float height)
	{
		m_screenRect = RectF(x, y, x + width, y + height);
	}
	void SetCenterPos(Vector center)
	{
		m_center = center;

		AlignLeftTop();
		AlignRightBottom();
	}

	void AlignLeftTop()
	{
		D2D1_SIZE_F bitmapSize = m_pBitmapTarget->GetSize();

		Vector leftTop = GetLeftTop();
		leftTop.x = MATH->Clamp(leftTop.x, 0.0f, bitmapSize.width);
		leftTop.y = MATH->Clamp(leftTop.y, 0.0f, bitmapSize.height);
		m_center = leftTop + m_size * 0.5f;
	}

	void AlignRightBottom()
	{
		D2D1_SIZE_F bitmapSize = m_pBitmapTarget->GetSize();

		Vector rightBottom = GetRightBottom();
		rightBottom.x = MATH->Clamp(rightBottom.x, 0.0f, bitmapSize.width);
		rightBottom.y = MATH->Clamp(rightBottom.y, 0.0f, bitmapSize.height);
		m_center = rightBottom - m_size * 0.5f;
	}

	void DrawT(wstring str, float x, float y, ColorF color, int size, ALIGN_TYPE align = ALIGN_LEFT, wstring fontName = TEXT("Arial")) 
	{
		m_pBitmapTarget->BeginDraw();

		Text text = { str, fontName, x, y, color, size, align };
		text.Render(m_pBitmapTarget, m_pDWriteFactory);

		m_pBitmapTarget->EndDraw();
	}

	void Draw(Sprite* sprite, Vector pos, int dir = -1, float opacity = 1.0f)
	{
		m_pBitmapTarget->BeginDraw();

		sprite->SetPosition(pos.x, pos.y);
		sprite->SetDirection(dir);
		sprite->Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void DrawLine(float startX, float startY, float endX, float endY, ColorF color, float lineSize)
	{
		m_pBitmapTarget->BeginDraw();

		GraphicsObject line = { GRAPHICS_LINE, startX, startY,
			endX, endY, color, lineSize };
		line.Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	//Vector SetVectorInMap(Vector point) {
	//	return Vector(VIEW_WIDTH - MINI_WIDTH + point.x*MINI_WIDTH / VIEW_WIDTH, VIEW_HEIGHT - MINI_HEIGHT + point.y*MINI_HEIGHT / VIEW_HEIGHT);
	//}

	// 크리쳐의 좌표 (미니맵 상의 좌표)를 전장 화면의 좌표로 바꿔주는 함수
	Vector ChangePositionToView(Vector startPos, float sightHeight, float t, int object_state)
	{
		float x, y;

		// x좌표 구하기
		float angle = 90 - MATH->Angle(Vector::Right(), startPos - Vector(MINI_WIDTH * 0.5, MINI_HEIGHT));
		//x = (angle > 90) ? pow(MINI_WIDTH * 0.5, 2) * PI * angle / 360 * -1 : pow(MINI_WIDTH * 0.5, 2) * PI * angle / 360;
		
		x = (angle > 90) ? VIEW_WIDTH * angle / 60 + VIEW_WIDTH * 0.5 * -1: VIEW_WIDTH * angle / 60 + VIEW_WIDTH * 0.5;

		// y좌표 구하기
		y = sightHeight + 130 + VIEW_WIDTH * 0.5 * t;
		if (object_state >= BULLET_NONE) y = y - (400 * t);

		return Vector(x, y);
	}

	// 크리쳐가 플레이어의 시야에 들어왔을 경우, 미니맵 상의 크리쳐를 전장 화면으로 출력해주는 함수, float 는 시작점부터 끝점까지 이동한 거리의 비율
	void Draw3D(Sprite* sprite, Vector startPos, float t, float sightHeight, int object_state, int dir = -1, float opacity = 1.0f) 
	{
		// 크리쳐가 플레이어의 시야 (미니맵 상의 두 파란선) 안에 들어왔는지 확인하는 단계. 플레이어의 시야는 CAMERA_ANGLE로 정의되어 있음
		//DrawLine(VIEW_WIDTH-MINI_WIDTH+moveLine.StartPoint().x, VIEW_HEIGHT - MINI_HEIGHT + moveLine.StartPoint().y, VIEW_WIDTH - MINI_WIDTH/2, VIEW_HEIGHT - MINI_HEIGHT / 2, ColorF::Red, 1);
		float Angle = MATH->Angle(Vector::Right(), startPos - Vector(MINI_WIDTH * 0.5, MINI_HEIGHT));

		if (Angle <= CAMERA_LEFT && Angle >= CAMERA_RIGHT)
		{
			m_pBitmapTarget->BeginDraw();

			Vector pos = ChangePositionToView(startPos, sightHeight, t, object_state);
			sprite->SetPosition(pos.x, pos.y);
			sprite->SetDirection(dir);
			sprite->Render(m_pBitmapTarget);

			m_pBitmapTarget->EndDraw();
		}

	}

	//void Draw3DLine(Sprite* sprite, Line line, int dir = -1, float opacity = 1.0f)
	//{
	//	// 크리쳐가 플레이어의 시야 (미니맵 상의 두 파란선) 안에 들어왔는지 확인하는 단계. 플레이어의 시야는 CAMERA_ANGLE로 정의되어 있음
	//	float Angle = MATH->Angle(Vector::Right(), line.StartPoint()- line.EndPoint());
	//
	//	if (Angle <= CAMERA_LEFT && Angle >= CAMERA_RIGHT)
	//	{
	//		m_pBitmapTarget->BeginDraw();
	//
	//		Vector posInMap = Vector(SetLine3D(line), m_height);
	//		sprite->SetPosition(posInMap.x, posInMap.y);
	//		sprite->SetDirection(dir);
	//		sprite->Render(m_pBitmapTarget);
	//
	//		m_pBitmapTarget->EndDraw();
	//	}
	//
	//}
	
	/*void PosInMap(Line line, ColorF color, float lineSize = 1)
	{
		DrawLine(SetVectorInMap(line.StartPoint()), SetVectorInMap(line.EndPoint()), color, lineSize);
	}

	void DrawInMap(Circle circle, ColorF color, float lineSize = 0)
	{
		DrawCircle(SetVectorInMap(circle.center), circle.radius*MINI_WIDTH / VIEW_WIDTH, color, lineSize);
	}

	void DrawInMap(Box2 box, ColorF color, float lineSize = 1)
	{
		DrawLine(SetVectorInMap(box.LeftTop()), SetVectorInMap(box.RightTop()), color, lineSize);
		DrawLine(SetVectorInMap(box.LeftTop()), SetVectorInMap(box.LeftBottom()), color, lineSize);
		DrawLine(SetVectorInMap(box.RightBottom()), SetVectorInMap(box.RightTop()), color, lineSize);
		DrawLine(SetVectorInMap(box.RightBottom()), SetVectorInMap(box.LeftBottom()), color, lineSize);
	}

	void DrawInMap(Triangle triangle, ColorF color, float lineSize = 1)
	{
		DrawLine(SetVectorInMap(triangle.p0), SetVectorInMap(triangle.p1), color, lineSize);
		DrawLine(SetVectorInMap(triangle.p1), SetVectorInMap(triangle.p2), color, lineSize);
		DrawLine(SetVectorInMap(triangle.p2), SetVectorInMap(triangle.p0), color, lineSize);
	}
	//MATH->Closest(ClosestPoint);*/
	//Vector SetVector3D(Vector pos)
	//{
	//	Vector BigPos = Vector(pos.x *5, pos.y *5);
	//	Vector CenterPoint = MATH->ClosestPoint(BigPos, m_LineCamera);
	//	/*float fBunJa = MATH->Distance(CenterPoint, BigPos);
	//	float fBunMo = MATH->Distance(MATH->ClosestPoint(CenterPoint, m_LineLeft), CenterPoint);*/
	//	float fBunJa = MATH->Distance(BigPos, m_LineCamera.EndPoint());
	//	float fBunMo = MATH->Distance(m_LineLeft.EndPoint(), m_LineCamera.EndPoint());
	//
	//	float X_3D=600.0f;
	//	if (BigPos.x>=VIEW_WIDTH/2) {
	//		X_3D += 600 * fBunJa / fBunMo;
	//	}
	//	else {
	//		X_3D -= 600 * fBunJa / fBunMo;
	//	}
	//	return Vector(X_3D, m_height);	
	//}

	float SetLine3D(Line line)
	{
		Vector CenterPoint = MATH->ClosestPoint(line.EndPoint(), m_LineCamera);
		float fBunJa = MATH->Distance(CenterPoint, line.EndPoint());
		float fBunMo = MATH->Distance(MATH->ClosestPoint(CenterPoint, m_LineLeft), CenterPoint);
		float X_3D = 600.0f;
		if (line.EndPoint().x >= VIEW_WIDTH / 2) {
			X_3D += 600 * fBunJa / fBunMo;
		}
		else {
			X_3D -= 600 * fBunJa / fBunMo;
		}
		return X_3D;
	}

	void DrawRect(Vector leftTop, Vector size,
		ColorF color = ColorF::Black, float lineSize = 1)
	{
		m_pBitmapTarget->BeginDraw();

		GraphicsObject rect = { GRAPHICS_RECT, leftTop.x, leftTop.y, size.x, size.y, color, lineSize };
		rect.Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void DrawFilledRect(Vector leftTop, Vector size, ColorF color = ColorF::Black)
	{
		m_pBitmapTarget->BeginDraw();

		GraphicsObject rect = { GRAPHICS_RECT, leftTop.x, leftTop.y, size.x, size.y, color, 0 };
		rect.Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void DrawCircle(Vector center, Vector size,
		ColorF color = ColorF::Black, float lineSize = 1)
	{
		m_pBitmapTarget->BeginDraw();

		GraphicsObject circle = { GRAPHICS_CIRCLE, center.x-(size.x * 0.5), center.y - (size.y * 0.5), size.x, size.y, color, lineSize };
		circle.Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void DrawFilledCircle(Vector center, Vector size, ColorF color = ColorF::Black)
	{
		m_pBitmapTarget->BeginDraw();

		GraphicsObject circle = { GRAPHICS_CIRCLE, center.x - (size.x * 0.5), center.y - (size.y * 0.5), size.x, size.y, color, 0 };
		circle.Render(m_pBitmapTarget);

		m_pBitmapTarget->EndDraw();
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1Bitmap* pBitmap = NULL;
		m_pBitmapTarget->GetBitmap(&pBitmap);

		Vector leftTop = GetLeftTop();
		pRenderTarget->DrawBitmap(pBitmap,
			m_screenRect, m_opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			RectF(leftTop.x, leftTop.y, leftTop.x + m_size.x, leftTop.y + m_size.y));

		m_pBitmapTarget->BeginDraw();
		m_pBitmapTarget->Clear(ColorF(0, 0, 0, 0));
		m_pBitmapTarget->EndDraw();
	}
};

class RenderManager : public Singleton<RenderManager>
{
	ID2D1Factory*			m_pFactory;
	ID2D1HwndRenderTarget*	m_pRenderTarget;

	IWICImagingFactory*		m_pImageFactory;

	IDWriteFactory*			m_pDWriteFactory;

	HWND				m_hWnd;

	map<wstring, ID2D1Bitmap*> m_images;
	map<int, Camera*> m_cameras;
	queue<Sprite*> m_queSprite;
	queue<Text> m_queText;
	queue<GraphicsObject>	m_queGraphics;

	queue<IGraphics*>		m_queIGraphics;

public:
	RenderManager();
	~RenderManager();

	void Init(HWND hWnd);
	void Release();
	Camera* CreateCamera(int tag, float maxSizeX, float maxSizeY, float sizeX, float sizeY);
	Camera* GetCamera(int tag);
	void DestroyCamera(int tag);
	void LoadImageFile(wstring key, wstring filename);
	void LoadImageFiles(wstring key, wstring filename, wstring extension, int count);
	ID2D1Bitmap* GetImage(wstring key);
	void Draw(Sprite* pSprite, float x, float y, int dir = 1);
	// 텍스트 Draw  함수명 변경
	void DrawT(wstring str, float x, float y, ColorF color = ColorF::Black, int size = 10, ALIGN_TYPE align = ALIGN_LEFT, wstring fontName = TEXT("Arial"));
	void DrawLine(float startX, float startY, float endX, float endY, ColorF color = ColorF::Black, float lineSize = 1);
	void DrawRect(float x, float y, float width, float height, ColorF color = ColorF::Black, float lineSize = 1);
	void DrawCircle(float x, float y, float width, float height, ColorF color = ColorF::Black, float lineSize = 1);
	void Render(HDC hdc);

	void Draw(wstring text, Vector pos, float size = 10, ColorF color = ColorF::White,
		TEXT_ALIGN align = TEXT_ALIGN_LEFT, wstring font = TEXT("Arial"))
	{
		IDWriteTextFormat* pFormat = NULL;
		m_pDWriteFactory->CreateTextFormat(font.c_str(), 0,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			size, TEXT("ko"), &pFormat);

		pFormat->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)align);
		m_queIGraphics.push(new GText(pFormat, text, pos, size, color));
	}

	void Draw(Line line, ColorF color, float lineSize = 1)
	{
		DrawLine(line.StartPoint(), line.EndPoint(), color, lineSize);
	}

	void Draw(Circle circle, ColorF color, float lineSize = 0)
	{
		DrawCircle(circle.center, circle.radius, color, lineSize);
	}

	void Draw(Box2 box, ColorF color, float lineSize = 1)
	{
		DrawLine(box.LeftTop(), box.RightTop(), color, lineSize);
		DrawLine(box.LeftTop(), box.LeftBottom(), color, lineSize);
		DrawLine(box.RightBottom(), box.RightTop(), color, lineSize);
		DrawLine(box.RightBottom(), box.LeftBottom(), color, lineSize);
	}

	void Draw(Triangle triangle, ColorF color, float lineSize = 1)
	{
		DrawLine(triangle.p0, triangle.p1, color, lineSize);
		DrawLine(triangle.p1, triangle.p2, color, lineSize);
		DrawLine(triangle.p2, triangle.p0, color, lineSize);
	}

	void DrawLine(Vector startPos, Vector endPos, ColorF color = ColorF::White, float lineSize = 1)
	{
		m_queIGraphics.push(new GLine(startPos, endPos, color, lineSize));
	}

	void FillRect(Vector center, Vector size, ColorF color = ColorF::White)
	{
		m_queIGraphics.push(new GRect(center, size, color, 0));
	}

	void DrawRect(Vector center, Vector size, ColorF color = ColorF::White, float lineSize = 1)
	{
		m_queIGraphics.push(new GRect(center, size, color, lineSize));
	}

	void FillCircle(Vector center, float radius, ColorF color = ColorF::White)
	{
		m_queIGraphics.push(new GCircle(center, radius, color, 0));
	}

	void DrawCircle(Vector center, float radius, ColorF color = ColorF::White, float lineSize = 1)
	{
		m_queIGraphics.push(new GCircle(center, radius, color, lineSize));
	}

	Vector SetVectorInMap(Vector point) {
		return Vector(VIEW_WIDTH - MINI_WIDTH + point.x*MINI_WIDTH / VIEW_WIDTH, VIEW_HEIGHT - MINI_HEIGHT + point.y*MINI_HEIGHT / VIEW_HEIGHT);
	}
	
};