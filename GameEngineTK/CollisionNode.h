/// <summary>
/// 当たり判定用ノード
/// </summary>
#pragma once

#include "Collision.h"
#include "Obj3d.h"

/// <summary>
/// 当たり判定ノード
/// </summary>
class CollisionNode
 {
 protected:
	 // デバッグ表示オン
	 static bool m_DebugVisible;

 public:
	 static void GetDebugVisible(bool flag) { m_DebugVisible = flag; }
	 static bool GetDebugVisible() { return m_DebugVisible; }

	public:
			// 初期化
			virtual void Initialize() = 0;
			// 毎フレーム更新
			virtual void Update() = 0;
			// 描画
			virtual void Draw() = 0;
			// 親をセット
			void SetParent(Obj3d* parent);
			// 親からのオフセットをセット
			void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_Trans = trans; }
	protected:
			// デバッグ表示用オブジェクト
			Obj3d m_Obj;
			// 親からのオフセット
			DirectX::SimpleMath::Vector3 m_Trans;
			};

/// <summary>
/// 球当たり判定ノード
/// </summary>
class SphereNode : public CollisionNode, public Sphere
 {
	public:
			// コンストラクタ
			SphereNode();
			// 初期化
			void Initialize();
			// 毎フレーム更新
			void Update();
			// 描画
			void Draw();
			// ローカル半径をセット
			void SetLocalRadius(float radius) { m_LocalRadius = radius; }
		protected:
				// ローカル半径
				float m_LocalRadius;
			};