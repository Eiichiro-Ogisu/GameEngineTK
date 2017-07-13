/// <summary>
/// Enemy
/// </summary>
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "Singleton.h"
#include "DXTKResouces.h"
#include "obj3d.h"
#include "CollisionNode.h"

class Enemy
{
public:

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
	Enemy();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

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
	/// 座標を取得
	/// </summary>
	const DirectX::SimpleMath::Vector3& GetPosition();

	// 行列の計算
	void Calc();

	/// <summary>
	/// 座標を設定
	/// </summary>
	void SetPosition(const DirectX::SimpleMath::Vector3& trans);

	/// <summary>
	/// ワールド行列を取得
	/// </summary>
	const DirectX::SimpleMath::Matrix& GetLocalWorld();

	/// <summary>
	/// 角度の取得
	/// </summary>
	const DirectX::SimpleMath::Vector3& GetAngle();

	/// 回転を設定
	void SetRot(const DirectX::SimpleMath::Vector3& rot);

	// 
	const SphereNode& GetCollisionNodeBody() { return _collisionNodeBody; }

protected:
	// サイン用の引数の角度
	float _sinAngle;

	// パーツ
	std::vector<Obj3d> _obj;

	// タイマー
	int _timer;

	// 目的地の角度
	float _distAngle;

	// 全身用の当たり判定
	SphereNode _collisionNodeBody;

};