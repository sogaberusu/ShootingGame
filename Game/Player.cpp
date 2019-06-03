#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Game.h"
#include "Bullet.h"
#include "Physics/CollisionAttr.h"
#include "WeaponAttr.h"


Player::Player(int playerNo)
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/Player_.cmo");

	m_model.SetShadowReciever(true);
	InitAnimation();

	m_charaCon.Init(20.0f, 150.0f, m_position);

	m_charaCon.GetRigidBody()->GetBody()->setUserIndex(playerNo);
}

void Player::InitAnimation()
{
	//tkaファイルの読み込み。
	m_animationClips[enAnimation_Idle].Load(L"Assets/animData/Player_Idle.tka");
	m_animationClips[enAnimation_Idle].SetLoopFlag(true);

	m_animationClips[enAnimation_Walk_Forward].Load(L"Assets/animData/Player_Walk_Forward.tka");
	m_animationClips[enAnimation_Walk_Forward].SetLoopFlag(true);

	m_animationClips[enAnimation_Walk_Back].Load(L"Assets/animData/Player_Walk_Back.tka");
	m_animationClips[enAnimation_Walk_Back].SetLoopFlag(true);

	m_animationClips[enAnimation_Walk_Right].Load(L"Assets/animData/Player_Walk_Right.tka");
	m_animationClips[enAnimation_Walk_Right].SetLoopFlag(true);

	m_animationClips[enAnimation_Walk_Left].Load(L"Assets/animData/Player_Walk_Left.tka");
	m_animationClips[enAnimation_Walk_Left].SetLoopFlag(true);

	m_animationClips[enAnimation_Walk_Shoot].Load(L"Assets/animData/Player_Walk_Shoot.tka");
	m_animationClips[enAnimation_Walk_Shoot].SetLoopFlag(true);

	m_animationClips[enAnimation_Walk_Reload].Load(L"Assets/animData/Player_Walk_Reload.tka");
	m_animationClips[enAnimation_Walk_Reload].SetLoopFlag(false);

	m_animationClips[enAnimation_Run].Load(L"Assets/animData/Player_Run.tka");
	m_animationClips[enAnimation_Run].SetLoopFlag(true);

	m_animationClips[enAnimation_Jump_Start].Load(L"Assets/animData/Player_Jump_Start.tka");
	m_animationClips[enAnimation_Jump_Start].SetLoopFlag(false);

	m_animationClips[enAnimation_Jump_Air].Load(L"Assets/animData/Player_Jump_Air.tka");
	m_animationClips[enAnimation_Jump_Air].SetLoopFlag(true);

	m_animationClips[enAnimation_Jump_Land].Load(L"Assets/animData/Player_Jump_Land.tka");
	m_animationClips[enAnimation_Jump_Land].SetLoopFlag(false);

	m_animationClips[enAnimation_Crouch_Idle].Load(L"Assets/animData/Player_Crouch_Idle.tka");
	m_animationClips[enAnimation_Crouch_Idle].SetLoopFlag(true);

	m_animationClips[enAnimation_Crouch_Reload].Load(L"Assets/animData/Player_Crouch_Reload.tka");
	m_animationClips[enAnimation_Crouch_Reload].SetLoopFlag(false);

	m_animationClips[enAnimation_Crouch_Shoot].Load(L"Assets/animData/Player_Crouch_Shoot.tka");
	m_animationClips[enAnimation_Crouch_Shoot].SetLoopFlag(false);

	m_animationClips[enAnimation_Crouch_Walk_Shoot].Load(L"Assets/animData/Player_Crouch_Walk_Shoot.tka");
	m_animationClips[enAnimation_Crouch_Walk_Shoot].SetLoopFlag(true);

	m_animationClips[enAnimation_Crouch_Walk_Forward].Load(L"Assets/animData/Player_Crouch_Walk_Forward.tka");
	m_animationClips[enAnimation_Crouch_Walk_Forward].SetLoopFlag(true);

	m_animationClips[enAnimation_Reload].Load(L"Assets/animData/Player_Reload.tka");
	m_animationClips[enAnimation_Reload].SetLoopFlag(false);

	m_animationClips[enAnimation_Shoot].Load(L"Assets/animData/Player_Shoot.tka");
	m_animationClips[enAnimation_Shoot].SetLoopFlag(false);

	m_animationClips[enAnimation_Damage].Load(L"Assets/animData/Player_Damage.tka");
	m_animationClips[enAnimation_Damage].SetLoopFlag(false);

	m_animationClips[enAnimation_Death].Load(L"Assets/animData/Player_Death.tka");
	m_animationClips[enAnimation_Death].SetLoopFlag(false);

	m_animationClips[enAnimation_Grenade].Load(L"Assets/animData/Player_Grenade.tka");
	m_animationClips[enAnimation_Grenade].SetLoopFlag(false);
	//アニメーションの初期化。
	m_animation.Init(
		m_model,			//アニメーションを流すスキンモデル。
							//これでアニメーションとスキンモデルが関連付けされる。
		m_animationClips,	//アニメーションクリップの配列。
		enAnimation_Num		//アニメーションクリップの数。
	);
}

