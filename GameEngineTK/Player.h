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
	/// �萔
	/// </summary>
	/// �d�͉����x
	const float GRAVITY_ACC = 0.03f;
	// �W�����v����
	const float JUMP_SPEED_FIRST = 0.5f;
	// �W�����v����<m/frame>
	const float JUMP_SPEED_MAX = 0.3f;


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
	Player();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player();

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
	/// �e�ۂ𔭎�
	/// </summary>
	void FireBullet();

	/// <summary>
	/// �e�ۂ��đ���
	/// </summary>
	void ResetBullet();

	/// <summary>
	/// ���W���擾
	/// </summary>
	const DirectX::SimpleMath::Vector3& GetPosition();

	void Calc();

	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	void SetPosition(const DirectX::SimpleMath::Vector3& trans);

	/// <summary>
	/// ���[���h�s����擾
	/// </summary>
	const DirectX::SimpleMath::Matrix& GetLocalWorld();

	// �e�ۗp�����蔻����擾
	const SphereNode& GetCollisionNodeBullet() { return _collisionNodeBullet; }

	// �S�g�̓����蔻�苅
	const SphereNode& GetCollisionNodeBody() { return _collisionNodeBody; }

	/// <summary>
	/// �p�x�̎擾
	/// </summary>
	const DirectX::SimpleMath::Vector3& GetRot();

	void StartJump();

	void StartFall();

	void StopJump();

	const DirectX::SimpleMath::Vector3& GetVelocity() { return m_velocity; }

protected:
	// �p�[�c
	std::vector<Obj3d> _obj;

	// ���@�̍��W
	DirectX::SimpleMath::Vector3 _position;

	DirectX::SimpleMath::Vector3 _angle;

	// �e�ۂ̑��x�x�N�g��
	DirectX::SimpleMath::Vector3 _bulletVel;

	int cnt = 0;

	bool isFire = false;

	// �e�ۗp�̓����蔻��
	SphereNode _collisionNodeBullet;

	// �S�g�p�̓����蔻��
	SphereNode _collisionNodeBody;

	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;

	// �������t���O
	bool m_isJump;
};