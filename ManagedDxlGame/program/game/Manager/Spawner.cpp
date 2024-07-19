#include "Sspawner.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyChase.h"
#include "../Character/EnemyBig.h"
#include "../Manager/ResourceManager.h"
#include "../Object/Camera.h"
#include "../Character/EnemyBase.h"
#include "../Object/ProtectObject.h"
#include "../Character/Player.h"

Spawner::Spawner(tnl::Vector3 map_center, float map_rad, std::shared_ptr<ProtectObject>& target_protectobj, std::shared_ptr<Player>& target_player) {
	//�^�[�Q�b�g���
	target_player_ = target_player;
	target_protectobj_ = target_protectobj;
	
	//�}�b�v���}��
	map_center_ = map_center;
	map_rad_ = map_rad;

	//�����_���l�̎�����ԂŐݒ�
	srand(time(0));

	//�e����
	shadow_mesh_ = dxe::Mesh::CreateDiskMV(1, 10, 10, 360);
	//�e�̃e�N�X�`�������[�h
	shadow_textures_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("SHADOW_2"));
	//�e����
	shadow_mesh_pool_ = dxe::InstMeshPool::Create(shadow_mesh_, duplicate_max_, &shadow_textures_);

	//������ normal_enemy_��mv1���f���ǂݍ���
	normal_enemy_.model_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("NORMAL_ENEMY_");
	normal_enemy_.colli_rad_ = normal_enemy_.size_.x * normal_enemy_.scale_.x;

	//������ enemy_chase_��mv1���f���ǂݍ���
	enemy_chase_.model_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("ENEMY_CHASE");
	//enemy_chase_�X�e�[�^�X�ݒ�
	enemy_chase_.colli_rad_ = enemy_chase_.size_.x * enemy_chase_.scale_.x;

	//������ big_enemy_�̃��f���ǂݍ���
	big_enemy_.model_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("BIG_ENEMY");
	//big_enemy_�X�e�[�^�X�ݒ�
	big_enemy_.scale_ = { 0.6f,0.6f,0.6f };
	big_enemy_.spawn_interval_low_ = 1.0f;
	big_enemy_.colli_size_ = (big_enemy_.colli_size_ / big_enemy_.scale_.x);
	big_enemy_.colli_rad_ = big_enemy_.size_.x * big_enemy_.scale_.x;
}

Spawner::~Spawner() {
	shadow_mesh_pool_.reset();
	MV1DeleteModel(normal_enemy_.model_hdl_);
	MV1DeleteModel(enemy_chase_.model_hdl_);
}

void Spawner::Update(float delta_time) {
	auto protectobj = target_protectobj_.lock();
	if (protectobj == nullptr) { return; }
	auto player = target_player_.lock();
	if (player == nullptr) { return; }

	//�G����
	Enemy_Spawn(protectobj, player, delta_time);

	//�G�̎��s�Ə���
	auto it = enemys_.begin();
	while (it != enemys_.end()){
		//���s
		(*it)->Update(delta_time);

		//is_alive_��false�Ȃ�Ώ����i�G���S�j
		if (!(*it)->Getter_is_alive()) {
			//�A�C�e������
			CreateItem(Item_Lottery(itemprob_[0],itemprob_[1], itemprob_[2], itemprob_[3], itemprob_[4]), (*it)->Getter_pos());

			it = enemys_.erase(it);
			duplicate_count_--;
			continue;
		}
		it++;
	}

	//�A�C�e���̎��s
	ItemUpdate(delta_time);
}

void Spawner::Draw(std::shared_ptr<Camera> camera) {
	dxe::DirectXRenderBegin();

	//�e�`��
	shadow_mesh_pool_->render(camera);

	dxe::DirectXRenderEnd();

	//�G�`��
	auto it = enemys_.begin();
	while (it != enemys_.end()) {
		//�G�`��
		(*it)->Draw(camera);
		it++;
	}

	//�A�C�e���`��
	ItemDraw(camera);
}

