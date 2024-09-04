#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"

class Camera;

class Play_Map {
private:
	//�n�ʊ֌W

	//�n�ʂ̉摜�n���h��
	Shared<dxe::Texture> ground_texture_;
	//�n�ʉ摜�̃��b�V��
	Shared<dxe::Mesh> ground_mesh_ = nullptr;
	//�n�ʂ̒��S
	const tnl::Vector3 ground_center_ = { 0,0,0 };
	//�n�ʉ摜�̃T�C�Y
	const tnl::Vector3 ground_scale_{ 5000.0f,5.0f,5000.0f };

//---------------------------------------------------------------------------
	//�؊֌W

	//�؂�mv1���f�� ������
	int tree_mhdl_ = 0;
	//��������؂̍ő吔
	static const int tree_duplicate_max_ = 2000;
	//�ؕ������f���̔z��
	std::vector<int> tree_duplicate_hdl_;
	//�؂�y���W
	const float tree_pos_y_ = 150.0;
	//�؂̃T�C�Y
	const DxLib::VECTOR tree_size_ = { 0.3f,0.3f,0.3f };
	//�؂̐����Ԋu
	const float tree_spawn_distance_ = 90.0f;
	//�����ʒu���������炷�l
	//-shift_����+shift�܂�
	const int shift_x_ = 30;
	const int shift_z_ = 30;

//---------------------------------------------------------------------------
	//�v���C���[�ړ��͈͉~�֌W

	//�v���C���[�̈ړ����E�̍��W�̒��S�A�~��
	tnl::Vector3 player_move_center = { 0,0,0 };
	//�v���C���[�̈ړ����E�̍��W�̔��a
	const float player_move_rad_ = 1000.0f;
	//�v���C���[�̈ړ����E�̒��S����̒����@�x�N�g��
	const float player_move_vec_ = static_cast<float>(pow(player_move_rad_, 2));

	//�v���C�G���A����������~�֌W
	Shared<dxe::Mesh> player_map = nullptr;
	Shared<dxe::Texture> player_map_tex = nullptr;
	//�~�ƒn�ʂƂ̋���
	const float circle_pos_y_ = 10.0f;

//---------------------------------------------------------------------------

	//�}�E�X�J�[�\���̃��C�Ƃ̓����蔻��p��box
	//�{�b�N�X�T�C�Y
	const float ray_box_size_ = 1.0f;

public:
	Play_Map();
	~Play_Map();
	//�}�b�v�\��
	//�����P�F�J�����C���X�^���X
	void Map_Draw(const std::shared_ptr<Camera>& camera);

//�Q�b�^�[�A�Z�b�^�[

	//�v���C���[�̈ړ����E�̒��S���W�̃Q�b�^�[
	tnl::Vector3 Getter_Playmap_Center()const {
		return player_move_center;
	};
	//�v���C���[�̈ړ����E�̔��a�̃Q�b�^�[
	float Getter_Playmap_Rad()const {
		return player_move_rad_;
	}
	//�n�ʂ̃��b�V���̃Q�b�^�[
	Shared<dxe::Mesh> Getter_Ground()const {return ground_mesh_; };
};
