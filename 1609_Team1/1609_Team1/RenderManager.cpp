#include "RenderManager.h"



RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}


void RenderManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	// 화면 사이즈
	RECT rc;
	GetClientRect(hWnd, &rc);
	D2D1_SIZE_U size = SizeU(rc.right - rc.left, rc.bottom - rc.top);

	// D2D1Factory 생성
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);

	// HwndRenderTarget 생성
	m_pFactory->CreateHwndRenderTarget(
		RenderTargetProperties(),
		HwndRenderTargetProperties(hWnd, size),
		&m_pRenderTarget);

	// WICImagingFactory 생성
	CoInitialize(NULL);
	CoCreateInstance(CLSID_WICImagingFactory, NULL,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory));

	// DWriteFactory 생성
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(*m_pDWriteFactory),
		(IUnknown**)&m_pDWriteFactory);
}

void RenderManager::Release()
{
	RELEASE_OBJECT(m_pDWriteFactory);
	RELEASE_OBJECT(m_pRenderTarget);
	RELEASE_OBJECT(m_pFactory);
}

Camera* RenderManager::CreateCamera(int tag, float maxSizeX, float maxSizeY, float sizeX, float sizeY)
{
	if (m_cameras.find(tag) != m_cameras.end()) return NULL;

	ID2D1BitmapRenderTarget* pCameraTarget = NULL;
	m_pRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(maxSizeX, maxSizeY), &pCameraTarget);
	m_cameras[tag] = new Camera(pCameraTarget, sizeX, sizeY);
	return m_cameras[tag];
}

Camera* RenderManager::GetCamera(int tag)
{
	if (m_cameras.find(tag) == m_cameras.end()) return NULL;
	return m_cameras[tag];
}

void RenderManager::DestroyCamera(int tag)
{
	Camera* pCamera = GetCamera(tag);
	if (pCamera != NULL)
	{
		m_cameras.erase(tag);
		delete pCamera;
	}
}

void RenderManager::LoadImageFile(wstring key, wstring filename)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pFrameDecode = NULL;
	IWICFormatConverter* pConverter = NULL;
	ID2D1Bitmap* pBitmap = NULL;

	if (m_images.find(key) == m_images.end())
	{
		// 이미지 파일을 Decoding
		m_pImageFactory->CreateDecoderFromFilename(filename.c_str(), NULL,
			GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
		pDecoder->GetFrame(0, &pFrameDecode);

		// Converter 생성 및 초기화
		m_pImageFactory->CreateFormatConverter(&pConverter);
		pConverter->Initialize(pFrameDecode, GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone, NULL, 0, WICBitmapPaletteTypeCustom);

		// Bitmap으로 변환 및 생성
		m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &pBitmap);
		m_images[key] = pBitmap;
	}
}

void RenderManager::LoadImageFiles(wstring key, wstring filename, wstring extension, int count)
{
	TCHAR strKey[100] = {};
	TCHAR strName[100] = {};
	for (int i = 0; i < count; i++)
	{
		wsprintf(strKey, TEXT("%s%d"), key.c_str(), i);
		wsprintf(strName, TEXT("%s%d.%s"), filename.c_str(), i, extension.c_str());
		LoadImageFile(strKey, strName);
	}
}

ID2D1Bitmap* RenderManager::GetImage(wstring key)
{
	if (m_images.find(key) == m_images.end()) return NULL;
	return m_images[key];
}

void RenderManager::Draw(Sprite* pSprite, float x, float y, int dir)
{
	if (pSprite != NULL)
	{
		pSprite->SetPosition(x, y);
		pSprite->SetDirection(dir);
		m_queSprite.push(pSprite);
	}
}

void RenderManager::Draw(wstring str, float x, float y, ColorF color, int size, ALIGN_TYPE align, wstring fontName)
{
	Text text = { str, fontName, x, y, color, size, align };
	m_queText.push(text);
}

void RenderManager::DrawLine(float startX, float startY, float endX, float endY, ColorF color , float lineSize)
{
	GraphicsObject line = { GRAPHICS_LINE, startX, startY,
		endX - startX, endY - startY, color, lineSize };
	m_queGraphics.push(line);
}

void RenderManager::DrawRect(float x, float y, float width, float height, ColorF color, float lineSize)
{
	GraphicsObject rect = { GRAPHICS_RECT, x, y, width, height, color, lineSize };
	m_queGraphics.push(rect);
}

void RenderManager::DrawCircle(float x, float y, float width, float height,	ColorF color, float lineSize)
{
	GraphicsObject rect = { GRAPHICS_CIRCLE, x, y, width, height, color, lineSize };
	m_queGraphics.push(rect);
}

void RenderManager::Render(HDC hdc)
{
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear(ColorF(ColorF::Black));

	// 카메라 출력
	map<int, Camera*>::iterator it;
	for (it = m_cameras.begin(); it != m_cameras.end(); it++)
	{
		it->second->Render(m_pRenderTarget);
	}

	// 스프라이트 출력
	while (m_queSprite.size() > 0)
	{
		Sprite* pSprite = m_queSprite.front();
		pSprite->Render(m_pRenderTarget);
		m_queSprite.pop();
	}

	// 도형 출력
	while (m_queGraphics.size() > 0)
	{
		m_queGraphics.front().Render(m_pRenderTarget);
		m_queGraphics.pop();
	}

	//도형 가져온 것 출력
	// 도형 출력
	while (m_queIGraphics.size() > 0)
	{
		m_queIGraphics.front()->Render(m_pRenderTarget);
		delete m_queIGraphics.front();
		m_queIGraphics.pop();
	}

	// 텍스트 출력
	while (m_queText.size() > 0)
	{
		m_queText.front().Render(m_pRenderTarget, m_pDWriteFactory);
		m_queText.pop();
	}

	m_pRenderTarget->EndDraw();
}