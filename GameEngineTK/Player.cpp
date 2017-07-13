#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
}

/// <summary>
/// ������
/// </summary>
void Player::Initialize()
{
	// ���@�p�[�c�̓ǂݍ���
	_obj.resize(PLAYER_PARTS_NUM);
	_obj[PLAYER_PARTS_LEG].LoadModel(L"Resources\\leg.cmo");
	_obj[PLAYER_PARTS_BODY].LoadModel(L"Resources\\body.cmo");
	_obj[PLAYER_PARTS_BATTERY].LoadModel(L"Resources\\battery.cmo");
	_obj[PLAYER_PARTS_BATTERY2].LoadModel(L"Resources\\battery.cmo");
	_obj[PLAYER_PARTS_HAND].LoadModel(L"Resources\\hand.cmo");
	_obj[PLAYER_PARTS_HAND2].LoadModel(L"Resources\\hand.cmo");
	_obj[PLAYER_PARTS_HEAD].LoadModel(L"Resources\\head.cmo");

	// �p�[�c�̐e�q�֌W���Z�b�g
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

	// �e����̃I�t�Z�b�g
	// �{�f�B�̍��W�����������̈ʒu��
	_obj[PLAYER_PARTS_BODY].SetTransform(Vector3(0, 0.25, 0));

	// ��������������
	_obj[PLAYER_PARTS_LEG].SetScale(Vector3(0.8, 0.25, 0.5));

	_obj[PLAYER_PARTS_LEG].SetTransform(Vector3(0, -0.25, 0));

	// ���������������
	_obj[PLAYER_PARTS_HAND].SetTransform(Vector3(-0.5, 0.6, -0.2));
	_obj[PLAYER_PARTS_HAND].SetScale(Vector3(0.25, 0.25, 0.75));

	_obj[PLAYER_PARTS_HAND2].SetTransform(Vector3(0.5, 0.6, -0.2));
	_obj[PLAYER_PARTS_HAND2].SetScale(Vector3(0.25, 0.25, 0.75));

	// ��������������
	_obj[PLAYER_PARTS_HEAD].SetTransform(Vector3(0, 1, 0));
	_obj[PLAYER_PARTS_HEAD].SetScale(Vector3(1.5, 1.5, 1.5));

	// �^���N������������
	_obj[PLAYER_PARTS_BATTERY].SetRotation(Vector3(0, 135, -0.55));
	_obj[PLAYER_PARTS_BATTERY].SetTransform(Vector3(-0.5, 0.9, -0.15));
	_obj[PLAYER_PARTS_BATTERY].SetScale(Vector3(0.5, 0.5, 0.5));


	_obj[PLAYER_PARTS_BATTERY2].SetRotation(Vector3(0, 135, 0.55));
	_obj[PLAYER_PARTS_BATTERY2].SetTransform(Vector3(0.5, 0.9, -0.15));
	_obj[PLAYER_PARTS_BATTERY2].SetScale(Vector3(0.5, 0.5, 0.5));


	// TODO
		{// �e�ۗp�̓����蔻���ݒ�
		_collisionNodeBullet.Initialize();
				// �e�p�[�c���w��
		_collisionNodeBullet.SetParent(&_obj[PLAYER_PARTS_HAND]);
		_collisionNodeBullet.SetTrans(Vector3(0, 0, 0));
		_collisionNodeBullet.SetLocalRadius(0.5f);
		}

		{// �S�g�p�̓����蔻���ݒ�
			_collisionNodeBody.Initialize();
			// �e�p�[�c���w��
			_collisionNodeBody.SetParent(&_obj[0]);
			_collisionNodeBody.SetTrans(Vector3(0, 1.0f, 0));
			_collisionNodeBody.SetLocalRadius(1.0f);
		}

		m_isJump = false;
}

