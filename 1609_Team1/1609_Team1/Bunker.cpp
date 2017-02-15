#include "Bunker.h"



Bunker::Bunker()
{
}

Bunker::Bunker(OBJ_TAG tag) : Object(tag)
{
	m_maxLife = 1000.0f;
	m_currentLife = m_maxLife;
	m_defense = 0.0f;
}


Bunker::~Bunker()
{
}

void Bunker::Update(float deltaTime)
{

}

void Bunker::Draw(Camera* pCamera)
{
	//벙커 천장 카메라 출력 (테스트)
		pCamera->DrawRect(Vector(0, 0), Vector(VIEW_WIDTH, VIEW_HEIGHT*0.8), ColorF::Indigo, 2.5f);
}