#pragma once

#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#define VIEW_WIDTH		1200
#define VIEW_HEIGHT		900

#define FPS				100		// 초당 프레임수

#define KEY_COUNT		256
#define MOUSE_COUNT		3

#define SOUND_MAX_CHANNEL	10

#define CAMERA_ANGLE			60
#define SIGHTHEIGHT_MIN			0.0f		// 플레이어의 상하 시야각의 최소값
#define SIGHTHEIGHT_MAX			600.0f		// 플레이어의 상하 시야각의 최대값
#define SIGHTHEIGHT_DEFAULT		500.0f		// 플레이어의 상하 시야각의 초기 시작값
#define MAP_WIDTH				1920
#define MAP_HEIGHT				1080
#define MINI_WIDTH				VIEW_WIDTH/5
#define	MINI_HEIGHT				VIEW_HEIGHT/5
#define CAMERA_LEFT				90+CAMERA_ANGLE/2
#define CAMERA_RIGHT			90-CAMERA_ANGLE/2
#define CHARACTER_X				VIEW_WIDTH*0.5F-30
#define CHARACTER_Y				VIEW_HEIGHT-30
#define ROTATE_SPEED			10
#define SIGHT					VIEW_WIDTH/2
#define GRENADE_SIZE			10

#define EPSILON					0.001


#define NEW_OBJECT(p, type) p = new type
#define DELETE_OBJECT(p) if ((p) != NULL) { delete (p); (p) = NULL; }
#define DELETE_OBJECTS(p) if ((p) != NULL) { delete[] (p); (p) = NULL; }
#define DpELETE_OBJECT()	if ((p) != NULL) { delete (p); (p) = NULL; }
#define DELETE_OBJECTS(p)	if ((p) != NULL) { delete[] (p); (p) = NULL; }
#define RELEASE_OBJECT(p)	if ((p) != NULL) { (p)->Release(); (p) = NULL; }
#define FOR_LIST(type, li) for (list<type>::iterator it = li.begin(); it != li.end(); it++)

/*
* VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
* 0x40 : unassigned
* VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
*/
//숫자 0 ~ 9 까지 키보드 좌측 키패드 숫자는 VK_NUMPAD0 ~VK_NUMPAD9 입니다.
#define VK_0		0x30
#define VK_1		0x31
#define VK_2		0x32
#define VK_3		0x33
#define VK_4		0x34
#define VK_5		0x35
#define VK_6		0x36
#define VK_7		0x37
#define VK_8		0x38
#define VK_9		0x39

// 'A' - 'Z'
#define VK_A				0x41
#define VK_B				0x42
#define VK_C				0x43
#define VK_D				0x44
#define VK_E				0x45
#define VK_F				0x46
#define VK_G				0x47
#define VK_H				0x48
#define VK_I				0x49
#define VK_J				0x4A
#define VK_K				0x4B
#define VK_L				0x4C
#define VK_M				0x4D
#define VK_N				0x4E
#define VK_O				0x4F
#define VK_P				0x50
#define VK_Q				0x51
#define VK_R				0x52
#define VK_S				0x53
#define VK_T				0x54
#define VK_U				0x55
#define VK_V				0x56
#define VK_W				0x57
#define VK_X				0x58
#define VK_Y				0x59
#define VK_Z				0x5A

enum KEY_STATE
{
	KEY_NONE, KEY_DOWN, KEY_UP, KEY_PRESS,
};

enum MOUSE_STATE
{
	MOUSE_NONE, MOUSE_DOWN, MOUSE_UP, MOUSE_PRESS, MOUSE_DRAG,
};

enum MOUSE_BUTTON
{
	MOUSE_LEFT, MOUSE_CENTER, MOUSE_RIGHT,
};

enum WND_TAG
{
	WND_NONE, WND_MAIN,
};

enum ALIGN_TYPE
{
	ALIGN_LEFT = 0, ALIGN_CENTER = 1, ALIGN_RIGHT = 2,
};

