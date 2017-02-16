#include "PlayScene.h"



PlayScene::PlayScene() : m_attackedColor(ColorF::Red)
{
	// ũ���� �����Ǵ� ����h�� ����. ���� ���콺�� ���� �ǽð� ��ȭ
	//m_heightOfCreature = 600;


	// ��� �̹��� ������ ����
	RENDER->LoadImageFile(TEXT("ForestBG"), TEXT("Image/BackGround/ForestBG.jpg")); 
	RENDER->LoadImageFile(TEXT("DroughtBG"), TEXT("Image/BackGround/DroughtBG.png"));

	// UI �̹��� ������ ����
	RENDER->LoadImageFile(TEXT("Aim"), TEXT("Image/UI/Aim/Aim.png"));
	RENDER->LoadImageFile(TEXT("Minimap"), TEXT("Image/UI/Minimap/Minimap.png"));
	RENDER->LoadImageFile(TEXT("Radar"), TEXT("Image/UI/Minimap/RadarBG.png"));

	// ũ���� ������ ����
	CREATURE->Init();
	
	// ũ��ó �̹��� ������ ����
	RENDER->LoadImageFiles(TEXT("EntIdle"), TEXT("Image/Creature/Ent/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("EntRun"), TEXT("Image/Creature/Ent/Run/Run"), TEXT("png"), 9);
	RENDER->LoadImageFiles(TEXT("EntAttack"), TEXT("Image/Creature/Ent/Attack/Attack"), TEXT("png"), 6);

	//�������̽� UI �̹��� ��������
	RENDER->LoadImageFile(TEXT("StageFont_UI"), TEXT("Image/UI/InterfaceUI/stage.png"));
	RENDER->LoadImageFile(TEXT("Bunker_UI"), TEXT("Image/UI/InterfaceUI/Bunker_UI.png"));
	RENDER->LoadImageFile(TEXT("ItemBar_UI"), TEXT("Image/UI/InterfaceUI/ItemBarUI.png"));
	RENDER->LoadImageFile(TEXT("ScoreUI"), TEXT("Image/UI/InterfaceUI/Score.png"));
	RENDER->LoadImageFile(TEXT("MoneyUI"), TEXT("Image/UI/InterfaceUI/money.png"));

	//Bullet ����
	RENDER->LoadImageFiles(TEXT("PistolIdle"), TEXT("Image/Bullet/Pistol/Idle/Idle"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("PistolExplode"), TEXT("Image/Bullet/Pistol/Explode/Explode"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("MachinegunIdle"), TEXT("Image/Bullet/Machinegun/Idle/Idle"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("MachinegunExplode"), TEXT("Image/Bullet/Machinegun/Explode/Explode"), TEXT("png"), 1);

	//Grenade �ӽ÷� ����
	RENDER->LoadImageFiles(TEXT("Grenade"), TEXT("Image/Item/Grenade/Grenade"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("Explode"), TEXT("Image/Item/Explode/explode"), TEXT("png"), 7);
	RENDER->LoadImageFiles(TEXT("Flame_idle"), TEXT("Image/Item/Grenade/Napalm"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("Flame_Explode"), TEXT("Image/Item/Flame/flame"), TEXT("png"), 30);

	//���� ICON ��������
	RENDER->LoadImageFile(TEXT("PistolOn"),		TEXT("Image/Item/Icon/ico_pistol_on.png"));
	RENDER->LoadImageFile(TEXT("PistolOff"),	TEXT("Image/Item/Icon/ico_pistol_off.png"));
	RENDER->LoadImageFile(TEXT("LaserOn"),		TEXT("Image/Item/Icon/ico_laser_on.png"));
	RENDER->LoadImageFile(TEXT("LaserOff"),		TEXT("Image/Item/Icon/ico_laser_off.png"));
	RENDER->LoadImageFile(TEXT("MachineOn"),	TEXT("Image/Item/Icon/ico_machine_on.png"));
	RENDER->LoadImageFile(TEXT("MachineOff"),	TEXT("Image/Item/Icon/ico_machine_off.png"));

	// ���� �̹��� ��������
	RENDER->LoadImageFile(TEXT("Num0"), TEXT("Image/UI/ScoreNUM/Num0.png"));
	RENDER->LoadImageFile(TEXT("Num1"), TEXT("Image/UI/ScoreNUM/Num1.png"));
	RENDER->LoadImageFile(TEXT("Num2"), TEXT("Image/UI/ScoreNUM/Num2.png"));
	RENDER->LoadImageFile(TEXT("Num3"), TEXT("Image/UI/ScoreNUM/Num3.png"));
	RENDER->LoadImageFile(TEXT("Num4"), TEXT("Image/UI/ScoreNUM/Num4.png"));
	RENDER->LoadImageFile(TEXT("Num5"), TEXT("Image/UI/ScoreNUM/Num5.png"));
	RENDER->LoadImageFile(TEXT("Num6"), TEXT("Image/UI/ScoreNUM/Num6.png"));
	RENDER->LoadImageFile(TEXT("Num7"), TEXT("Image/UI/ScoreNUM/Num7.png"));
	RENDER->LoadImageFile(TEXT("Num8"), TEXT("Image/UI/ScoreNUM/Num8.png"));
	RENDER->LoadImageFile(TEXT("Num9"), TEXT("Image/UI/ScoreNUM/Num9.png"));

	// ��Ŀ ü�� ���� ����
	m_bunkerLife = new UIProgressBar(Vector(20, 35), Vector(240, 30), ColorF::YellowGreen, ColorF::LightYellow);
	m_bunkerLife->SetMinMaxColor(ColorF::Red, ColorF::Green);

	// ī�޶� ����
	RENDER->CreateCamera(CAM_MAIN, MAP_WIDTH, MAP_HEIGHT, VIEW_WIDTH, VIEW_HEIGHT);
	RENDER->CreateCamera(CAM_MINIMAP, MINI_WIDTH, MINI_HEIGHT* 5, MINI_WIDTH, MINI_HEIGHT * 2);
	RENDER->CreateCamera(CAM_UI, VIEW_WIDTH, VIEW_HEIGHT, VIEW_WIDTH, VIEW_HEIGHT);

	pMainCamera = RENDER->GetCamera(CAM_MAIN);
	pMinimapCamera = RENDER->GetCamera(CAM_MINIMAP);
	pUICamera = RENDER->GetCamera(CAM_UI);

	// ũ���� ���ݿ� ���� ��鸲 ������ ���ؼ� �ʱ�ȭ
	m_MainCameraPos = Vector(0, 0);
	m_swayPos = Vector(300, 0);

	// �÷��̾� ����
	OBJECT->CreatePlayer(Vector(MINI_WIDTH * 0.5F, MINI_HEIGHT), Vector(10, 10), Vector(0.5f, 1.0f));
	Object* p = OBJECT->GetPlayer();
	// ��Ŀ ����
	OBJECT->CreateBunker();
	Object* pObj = OBJECT->GetBunker();

	m_createdCretureCount = 0;
}


PlayScene::~PlayScene()
{
}


void PlayScene::OnEnter()
{
	// ��� �̹��� ��������Ʈ�� ����
	NEW_OBJECT(m_pBg, Sprite(RENDER->GetImage(TEXT("DroughtBG")), 1.8));

	// UI �̹��� ��������Ʈ�� ����
	NEW_OBJECT(m_pAim, Sprite(RENDER->GetImage(TEXT("Aim")), 0.825));
	NEW_OBJECT(m_pMinimap, Sprite(RENDER->GetImage(TEXT("Minimap")), 1.0));
	NEW_OBJECT(m_pRadar, Sprite(RENDER->GetImage(TEXT("Radar")), 0.85, 0.0,0.0));

	// UI �̹��� ����
	NEW_OBJECT(m_stageUI, Sprite(RENDER->GetImage(TEXT("StageFont_UI"))));
	NEW_OBJECT(m_ScoreUI, Sprite(RENDER->GetImage(TEXT("ScoreUI")),0.8f));
	NEW_OBJECT(m_MoneyUI, Sprite(RENDER->GetImage(TEXT("MoneyUI")), 0.8f));
	NEW_OBJECT(m_BunkerUI, Sprite(RENDER->GetImage(TEXT("Bunker_UI"))));
	NEW_OBJECT(m_ItemBarUI, Sprite(RENDER->GetImage(TEXT("ItemBar_UI"))));

	//ico pistol
	NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOn"))));
	NEW_OBJECT(m_ico_laser, Sprite(RENDER->GetImage(TEXT("LaserOff"))));
	NEW_OBJECT(m_ico_machine, Sprite(RENDER->GetImage(TEXT("MachineOff"))));	

	NEW_OBJECT(m_num1, Sprite(RENDER->GetImage(TEXT("Num1")), 1.0, 0,0));
	NEW_OBJECT(m_num2, Sprite(RENDER->GetImage(TEXT("Num2")), 1.0, 0,0));
	NEW_OBJECT(m_num3, Sprite(RENDER->GetImage(TEXT("Num3")), 1.0, 0,0));
	NEW_OBJECT(m_num4, Sprite(RENDER->GetImage(TEXT("Num4")), 1.0, 0,0));
	NEW_OBJECT(m_num5, Sprite(RENDER->GetImage(TEXT("Num5")), 1.0, 0,0));
	NEW_OBJECT(m_num6, Sprite(RENDER->GetImage(TEXT("Num6")), 1.0, 0,0));
	NEW_OBJECT(m_num7, Sprite(RENDER->GetImage(TEXT("Num7")), 1.0, 0,0));
	NEW_OBJECT(m_num8, Sprite(RENDER->GetImage(TEXT("Num8")), 1.0, 0,0));
	NEW_OBJECT(m_num9, Sprite(RENDER->GetImage(TEXT("Num9")), 1.0, 0,0));
	NEW_OBJECT(m_num0, Sprite(RENDER->GetImage(TEXT("Num0")), 1.0, 0,0));

	// ũ���� ���� ������ ���� ����(�� �����) ���� �ʱ�ȭ
	m_attackedColor.a = 0;

	// ī�޶� ����
	pMainCamera->SetScreenRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
	pMinimapCamera->SetScreenRect(VIEW_WIDTH - MINI_WIDTH - 10, VIEW_HEIGHT - MINI_HEIGHT * 2 + 50, MINI_WIDTH, MINI_HEIGHT * 2);
	pUICamera->SetScreenRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);

	// �׽�Ʈ�� ũ���� ����
	//OBJECT->CreateCreature(OBJ_ENT, Vector(120, 60));

	// ���콺 Ŀ�� ���ֱ�
	ShowCursor(false);

}

void PlayScene::OnUpdate(float deltaTime)
{
	//Icon ����
	ChangeIcon();
	// ũ���� ������ ���� ���� �ð� ������Ʈ
	m_gameTime += deltaTime;

	// ���� �ð��� ���� ũ���� ����
	//SetCreature(deltaTime);
	
	// ������Ʈ ��ü ������Ʈ
	OBJECT->Update(deltaTime);

	// ��Ŀ ü�� UIProgressBar ������Ʈ(�̰��� ��Ŀ ��ü �������� �ƴ� UI�̹Ƿ� �÷��̾����� ������ ������Ʈ �ϴ� ���� �¾ƺ���)
	m_bunkerLife->SetTargetValue(OBJECT->GetBunker()->GetCurrentLife() / OBJECT->GetBunker()->GetMaxLife());
	m_bunkerLife->Update(deltaTime);

	// m_attackedColor ���� �����Ͽ� ���ݴ��� ���� �κ����� ������ ���� �����ִ� �κ�
	if (m_attackedColor.a != 0)
	{
		// ���� ���� ��� ��鸲�� ���� ī�޶� ��ġ �� ��鸲 ��ȭ�� �ʱ�ȭ		
		if (m_attackedColor.a >= 0.4999)
		{
			pMainCamera->SetScreenRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
			m_MainCameraPos = Vector(0, 0);
		}

		// ��鸲 ���� �Լ�
		SwayScreen(deltaTime);

		// ���� ǥ�ø� ���� ȭ���� ������ ǥ�úκ��� ���� ����
		m_attackedColor.a = MATH->Clamp(m_attackedColor.a - deltaTime, 0.0f, 20.0f);				
	}
	else if(m_attackedColor.a <= 0) pMainCamera->SetScreenRect(0,0, VIEW_WIDTH, VIEW_HEIGHT);

}

void PlayScene::ChangeIcon() {
	switch (OBJECT->GetPlayer()->GetItemState()) {
		case ITEM_PISTOL: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOn"))));
			NEW_OBJECT(m_ico_machine, Sprite(RENDER->GetImage(TEXT("MachineOff"))));
			NEW_OBJECT(m_ico_laser, Sprite(RENDER->GetImage(TEXT("LaserOff"))));
			break;
		}
		case ITEM_MACHINEGUN: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOff"))));
			NEW_OBJECT(m_ico_machine, Sprite(RENDER->GetImage(TEXT("MachineOn"))));
			NEW_OBJECT(m_ico_laser, Sprite(RENDER->GetImage(TEXT("LaserOff"))));
			break;
		}
		case ITEM_LASERGUN: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOff"))));
			NEW_OBJECT(m_ico_machine, Sprite(RENDER->GetImage(TEXT("MachineOff"))));
			NEW_OBJECT(m_ico_laser, Sprite(RENDER->GetImage(TEXT("LaserOn"))));
			break;
		}
	}
}

void PlayScene::OnExit()
{
	//Exit	
}

void PlayScene::OnDraw()
{	

	// ��� �׷��ִ� �κ� (���̴� ȭ�� �¿�� �ϳ��� ��)
	DrawBG();

	// �ӽ� �̴ϸ� ���
	pMinimapCamera->Draw(m_pRadar, Vector(-24, -23));

	// �̴ϸ� �þ� ���� ǥ��
	pMinimapCamera->DrawLine(MINI_WIDTH * 0.5, MINI_HEIGHT,
		MINI_WIDTH * 0.5 - MINI_WIDTH * 0.5 * MATH->Sin(CAMERA_ANGLE * 0.5), MINI_HEIGHT - MINI_WIDTH * 0.5 * MATH->Cos(CAMERA_ANGLE * 0.5), ColorF::Yellow, 2);
	pMinimapCamera->DrawLine(MINI_WIDTH * 0.5, MINI_HEIGHT,
		MINI_WIDTH * 0.5 + MINI_WIDTH * 0.5 * MATH->Sin(CAMERA_ANGLE * 0.5), MINI_HEIGHT - MINI_WIDTH * 0.5 * MATH->Cos(CAMERA_ANGLE * 0.5), ColorF::Yellow, 2);
	// pMinimapCamera->DrawLine(MINI_WIDTH * 0.5, MINI_HEIGHT, MINI_WIDTH * 0.5, MINI_HEIGHT - MINI_WIDTH * 0.5, ColorF::Yellow, 1); �̴ϸ� ���̴��� �߾Ӽ�

	// �̴ϸ� ũ���� �����Ǵ� ���� ǥ��	
	//pMinimapCamera->DrawCircle(Vector(MINI_WIDTH * 0.5, MINI_HEIGHT), Vector(MINI_WIDTH, MINI_WIDTH), ColorF::Yellow);

	// �̴ϸʿ� �÷��̾� ��ġ ǥ��
	pMinimapCamera->DrawFilledCircle(Vector(MINI_WIDTH * 0.5 , MINI_HEIGHT), Vector(8, 8), ColorF::Yellow);

	// �̴ϸʿ� ũ���� ��ġ ǥ��
	list<Object*> pList = OBJECT->GetCreatureList();
	FOR_LIST(Object*, pList)
	{
		Vector pos = (*it)->Position();
		Vector colSize = (*it)->Collider().size;
		pMinimapCamera->DrawFilledCircle(pos - 4, Vector(8, 8), ColorF::Red);
		pMinimapCamera->DrawLine((*it)->GetStartPos().x, (*it)->GetStartPos().y, OBJECT->GetPlayer()->Position().x, OBJECT->GetPlayer()->Position().y, ColorF::Red, 2);
		//pMinimapCamera->DrawFilledRect(pos - colSize * 0.5, colSize, ColorF::Blue);	// �̴ϸ� �� ũ������ �浹ü ǥ�����ִ� �κ�
	}

	//źȯ �� �߱�
	list<Object*> pBulletList = OBJECT->GetBulletList();
	FOR_LIST(Object*, pBulletList)
	{
		Vector pos = (*it)->Position();
		pMinimapCamera->DrawFilledCircle(pos - 4, Vector(8, 8), ColorF::DeepPink);
		//pMinimapCamera->DrawLine((*it)->GetStartPos().x, (*it)->GetStartPos().y, OBJECT->GetPlayer()->Position().x, OBJECT->GetPlayer()->Position().y, ColorF::DeepPink, 2);
	}

	//����ź �� �߱�
	list<Object*> pGrenadeList = OBJECT->GetGrenadeList();
	FOR_LIST(Object*, pGrenadeList)
	{
		Vector pos = (*it)->Position();
		pMinimapCamera->DrawFilledCircle(pos - 4, Vector(8, 8), ColorF::Yellow);
		//pMinimapCamera->DrawLine((*it)->GetStartPos().x, (*it)->GetStartPos().y, OBJECT->GetPlayer()->Position().x, OBJECT->GetPlayer()->Position().y, ColorF::DeepPink, 2);
	}
	
	OBJECT->Draw(pMainCamera);
	
	/*pUICamera->Draw(OBJECT->GetPlayer()->Animation()->Current()->GetSprite(), Vector(VIEW_WIDTH * 0.5, VIEW_HEIGHT * 1.0f));*/

	// Aim �׷��ִ� �κ�
	pUICamera->Draw(m_pAim, Vector(VIEW_WIDTH * 0.5, VIEW_HEIGHT * 0.5f));

	//�÷��� UI���
	//1.Stage UI ���
	pUICamera->Draw(m_stageUI, Vector(600, 100));
	pUICamera->DrawRect(Vector(565, 125), Vector(70, 70), ColorF::Red, 3);
	pUICamera->DrawT(TEXT("1"), 590, 140, ColorF::Red, 30, ALIGN_RIGHT);
	//pUICamera->DrawT(TEXT("Stage 1"), VIEW_WIDTH / 2 - 50, 40, ColorF::White, 30, ALIGN_CENTER);

	//2.��ĿUI / ��ų UI
	pUICamera->Draw(m_BunkerUI, Vector(146, 80));
	pUICamera->Draw(m_ItemBarUI, Vector(200, 790));
	
	//3.���� ���
	//pUICamera->DrawT(TEXT("���� : "), VIEW_WIDTH - 300, 30, ColorF::White, 30, ALIGN_RIGHT);
	//pUICamera->DrawT(TEXT("��� : "), VIEW_WIDTH - 300, 70, ColorF::White, 30, ALIGN_RIGHT);
	pUICamera->Draw(m_ScoreUI, Vector(VIEW_WIDTH - 300, 45));
	ShowScore(pUICamera);
	pUICamera->Draw(m_MoneyUI, Vector(VIEW_WIDTH - 300, 100));
	ShowMoney(pUICamera);

	// ũ���Ŀ��� ���� �޾����� ��Ÿ���� ���� �κ�
	if (m_attackedColor.a != 0) pUICamera->DrawFilledRect(Vector(0,0), Vector(VIEW_WIDTH, VIEW_HEIGHT), m_attackedColor);

	//Bunker ü��
	m_bunkerLife->Render(pUICamera);

	//Icon
	pUICamera->DrawRect(Vector(20, 87), Vector(240, 45), ColorF::Blue, 1);

	pUICamera->Draw(m_ico_pistol, Vector(46, VIEW_HEIGHT-110));
	pUICamera->Draw(m_ico_machine, Vector(108, VIEW_HEIGHT - 110));
	pUICamera->Draw(m_ico_laser, Vector(170, VIEW_HEIGHT - 110));
	pUICamera->DrawRect(Vector(146, 85), Vector(50, 50), ColorF::Red, 1);


	
	pUICamera->DrawRect(Vector(28, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red, 1);
	pUICamera->DrawRect(Vector(118, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red, 1);
	pUICamera->DrawRect(Vector(208, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red,1);
	pUICamera->DrawRect(Vector(298, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red,1);


}

void PlayScene::SetCreature(float deltaTime)
{
	int creatureLimit = m_gameTime / 4;
	if (m_createdCretureCount < creatureLimit)
	{
		int x = rand() % MINI_WIDTH * 0.5;
		if (rand() % 2 == 0) x *= -1;

		int y = sqrt(pow(MINI_WIDTH * 0.5f, 2) - pow(x, 2));
		if (rand() % 2 == 0) y *= -1;

		if (y >= 0)
		{
			y = MINI_HEIGHT - y;
		}
		else
		{
			y = MINI_HEIGHT + y;
		}

		x = x + MINI_WIDTH * 0.5;
		OBJECT->CreateCreature(OBJ_ENT, Vector(x, y));
		m_createdCretureCount++;
	}

}

void PlayScene::DrawBG()
{
	Vector bgPos = OBJECT->GetSightPos();
	pMainCamera->Draw(m_pBg, bgPos);

	if(bgPos.x > 0) pMainCamera->Draw(m_pBg, bgPos - Vector(1920 * 2 * 1.8, 0));
	else pMainCamera->Draw(m_pBg, bgPos + Vector(1920 * 2 * 1.8, 0));
}

void PlayScene::SwayScreen(float deltaTime)
{
	if (m_MainCameraPos.x <= -10) m_swayPos *= -1;
	else if (m_MainCameraPos.x >= 10) m_swayPos *= -1;

	m_MainCameraPos += m_swayPos *deltaTime;

	pMainCamera->SetScreenRect(m_MainCameraPos.x, m_MainCameraPos.y, VIEW_WIDTH, VIEW_HEIGHT);
}

void PlayScene::ShowMoney(Camera* pCamera)
{
	int money = OBJECT->GetPlayer()->GetMoney();
	int num = 0;

	// ���� �ڸ�
	num = money % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 40, 80));

	// ���� �ڸ�
	num = money / 10 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 70, 80));

	// ���� �ڸ�
	num = money / 100 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 100, 80));

	// õ�� �ڸ�
	num = money / 1000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 130, 80));

	// ���� �ڸ�
	num = money / 10000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 160, 80));

	// �ʸ��� �ڸ�
	num = money / 100000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 190, 80));

	// �鸸�� �ڸ�
	num = money / 1000000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 220, 80));
}

