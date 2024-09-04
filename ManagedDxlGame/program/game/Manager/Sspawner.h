#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "ItemSpawner.h"

class Camera;
class EnemyBase;
class Player;
class ProtectObject;

//�G
struct ENEMY {
	//�G�̕��������f��
	int model_hdl_ = 0;
	//�G�̃T�C�Y
	DxLib::VECTOR scale_ = { 0.3f,0.3f,0.3f };
	//�ړ����x
	float speed_ = 0.0f;
	//�̗�
	float hp_ = 0.0f;
	//���f���̌��̃T�C�Y
	const tnl::Vector3 size_{ 100,310,100 };
	//�e�Ƃ̓����蔻��p���a
	float colli_rad_ = 0.0f;
	//�v���C���[�Ƃ̓����蔻��p�T�C�Y
	tnl::Vector3 colli_size_{35,50,35};

	//�X�|������Ԋu
	float spawn_count_ = 0.0f, spawn_interval_ = 0.0f;
	//�Œ�X�|���Ԋu
	float spawn_interval_low_ = 0.1f;
};

//�G�̎��
enum class ENEMYTYPE {
	normal,
	chase,
	big,
	max
};

class Spawner : public ItemSpawner {
private:
	//�G�̃^�[�Q�b�g
	std::weak_ptr<ProtectObject> target_protectobj_;
	std::weak_ptr<Player> target_player_;

	//�ʏ�G
	ENEMY normal_enemy_;
	//�v���C���[��ǂ�������G
	ENEMY enemy_chase_;
	//�傫���G
	ENEMY big_enemy_;

	//��������ő吔
	const int duplicate_max_ = 1000;
	//�����J�E���g
	int duplicate_count_ = 0;

	//�������e�̃��b�V��
	Shared<dxe::Mesh> shadow_mesh_ = nullptr;
	//�C���X�^���V���O���b�V���v�[��
	Shared<dxe::InstMeshPool> shadow_mesh_pool_ = nullptr;
	//�e�̃e�N�X�`���z��
	std::vector<Shared<dxe::Texture>> shadow_textures_;
	//90�x�|��
	tnl::Quaternion shadow_down_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));
	//�e��y���W
	const float shadow_pos_y_ = 3.0f;

	//�e�N�X�`����vector
	std::vector<Shared<dxe::Texture>> enemy1_textures_;

	//�G��list
	std::list<std::shared_ptr<EnemyBase>> enemys_;

	//�}�b�v�̒��S���W
	tnl::Vector3 map_center_{ 0,0,0 };
	//�}�b�v�̔��a
	float map_rad_ = 0.0f;

	//�����_���Ȋp�x�i���������j
	float rad_ = 0.0f;

	//�A�C�e���̐����m��
	//�v�f 0.none 1.itemred 2.itemblue 3.itemgreen 4.itembomb
	int itemprob_[5]{50,10,10,10,20};

public:
	Spawner() = default;

	//�����P�F�v���C�G���A�̒��S�A�Q�F�v���C�G���A�̔��a�A�R�F�^�[�Q�b�g�i�D�j�A�S�F�^�[�Q�b�g�i�v���C���[�j�j
	Spawner(const tnl::Vector3& map_center, const float& map_rad, const std::shared_ptr<ProtectObject>& target_protectobj, const std::shared_ptr<Player>& target_player);
	~Spawner();
	
	//���s
	//�����P�F����
	void Update(const float& delta_time);
	//�\��
	//�����P�F�J�����C���X�^���X
	void Draw(const std::shared_ptr<Camera>& camera);
	
	//�G����
	//�����F�P�D�C���X�^���X�A�Q�F�v���C���[�C���X�^���X�A�R�F����
	void Enemy_Spawn(std::weak_ptr<ProtectObject> protectobject, std::weak_ptr<Player> player, const float& delta_time);
	
	//�ʏ�G�X�|���Ԋu�A�X�|�����̃X�e�[�^�X�ύX
	//�����P�F�G�̎�ށA�@�����Q�F���Z�l�X�|���C���^�[�o���A�@�����R�F���Z�lhp�A�@�����S�F���Z�l�X�s�[�h
	void Enemy_SpawnStatusChange(const ENEMYTYPE& enemytype, const float& sub_spawn_interval, const float& add_hp, const float& add_speed);
	
	//�G�����A�����ʒu�Ɉړ��A�T�C�Y�ύX
	//�����P�F���������f���A�Q�F�T�C�Y�X�P�[��
	int EnemyDupe(const int& model_hdl, const DxLib::VECTOR& scale);	
	
	//�e����
	//�����P�F�������e���f��
	Shared<dxe::InstMesh> ShadowDupe(const int& enedupe);
	 
//�Q�b�^�[�A�Z�b�^�[

	//list�̃Q�b�^�[
	std::list< std::shared_ptr<EnemyBase>>& Getter_enemy_list() { return enemys_; };
};