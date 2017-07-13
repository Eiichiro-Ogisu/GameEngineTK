#include "CollisionNode.h"

 using namespace DirectX::SimpleMath;

 bool CollisionNode::m_DebugVisible = false;

/// <summary>
/// CollisionNodeのメンバ関数
/// </summary>

void CollisionNode::SetParent(Obj3d * parent)
{
	m_Obj.SetParent(parent);
}

/// <summary>
/// SphereNodeのメンバ関数
/// </summary>

SphereNode::SphereNode()
{
	// デフォルト半径を1メートルにする
	m_LocalRadius = 1.0f;
}

void SphereNode::Initialize()
{
	// デバッグ表示用モデルを読み込む
	m_Obj.LoadModel(L"Resources\\SphereNode.cmo");
}

void SphereNode::Update()
{
	m_Obj.SetTransform(m_Trans);
	m_Obj.SetScale(Vector3(m_LocalRadius));
	
	// ワールド行列の更新
	m_Obj.Update();

	// ワールド座標での当たり判定球を計算
	{
		// 計算済みのワールド行列を取得
		const Matrix& worldm = m_Obj.GetWorld();

		// モデル座標系での中心点
		Vector3 center(0, 0, 0);

		// モデル座標系での右端
		Vector3 right(1, 0, 0);

		// ワールド座標に変換
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		// 当たり判定球に結果を代入
		Sphere::_center = center;
		Sphere::_radius = Vector3::Distance(center, right);
	}
}

void SphereNode::Draw()
 {
	m_Obj.Draw();
}