void Spawner::Enemy_Spawn(std::weak_ptr<ProtectObject> protectobject, std::weak_ptr<Player> player, float delta_time) {
	//normal_enemy_�X�|��
	normal_enemy_.spawn_count_ += delta_time;
	if (normal_enemy_.spawn_count_ > normal_enemy_.spawn_interval_) {
		//�G����
		int duplication = EnemyDupe(normal_enemy_.model_hdl_, normal_enemy_.scale_);
		//�e����
		auto shadow = ShadowDupe(duplication);

		//list�ɑ}��
		enemys_.emplace_back(std::make_shared<Enemy>(protectobject, duplication, shadow, normal_enemy_.speed_, normal_enemy_.hp_, normal_enemy_.colli_rad_, normal_enemy_.colli_size_));
		duplicate_count_++;

		//�J�E���g���Z�b�g
		normal_enemy_.spawn_count_ = 0.0f;
	}

	//enemy_chase_�X�|��
	enemy_chase_.spawn_count_ += delta_time;
	if (enemy_chase_.spawn_count_ > enemy_chase_.spawn_interval_) {
		//�G����
		int duplication = EnemyDupe(enemy_chase_.model_hdl_, enemy_chase_.scale_);
		//�e����
		auto shadow = ShadowDupe(duplication);

		//list�ɑ}��
		enemys_.emplace_back(std::make_shared<EnemyChase>(player, duplication, shadow, enemy_chase_.speed_, enemy_chase_.hp_, enemy_chase_.colli_rad_, enemy_chase_.colli_size_));
		duplicate_count_++;

		//�J�E���g���Z�b�g
		enemy_chase_.spawn_count_ = 0.0f;
	}

	//big_enemy_�X�|��
	big_enemy_.spawn_count_ += delta_time;
	if (big_enemy_.spawn_count_ > big_enemy_.spawn_interval_) {
		//�G����
		int duplication = EnemyDupe(big_enemy_.model_hdl_, big_enemy_.scale_);
		//�e����
		auto shadow = ShadowDupe(duplication);

		//list�ɑ}��
		enemys_.emplace_back(std::make_shared<EnemyBig>(protectobject, duplication, shadow, big_enemy_.speed_, big_enemy_.hp_, big_enemy_.colli_rad_, big_enemy_.colli_size_));
		duplicate_count_++;

		//�J�E���g���Z�b�g
		big_enemy_.spawn_count_ = 0.0f;
	}
}

void Spawner::Enemy_SpawnStatusChange(ENEMYTYPE enemytype, float sub_spawn_interval, float add_hp, float add_speed) {
	switch (enemytype){
	case ENEMYTYPE::normal:
		//�X�|���C���^�[�o�����Z
		normal_enemy_.spawn_interval_ -= sub_spawn_interval;
		//�Œ�X�|���C���^�[�o�������ɂ��Ȃ�
		if (normal_enemy_.spawn_interval_ <= normal_enemy_.spawn_interval_low_) {
			normal_enemy_.spawn_interval_ = normal_enemy_.spawn_interval_low_;
		}
		//hp���Z
		normal_enemy_.hp_ += add_hp;
		//speed���Z
		normal_enemy_.speed_ += add_speed;
		break;
	case ENEMYTYPE::chase:
		//�X�|���C���^�[�o�����Z
		enemy_chase_.spawn_interval_ -= sub_spawn_interval;
		//�Œ�X�|���C���^�[�o�������ɂ��Ȃ�
		if (enemy_chase_.spawn_interval_ <= enemy_chase_.spawn_interval_low_) {
			enemy_chase_.spawn_interval_ = enemy_chase_.spawn_interval_low_;
		}
		//hp���Z
		enemy_chase_.hp_ += add_hp;
		//speed���Z
		enemy_chase_.speed_ += add_speed;
		break;
	case ENEMYTYPE::big:
		//�X�|���C���^�[�o�����Z
		big_enemy_.spawn_interval_ -= sub_spawn_interval;
		//�Œ�X�|���C���^�[�o�������ɂ��Ȃ�
		if (big_enemy_.spawn_interval_ <= big_enemy_.spawn_interval_low_) {
			big_enemy_.spawn_interval_ = big_enemy_.spawn_interval_low_;
		}
		//hp���Z
		big_enemy_.hp_ += add_hp;
		//speed���Z
		big_enemy_.speed_ += add_speed;
	default:
		break;
	}	
}

int Spawner::EnemyDupe(int model_hdl, DxLib::VECTOR scale) {
	//�����_���Ȋp�x�i���������j
	rad_ = rand() % 360;
	float x = cos(rad_) * map_rad_;
	float z = sin(rad_) * map_rad_;
	//normal_enemy_����
	int ene = MV1DuplicateModel(model_hdl);
	//�����ʒu�Ɉړ�
	MV1SetPosition(ene, DxLib::VECTOR{ x,0.0f,z });
	//�T�C�Y�ύX
	MV1SetScale(ene, scale);

	return ene;
}

Shared<dxe::InstMesh> Spawner::ShadowDupe(int enedupe) {
	auto shadow = shadow_mesh_pool_->CreateInstMesh();
	shadow->setPosition({ MV1GetPosition(enedupe).x, shadow_pos_y_, MV1GetPosition(enedupe).z });
	shadow->setRotation(shadow_down_);
	shadow->setUseTextureIndex(0);
	shadow->setScale({ 30.0f,30.0f,0 });

	return shadow;
}
