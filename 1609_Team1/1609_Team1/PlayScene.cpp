#include "PlayScene.h"



PlayScene::PlayScene()
{
	// ũ���� �����Ǵ� ����h�� ����. ���� ���콺�� ���� �ǽð� ��ȭ
	m_heightOfCreature = 600;


	// ��� �̹��� ������ ����
	RENDER->LoadImageFile(TEXT("ForestBG"), TEXT("Image/BackGround/ForestBG.jpg")); //��� ��Ʈ ���� ����̹��� ���� ����.

	// ũ���� ������ ����
	CREATURE->Init();
	
	// ũ��ó �̹��� ������ ����
	RENDER->LoadImageFiles(TEXT("EntIdle"), TEXT("Image/Creature/Ent/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("EntRun"), TEXT("Image/Creature/Ent/Run/Run"), TEXT("png"), 9);
	RENDER->LoadImageFiles(TEXT("EntAttack"), TEXT("Image/Creature/Ent/Attack/Attack"), TEXT("png"), 6);

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
	RENDER->GetCamera(CAM_MINIMAP)->SetScreenRect(VIEW_WIDTH - MINI_WIDTH, VIEW_HEIGHT - MINI_HEIGHT, MINI_WIDTH, MINI_HEIGHT);

	m_createdCretureCount = 0;
}

void PlayScene::OnUpdate(float deltaTime)
{
	// ũ���� ������ ���� ���� �ð� ������Ʈ
	m_gameTime += deltaTime;

	// ���� �ð��� ���� ũ���� ����
	SetCreature(deltaTime);
	
	// ������Ʈ ��ü ������Ʈ
	OBJECT->Update(deltaTime);
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
	pMinimapCamera->DrawFilledRect(Vector(0,0), Vector(MINI_WIDTH,MINI_HEIGHT), ColorF::Green);

	// �̴ϸʿ� ũ���� ��ġ ǥ��
	list<Object*> pList = OBJECT->GetCreatureList();
	FOR_LIST(Object*, pList)
	{
		Vector pos = (*it)->Position();
		pMinimapCamera->DrawFilledRect(pos - 10, Vector(20, 20), ColorF::Red);
	}


	OBJECT->Draw(pMainCamera);
}

void PlayScene::SetCreature(float deltaTime)
{
	int creatureLimit = m_gameTime / 3;
	if (m_createdCretureCount < creatureLimit)
	{
		int x = rand() % MINI_WIDTH;
		int y = sqrt(pow(MINI_WIDTH * 0.5, 2) - pow(x - MINI_WIDTH * 0.5, 2));
		if (rand() % 2 == 0) y *= -1;
		OBJECT->CreateCreature(OBJ_ENT, Vector(x, y));
		m_createdCretureCount++;
	}

}