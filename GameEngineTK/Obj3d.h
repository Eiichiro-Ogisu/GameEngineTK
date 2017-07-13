/// <summary>
/// 3Dオブジェクトのクラス
/// </summary>
#pragma once

#include <Windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <CommonStates.h>
#include <Effects.h>
#include <SimpleMath.h>
#include <Model.h>

#include "Camera.h"
class Obj3d
{
	// 静的メンバ
public:
	/// <summary>
	/// 静的メンバ初期化関数
	/// </summary>
	static void InitializeStatic(
		Microsoft::WRL::ComPtr<ID3D11Device> device, 
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
		Camera* camera);

private:
	// デバイス
	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
	
	// デバイスコンテキスト
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;

	// カメラ
	static Camera* m_camera;

	// 汎用描画ステート
	static std::unique_ptr<DirectX::CommonStates> m_states;

	// エフェクトファクトリ
	static std::unique_ptr<DirectX::EffectFactory> m_factory;

public:
	// コンストラクタ
	Obj3d();

	// モデルのロード
	void LoadModel(const wchar_t* fileName);

	// 更新
	void Update();

	// 描画
	void Draw();

	// setter
	// スケーリング
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }

	// 回転角(XYZ)
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation) { m_rotation = rotation; _useQuaternion = false; }

	// 回転角(XYZ)
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rotation) { _rotationQ = rotation; _useQuaternion = true; }

	// 平行移動(XYZ)
	void SetTransform(const DirectX::SimpleMath::Vector3& transform) { m_translation = transform; }

	// 親の3dオブジェクトのポインタ
	void SetParent(Obj3d* parent) { m_parent = parent; }

	// ワールド行列
	void SetWorld(const DirectX::SimpleMath::Matrix world) { m_world = world; }

	// getter
	// スケーリング(XYZ)
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }

	// 回転角(XYZ)
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }

	// 回転角(クォータニオン)
	DirectX::SimpleMath::Quaternion _rotationQ;

	// 平行移動(XYZ)
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_translation; }

	// ワールド行列
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }

	// 親の3dオブジェクトのポインタ
	Obj3d* GetParent() { return m_parent; }


private:
	// メンバ変数

	// 3Dモデル
	std::unique_ptr<DirectX::Model> m_model;

	// スケーリング
	DirectX::SimpleMath::Vector3 m_scale;

	// 回転角(XYZ)
	DirectX::SimpleMath::Vector3 m_rotation;

	// 平行移動(XYZ)
	DirectX::SimpleMath::Vector3 m_translation;

	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	// 親の3Dオブジェクトクラスののポインタ
	Obj3d* m_parent;

	// クォータニオン使用フラグ
	bool _useQuaternion;
};