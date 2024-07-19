#include "EnemyBase.h"
#include "../Object/Camera.h"
#include "../Manager/ResourceManager.h"
#include "math.h"

EnemyBase::EnemyBase(){

	//�v���C���[�̍U�����q�b�g��������se�ǂݍ���
	hit_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Hit_SE");

	//���S���̃p�[�e�B�N���ǂݍ���
	death_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("Enemy_Death");

}

EnemyBase::~EnemyBase(){
	MV1DeleteModel(duplication_model_);
	death_ptcl_.reset();

}

void EnemyBase::Update(float delat_time){

	//�ړ��O���W�ݒ�
	prev_pos_ = MV1GetPosition(duplication_model_);
}

void EnemyBase::Draw(std::shared_ptr<Camera> camera){
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
		return (atan(aaa) + tnl::PI );
	}
	else {
		return atan(aaa);
	}
}

float EnemyBase::Distance_target() {
	return distance_target_ = static_cast<float>(sqrt(pow(MV1GetPosition(duplication_model_).x - target_pos_.x, 2) + pow(MV1GetPosition(duplication_model_).z - target_pos_.z, 2)));
}

void EnemyBase::Movedir_update(float delta_time, float movedir_update_interval){	
	//movedir_update_interval���Ƃɐi�s�����X�V
	movedir_update_count_ += delta_time;
	if (movedir_update_count_ >= movedir_update_interval) {
		movedir_update_count_ = 0.0f;

		//�i�s�����X�V
		move_dir_ = tnl::Vector3::Normalize(target_pos_ - Getter_pos());
	}
}

void EnemyBase::PlyaerAttack_Recieve(float damage){
	//�v���C���[�̍U����������������se�Đ�
	PlaySoundMem(hit_se_hdl_, DX_PLAYTYPE_BACK);
	//�_���[�W���f
	Setter_hp(damage);
	//�_���[�W�t���Otrue
	is_HitRecieve_ = true;
}

void EnemyBase::Anim_Change(int animtype){
	//�A�j���[�V�����̎�ޕύX
	anim_attachi_index_ = MV1AttachAnim(duplication_model_, animtype, -1, false);
	//�A�j���[�V�����̍Đ����Ԑݒ�
	anim_totaltime_ = MV1GetAttachAnimTotalTime(duplication_model_, anim_attachi_index_);
	//�A�j���[�V�����Đ����ԃ��Z�b�g
	anim_count_ = 0.0f;
}

void EnemyBase::AnimPlay(float delta_time){
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