void PlayScene::ShowScore(Camera* pCamera)
{
	int score = OBJECT->GetPlayer()->GetScore();
	int num = 0;

	// ���� �ڸ�
	num = score % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 40, 25));

	// ���� �ڸ�
	num = score / 10 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 70, 25));

	// ���� �ڸ�
	num = score / 100 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 100, 25));

	// õ�� �ڸ�
	num = score / 1000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 130, 25));

	// ���� �ڸ�
	num = score / 10000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 160, 25));

	// �ʸ��� �ڸ�
	num = score / 100000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 190, 25));

	// �鸸�� �ڸ�
	num = score / 1000000 % 10;
	DrawNum(pCamera, num, Vector(VIEW_WIDTH - 220, 25));
}

void PlayScene::DrawNum(Camera* pCamera, int num, Vector leftTop)
{
	switch (num)
	{
	case 0:
		pCamera->Draw(m_num0, leftTop, 1);
		break;
	case 1:
		pCamera->Draw(m_num1, leftTop, 1);
		break;
	case 2:
		pCamera->Draw(m_num2, leftTop, 1);
		break;
	case 3:
		pCamera->Draw(m_num3, leftTop, 1);
		break;
	case 4:
		pCamera->Draw(m_num4, leftTop, 1);
		break;
	case 5:
		pCamera->Draw(m_num5, leftTop, 1);
		break;
	case 6:
		pCamera->Draw(m_num6, leftTop, 1);
		break;
	case 7:
		pCamera->Draw(m_num7, leftTop, 1);
		break;
	case 8:
		pCamera->Draw(m_num8, leftTop, 1);
		break;
	case 9:
		pCamera->Draw(m_num9, leftTop, 1);
		break;
	}
}