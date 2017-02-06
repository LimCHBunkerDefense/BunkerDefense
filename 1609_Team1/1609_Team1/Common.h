#pragma once

#define VIEW_WIDTH		1200
#define VIEW_HEIGHT		900

#define FPS				100		// 초당 프레임수

#define KEY_COUNT		256
#define MOUSE_COUNT		3

#define SOUND_MAX_CHANNEL	10

#define CAMERA_ANGLE	60
#define MINI_WIDTH		160
#define	MINI_HEIGHT		120
#define CAMERA_LEFT		90+CAMERA_ANGLE/2
#define CAMERA_RIGHT	90-CAMERA_ANGLE/2
#define GROUND_HEIGHT	400
#define CHARACTER_X		VIEW_WIDTH*0.5F-30
#define CHARACTER_Y		VIEW_HEIGHT-30
#define ROTATE_SPEED	2


#define NEW_OBJECT(p, type) p = new type
#define DELETE_OBJECT(p) if ((p) != NULL) { delete (p); (p) = NULL; }
#define DELETE_OBJECTS(p) if ((p) != NULL) { delete[] (p); (p) = NULL; }
#define DpELETE_OBJECT()	if ((p) != NULL) { delete (p); (p) = NULL; }
#define DELETE_OBJECTS(p)	if ((p) != NULL) { delete[] (p); (p) = NULL; }
#define RELEASE_OBJECT(p)	if ((p) != NULL) { (p)->Release(); (p) = NULL; }
#define FOR_LIST(type, li) for (list<type>::iterator it = li.begin(); it != li.end(); it++)


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
	OBJ_ENT, 
	OBJ_BUNKER, 
	OBJ_BULLET,
};

enum ITEM_TAG
{
	ITEM_NONE, ITEM_WEAPON, 
};

enum PLAYER_STATE
{
	PLAYER_NONE, PLAYER_ATTACK, PLAYER_SHOP,
};

enum CREATURE_STATE
{
	CREATURE_NONE, CREATURE_RUN, CREATURE_ATTACK, CREATURE_DEAD,
};

enum DIRECTION_TAG
{
	DIRECTION_LEFT, DIRECTION_RIGHT, DIRECTION_CENTER,
};
enum TEXT_ALIGN
{
	TEXT_ALIGN_LEFT = 0, TEXT_ALIGN_RIGHT = 1, TEXT_ALIGN_CENTER = 2,
};