/// <summary>
/// �X�V����
/// </summary>
void Player::Update()
{
	// DXTK���Ǘ�����C���X�^���X���擾
	DXTK::DXTKResources& dxtk = DXTK::DXTKResources::singleton();

	dxtk.UpdateInputState();

	// �L-�{�[�h�̏��
	Keyboard::State keyboardState = dxtk.m_keyboard->GetState();

	//// �f�o�b�O�\���p�L�[����
	//if (keyboardState.B)
	//{
	//	CollisionNode::GetDebugVisible(true);
	//}

	/// <summary>
	/// �d�͊֘A
	/// </summary>
	if (keyboardState.M)
	{
		// �W�����v�J�n
		StartJump();
	}

	// �W�����v��
	if (m_isJump)
	{
		m_velocity.y -= GRAVITY_ACC;
		if (m_velocity.y <= -JUMP_SPEED_MAX)
		{
			m_velocity.y = -JUMP_SPEED_MAX;
		}
	}

	Vector3 trans = this->GetPosition();
	trans += m_velocity;
	this->SetPosition(trans);

	// �L�[����
	if (keyboardState.W)
	{
		// �ړ���
		Vector3 moveV = Vector3(0.0f, 0.0f, -0.1f);

		float angle = _obj[PLAYER_PARTS_BODY].GetRotation().y;

		Matrix rotmat = Matrix::CreateRotationY(angle);

		moveV = Vector3::TransformNormal(moveV, rotmat);

		// ���@�ړ�
		Vector3 pos = _obj[PLAYER_PARTS_BODY].GetTranslation();
		_obj[PLAYER_PARTS_BODY].SetTransform(pos += moveV);
	}

	if (keyboardState.S)
	{
		// �ړ���
		Vector3 moveV = Vector3(0.0f, 0.0f, 0.1f);

		float angle = _obj[PLAYER_PARTS_BODY].GetRotation().y;

		Matrix rotmat = Matrix::CreateRotationY(angle);

		moveV = Vector3::TransformNormal(moveV, rotmat);

		// ���@�ړ�
		Vector3 pos = _obj[PLAYER_PARTS_BODY].GetTranslation();
		_obj[PLAYER_PARTS_BODY].SetTransform(pos += moveV);
	}

	if (keyboardState.A)
	{
		// ��]��
		float angle = _obj[PLAYER_PARTS_BODY].GetRotation().y;
		_obj[PLAYER_PARTS_BODY].SetRotation(Vector3(0, angle + 0.03f, 0));
	}

	if (keyboardState.D)
	{
		// ��]��
		//float rot = -0.03f;
		float angle = _obj[PLAYER_PARTS_BODY].GetRotation().y;
		_obj[PLAYER_PARTS_BODY].SetRotation(Vector3(0, angle - 0.03f, 0));
	}




	// �����蔻��̍X�V
	_collisionNodeBullet.Update();


	if (keyboardState.Space)
	{
		FireBullet();

		isFire = true;
	}

	if (isFire)
	{
		cnt++;
		// �e�ۂ𔭎˂���
		{
			//���@�ړ�
			Vector3 pos = _obj[PLAYER_PARTS_HAND].GetTranslation();
			_obj[PLAYER_PARTS_HAND].SetTransform(pos += _bulletVel);

			Vector3 pos2 = _obj[PLAYER_PARTS_HAND2].GetTranslation();
			_obj[PLAYER_PARTS_HAND2].SetTransform(pos2 += _bulletVel);

		}

		if (cnt > 120)
		{
			ResetBullet();

			isFire = false;

			cnt = 0;
		}
	}
	Calc();
}

void Player::Draw()
{
	for (std::vector<Obj3d>::iterator it = _obj.begin(); 
		it != _obj.end();
		it++)
	{
		it->Draw();
	}

	if (CollisionNode::GetDebugVisible())
	{
		_collisionNodeBullet.Draw();

		_collisionNodeBody.Draw();
	}
}

