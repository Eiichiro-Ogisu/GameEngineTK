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

	// ���@�p�[�c
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
	/// �R���X�g���N�^
	/// </summary>
	Enemy();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Enemy();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���W���擾
	/// </summary>
	const DirectX::SimpleMath::Vector3& GetPosition();

	// �s��̌v�Z
	void Calc();

	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	void SetPosition(const DirectX::SimpleMath::Vector3& trans);

	/// <summary>
	/// ���[���h�s����擾
	/// </summary>
	const DirectX::SimpleMath::Matrix& GetLocalWorld();

	/// <summary>
	/// �p�x�̎擾
	/// </summary>
	const DirectX::SimpleMath::Vector3& GetAngle();

	/// ��]��ݒ�
	void SetRot(const DirectX::SimpleMath::Vector3& rot);

	// 
	const SphereNode& GetCollisionNodeBody() { return _collisionNodeBody; }

protected:
	// �T�C���p�̈����̊p�x
	float _sinAngle;

	// �p�[�c
	std::vector<Obj3d> _obj;

	// �^�C�}�[
	int _timer;

	// �ړI�n�̊p�x
	float _distAngle;

	// �S�g�p�̓����蔻��
	SphereNode _collisionNodeBody;

};