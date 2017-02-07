#include "PlayScene.h"



PlayScene::PlayScene()
{
	// ũ���� �����Ǵ� ����h�� ����. ���� ���콺�� ���� �ǽð� ��ȭ
	m_heightOfCreature = 300;


	// ��� �̹��� ������ ����
	RENDER->LoadImageFile(TEXT("ForestBG"), TEXT("Image/BackGround/ForestBG.jpg")); //��� ��Ʈ ���� ����̹��� ���� ����.

	// ũ���� ������ ����
	CREATURE->Init();
	
	// ũ��ó �̹��� ������ ����
	RENDER->LoadImageFiles(TEXT("EntRun"), TEXT("Image/Creature/Ent/Run/Run"), TEXT("png"), 9);

	// ī�޶� ����
	RENDER->CreateCamera(CAM_MAIN, 1920, 1200, VIEW_WIDTH, VIEW_HEIGHT);
	RENDER->CreateCamera(CAM_MINIMAP, MINI_WIDTH, MINI_HEIGHT * 2, MINI_WIDTH, MINI_HEIGHT);

}


PlayScene::~PlayScene()
{
}


void PlayScene::OnEnter()
{
	// ��� �̹��� ��������Ʈ�� ����
	NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("ForestBG")), 1.0f, 0, 0));

	// �÷��̾� ����
	OBJECT->CreatePlayer(Vector(VIEW_WIDTH * 0.5F, VIEW_HEIGHT), Vector(10, 10), Vector(0.5f, 1.0f));

	// ī�޶� ����
	RENDER->GetCamera(CAM_MAIN)->SetScreenRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
	RENDER->GetCamera(CAM_MINIMAP)->SetScreenRect(VIEW_WIDTH - MINI_WIDTH/2, VIEW_HEIGHT, MINI_WIDTH, MINI_HEIGHT);
}

void PlayScene::OnUpdate(float deltaTime)
{
	// ũ���� ������ ���� ���� �ð� ������Ʈ
	m_gameTime += deltaTime;

	// ���� �ð��� ���� ũ���� ����
	SetCreature(deltaTime);
	
	// ������Ʈ ��ü ������Ʈ
	OBJECT->Update(deltaTime);

	// �� ä���� �߰� (170207 ������)
	if (INPUT->IsKeyDown(VK_F3))
	{
		SCENE->ChangeScene(SCENE_SHOP);
	}

}

void PlayScene::OnExit()
{
	//Exit	
}

void PlayScene::OnDraw()
{
	Camera* pMainCamera = RENDER->GetCamera(CAM_MAIN);
	Camera* pMinimapCamera = RENDER->GetCamera(CAM_MINIMAP);

	pMainCamera->Draw(m_pBg, Vector(0, 0));
	pMainCamera->DrawFilledRect(OBJECT->GetPlayer()->Position() - Vector(50, 50), Vector(100, 100), ColorF::Aqua);
	OBJECT->Draw(pMainCamera);
}

void PlayScene::SetCreature(float deltaTime)
{
	
	int x = rand() % 1200;
	OBJECT->CreateCreature(OBJ_ENT, Vector(x, m_heightOfCreature));
}