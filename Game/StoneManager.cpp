#include "stdafx.h"
#include "StoneManager.h"
#include "Stone.h"

StoneManager::StoneManager()
{
}

StoneManager::~StoneManager()
{
	for (auto& Stone : m_stones) {
		delete Stone;
	}
}
Stone* StoneManager::NewStone()
{
	Stone* newStone = new Stone;
	m_stones.push_back(newStone);
	return newStone;
}
void StoneManager::Update()
{
	for (auto& Stone : m_stones) {
		Stone->Update();
	}
	HitCheck();
	auto it = m_stones.begin();
	while (it != m_stones.end()) {
		if ((*it)->IsDead() == true) {
			delete *it;
			it = m_stones.erase(it);
		}
		else {
			it++;
		}
	}

}
void StoneManager::Draw(Camera& camera)
{
	for (auto& Stone : m_stones) {
		Stone->Draw(camera);
	}

}

void StoneManager::HitCheck()
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
}
