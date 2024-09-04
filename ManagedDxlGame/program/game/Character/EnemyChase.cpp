#include "EnemyChase.h"
#include "../Object/Camera.h"
#include "../Character/CharacterBase.h"
#include "../Manager/ResourceManager.h"

EnemyChase::EnemyChase(std::weak_ptr<CharacterBase> player, const int& duplication_mesh, const Shared<dxe::InstMesh>& shadow_mesh, 
	const float& speed, const float& hp, const float& colli_rad, const tnl::Vector3& colli_size) : 
	EnemyBase(duplication_mesh, shadow_mesh, speed, hp, colli_rad, colli_size) {
	//�^�[�Q�b�g
	target_ = player;
	auto target = target_.lock();
	if (!target) {
		return;
	}
	//�^�[�Q�b�g���W
	target_pos_ = target->GetterPos();
	//�U���̃C���^�[�o��
	attack_interval_ = 1.0f;
	//�U���Ɉڂ�^�[�Q�b�g�Ƃ̋���
	trans_attack_distance_ = 20.0f;
	//�ړ������X�V�C���^�[�o��
	movedir_update_interval_ = 0.2f;
	//�����ړ������v�Z
	move_dir_ = tnl::Vector3::Normalize(target->GetterPos() - Getter_pos());

	//�U����se�ǂݍ���
	attack_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Enemy2_Voice_SE");
	//���S����se�ǂݍ���
	death_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Enemy2_Death");

	//�Đ��A�j���[�V����
	anim_attachi_index_ = MV1AttachAnim(duplication_model_, animtype_, -1, false);
	//�Đ�����A�j���[�V�����̍Đ�����
	anim_totaltime_ = MV1GetAttachAnimTotalTime(duplication_model_, anim_attachi_index_);
}

EnemyChase::~EnemyChase(){

}

void EnemyChase::Update(const float& delta_time){
	auto target = target_.lock();
	if (!target) {return;}

	//�x�[�X�N���X�L�ڂ̎��s����
	__super::Update(delta_time);

	//�V�[�P���X���s
	tnl_sequence_.update(delta_time);

	//�^�[�Q�b�g�̍��W�X�V
	target_pos_ = target->GetterPos();

	//�����蔻����W�X�V
	colli_center_ = {Getter_pos().x, Getter_pos().y + colli_rad_, Getter_pos().z};
	//�e�̍��W�X�V
	shadow_mesh_->setPosition({ Getter_pos().x, shadow_mesh_->getPosition().y, Getter_pos().z });
}

void EnemyChase::Draw(const std::shared_ptr<Camera>& camera){
	//�x�[�X�N���X�L�ڂ̕`�揈��
	__super::Draw(camera);

	//�����蔻��`��
	//DrawAABB(camera, colli_center_, colli_size_);
}

bool EnemyChase::SEQ_Move(const float delta_time){
	if (tnl_sequence_.isStart()) {
		//�A�j���[�V������Walk�ɕύX
		Anim_Change(Walk);

		//���S�����ꍇ�A�C�e�����h���b�v���Ȃ�
		is_itemspawn_ = true;
	}

	//�ړ�
	MV1SetPosition(duplication_model_,
		{ Getter_pos().x + (move_dir_.x * speed_), Getter_pos().y, Getter_pos().z + (move_dir_.z * speed_) });

	//�i�s�����X�V
	Movedir_update(delta_time, movedir_update_interval_);
	if (Getter_is_movedirchange()) {
		//�i�s����������
		MV1SetRotationXYZ(duplication_model_, { 0, Rotate_front(), 0 });
	}
	
	//�V�[�P���X�ړ�����
	//�̗͂�0�ȉ��ɏꍇ���S�V�[�P���X�Ɉړ�
	if (hp_ <= 0) {
		tnl_sequence_.change(&EnemyChase::SEQ_Death);
	}
	//�^�[�Q�b�g�ɋ߂Â����Ƃ�
	else if (Distance_target() <= trans_attack_distance_) {
		tnl_sequence_.change(&EnemyChase::SEQ_Attack);
	}
	//�U�����󂯂���
	else if (is_HitRecieve_) {
		tnl_sequence_.change(&EnemyChase::SEQ_HitRecieve);
	}

	TNL_SEQ_CO_END
}

bool EnemyChase::SEQ_Attack(const float delta_time){
	if (tnl_sequence_.isStart()) {
		//�A�j���[�V�����ύX
		Anim_Change(Danse);
	}

	//�V�[�P���X�ړ�����
	//�̗͂�0�ȉ��̏ꍇ
	if (hp_ <= 0) {
		tnl_sequence_.change(&EnemyChase::SEQ_Death);
	}
	//�^�[�Q�b�g�Ɨ��ꂽ��
	else if (Distance_target() >= trans_attack_distance_) {
		tnl_sequence_.change(&EnemyChase::SEQ_Move);
	}
	//�v���C���[�̍U�����󂯂���
	else if (is_HitRecieve_) {
		tnl_sequence_.change(&EnemyChase::SEQ_HitRecieve);
	}

	TNL_SEQ_CO_END
}

bool EnemyChase::SEQ_HitRecieve(const float dleta_time){
	if (tnl_sequence_.isStart()) {
		//�A�j���[�V�����ύX
		Anim_Change(HitRecieve);
	}

	//�_���[�W�t���Ofalse
	is_HitRecieve_ = false;

	//�V�[�P���X�ړ�����
	//�A�j���[�V�������I���������O��SEQ�ɖ߂�
	if (is_anim_end_) {
		tnl_sequence_.undo();
	}
	//�̗͂�0�ȉ��̏ꍇ
	else if (hp_ <= 0) {
		tnl_sequence_.change(&EnemyChase::SEQ_Death);
	}

	TNL_SEQ_CO_END
}

bool EnemyChase::SEQ_Death(const float delta_time){
	if (tnl_sequence_.isStart()) {
		//���S��se�Đ�
		PlaySoundMem(death_se_hdl_, DX_PLAYTYPE_BACK);

		//�p�[�e�B�N������
		death_ptcl_->setPosition(Getter_pos());
		death_ptcl_->start();
	}

	//���S��se�̍Đ����I���Ύ�
	int cheack = CheckSoundMem(death_se_hdl_);
	if (cheack != 0) {
		//����
		Delete();
	}

	TNL_SEQ_CO_END
}
