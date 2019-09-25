#pragma once
#include "character/CharacterController.h"
#include "graphics/ShadowMap.h"
#include "Benelli_M4.h"
#include "M4A1.h"
#include "MP5.h"
#include "M110.h"
#include "SMAW.h"
#include "Physics/CollisionAttr.h"
#include "WeaponAttr.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class GameCamera;
struct SPlayerStatus
{
	int HitPoint = 100;				//体力
	int Kills = 0;					//キル数
	int HealTimer = 0;				//自動回復するまでの時間
	int Grenades = 2;				//グレネードの所持数
	float CaptureTime = 0.0f;
};
class Player
{
public:
	
	Player(int playerNo);
	~Player();
	//更新
	void Update(Camera& camera, int PlayerNumber);
	//描画
	void Draw(Camera& camera, int ViewportNumber, int PlayerNumber);
	//シルエット描画
	void SilhouetteDrwa(Camera& camera, int ViewportNumber, int PlayerNumber);
	//プレイヤーの状態を表す
	enum EnState {
		enState_Idle,				//アイドル
		enState_Walk_Forward,		//前歩き
		enState_Walk_Back,			//後ろ歩き
		enState_Walk_Right,			//右歩き
		enState_Walk_Left,			//左歩き
		enState_Walk_Shoot,			//歩き撃ち
		enState_Walk_Reload,		//歩きながらリロード
		enState_Run,				//ダッシュ
		enState_Jump_Start,			//ジャンプ返し
		enState_Jump_Air,			//ジャンプ中
		enState_Jump_Land,			//着地
		enState_Crouch_Idle,		//しゃがみアイドル
		enState_Crouch_Reload,		//しゃがみリロード
		enState_Crouch_Shoot,		//しゃがみ撃ち
		enState_Crouch_Walk_Shoot,	//しゃがみ歩き撃ち
		enState_Crouch_Walk_Forward,//しゃがみ前歩き
		enState_Reload,				//リロード
		enState_Shoot,				//弾丸発射
		enState_Damage,				//ダメージをくらう
		enState_Death,				//死亡
		enState_Grenade,			//グレネードを投げる
		enState_Num					//プレイヤーの状態数
	};
	enum EnPart
	{
		enPart_Head,				//頭の剛体
		enPart_Body,				//体の剛体
		enPart_LeftLeg,				//左足の剛体
		enPart_RightLeg,			//右足の剛体
		enPart_Num					//プレイヤー1体の剛体の数
	};
	//プレイヤーの座標を設定
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		m_charaCon.SetPosition(m_position);
	}
	//プレイヤーの回転を設定
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	//プレイヤーの座標を返す
	CVector3 GetPosition()
	{
		return m_position;
	}
	//プレイヤーの移動速度を返す
	CVector3 GetMoveSpped()
	{
		return m_moveSpeed;
	}
	//プレイヤーの前方向を返す
	CVector3 GetForward()
	{
		return m_forward;
	}
	//プレイヤーの右方向を返す
	CVector3 GetRight()
	{
		return m_right;
	}
	//右スティックのxの値を返す
	float GetRStickX()
	{
		return m_rStickX;
	}
	//右スティックのyの値を返す
	float GetRStickY()
	{
		return m_rStickY;
	}
	//左スティックのxの値を返す
	float GetLStickX()
	{
		return m_lStickX;
	}
	//左スティックのyの値を返す
	float GetLStickY()
	{
		return m_lStickY;
	}
	//プレイヤーの手の座標を返す
	CVector3 GetHandPos()
	{
		return m_rHandPos;
	}
	//プレイヤーのステータスを返す
	SPlayerStatus GetStatus()
	{
		return m_status;
	}
	//プレイヤーのヒットポイントを設定する
	void SetHitPoint(int hp)
	{
		m_status.HitPoint = hp;
	}
	//プレイヤーが死んだらする処理
	void SetDead()
	{
		m_state = enState_Death;
		m_deadflag = true;
		m_charaCon.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Default);
		m_rigidBody[enPart_Head].GetBody()->setUserIndex(enCollisionAttr_Default);
		m_rigidBody[enPart_Body].GetBody()->setUserIndex(enCollisionAttr_Default);
		m_rigidBody[enPart_LeftLeg].GetBody()->setUserIndex(enCollisionAttr_Default);
		m_rigidBody[enPart_RightLeg].GetBody()->setUserIndex(enCollisionAttr_Default);
	}
	//プレイヤーのキル数を設定する
	void SetKills(int kills)
	{
		m_status.Kills = kills;
	}
	//プレイヤーが自動回復するまでの時間を設定する
	void SetHealTimer(int timer)
	{
		m_status.HealTimer = timer;
	}
	//カメラの方向を設定する
	void SetCameraDirection(CVector3 direction)
	{
		m_cameraDirection = direction;
	}
	//プレイヤーを描画するかのフラグをfalseにする
	void DrawSetFalse()
	{
		m_drawflag = false;
	}
	//プレイヤーを描画するかのフラグをtrueにする
	void DrawSetTrue()
	{
		m_drawflag = true;
	}
	//プレイヤーのステータスを返す
	EnState GetState()
	{
		return m_state;
	}
