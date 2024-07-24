#include "EnemyBase.h"
#include "../Object/Camera.h"
#include "../Manager/ResourceManager.h"
#include "math.h"

EnemyBase::EnemyBase(const int& duplication_mesh, const Shared<dxe::InstMesh>& shadow_mesh,
	const float& speed, const float& hp, const float& colli_rad, const tnl::Vector3& colli_size){
	//�v���C���[�̍U�����q�b�g��������se�ǂݍ���
	hit_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Hit_SE");
	//���S���̃p�[�e�B�N���ǂݍ���
	death_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("Enemy_Death");

	//���f��
	duplication_model_ = duplication_mesh;
	//�e�̃��b�V��
	shadow_mesh_ = shadow_mesh;
	//�ړ����x�ݒ�
	speed_ = speed;
	//�e�Ƃ̓����蔻��p���a
	colli_rad_ = colli_rad;
	//�v���C���[�Ƃ̓����蔻��p�{�b�N�X�T�C�Y
	colli_size_ = colli_size;
	//�̗�
	hp_ = hp;
}

EnemyBase::~EnemyBase(){
	MV1DeleteModel(duplication_model_);
	death_ptcl_.reset();

}

void EnemyBase::Update(const float& delta_time){
	//�ړ��O���W�ݒ�
	prev_pos_ = MV1GetPosition(duplication_model_);

	//�m�b�N�o�b�N�����Ƀm�b�N�o�b�N������
	tnl::Vector3 knockback = Getter_pos() + (knockback_dir_ * knockback_value_);
	MV1SetPosition(duplication_model_, VGet(knockback.x, 0, knockback.z));

	//�m�b�N�o�b�N�l��0��葽����Ό��炷
	if (knockback_value_ > 0) {
		knockback_value_ -= delta_time;
	}
	else {
		knockback_value_ = 0;
		//������i�s�����������悤�ɂ���
		is_movedir_ = true;
	}

	//�A�j���[�V�����Đ�
	AnimPlay(delta_time);
}

void EnemyBase::Draw(const std::shared_ptr<Camera>& camera){
	//�`��
	MV1DrawModel(duplication_model_);

	dxe::DirectXRenderBegin();

	//�p�[�e�B�N���̕`��
	death_ptcl_->render(camera);

	dxe::DirectXRenderEnd();
}

float EnemyBase::Rotate_front() {
	//�ړ��O���W�ƌ����W��x��z�̍��i�����j
	float vec_x = Getter_pos().x - prev_pos_.x;
	float vec_z = Getter_pos().z - prev_pos_.z;

	//����v�Z
	float aaa = vec_x / vec_z;

	//z�̍������̐��������ꍇ�t�����ɂ���
	if (vec_z >= 0) {
		return (atan(aaa) + tnl::PI);
	}
	else {
		return atan(aaa);
	}
}

float EnemyBase::Distance_target() {
	return distance_target_ = static_cast<float>(sqrt(pow(MV1GetPosition(duplication_model_).x - target_pos_.x, 2) + pow(MV1GetPosition(duplication_model_).z - target_pos_.z, 2)));
}

void EnemyBase::Movedir_update(const float& delta_time, const float& movedir_update_interval){	
	//�i�s�����ύX�t���O��true�Ȃ��
	if (is_movedir_) {
		//movedir_update_interval���Ƃɐi�s�����X�V
		movedir_update_count_ += delta_time;
		if (movedir_update_count_ >= movedir_update_interval) {
			movedir_update_count_ = 0.0f;

			//�i�s�����X�V
			move_dir_ = tnl::Vector3::Normalize(target_pos_ - Getter_pos());
		}
	}
}

void EnemyBase::PlyaerAttack_Recieve(const float& damage, const tnl::Vector3& atkpos, const float& knockback_value){
	//�v���C���[�̍U����������������se�Đ�
	PlaySoundMem(hit_se_hdl_, DX_PLAYTYPE_BACK);
	//�_���[�W���f
	Setter_hp(damage);
	//�_���[�W�t���Otrue
	is_HitRecieve_ = true;
	//�_���[�W���󂯂���������ς��Ȃ�
	is_movedir_ = false;
	//�m�b�N�o�b�N�l�ݒ�
	knockback_value_ = knockback_value;
	//�m�b�N�o�b�N�����ݒ�
	knockback_dir_ = tnl::Vector3::Normalize(Getter_pos() - atkpos);
}

void EnemyBase::Anim_Change(const int& animtype){
	//�A�j���[�V�����̎�ޕύX
	anim_attachi_index_ = MV1AttachAnim(duplication_model_, animtype, -1, false);
	//�A�j���[�V�����̍Đ����Ԑݒ�
	anim_totaltime_ = MV1GetAttachAnimTotalTime(duplication_model_, anim_attachi_index_);
	//�A�j���[�V�����Đ����ԃ��Z�b�g
	anim_count_ = 0.0f;
}

void EnemyBase::AnimPlay(const float& delta_time){
	//�A�j���[�V�����I���t���O��false
	is_anim_end_ = false;
	//�A�j���[�V�����Đ�
	if (is_anim_) {
		anim_count_ += (delta_time * anim_speed_);
		if (anim_count_ >= anim_totaltime_) {
			anim_count_ = 0.0f;
			//�A�j���[�V�����I��true
			is_anim_end_ = true;
		}
		MV1SetAttachAnimTime(duplication_model_, anim_attachi_index_, anim_count_);
	}
}