void Player::FireBullet()
{
	// ���˂���p�[�c�̃��[���h�s����擾
	Matrix worldm = _obj[PLAYER_PARTS_HAND].GetWorld();

	Matrix worldm2 = _obj[PLAYER_PARTS_HAND2].GetWorld();


	// ���[���h�s�񂩂�e�v�f�𒊏o
	Vector3 scale;			// ���[���h�X�P�[�����O
	Quaternion rotation;	// ���[���h��]
	Vector3 translation;	// ���[���h���W

	worldm.Decompose(scale,rotation, translation);

	// ���˂�p�[�c��e���番�����ēƗ�
	_obj[PLAYER_PARTS_HAND].SetParent(nullptr);
	_obj[PLAYER_PARTS_HAND].SetScale(scale);
	_obj[PLAYER_PARTS_HAND].SetRotationQ(rotation);
	_obj[PLAYER_PARTS_HAND].SetTransform(translation);

	worldm2.Decompose(scale, rotation, translation);

	_obj[PLAYER_PARTS_HAND2].SetParent(nullptr);
	_obj[PLAYER_PARTS_HAND2].SetScale(scale);
	_obj[PLAYER_PARTS_HAND2].SetRotationQ(rotation);
	_obj[PLAYER_PARTS_HAND2].SetTransform(translation);


	// �e�ۂ̑��x��ݒ�
	_bulletVel = Vector3(0, 0, -0.5f);
	_bulletVel = Vector3::Transform(_bulletVel, rotation);
}

void Player::ResetBullet()
{
		_obj[PLAYER_PARTS_HAND].SetParent(&_obj[PLAYER_PARTS_BODY]);
		_obj[PLAYER_PARTS_HAND2].SetParent(&_obj[PLAYER_PARTS_BODY]);

		_obj[PLAYER_PARTS_HAND].SetTransform(Vector3(-0.5, 0.6, -0.2));
		_obj[PLAYER_PARTS_HAND].SetRotation(Vector3(0, 0, 0));
		_obj[PLAYER_PARTS_HAND].SetScale(Vector3(0.25, 0.25, 0.75));


		_obj[PLAYER_PARTS_HAND2].SetTransform(Vector3(0.5, 0.6, -0.2));
		_obj[PLAYER_PARTS_HAND2].SetRotation(Vector3(0,0,0));
		_obj[PLAYER_PARTS_HAND2].SetScale(Vector3(0.25, 0.25, 0.75));

}

const DirectX::SimpleMath::Vector3 & Player::GetPosition()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	return _obj[PLAYER_PARTS_BODY].GetTranslation();
}

void Player::Calc()
{
	for (std::vector<Obj3d>::iterator it = _obj.begin();
		it != _obj.end();
		it++)
	{
		it->Update();
	}

	_collisionNodeBody.Update();

	_collisionNodeBullet.Update();
}

void Player::SetPosition(const DirectX::SimpleMath::Vector3 & trans)
{
	_obj[PLAYER_PARTS_BODY].SetTransform(trans);
}

const DirectX::SimpleMath::Matrix & Player::GetLocalWorld()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	return _obj[PLAYER_PARTS_BODY].GetWorld();

}

const DirectX::SimpleMath::Vector3 & Player::GetRot()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	return _obj[PLAYER_PARTS_BODY].GetRotation();
}

/// <summary>
/// �W�����v�J�n
/// </summary>
void Player::StartJump()
{
	// �W�����v���łȂ���
	if (!m_isJump)
	{
		// ������̑��x��ݒ�
		m_velocity.y = JUMP_SPEED_FIRST;

		m_isJump = true;
	}
}

/// <summary>
/// �����J�n
/// </summary>
void Player::StartFall()
{
	// �W�����v���łȂ���
	if (!m_isJump)
	{
		// ������̑��x��ݒ�
		m_velocity.y = 0.0f;

		m_isJump = true;
	}
}

/// <summary>
/// �W�����v���I������
/// </summary>
void Player::StopJump()
{
	m_isJump = false;

	m_velocity = Vector3::Zero;
}