Player::~Player()
{
}

void Player::Update(Camera& camera, int PlayerNumber)
{
	if (m_state != enState_Death)
	{
		m_charaCon.GetRigidBody()->GetBody()->setUserIndex(PlayerNumber);
		//移動処理
		Move(camera, PlayerNumber);
		if (m_status.HealTimer > 0)
		{
			m_status.HealTimer--;
		}
		if (m_status.HitPoint < 100 && m_status.HealTimer == 0)
		{
			m_status.HitPoint++;
		}
	}
	if (m_state == enState_Death &&
		m_animation.IsPlaying() == false)
	{
		m_rStickX = 0.0f;
		m_rStickY = 0.0f;
		auto respawn = g_game->GetPlayerRespawn(PlayerNumber, GetRandom(0, 3));
		m_position = respawn.PlayerPosition;
		m_rotation = respawn.PlayerRotation;
		m_charaCon.SetPosition(m_position);
		m_state = enState_Idle;
		m_status.HitPoint = 100;
		m_status.HealTimer = 0;

		m_m4a1->SetAmmo(30);

		m_mp5->SetAmmo(30);

		m_benelliM4->SetAmmo(7);

		m_m110->SetAmmo(10);

	}
	//回転処理
	Turn(PlayerNumber);
	switch (m_state)
	{
	case Player::enState_Idle:
		m_animation.Play(enAnimation_Idle, 0.3);
		break;
	case Player::enState_Walk_Forward:
		m_animation.Play(enAnimation_Walk_Forward, 0.3);
		break;
	case Player::enState_Walk_Back:
		m_animation.Play(enAnimation_Walk_Back, 0.3);
		break;
	case Player::enState_Walk_Right:
		m_animation.Play(enAnimation_Walk_Right, 0.3);
		break;
	case Player::enState_Walk_Left:
		m_animation.Play(enAnimation_Walk_Left, 0.3);
		break;
	case Player::enState_Walk_Shoot:
		m_animation.Play(enAnimation_Walk_Shoot, 0.3);
		break;
	case Player::enState_Walk_Reload:
		m_animation.Play(enAnimation_Walk_Reload, 0.3);
		if (m_animation.IsPlaying() == false)
		{
			switch (m_weapon)
			{
			case enWeapon_M4A1:
				m_m4a1->SetAmmo(30);
				break;
			case enWeapon_MP5:
				m_mp5->SetAmmo(30);
				break;
			case enWeapon_Benelli_M4:
				m_benelliM4->SetAmmo(7);
				break;
			case enWeapon_M110:
				m_m110->SetAmmo(10);
				break;
			}
			m_state = enState_Idle;
		}
		break;
	case Player::enState_Run:
		m_animation.Play(enAnimation_Run, 0.3);
		break;
	case Player::enState_Jump_Start:
		m_animation.Play(enAnimation_Jump_Start, 0.3);
		break;
	case Player::enState_Jump_Air:
		m_animation.Play(enAnimation_Jump_Air, 0.3);
		break;
	case Player::enState_Jump_Land:
		m_animation.Play(enAnimation_Jump_Land, 0.3);
		break;
	case Player::enState_Crouch_Idle:
		m_animation.Play(enAnimation_Crouch_Idle, 0.3);
		break;
	case Player::enState_Crouch_Reload:
		m_animation.Play(enAnimation_Crouch_Reload, 0.3);
		if (m_animation.IsPlaying() == false)
		{
			switch (m_weapon)
			{
			case enWeapon_M4A1:
				m_m4a1->SetAmmo(30);
				break;
			case enWeapon_MP5:
				m_mp5->SetAmmo(30);
				break;
			case enWeapon_Benelli_M4:
				m_benelliM4->SetAmmo(7);
				break;
			case enWeapon_M110:
				m_m110->SetAmmo(10);
				break;
			}
			m_state = enState_Crouch_Idle;

		}
		break;
	case Player::enState_Crouch_Shoot:
		m_animation.Play(enAnimation_Crouch_Shoot, 0.3);
		break;
	case Player::enState_Crouch_Walk_Shoot:
		m_animation.Play(enAnimation_Crouch_Walk_Shoot,0.3);
		break;
	case Player::enState_Crouch_Walk_Forward:
		m_animation.Play(enAnimation_Crouch_Walk_Forward,0.3);
		break;
	case Player::enState_Reload:
		m_animation.Play(enAnimation_Reload, 0.3);
		if (m_animation.IsPlaying() == false)
		{
			switch (m_weapon)
			{
			case enWeapon_M4A1:
				m_m4a1->SetAmmo(30);
				break;
			case enWeapon_MP5:
				m_mp5->SetAmmo(30);
				break;
			case enWeapon_Benelli_M4:
				m_benelliM4->SetAmmo(7);
				break;
			case enWeapon_M110:
				m_m110->SetAmmo(10);
				break;
			}
			m_state = enState_Idle;

		}
		break;
	case Player::enState_Shoot:
		m_animation.Play(enAnimation_Shoot, 0.3);
		break;
	case Player::enState_Damage:
		m_animation.Play(enAnimation_Damage, 0.3);
		break;
	case Player::enState_Death:
		m_animation.Play(enAnimation_Death, 0.3);
		break;
	case Player::enState_Grenade:
		m_animation.Play(enAnimation_Grenade, 0.3);
		break;
	default:
		m_position = { 0.0f,0.0f,0.0f };
		break;
	}
	Bone* m_righthandBoneMat = m_model.FindBone(L"Bip001 R Hand");
	CMatrix hand = m_righthandBoneMat->GetWorldMatrix();
	m_handPos.x = hand.m[3][0];
	m_handPos.y = hand.m[3][1];
	m_handPos.z = hand.m[3][2];

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_animation.Update(1.0f / 30.0f);
	//シャドウキャスターを登録。
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);

	
}
void Player::Move(Camera& camera, int PlayerNumber)
{
	//XZ平面の移動速度はパッドの入力から引っ張ってくる。
	m_lStickX = g_pad[PlayerNumber].GetLStickXF();
	m_lStickY = g_pad[PlayerNumber].GetLStickYF();
	//パッドの入力を使ってカメラを回す。
	m_rStickX = g_pad[PlayerNumber].GetRStickXF();
	m_rStickY = g_pad[PlayerNumber].GetRStickYF();
	//カメラの前方方向と右方向を取得。
	CVector3 cameraForward = camera.GetForward();
	CVector3 cameraRight = camera.GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y -= 980.0f *(1.0f / 60.0f);
	m_moveSpeed += cameraForward * m_lStickY * 200.0f;		//奥方向への移動速度を加算。
	m_moveSpeed += cameraRight * m_lStickX * 200.0f;		//右方向への移動速度を加算。
	if (m_moveSpeed.x == 0 && m_moveSpeed.z == 0) {
		if (m_state == enState_Crouch_Walk_Forward ||
			m_state == enState_Crouch_Walk_Shoot)
		{
			m_state = enState_Crouch_Idle;
		}
		else if (
			m_state != enState_Crouch_Idle &&
			m_state != enState_Crouch_Reload &&
			m_state != enState_Crouch_Shoot &&
			m_state != enState_Jump_Air &&
			m_state != enState_Jump_Start &&
			m_state != enState_Jump_Land &&
			m_state != enState_Reload && 
			m_state != enState_Walk_Reload &&
			m_state != enState_Grenade
			)
		{
			m_state = enState_Idle;
		}
	}
	else{
		if (m_state == enState_Crouch_Idle ||
			m_state == enState_Crouch_Walk_Forward ||
			m_state == enState_Crouch_Walk_Shoot ||
			m_state == enState_Crouch_Shoot)
		{
			m_state = enState_Crouch_Walk_Forward;
		}
		else if(m_charaCon.IsOnGround() == true 
			&& m_state != enState_Crouch_Walk_Forward
			&& m_state != enState_Crouch_Reload
			&& m_state != enState_Run
			&& m_state != enState_Walk_Reload
			&& m_state != enState_Reload)
		{
			if (m_lStickY > 0.8)
			{
				m_state = enState_Walk_Forward;
			}
			if (m_lStickY < -0.8)
			{
				m_state = enState_Walk_Back;
			}
			if (m_lStickX > 0.8 && m_lStickY < 0.8)
			{
				m_state = enState_Walk_Left;
			}
			if (m_lStickX < -0.8 && m_lStickY > -0.8)
			{
				m_state = enState_Walk_Right;
			}
		}
	}
	if (g_pad[PlayerNumber].IsPress(enButtonLB3) == true)
	{
		m_state = enState_Run;
	}
	if (g_pad[PlayerNumber].IsTrigger(enButtonA) == true
		&& m_charaCon.IsOnGround() == true
		) {
		if (m_state != enState_Reload
			&& m_state != enState_Walk_Reload)
		{
			m_moveSpeed.y += 300.0f;
			m_state = enState_Jump_Start;
		}
		else
		{
			if (m_state == enState_Crouch_Reload)
			{
				m_state = enState_Reload;
				m_moveSpeed.y += 300.0f;
			}
			else
			{
				m_moveSpeed.y += 300.0f;
			}
		}
	}
	if (m_charaCon.IsOnGround() == false
		&& m_state != enState_Crouch_Reload
		&& m_state != enState_Reload
		&& m_state != enState_Walk_Reload
		)
	{
		m_state = enState_Jump_Air;
	}
	if (m_state == enState_Jump_Air && m_charaCon.IsOnGround() == true)
	{
		m_state = enState_Jump_Land;
	}
	
	if (g_pad[PlayerNumber].IsTrigger(enButtonB) == true
		&& m_charaCon.IsOnGround() == true)
	{
		if (m_state == enState_Crouch_Idle ||
			m_state == enState_Crouch_Walk_Forward ||
			m_state == enState_Crouch_Walk_Shoot ||
			m_state == enState_Crouch_Shoot ||
			m_state == enState_Crouch_Reload 
			)
		{
			m_state = enState_Idle;
		}
		else
		{
			m_state = enState_Crouch_Idle;
		}
	}
	if (g_pad[PlayerNumber].IsTrigger(enButtonY) == true)
	{
		m_weapon = static_cast<EnWeapon>(m_weapon + 1);
		if (m_weapon == enWeapon_Num)
		{
			m_weapon = enWeapon_M4A1;
		}
	}
	if (g_pad[PlayerNumber].IsTrigger(enButtonX) == true)
	{
		if (m_state == enState_Crouch_Idle ||
			m_state == enState_Crouch_Walk_Forward ||
			m_state == enState_Crouch_Walk_Shoot ||
			m_state == enState_Crouch_Shoot
			)
		{
			m_state = enState_Crouch_Reload;
		}
		else 
		{
			m_state = enState_Reload;
		}
		if (m_moveSpeed.x != 0 && m_moveSpeed.y != 0
			&& m_crouch == false
			)
		{
			m_state = enState_Walk_Reload;
		}
	}

	if (g_pad[PlayerNumber].IsTrigger(enButtonRB1) == true)
	{
		m_state = enState_Grenade;
	}

	if (g_pad[PlayerNumber].IsPress(enButtonRB2) == true
		&& m_state != enState_Crouch_Reload
		&& m_state != enState_Reload
		&& m_state != enState_Walk_Reload
		)
	{
		Shot(PlayerNumber, camera);
	}
	else
	{
		switch (m_weapon)
		{
		case enWeapon_M4A1:
			m_m4a1->SetShootIntervalNow(100.0f);
			break;
		case enWeapon_MP5:
			m_mp5->SetShootIntervalNow(100.0f);
			break;
		case enWeapon_Benelli_M4:
			m_benelliM4->SetShootIntervalNow(100.0f);
			break;
		case enWeapon_M110:
			m_m110->SetShootIntervalNow(100.0f);
			break;
		}
	}
	
	if (m_state == enState_Run)
	{
		m_moveSpeed.Add(m_moveSpeed);
	}

	/*if (m_status.HitPoint <= 0)
	{
		m_charaCon.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Ground);

		m_state = enState_Death;
	}*/
	if (m_state == enState_Crouch_Idle ||
		m_state == enState_Crouch_Reload ||
		m_state == enState_Crouch_Shoot ||
		m_state == enState_Crouch_Walk_Forward ||
		m_state == enState_Crouch_Walk_Shoot)
	{
		m_crouch = true;
	}
	else
	{
		m_crouch = false;
	}

	
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);

	CMatrix rotMatrix = m_model.GetRotationMatrix();
	m_forward.x = rotMatrix.m[2][0];
	m_forward.y = rotMatrix.m[2][1];
	m_forward.z = rotMatrix.m[2][2];
	m_forward.Normalize();
	m_right.x = rotMatrix.m[0][0];
	m_right.y = rotMatrix.m[0][1];
	m_right.z = rotMatrix.m[0][2];
	m_right.Normalize();
}

