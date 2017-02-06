#include "PlayScene.h"



PlayScene::PlayScene()
{
	// ��� �̹��� ������ ����
	RENDER->LoadImageFile(TEXT("ForestBG"), TEXT("Image/BackGround/ForestBG.jpg")); //��� ��Ʈ ���� ����̹��� ���� ����.

	// ũ���� ������ ����
	CREATURE->Init();
	
	// ũ��ó �̹��� ������ ����
	RENDER->LoadImageFiles(TEXT("EntRun"), TEXT("Image/Creature/Ent/Run/Run"), TEXT("png"), 9);

	// ī�޶� ����
	RENDER->CreateCamera(CAM_MAIN, 3000, 1000, VIEW_WIDTH, VIEW_HEIGHT);
}


PlayScene::~PlayScene()
{
}


void PlayScene::OnEnter()
{
	// ��� �̹��� ��������Ʈ�� ����
	NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("ForestBG")), 1.0f, 0, 0));

	// �׽�Ʈ�� ũ���� ����
	OBJECT->CreateCreature(OBJ_ENT, Vector(500, 500), Vector(100, 100));

	// ī�޶� ����
	RENDER->GetCamera(CAM_MAIN)->SetScreenRect(100, 100, 600, 400);
}

void PlayScene::OnUpdate(float deltaTime)
{
	OBJECT->Update(deltaTime);
	m_example.Update(deltaTime);

	if (INPUT->IsKeyDown(VK_F3))
	{
	}

}

void PlayScene::OnExit()
{
	//Exit	
}

void PlayScene::OnDraw()
{
	Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
	pMainCamera->Draw(m_pBg, Vector(0, 0));
	OBJECT->Draw(pMainCamera);
	m_example.Render();
}