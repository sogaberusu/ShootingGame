#pragma once
#include "GrenadeController.h"
#include "physics/CollisionAttr.h"

class Grenade
{
public:
	Grenade(CVector3 pos, int PlayerNumber, CVector3 target);
	~Grenade();
	/// <summary>
	/// アップデート
	/// </summary>
	void Update(int PlayerNumber);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">描画したいカメラを送る</param>
	void Draw(Camera& camera);
	/// <summary>
	/// グレネードの状態を返す
	/// </summary>
	/// <returns>treu爆発　false爆発待ち</returns>
	bool IsDead()
	{
		return m_isDead;
	}
	//グレネードの座標を返す
	CVector3 GetPosition()
	{
		return m_position;
	}
	//誰が投げたのかを返す。キル数を加算するのに使う
	int GetThrowPlayer()
	{
		return m_throwplayer;
	}
private:
	GrenadeController m_grenadeController;				//グレネードコントローラー
	SkinModel m_model;									//モデル
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_target = CVector3::Zero();				//グレネードを投げる方向
	int m_life = 100;									//爆発までの時間		
	bool m_isDead = false;								//爆発しているか
	int m_throwplayer;									//誰が投げたのか記録しておく
};