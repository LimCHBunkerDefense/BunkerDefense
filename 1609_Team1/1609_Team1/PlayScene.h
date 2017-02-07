#pragma once
#include "SceneManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "CreatureDB.h"
#include "Common.h"
#include "Math.h"

class Example {
	Vector m_dir;
	Circle m_player;
	float m_angle;//ȸ�� ����

	Line m_LineCamera, m_LineLeft, m_LineRight;//	1. ī�޶� �߽ɼ�, ����, ������ ��

	Line m_enemy1, m_enemy2, m_enemy3;
	float m_height;
	list<Line*> m_listLine;  //ĳ���Ϳ� ���õ� ���� �ƴ� �͵��� �־����.


public:
	Example() : m_player(Vector(VIEW_WIDTH*0.5F - 30, VIEW_HEIGHT - 30), 30),
		m_LineCamera(m_player.center, Vector(200, 300)),
		m_LineLeft(m_player.center, Vector(0, 0)),
		m_LineRight(m_player.center, Vector(0, 0)),
		m_enemy1(m_player.center, Vector(500, 200)),
		m_enemy2(m_player.center, Vector(600, 400)),
		m_enemy3(m_player.center, Vector(300, 200)) {
		m_angle = 0;
		m_height = GROUND_HEIGHT;
		m_dir = Vector::Right();


		//1. ī�޶� �� ǥ��
		Vector m_CameraMid = MATH->ToDirection(90);
		Vector m_CameraLeft = MATH->ToDirection(50);
		Vector m_CameraRight = MATH->ToDirection(130);
		m_LineCamera.SetEndPoint(m_player.center + m_CameraMid * 600);
		m_LineLeft.SetEndPoint(m_player.center + m_CameraLeft * 600);
		m_LineRight.SetEndPoint(m_player.center + m_CameraRight * 600);

		m_listLine.push_back(&m_enemy1);
		m_listLine.push_back(&m_enemy2);
		m_listLine.push_back(&m_enemy3);
	}

	void Update(float deltaTime) {

		//���콺 ������ ���� ���ư���
		float fTurnSpeed = 0;
		if (INPUT->IsKeyPress(VK_LEFT)) {
			//m_angle -= 10 * deltaTime;
			fTurnSpeed = -ROTATE_SPEED;
		}
		if (INPUT->IsKeyPress(VK_RIGHT)) {
			//m_angle += 10 * deltaTime;
			fTurnSpeed = ROTATE_SPEED;
		}
		if (INPUT->IsKeyPress(VK_UP)) {
			//m_angle -= 10 * deltaTime;
			m_height += ROTATE_SPEED * 5;
		}
		if (INPUT->IsKeyPress(VK_DOWN)) {
			//m_angle += 10 * deltaTime;
			m_height -= ROTATE_SPEED * 5;
		}
		FOR_LIST(Line*, m_listLine) {
			float prev_angle = MATH->Angle(m_dir, (*it)->EndPoint() - (*it)->StartPoint());
			Vector result_dir = MATH->ToDirection(prev_angle + fTurnSpeed);
			(*it)->SetEndPoint(m_player.center + result_dir * 600);
		}
	}

	void Render() {
		//ColorF lineColor = MATH->IsCollided(m_player, m_LeftLine) ? ColorF::DeepPink : ColorF::Green;
		/*RENDER->DrawInMap(m_LineCamera, ColorF::Red, 2);
		RENDER->DrawInMap(m_LineLeft, ColorF::Blue, 2);
		RENDER->DrawInMap(m_LineRight, ColorF::Blue, 2);


		//����
		FOR_LIST(Line*, m_listLine) {
			float now_angle = MATH->Angle(m_dir, (*it)->EndPoint() - (*it)->StartPoint());
			RENDER->DrawInMap(*(*it), ColorF::Red);
			if (now_angle <= CAMERA_LEFT && now_angle >= CAMERA_RIGHT) {

				if (now_angle <= 90)	RENDER->Draw3D(m_LineCamera, m_LineLeft, *(*it), m_height, ColorF::Red);
				else					RENDER->Draw3D(m_LineCamera, m_LineRight, *(*it), m_height, ColorF::Red, false);
			}
		}

		RENDER->DrawInMap(m_player, ColorF::Aqua);
		RENDER->Draw(m_player, ColorF::Aqua);*/
	}
};

class PlayScene : public IScene
{
	Sprite* m_pBg;
	
	// ũ���� ���� y��ǥ(���� h)
	float m_heightOfCreature;

	// ȭ�� ����� ���� �þ��� ����
	float m_angleToSee;

	// ũ���� ������ ���� ���� �ð�
	float m_gameTime;
	
	// ũ���� �� ������ ��
	int m_createdCretureCount;
	
public:
	PlayScene();
	~PlayScene();

	void OnEnter();
	void OnUpdate(float deltaTime);
	void OnExit();
	void OnDraw();

	void SetCreature(float deltaTime);
};