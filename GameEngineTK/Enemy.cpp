#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
}

/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize()
{
	// 自機パーツの読み込み
	_obj.resize(PLAYER_PARTS_NUM);
	_obj[PLAYER_PARTS_LEG].LoadModel(L"Resources\\leg.cmo");
	_obj[PLAYER_PARTS_BODY].LoadModel(L"Resources\\body.cmo");
	_obj[PLAYER_PARTS_BATTERY].LoadModel(L"Resources\\battery.cmo");
	_obj[PLAYER_PARTS_BATTERY2].LoadModel(L"Resources\\battery.cmo");
	_obj[PLAYER_PARTS_HAND].LoadModel(L"Resources\\hand.cmo");
	_obj[PLAYER_PARTS_HAND2].LoadModel(L"Resources\\hand.cmo");
	_obj[PLAYER_PARTS_HEAD].LoadModel(L"Resources\\head.cmo");

	// パーツの親子関係をセット
	_obj[PLAYER_PARTS_HEAD].SetParent(
		&_obj[PLAYER_PARTS_BODY]);

	_obj[PLAYER_PARTS_HAND].SetParent(
		&_obj[PLAYER_PARTS_BODY]);

	_obj[PLAYER_PARTS_HAND2].SetParent(
		&_obj[PLAYER_PARTS_BODY]);

	_obj[PLAYER_PARTS_LEG].SetParent(
		&_obj[PLAYER_PARTS_BODY]);

	_obj[PLAYER_PARTS_BATTERY].SetParent(
		&_obj[PLAYER_PARTS_BODY]);

	_obj[PLAYER_PARTS_BATTERY2].SetParent(
		&_obj[PLAYER_PARTS_BODY]);

	// 親からのオフセット
	// ボディの座標をいい感じの位置に
	_obj[PLAYER_PARTS_BODY].SetTransform(Vector3(0, 0.25, 0));

	// 足をいい感じに
	_obj[PLAYER_PARTS_LEG].SetScale(Vector3(0.8, 0.25, 0.5));

	_obj[PLAYER_PARTS_LEG].SetTransform(Vector3(0, -0.25, 0));

	// 両手をいい感じに
	_obj[PLAYER_PARTS_HAND].SetTransform(Vector3(-0.5, 0.6, -0.2));
	_obj[PLAYER_PARTS_HAND].SetScale(Vector3(0.25, 0.25, 0.75));

	_obj[PLAYER_PARTS_HAND2].SetTransform(Vector3(0.5, 0.6, -0.2));
	_obj[PLAYER_PARTS_HAND2].SetScale(Vector3(0.25, 0.25, 0.75));

	// 頭をいい感じに
	_obj[PLAYER_PARTS_HEAD].SetTransform(Vector3(0, 1, 0));
	_obj[PLAYER_PARTS_HEAD].SetScale(Vector3(1.5, 1.5, 1.5));

	// タンクをいい感じに
	_obj[PLAYER_PARTS_BATTERY].SetRotation(Vector3(0, 135, -0.55));
	_obj[PLAYER_PARTS_BATTERY].SetTransform(Vector3(-0.5, 0.9, -0.15));
	_obj[PLAYER_PARTS_BATTERY].SetScale(Vector3(0.5, 0.5, 0.5));


	_obj[PLAYER_PARTS_BATTERY2].SetRotation(Vector3(0, 135, 0.55));
	_obj[PLAYER_PARTS_BATTERY2].SetTransform(Vector3(0.5, 0.9, -0.15));
	_obj[PLAYER_PARTS_BATTERY2].SetScale(Vector3(0.5, 0.5, 0.5));

	// 初期配置
	Vector3 pos;

	pos.x = rand()%10;

	pos.z = rand()%10;

	this->SetPosition(pos);

	_timer = 60;

	{// 前進用の当たり判定を設定
		_collisionNodeBody.SetParent(&_obj[PLAYER_PARTS_BODY]);
		_collisionNodeBody.SetTrans(Vector3(0,0.5f,0));
		_collisionNodeBody.SetLocalRadius(1.0f);
	}

	_distAngle = 0.0f;
}

/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update()
{
	_timer--;
	if (_timer < 0)
	{
		_timer = 60;

		float rnd = (float)rand() / RAND_MAX - 0.5f;

		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		_distAngle += rnd;
	}

	// 目標角度に向かって角度を補間
	{
		Vector3 rotv = _obj[PLAYER_PARTS_BODY].GetRotation();

		// 目標角度への最短角度を取得
		float angle = _distAngle - rotv.y;

		// 180度を越えていた場合逆回りに
		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}

		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}

		// 補間
		rotv.y += angle * 0.05f;

		SetRot(rotv);

	}

	// 機体が向いている方向に進む
	{
		// 移動量
		Vector3 moveV = Vector3(0.0f, 0.0f, -0.1f);

		float angle = _obj[PLAYER_PARTS_BODY].GetRotation().y;

		Matrix rotmat = Matrix::CreateRotationY(angle);

		moveV = Vector3::TransformNormal(moveV, rotmat);

		// 自機移動
		Vector3 pos = _obj[PLAYER_PARTS_BODY].GetTranslation();
		_obj[PLAYER_PARTS_BODY].SetTransform(pos + moveV);
	}

	// 行列の計算
	Calc();

	// 当たり判定の更新
	_collisionNodeBody.Update();
}

void Enemy::Draw()
{
	for (std::vector<Obj3d>::iterator it = _obj.begin(); 
		it != _obj.end();
		it++)
	{
		it->Draw();
	}
	_collisionNodeBody.Draw();


}
const DirectX::SimpleMath::Vector3 & Enemy::GetPosition()
{
	// TODO: return ステートメントをここに挿入します
	return _obj[PLAYER_PARTS_BODY].GetTranslation();
}

void Enemy::Calc()
{
	for (std::vector<Obj3d>::iterator it = _obj.begin();
		it != _obj.end();
		it++)
	{
		it->Update();
	}
	_collisionNodeBody.Update();
}

void Enemy::SetPosition(const DirectX::SimpleMath::Vector3 & trans)
{
	_obj[PLAYER_PARTS_BODY].SetTransform(trans);
}

const DirectX::SimpleMath::Matrix & Enemy::GetLocalWorld()
{
	// TODO: return ステートメントをここに挿入します
	return _obj[PLAYER_PARTS_BODY].GetWorld();

}

const DirectX::SimpleMath::Vector3 & Enemy::GetAngle()
{
	// TODO: return ステートメントをここに挿入します
	return _obj[PLAYER_PARTS_BODY].GetRotation();
}

void Enemy::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// タンクパーツの座標を設定
	_obj[PLAYER_PARTS_BODY].SetRotation(rot);
}