private:
	//弾丸を発射する
	void Shot(int PlayerNumber,Camera& camera);
public:
	enum EnCameraType {
		enType_TPS,					//TPSカメラ
		enType_FPS					//FPSカメラ
	};
	//今のカメラの状態を返す
	bool GetCameraType()
	{
		return m_cameratype;
	}
	//カメラの状態を設定する
	void SetCameraType(EnCameraType type)
	{
		m_cameratype = type;
	}
	//スキンモデルを返す
	SkinModel GetSkinModel()
	{
		return m_model;
	}
	//プレイヤーがしゃがんでいるかを返す
	bool GetCrouch()
	{
		return m_crouch;
	}
	//乱数を返す
	int GetRandom(int min, int max)
	{
		return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
	}
	//プレイヤーのキル数を返す
	int GetKills()
	{
		return m_status.Kills;
	}
	//プレイヤーを描画するかのフラグを返す
	bool GetDrawFlag()
	{
		return m_drawflag;
	}
	//回転を返す
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	//プレイヤーのヒットポイントを返す
	int GetHitPoint()
	{
		return m_status.HitPoint;
	}
	//グレネード数を返す
	int GetGrenade()
	{
		return m_status.Grenades;
	}
	//攻撃が当たった時にヒットマーカーを表示するフラグをtrueにする
	void SetAttackTrue()
	{
		m_attackflag = true;
	}
	//攻撃が当たった時にヒットマーカーを表示するフラグをfalseにする
	void SetAttackFalse()
	{
		m_attackflag = false;
	}
	//ヒットマーカーを表示する時間を設定する
	void SetAttackCount(int time)
	{
		m_attackflagcount = time;
	}
	//ヒットマーカーを表示するフラグを返す
	bool GetAttackFlag()
	{
		return m_attackflag;
	}
	//キルマーカーを表示するフラグをtrueにする
	void SetKillTrue()
	{
		m_killflag = true;
	}
	//キルマーカーを表示するフラグをfalseにする
	void SetKillFalse()
	{
		m_killflag = false;
	}
	//キルマーカーを表示する時間を設定する
	void SetKillCount(int time)
	{
		m_killflagcount = time;
	}
	//キルマーカーを表示する時間を設定する
	bool GetKillFlag()
	{
		return m_killflag;
	}
	//装備している銃を返す
	EnWeapon GetWeapon()
	{
		return m_weapon;
	}
	//装備する銃を設定する
	void SetWeapon(EnWeapon weapon)
	{
		m_weapon = weapon;
	}
	//銃のインスタンスを設定する
	void SetWeaponInstance(M4A1 *m4a1,MP5 *mp5,Benelli_M4 *benelliM4,M110 *m110)
	{
		m_m4a1 = m4a1;
		m_mp5  = mp5;
		m_benelliM4 = benelliM4;
		m_m110 = m110;
	}
	//プレイヤーが旗を持っているかのフラグを返す
	bool GetIsFlag()
	{
		return m_isflag;
	}
	//プレイヤーが旗を持っているかどうかのフラグを設定する
	void SetIsFlag(bool flag)
	{
		m_isflag = flag;
	}
	//旗を確保している時間を返す
	float GetCaptureTime()
	{
		return m_status.CaptureTime;
	}
	//キャラクターコントローラーを返す
	CharacterController GetCharaCon()
	{
		return m_charaCon;
	}
	//プレイヤーが倒されたかどうかのフラグを返す
	bool GetDeadFlag()
	{
		return m_deadflag;
	}
	//プレイヤーが旗を確保している時間を設定する
	void SetCaptureTime(float time)
	{
		m_status.CaptureTime = time;
	}
	void CreateHeadCollider(int playerNo);				//ヘッドショット用の当たり判定を作成する
	void CreateBodyCollider(int playerNo);				//体の当たり判定を作成する
	void CreateLeftLegCollider(int playerNo);			//左足の当たり判定を作成する
	void CreateRightLegCollider(int playerNo);			//右足の当たり判定を作成する
