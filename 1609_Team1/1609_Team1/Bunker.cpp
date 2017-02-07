#include "Bunker.h"



Bunker::Bunker()
{
}

Bunker::Bunker(OBJ_TAG tag) : Object(tag)
{
	m_life = 1000.0f;
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

}