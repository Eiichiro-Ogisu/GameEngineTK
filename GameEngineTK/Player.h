#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "Singleton.h"
#include "DXTKResouces.h"
#include "obj3d.h"
#include "CollisionNode.h"

class Player
{
public:

	/// <summary>
	/// 定数
	/// </summary>
	/// 重力加速度
	const float GRAVITY_ACC = 0.03f;
	// ジャンプ初速
	const float JUMP_SPEED_FIRST = 0.5f;
	// ジャンプ初速<m/frame>
	const float JUMP_SPEED_MAX = 0.3f;


	// 自機パーツ
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_BODY,
		PLAYER_PARTS_LEG,
		PLAYER_PARTS_BATTERY,
		PLAYER_PARTS_BATTERY2,
		PLAYER_PARTS_HAND,
		PLAYER_PARTS_HAND2,
		PLAYER_PARTS_HEAD,

		PLAYER_PARTS_NUM
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 弾丸を発射
	/// </summary>
	void FireBullet();

	/// <summary>
	/// 弾丸を再装着
	/// </summary>
	void ResetBullet();

	/// <summary>
	/// 座標を取得
	/// </summary>
	const DirectX::SimpleMath::Vector3& GetPosition();

	void Calc();

	/// <summary>
	/// 座標を設定
	/// </summary>
	void SetPosition(const DirectX::SimpleMath::Vector3& trans);

	/// <summary>
	/// ワールド行列を取得
	/// </summary>
	const DirectX::SimpleMath::Matrix& GetLocalWorld();

	// 弾丸用当たり判定を取得
	const SphereNode& GetCollisionNodeBullet() { return _collisionNodeBullet; }

	// 全身の当たり判定球
	const SphereNode& GetCollisionNodeBody() { return _collisionNodeBody; }

	/// <summary>
	/// 角度の取得
	/// </summary>
	const DirectX::SimpleMath::Vector3& GetRot();

	void StartJump();

	void StartFall();

	void StopJump();

	const DirectX::SimpleMath::Vector3& GetVelocity() { return m_velocity; }

protected:
	// パーツ
	std::vector<Obj3d> _obj;

	// 自機の座標
	DirectX::SimpleMath::Vector3 _position;

	DirectX::SimpleMath::Vector3 _angle;

	// 弾丸の速度ベクトル
	DirectX::SimpleMath::Vector3 _bulletVel;

	int cnt = 0;

	bool isFire = false;

	// 弾丸用の当たり判定
	SphereNode _collisionNodeBullet;

	// 全身用の当たり判定
	SphereNode _collisionNodeBody;

	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;

	// 落下中フラグ
	bool m_isJump;
};