private:
	void InitAnimation();								//アニメーションの初期化
	void Move(Camera& camera, int PlayerNumber);		//移動処理
	void Turn(int PlayerNumber);						//回転処理
	//プレイヤーのアニメーション
	enum EnAnimation {
		enAnimation_Idle,								//アイドル
		enAnimation_Walk_Forward,						//前歩き
		enAnimation_Walk_Back,							//後ろ歩き
		enAnimation_Walk_Right,							//右歩き
		enAnimation_Walk_Left,							//左歩き
		enAnimation_Walk_Shoot,							//歩きながら銃を撃つ
		enAnimation_Walk_Reload,						//歩きながらリロード
		enAnimation_Run,								//走る
		enAnimation_Jump_Start,							//ジャンプ開始
		enAnimation_Jump_Air,							//落下中
		enAnimation_Jump_Land,							//着地
		enAnimation_Crouch_Idle,						//しゃがみアイドル
		enAnimation_Crouch_Reload,						//しゃがみリロード
		enAnimation_Crouch_Shoot,						//しゃがみ撃ち
		enAnimation_Crouch_Walk_Shoot,					//しゃがみ歩き撃ち
		enAnimation_Crouch_Walk_Forward,				//しゃがみ前歩き
		enAnimation_Reload,								//リロード
		enAnimation_Shoot,								//弾を撃つ
		enAnimation_Damage,								//ダメージをくらう
		enAnimation_Death,								//倒れる
		enAnimation_Grenade,							//グレネードを投げる
		enAnimation_Num									//アニメーション数
	};
	
	SkinModel m_model;									//スキンモデル。
	Animation m_animation;								//アニメーション。
	AnimationClip m_animationClips[enAnimation_Num];	//アニメーションクリップ。
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_scale = CVector3::One();					//拡大率。
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	CVector3 m_forward;									//キャラクターの前方向
	CVector3 m_right;									//キャラクターの右方向
	CharacterController m_charaCon;						//キャラクターコントローラー
	EnState m_state = enState_Idle;						//状態
	bool m_cameratype = EnCameraType::enType_TPS;		//カメラ
	float m_rStickX;									//右スティックのX
	float m_rStickY;									//右スティックのY
	float m_lStickX;									//左スティックのX
	float m_lStickY;									//左スティックのY
	CVector3 m_cameraDirection;							//カメラの前方向
	bool m_drawflag = true;								//fps視点の時に自分のモデルを表示しないために使う
	CVector3 m_rHandPos;								//モデルの右手の座標
	CVector3 m_lHandPos;								//モデルの左手の座標
	RigidBody m_rigidBody[enPart_Num];					//剛体
	SPlayerStatus m_status;								//プレイヤーのステイタス
	bool m_crouch = false;								//プレイヤーがしゃがんでいるか
	bool m_attackflag = false;							//攻撃が当たった時に白いマーカーを出すためのフラグ
	int m_attackflagcount;								//白いマーカーを表示する時間
	bool m_killflag = false;							//敵を倒したときに赤いマーカーを出すためのフラグ
	int m_killflagcount;								//赤いマーカーを表示する時間
	EnWeapon m_weapon = enWeapon_M4A1;                  //装備している武器を持つ
	M4A1 *m_m4a1;										//武器　アサルトライフル
	MP5  *m_mp5;										//武器　サブマシンガン
	Benelli_M4 *m_benelliM4;							//武器　ショットガン
	M110 *m_m110;										//武器　スナイパー
	bool m_isflag = false;								//プレイヤーが旗を確保しているとシルエット描画するフラグ						
	bool m_deadflag = false;							//プレイヤーが倒されたときにtrueになるフラグ
	CapsuleCollider m_headCollider;						//ヘッドショット用のカプセルコライダー
	CapsuleCollider	m_bodyCollider;						//胴体用のカプセルコライダー
	CapsuleCollider	m_leftlegCollider;					//左足用のカプセルコライダー
	CapsuleCollider	m_rightlegCollider;					//右足用のカプセルコライダー
};