void Player::Turn(int PlayerNumber)
{
	if (g_pad[PlayerNumber].IsPress(enButtonLB2) == true)
	{
		SetCameraType(EnCameraType::enType_FPS);

		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisY(), m_rStickX* 2.0f);
		//回転を加算する。
		m_rotation.Multiply(qRot);
		//m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_cameraDirection.x, m_cameraDirection.z));
	}
	else
	{
		SetCameraType(EnCameraType::enType_TPS);

		//向きも変える。
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_cameraDirection.x, m_cameraDirection.z));

	}
}
void Player::Draw(Camera& camera, int ViewportNumber, int PlayerNumber)
{
	if (m_drawflag == true || ViewportNumber != PlayerNumber)
	{
		m_model.Draw(
			camera.GetViewMatrix(),
			camera.GetProjectionMatrix(),
			0
		);
	}
	
}

void Player::Shot(int PlayerNumber,Camera& camera)
{
	
	if (m_state == enState_Crouch_Idle ||
		m_state == enState_Crouch_Walk_Forward ||
		m_state == enState_Crouch_Walk_Shoot ||
		m_state == enState_Crouch_Reload ||
		m_state == enState_Crouch_Shoot
		)
	{
		if (m_moveSpeed.x == 0 && m_moveSpeed.z == 0)
		{
			m_state = enState_Crouch_Shoot;
		}
		else {
			m_state = enState_Crouch_Walk_Forward;
		}
		CVector3 target = camera.GetTarget() - camera.GetPosition();
		target.Normalize();
		switch (m_weapon)
		{
		case enWeapon_M4A1:
			m_m4a1->Shot(target, PlayerNumber);
			break;
		case enWeapon_MP5:
			m_mp5->Shot(target, PlayerNumber);
			break;
		case enWeapon_Benelli_M4:
			m_benelliM4->Shot(target, PlayerNumber);
			break;
		case enWeapon_M110:
			m_m110->Shot(target, PlayerNumber);
			break;
		}
	}
	if (m_state != enState_Crouch_Idle &&
		m_state != enState_Crouch_Walk_Forward &&
		m_state != enState_Crouch_Walk_Shoot &&
		m_state != enState_Crouch_Reload &&
		m_state != enState_Crouch_Shoot
		)
	{
		if (m_moveSpeed.x == 0 && m_moveSpeed.z == 0)
		{
			m_state = enState_Shoot;
		}
		else {
			m_state = enState_Walk_Shoot;
		}
		
			CVector3 target = camera.GetTarget() - camera.GetPosition();
			target.Normalize();
			switch (m_weapon)
			{
			case enWeapon_M4A1:
				m_m4a1->Shot(target, PlayerNumber);
				break;
			case enWeapon_MP5:
				m_mp5->Shot(target, PlayerNumber);
				break;
			case enWeapon_Benelli_M4:
				m_benelliM4->Shot(target, PlayerNumber);
				break;
			case enWeapon_M110:
				m_m110->Shot(target, PlayerNumber);
				break;
			}
	}
}