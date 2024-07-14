#include "EnemyBig.h"

EnemyBig::EnemyBig(std::weak_ptr<ProtectObject> protectobject, int duplication_mesh, Shared<dxe::InstMesh> shadow_mesh, 
    float speed, float hp, float colli_rad, tnl::Vector3 colli_size){
    //�^�[�Q�b�g
    target_ = protectobject;
    auto target = target_.lock();
    if (!target) {
        return;
    }

    //�^�[�Q�b�g���W
    target_pos_ = target->GetterPos();
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
    //�U���̃C���^�[�o��
    attack_interval_ = 3.0f;
    attack_count_ = attack_interval_;
    //�U���Ɉڂ�^�[�Q�b�g�Ƃ̋���
    trans_attack_distance_ = 100.0f;
    //�̗�
    hp_ = hp;

    //�U���͐ݒ�
    attack_power_ = 8.0f;
    //�ړ������v�Z
    move_dir_ = tnl::Vector3::Normalize(target->GetterPos() - Getter_pos());

    //�U����se�ǂݍ���
    attack_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Enemy3_Voice");
    //���S����se�ǂݍ���
    death_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Enemy3_Death");
    
    //�Đ��A�j���[�V����
    anim_attachi_index_ = MV1AttachAnim(duplication_model_, animtype_, -1, false);
    //�Đ�����A�j���[�V�����̍Đ�����
    anim_totaltime_ = MV1GetAttachAnimTotalTime(duplication_model_, anim_attachi_index_);
}

EnemyBig::~EnemyBig(){

}

void EnemyBig::Update(float delta_time){
    auto target = target_.lock();
    if (!target) { return; }

    //�x�[�X�N���X�L�ڂ̎��s����
    __super::Update(delta_time);

    //�V�[�P���X���s
    tnl_sequence_.update(delta_time);

    //�^�[�Q�b�g���W�X�V
    target_pos_ = target->GetterPos();
    //�ړ������X�V
    Movedir_update(delta_time);

    //�����蔻��p�̍��W�X�V
    colli_center_ = { Getter_pos().x, Getter_pos().y + colli_rad_, Getter_pos().z };
    //�e�̍��W�X�V
    shadow_mesh_->setPosition({ Getter_pos().x, shadow_mesh_->getPosition().y, Getter_pos().z });

    //�A�j���[�V�����Đ�
    AnimPlay(delta_time);
}

void EnemyBig::Draw(std::shared_ptr<Camera> camera){
    //�x�[�X�N���X�L�ڂ̕`�揈��
    __super::Draw(camera);

    //�����蔻��̕\��
    //DrawAABB(camera, colli_center_, colli_size_);
    //DrawSphere3D(VGet(colli_center_.x,colli_center_.y,colli_center_.z ), colli_rad_, 8, GetColor(255, 0,0), GetColor(255, 255, 255), true);
}

bool EnemyBig::SEQ_Move(const float delta_time){
    if (tnl_sequence_.isStart()) {
        //�A�j���[�V������Walk�ɕύX
        Anim_Change(Walk);
    }

    //�ړ�
    MV1SetPosition(duplication_model_,
        { Getter_pos().x + (move_dir_.x * speed_), Getter_pos().y, Getter_pos().z + (move_dir_.z * speed_) });

    //�i�s����������
    MV1SetRotationXYZ(duplication_model_, { 0, Rotate_front(), 0 });

    //�V�[�P���X�ړ�����
    //�̗͂�0�ȉ��̏ꍇ
    if (hp_ <= 0) {
        tnl_sequence_.change(&EnemyBig::SEQ_Death);
    }
    //�^�[�Q�b�g�ɋ߂Â����ꍇ
    else if (Distance_target() <= trans_attack_distance_) {
        tnl_sequence_.change(&EnemyBig::SEQ_Attack);
    }
    //�v���C���[�̍U�����󂯂���
    else if (is_HitRecieve_) {
        tnl_sequence_.change(&EnemyBig::SEQ_HitRecieve);
    }

    TNL_SEQ_CO_END
}

bool EnemyBig::SEQ_Attack(const float delta_time){
    auto target = target_.lock();
    if (!target) {return false;}

    if (tnl_sequence_.isStart()) {
        //�A�j���[�V������Attack_1�ɕύX
        Anim_Change(Attack_1);
    }

    attack_count_ += delta_time;
    //�U����^����
    if (attack_count_ >= attack_interval_) {
        attack_count_ = 0.0f;

        //se�Đ�
        PlaySoundMem(attack_se_hdl_, DX_PLAYTYPE_BACK);

        //�^�[�Q�b�g��hp�����炷
        target->Setter_Hp(-attack_power_);
    }

    //�V�[�P���X�ړ�����
    //�̗͂�0�ȉ��̏ꍇ
    if (hp_ <= 0) {
        tnl_sequence_.change(&EnemyBig::SEQ_Death);
    }
    //�^�[�Q�b�g�Ɨ��ꂽ��
    else if (Distance_target() >= trans_attack_distance_) {
        tnl_sequence_.change(&EnemyBig::SEQ_Move);
    }
    //�v���C���[�̍U�����󂯂���
    else if (is_HitRecieve_) {
        tnl_sequence_.change(&EnemyBig::SEQ_HitRecieve);
    }

    TNL_SEQ_CO_END
}

bool EnemyBig::SEQ_HitRecieve(const float delta_time){
    if (tnl_sequence_.isStart()) {
        //�A�j���[�V�����ύX
        Anim_Change(HitRecieve);
    }

    is_HitRecieve_ = false;

    //�V�[�P���X�ړ�����
    //�A�j���[�V�������I���������O��SEQ�ɖ߂�
    if (is_anim_end_) {
        tnl_sequence_.undo();
    }
    //�̗͂�0�ȉ��̏ꍇ
    else if (hp_ <= 0) {
        tnl_sequence_.change(&EnemyBig::SEQ_Death);
    }

    TNL_SEQ_CO_END
}

bool EnemyBig::SEQ_Death(const float delta_time){
    if (tnl_sequence_.isStart()) {
        //���Sse�Đ�
        PlaySoundMem(death_se_hdl_, DX_PLAYTYPE_BACK);

        //�p�[�e�B�N������
        death_ptcl_->setPosition(Getter_pos());
        death_ptcl_->start();
    }

    //���S����se���Đ����I���Ύ�
    int check = CheckSoundMem(death_se_hdl_);
    if (check != 0) {
        //�����i���S�j
        Delete();
    }

    TNL_SEQ_CO_END
}