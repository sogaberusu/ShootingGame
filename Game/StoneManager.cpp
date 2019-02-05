#include "stdafx.h"
#include "StoneManager.h"
#include "Stone.h"

StoneManager::StoneManager()
{
	for (int i = 0; i < 4; i++)
	{
		m_player[i] = nullptr;
	}
}

StoneManager::~StoneManager()
{
	for (int i = 0; i < 4; i++)
	{
		for (auto& Stone : m_stones[i]) {
			delete Stone;
		}
	}
}
Stone* StoneManager::NewStone(int i)
{
	Stone* newStone = new Stone;
	m_stones[i].push_back(newStone);
	return newStone;
}
void StoneManager::Update()
{
	for (int i = 0; i < 4; i++)
	{
		for (auto& Stone : m_stones[i]) {
			Stone->Update();
		}

		HitCheck(i);
		auto it = m_stones[i].begin();
		while (it != m_stones[i].end()) {
			if ((*it)->IsDead() == true) {
				delete *it;
				it = m_stones[i].erase(it);
			}
			else {
				it++;
			}
		}
	}
}
void StoneManager::Draw(Camera& camera)
{
	for (int i = 0; i < 4; i++)
	{
		for (auto& Stone : m_stones[i]) {
			Stone->Draw(camera);
		}
	}
}

void StoneManager::HitCheck(int i)
{
	//for (auto& Stone : m_stones)
	//{
	//	auto vDiff = m_goblin->GetPosition() - Stone->GetPosition();
	//	auto len = vDiff.Length();
	//	if (len < 60.0f) {
	//		//死亡フラグを立てる。
	//		Stone->SetStoneDead();
	//	}
	//}
	//for (auto& Stone : m_stones)
	//{
	//	auto vDiff = m_orc->GetPosition() - Stone->GetPosition();
	//		auto len = vDiff.Length();
	//		if (len < 80.0f) {
	//			//死亡フラグを立てる。
	//			Stone->SetStoneDead();
	//		}
	//}
	for (auto& Stone : m_stones[i])
	{
		for (int j = 0; j < 4; j++)
		{
			if (i != j)
			{
				auto vDiff = m_player[j]->GetPosition() - Stone->GetPosition();
				auto len = vDiff.Length();
				if (len < 80.0f) {
					//死亡フラグを立てる。
					Stone->SetStoneDead();
				}	
			}
		}
	}
}