enum GRAPHICS_TYPE
{
	GRAPHICS_NONE, GRAPHICS_LINE, GRAPHICS_RECT, GRAPHICS_CIRCLE,
};

enum CAMERA_TAG
{
	CAM_NONE, CAM_MAIN, CAM_UI, CAM_MINIMAP,
};

enum SCENE_TAG
{
	SCENE_NONE, SCENE_START, SCENE_PLAY, SCENE_SHOP, SCENE_END,
};

enum OBJ_TAG
{
	OBJ_NONE, OBJ_PLAYER, 
	OBJ_LAVA, OBJ_ENT, OBJ_DARKPRIEST,
	OBJ_BUNKER, OBJ_BULLET, OBJ_GRENADE,
};

enum ITEMTYPE_TAG																// 중분류 아이템 태그
{	
	ITEMTYPE_NONE, ITEMTYPE_WEAPON, ITEMTYPE_BULLET, ITEMTYPE_USINGITEM,		
};

enum ITEM_TAG																	// 소분류 아이템 태그
{ 
	ITEM_NONE = 0, 
	ITEM_PISTOL = 1001, ITEM_SHOTGUN, ITEM_MACHINEGUN,  ITEM_LASERGUN,
	ITEM_PSBULLET = 2001, ITEM_SGBULLET, ITEM_MGBULLET, ITEM_LGBULLET,
	ITEM_GRENADE = 3001, ITEM_AIRBOMB, ITEM_RAVAREGION, ITEM_BUNKERREPAIR,
};

enum BUTTON_TAG
{
	BUTTON_NONE, 
	BUTTON_COUNT, BUTTON_BUY, BUTTON_EXIT,										// 수량 버튼, 구매 버튼, 나가기 버튼
	BUTTON_WEAPON, BUTTON_BULLET, BUTTON_USINGITEM,								// 중분류 - 무기/총알/소모품
	BUTTON_FIRST, BUTTON_SECOND, BUTTON_THIRD, BUTTON_FORTH,					// 소분류 - 버튼 4개 
};

enum PLAYER_STATE
{
	PLAYER_NONE, PLAYER_ATTACK, PLAYER_SHOP, PLAYER_THROW,
};

enum GUN_STATE
{
	GUN_NONE, GUN_IDLE, GUN_SHOT, GUN_RELOAD,
};

//따로 둘 경우 애니메이션 ID로 불러올 때 값 문제가 있어서 일단 여기에 추가했음. 나중에 int를 바꿔서 오버라이딩하거나 enum 이름을 바꿔야할 듯.


//크리쳐를 구분할 태그 생성(일단 테스트용)
enum CREATUR_TAG
{
	CREATUR_ENT, CREATUR_HYD, CREATUR_ZERG,
};

enum CREATURE_STATE
{
	CREATURE_NONE, CREATURE_IDLE, CREATURE_RUN, CREATURE_ATTACK, CREATURE_DEAD, 
};

enum BULLET_STATE
{
	BULLET_NONE = 100, BULLET_IDLE, BULLET_EXPLODE,
};



enum DIRECTION_TAG
{
	DIRECTION_LEFT, DIRECTION_RIGHT, DIRECTION_CENTER,
};
enum TEXT_ALIGN
{
	TEXT_ALIGN_LEFT = 0, TEXT_ALIGN_RIGHT = 1, TEXT_ALIGN_CENTER = 2,
};

enum GRENADE_STATE {
	GRENADE_NONE=200, GRENADE_IDLE, GRENADE_EXPLODE, FLAME_IDLE, FLAME_EXPLODE, AIRBOMB_IDLE, AIRBOMB_EXPLODE,
};

enum PROGRESS_STATE
{
	PROGRESS_STATE_NONE,
	PROGRESS_STATE_CHANGE,
	PROGRESS_STATE_DRAG,
};

enum PLAYER_ANISTATE {
	ANY_NONE=300, IDLE_PISTOL, SHOT_PISTOL, IDLE_MACHINE, SHOT_MACHINE, IDLE_LASER, SHOT_LASER, IDLE_SHOT, SHOT_SHOT, RELOAD_SHOT,
};
