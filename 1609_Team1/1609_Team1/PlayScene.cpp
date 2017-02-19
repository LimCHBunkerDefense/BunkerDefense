#include "PlayScene.h"



PlayScene::PlayScene() : m_attackedColor(ColorF::Red)
{
	// ũ���� �����Ǵ� ����h�� ����. ���� ���콺�� ���� �ǽð� ��ȭ
	//m_heightOfCreature = 600;

	//ĳ���� ��Ÿ���� �̹���
	RENDER->LoadImageFiles(TEXT("Idle_Pistol"), TEXT("Image/Item/Pistol/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("Attack_Pistol"), TEXT("Image/Item/Pistol/Attack/Attack"), TEXT("png"), 4);
	RENDER->LoadImageFiles(TEXT("Idle_Machine"), TEXT("Image/Item/MachineGun/Idle/MachineGunIdle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("Attack_Machine"), TEXT("Image/Item/MachineGun/Shot/MachineGunShot"), TEXT("png"), 8);
	RENDER->LoadImageFiles(TEXT("Idle_Laser"), TEXT("Image/Item/LaserGun/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("Attack_Laser"), TEXT("Image/Item/LaserGun/Shot/Shot"), TEXT("png"), 22);
	RENDER->LoadImageFiles(TEXT("Idle_Shot"), TEXT("Image/Item/ShotGun/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("Attack_Shot"), TEXT("Image/Item/ShotGun/Shot/Shot"), TEXT("png"), 4);
	RENDER->LoadImageFiles(TEXT("Reload_Shot"), TEXT("Image/Item/ShotGun/Reload/Reload"), TEXT("png"), 11);

	// ��� �̹��� ������ ����
	RENDER->LoadImageFile(TEXT("ForestBG"), TEXT("Image/BackGround/ForestBG.jpg")); 
	RENDER->LoadImageFile(TEXT("DroughtBG"), TEXT("Image/BackGround/DroughtBG.png"));

	// UI �̹��� ������ ����
	RENDER->LoadImageFile(TEXT("Aim"), TEXT("Image/UI/Aim/Aim.png"));
	//RENDER->LoadImageFile(TEXT("Minimap"), TEXT("Image/UI/Minimap/Minimap.png"));
	RENDER->LoadImageFile(TEXT("Radar"), TEXT("Image/UI/Minimap/RadarBG.png"));
	
	// ũ��ó �̹��� ����
	// Ent
	RENDER->LoadImageFiles(TEXT("EntIdle"), TEXT("Image/Creature/Ent/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("EntRun"), TEXT("Image/Creature/Ent/Run/Run"), TEXT("png"), 21);	
	RENDER->LoadImageFiles(TEXT("EntAttack"), TEXT("Image/Creature/Ent/Attack/Attack"), TEXT("png"), 16);
	RENDER->LoadImageFiles(TEXT("EntDie"), TEXT("Image/Creature/Ent/Die/Die"), TEXT("png"), 7);
	// Lava
	RENDER->LoadImageFiles(TEXT("LavaIdle"), TEXT("Image/Creature/Lava/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("LavaRun"), TEXT("Image/Creature/Lava/Run/Run"), TEXT("png"), 23);
	RENDER->LoadImageFiles(TEXT("LavaAttack"), TEXT("Image/Creature/Lava/Attack/Attack"), TEXT("png"), 21);
	RENDER->LoadImageFiles(TEXT("LavaDie"), TEXT("Image/Creature/Lava/Die/Die"), TEXT("png"), 13);
	// DarkPriest
	RENDER->LoadImageFiles(TEXT("DarkpriestIdle"), TEXT("Image/Creature/DarkPriest/Idle/Idle"), TEXT("png"), 2);
	RENDER->LoadImageFiles(TEXT("DarkpriestRun"), TEXT("Image/Creature/DarkPriest/Walk/Walk"), TEXT("png"), 16);
	RENDER->LoadImageFiles(TEXT("DarkpriestAttack"), TEXT("Image/Creature/DarkPriest/Attack/Attack"), TEXT("png"), 32);
	RENDER->LoadImageFiles(TEXT("DarkpriestDie"), TEXT("Image/Creature/DarkPriest/Die/Die"), TEXT("png"), 23);

	//�������̽� UI �̹��� ��������
	RENDER->LoadImageFile(TEXT("StageFont_UI"), TEXT("Image/UI/InterfaceUI/stage.png"));
	RENDER->LoadImageFile(TEXT("ItemBar_UI"), TEXT("Image/UI/InterfaceUI/ItemBarUI.png"));
	RENDER->LoadImageFile(TEXT("Bunker_UI"), TEXT("Image/UI/InterfaceUI/Bunker_UI.png"));
	RENDER->LoadImageFile(TEXT("ScoreUI"), TEXT("Image/UI/InterfaceUI/Score.png"));
	RENDER->LoadImageFile(TEXT("MoneyUI"), TEXT("Image/UI/InterfaceUI/money.png"));

	//Bullet ����
	RENDER->LoadImageFiles(TEXT("PSBulletIdle"), TEXT("Image/Bullet/Pistol/Idle/Idle"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("PSBulletExplode"), TEXT("Image/Bullet/Pistol/Explode/Explode"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("MGBulletIdle"), TEXT("Image/Bullet/Machinegun/Idle/Idle"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("MGBulletExplode"), TEXT("Image/Bullet/Machinegun/Explode/Explode"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("SGBulletIdle"), TEXT("Image/Bullet/Shotgun/Idle/Idle"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("SGBulletExplode"), TEXT("Image/Bullet/Shotgun/Explode/Explode"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("LGBulletIdle"), TEXT("Image/Bullet/Lasergun/Idle/Idle"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("LGBulletExplode"), TEXT("Image/Bullet/Lasergun/Explode/Explode"), TEXT("png"), 1);

	//Grenade ����
	RENDER->LoadImageFiles(TEXT("Grenade"), TEXT("Image/Item/Grenade/Grenade"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("Explode"), TEXT("Image/Item/Explode/explode"), TEXT("png"), 7);
	RENDER->LoadImageFiles(TEXT("Flame_idle"), TEXT("Image/Item/Grenade/Napalm"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("Flame_Explode"), TEXT("Image/Item/Flame/flame"), TEXT("png"), 30);
	RENDER->LoadImageFiles(TEXT("Plane_idle"), TEXT("Image/Item/Grenade/AirPlane"), TEXT("png"), 1);
	RENDER->LoadImageFiles(TEXT("Plane_Explode"), TEXT("Image/Item/SkyBomb/airBomb"), TEXT("png"), 42);

	//���� ICON ��������
	RENDER->LoadImageFile(TEXT("PistolOn"),		TEXT("Image/Item/Icon/ico_pistol_on.png"));
	RENDER->LoadImageFile(TEXT("PistolOff"),	TEXT("Image/Item/Icon/ico_pistol_off.png"));
	RENDER->LoadImageFile(TEXT("ShotGunOn"), TEXT("Image/Item/Icon/ico_shot_on.png"));
	RENDER->LoadImageFile(TEXT("ShotGunOff"), TEXT("Image/Item/Icon/ico_shot_off.png"));
	RENDER->LoadImageFile(TEXT("MachineGunOn"), TEXT("Image/Item/Icon/ico_machine_on.png"));
	RENDER->LoadImageFile(TEXT("MachineGunOff"), TEXT("Image/Item/Icon/ico_machine_off.png"));
	RENDER->LoadImageFile(TEXT("LaserGunOn"),		TEXT("Image/Item/Icon/ico_laser_on.png"));
	RENDER->LoadImageFile(TEXT("LaserGunOff"),		TEXT("Image/Item/Icon/ico_laser_off.png"));
	RENDER->LoadImageFile(TEXT("FixOn"), TEXT("Image/Item/Icon/ico_fix_on.png"));
	RENDER->LoadImageFile(TEXT("FixOff"), TEXT("Image/Item/Icon/ico_fix_off.png"));
	RENDER->LoadImageFile(TEXT("GrenadeOn"), TEXT("Image/Item/Icon/ico_grenade_on.png"));
	RENDER->LoadImageFile(TEXT("GrenadeOff"), TEXT("Image/Item/Icon/ico_grenade_off.png"));
	RENDER->LoadImageFile(TEXT("PlaneOn"), TEXT("Image/Item/Icon/ico_plane_on.png"));
	RENDER->LoadImageFile(TEXT("PlaneOff"), TEXT("Image/Item/Icon/ico_plane_off.png"));
	RENDER->LoadImageFile(TEXT("NapalmOn"), TEXT("Image/Item/Icon/ico_capsule_on.png"));
	RENDER->LoadImageFile(TEXT("NapalmOff"), TEXT("Image/Item/Icon/ico_capsule_off.png"));

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

	// BGM ����
	SOUND->LoadFile("MainBGM_0", "Sound/BGM/Main/Main_0.mp3", true);
	SOUND->LoadFile("MainBGM_1", "Sound/BGM/Main/Main_1.mp3", true);
	SOUND->LoadFile("MainBGM_2", "Sound/BGM/Main/Main_2.mp3", true);
	SOUND->LoadFile("ShopBGM_0", "Sound/BGM/Shop/Shop_0.mp3", true);


	// ��Ŀ ü�� ���� ����
	m_bunkerLife = new UIProgressBar(Vector(24, 830), Vector(320, 45), ColorF::YellowGreen, ColorF::LightGoldenrodYellow);
	m_bunkerLife->SetMinMaxColor(ColorF::Red, ColorF::YellowGreen);

	// �Ѿ� ������ ���� ����
	m_bulletGage = new UIBulletBar(Vector(24, 770), Vector(320, 45), ColorF::DarkBlue, ColorF::LightBlue);

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

	m_createdLavaCount = 0;
	m_createdEntCount = 0;
	m_createdDarkpriestCount = 0;
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
	//NEW_OBJECT(m_pMinimap, Sprite(RENDER->GetImage(TEXT("Minimap")), 1.0));
	NEW_OBJECT(m_pRadar, Sprite(RENDER->GetImage(TEXT("Radar")), 0.85, 0.0,0.0));

	// UI �̹��� ����
	NEW_OBJECT(m_stageUI, Sprite(RENDER->GetImage(TEXT("StageFont_UI"))));
	NEW_OBJECT(m_ScoreUI, Sprite(RENDER->GetImage(TEXT("ScoreUI")),0.8f));
	NEW_OBJECT(m_MoneyUI, Sprite(RENDER->GetImage(TEXT("MoneyUI")), 0.8f));
	NEW_OBJECT(m_BunkerUI, Sprite(RENDER->GetImage(TEXT("Bunker_UI"))));
	NEW_OBJECT(m_ItemBarUI, Sprite(RENDER->GetImage(TEXT("ItemBar_UI"))));

	// PlayScene BGM ����
	SOUND->Play("MainBGM_0", 1.0f);			// �ĺ��� 1
	// SOUND->Play("MainBGM_1", 0.5f);		// �ĺ��� 2
	// SOUND->Play("MainBGM_2", 0.5f);		// �ĺ��� 3

	//ico pistol
	NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOn"))));
	NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOff"))));
	NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOff"))));	
	NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOff"))));

	NEW_OBJECT(m_ico_grenade, Sprite(RENDER->GetImage(TEXT("GrenadeOff"))));
	NEW_OBJECT(m_ico_plane, Sprite(RENDER->GetImage(TEXT("PlaneOff"))));
	NEW_OBJECT(m_ico_napalm, Sprite(RENDER->GetImage(TEXT("NapalmOff"))));
	NEW_OBJECT(m_ico_fix, Sprite(RENDER->GetImage(TEXT("FixOn"))));

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
	OBJECT->CreateCreature(OBJ_ENT, Vector(120, 60));
	//OBJECT->CreateCreature(OBJ_LAVA, Vector(0, 180));
	//OBJECT->CreateCreature(OBJ_DARKPRIEST, Vector(120, 240));

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
	ITEM_TAG item_tag = OBJECT->GetPlayer()->GetItemState();
	GRENADE_STATE gre_state = OBJECT->GetPlayer()->GetGreState();
	if (item_tag == ITEM_PISTOL) {	NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOn"))));	}
	else { NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOff")))); }
	if (item_tag == ITEM_SHOTGUN) { NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOn")))); }
	else { NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOff")))); }
	if (item_tag == ITEM_MACHINEGUN) { NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOn")))); }
	else { NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOff")))); }
	if (item_tag == ITEM_LASERGUN) { NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOn")))); }
	else { NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOff")))); }

	if (gre_state == GRENADE_IDLE) { NEW_OBJECT(m_ico_grenade, Sprite(RENDER->GetImage(TEXT("GrenadeOn")))); }
	else { NEW_OBJECT(m_ico_grenade, Sprite(RENDER->GetImage(TEXT("GrenadeOff")))); }
	if (gre_state == AIRBOMB_IDLE) { NEW_OBJECT(m_ico_plane, Sprite(RENDER->GetImage(TEXT("PlaneOn")))); }
	else { NEW_OBJECT(m_ico_plane, Sprite(RENDER->GetImage(TEXT("PlaneOff")))); }
	if (gre_state == FLAME_IDLE) { NEW_OBJECT(m_ico_napalm, Sprite(RENDER->GetImage(TEXT("NapalmOn")))); }
	else { NEW_OBJECT(m_ico_napalm, Sprite(RENDER->GetImage(TEXT("NapalmOff")))); }
	NEW_OBJECT(m_ico_fix, Sprite(RENDER->GetImage(TEXT("FixOn"))));

	/*if (gre_state == GRENADE_IDLE) { NEW_OBJECT(m_ico_fix, Sprite(RENDER->GetImage(TEXT("PistolOn")))); }
	else { NEW_OBJECT(m_ico_fix, Sprite(RENDER->GetImage(TEXT("PistolOff")))); */


	/* Too Long
	switch (OBJECT->GetPlayer()->GetItemState()) {
		case ITEM_PISTOL: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOn"))));
			NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOff"))));
			NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOff"))));
			NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOff"))));
			break;
		}
		case ITEM_SHOTGUN: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOff"))));
			NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOn"))));
			NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOff"))));
			NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOff"))));
			break;
		}
		case ITEM_MACHINEGUN: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOff"))));
			NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOff"))));
			NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOn"))));
			NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOff"))));
			break;
		}
		case ITEM_LASERGUN: {
			NEW_OBJECT(m_ico_pistol, Sprite(RENDER->GetImage(TEXT("PistolOff"))));
			NEW_OBJECT(m_ico_shotGun, Sprite(RENDER->GetImage(TEXT("ShotGunOff"))));
			NEW_OBJECT(m_ico_machineGun, Sprite(RENDER->GetImage(TEXT("MachineGunOff"))));
			NEW_OBJECT(m_ico_laserGun, Sprite(RENDER->GetImage(TEXT("LaserGunOn"))));
			break;
		}
	}*/
}

void PlayScene::OnExit()
{
	//Exit	

	// PlayScene ���� �� Pause ����
	SOUND->Pause("MainBGM_0");			// �ĺ��� 1
	// SOUND->Pause("MainBGM_1");		// �ĺ��� 2
	// SOUND->Pause("MainBGM_2");		// �ĺ��� 3
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
		pMinimapCamera->DrawFilledRect(Vector(pos.x - colSize.x * 0.5, pos.y - colSize.y), colSize, ColorF::Blue);	// �̴ϸ� �� ũ������ �浹ü ǥ�����ִ� �κ�
	}

	//źȯ �� �߱�
	list<Object*> pBulletList = OBJECT->GetBulletList();
	FOR_LIST(Object*, pBulletList)
	{
		Vector pos = (*it)->Position();
		Vector colSize = (*it)->Collider().size;
		pMinimapCamera->DrawFilledCircle(pos - 4, Vector(8, 8), ColorF::DeepPink);
		//pMinimapCamera->DrawLine((*it)->GetStartPos().x, (*it)->GetStartPos().y, OBJECT->GetPlayer()->Position().x, OBJECT->GetPlayer()->Position().y, ColorF::DeepPink, 2);
		//pMinimapCamera->DrawFilledRect(pos - colSize * 0.5, colSize, ColorF::Blue);	// �̴ϸ� �� �Ѿ��� �浹ü ǥ�����ִ� �κ�
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

	// Aim �׷��ִ� �κ�
	pUICamera->Draw(m_pAim, Vector(VIEW_WIDTH * 0.5, VIEW_HEIGHT * 0.5f));

	//�÷��� UI���
	//1.Stage UI ���
	pUICamera->Draw(m_stageUI, Vector(600, 100));
	pUICamera->DrawRect(Vector(565, 125), Vector(70, 70), ColorF::Red, 3);
	pUICamera->DrawT(TEXT("1"), 590, 140, ColorF::Red, 30, ALIGN_RIGHT);
	//pUICamera->DrawT(TEXT("Stage 1"), VIEW_WIDTH / 2 - 50, 40, ColorF::White, 30, ALIGN_CENTER);

	//2.��ĿUI / ��ų UI
	pUICamera->Draw(m_ItemBarUI, Vector(146, 80));
	pUICamera->Draw(m_BunkerUI, Vector(186, 820));
	
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

	// �Ѿ� ������
	m_bulletGage->Render(pUICamera);

	//Icon

	pUICamera->Draw(m_ico_pistol, Vector(48, VIEW_HEIGHT - 852));
	pUICamera->Draw(m_ico_shotGun, Vector(109, VIEW_HEIGHT - 852));
	pUICamera->Draw(m_ico_machineGun, Vector(172, VIEW_HEIGHT - 852));
	pUICamera->Draw(m_ico_laserGun, Vector(238, VIEW_HEIGHT - 852));

	pUICamera->Draw(m_ico_grenade, Vector(48, VIEW_HEIGHT - 792));
	pUICamera->Draw(m_ico_plane, Vector(109, VIEW_HEIGHT - 792));
	pUICamera->Draw(m_ico_napalm, Vector(172, VIEW_HEIGHT - 792));
	pUICamera->Draw(m_ico_fix, Vector(238, VIEW_HEIGHT - 792));
	//pUICamera->DrawRect(Vector(146, 85), Vector(50, 50), ColorF::Red, 1);

	
	pUICamera->DrawRect(Vector(24, VIEW_HEIGHT - 130), Vector(320, 45), ColorF::Blue, 2);
	//pUICamera->DrawRect(Vector(28, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red, 1);
	//pUICamera->DrawRect(Vector(118, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red, 1);
	//pUICamera->DrawRect(Vector(208, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red,1);
	//pUICamera->DrawRect(Vector(298, VIEW_HEIGHT - 95), Vector(70, 70), ColorF::Red,1);

	// �������� ���� ���� ���
	if (OBJECT->GetPlayer()->GetCurrentItem()->GetTag() == ITEM_LASERGUN)
	{
		OBJECT->GetPlayer()->GetLaserChargerBar()->Render(pUICamera);
	}
}

void PlayScene::SetCreature(float deltaTime)
{
	int randDegree;

	// �������� 1
	if(m_gameTime / 3 > m_createdLavaCount)
	{
		randDegree = rand() % 360;
		Vector pos = MATH->ToDirection(randDegree) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();
		OBJECT->CreateCreature(OBJ_LAVA, pos);
		m_createdLavaCount++;
	}

	// �������� 2
	if ((m_gameTime -  20) / 5 > m_createdEntCount)
	{
		randDegree = rand() % 360;
		Vector pos = MATH->ToDirection(randDegree) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();
		OBJECT->CreateCreature(OBJ_ENT, pos);
		m_createdEntCount++;
	}

	// �뻧
	if (m_gameTime>100 && m_createdDarkpriestCount < 1)
	{
		randDegree = rand() % 360;
		Vector pos = MATH->ToDirection(randDegree) * MINI_WIDTH * 0.5 + OBJECT->GetPlayer()->Position();
		OBJECT->CreateCreature(OBJ_DARKPRIEST, pos);
		m_createdDarkpriestCount++;
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