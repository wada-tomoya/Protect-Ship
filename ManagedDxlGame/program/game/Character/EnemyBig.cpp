#include "EnemyBig.h"

EnemyBig::EnemyBig(std::weak_ptr<ProtectObject> protectobject, int duplication_mesh, Shared<dxe::InstMesh> shadow_mesh, 
    float speed, float hp, float colli_rad, tnl::Vector3 colli_size){
    //ターゲット
    target_ = protectobject;
    auto target = target_.lock();
    if (!target) {
        return;
    }

    //ターゲット座標
    target_pos_ = target->GetterPos();
    //モデル
    duplication_model_ = duplication_mesh;
    //影のメッシュ
    shadow_mesh_ = shadow_mesh;
    //移動速度設定
    speed_ = speed;
    //弾との当たり判定用半径
    colli_rad_ = colli_rad;
    //プレイヤーとの当たり判定用ボックスサイズ
    colli_size_ = colli_size;
    //攻撃のインターバル
    attack_interval_ = 3.0f;
    attack_count_ = attack_interval_;
    //攻撃に移るターゲットとの距離
    trans_attack_distance_ = 100.0f;
    //体力
    hp_ = hp;

    //攻撃力設定
    attack_power_ = 8.0f;
    //移動方向計算
    move_dir_ = tnl::Vector3::Normalize(target->GetterPos() - Getter_pos());

    //攻撃のse読み込み
    attack_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Enemy3_Voice");
    //死亡時のse読み込み
    death_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Enemy3_Death");
    
    //再生アニメーション
    anim_attachi_index_ = MV1AttachAnim(duplication_model_, animtype_, -1, false);
    //再生するアニメーションの再生時間
    anim_totaltime_ = MV1GetAttachAnimTotalTime(duplication_model_, anim_attachi_index_);
}

EnemyBig::~EnemyBig(){

}

void EnemyBig::Update(float delta_time){
    auto target = target_.lock();
    if (!target) { return; }

    //ベースクラス記載の実行処理
    __super::Update(delta_time);

    //シーケンス実行
    tnl_sequence_.update(delta_time);

    //ターゲット座標更新
    target_pos_ = target->GetterPos();
    //移動方向更新
    Movedir_update(delta_time);

    //当たり判定用の座標更新
    colli_center_ = { Getter_pos().x, Getter_pos().y + colli_rad_, Getter_pos().z };
    //影の座標更新
    shadow_mesh_->setPosition({ Getter_pos().x, shadow_mesh_->getPosition().y, Getter_pos().z });

    //アニメーション再生
    AnimPlay(delta_time);
}

void EnemyBig::Draw(std::shared_ptr<Camera> camera){
    //ベースクラス記載の描画処理
    __super::Draw(camera);

    //当たり判定の表示
    //DrawAABB(camera, colli_center_, colli_size_);
    //DrawSphere3D(VGet(colli_center_.x,colli_center_.y,colli_center_.z ), colli_rad_, 8, GetColor(255, 0,0), GetColor(255, 255, 255), true);
}

bool EnemyBig::SEQ_Move(const float delta_time){
    if (tnl_sequence_.isStart()) {
        //アニメーションをWalkに変更
        Anim_Change(Walk);
    }

    //移動
    MV1SetPosition(duplication_model_,
        { Getter_pos().x + (move_dir_.x * speed_), Getter_pos().y, Getter_pos().z + (move_dir_.z * speed_) });

    //進行方向を向く
    MV1SetRotationXYZ(duplication_model_, { 0, Rotate_front(), 0 });

    //シーケンス移動条件
    //体力が0以下の場合
    if (hp_ <= 0) {
        tnl_sequence_.change(&EnemyBig::SEQ_Death);
    }
    //ターゲットに近づいた場合
    else if (Distance_target() <= trans_attack_distance_) {
        tnl_sequence_.change(&EnemyBig::SEQ_Attack);
    }
    //プレイヤーの攻撃を受けた時
    else if (is_HitRecieve_) {
        tnl_sequence_.change(&EnemyBig::SEQ_HitRecieve);
    }

    TNL_SEQ_CO_END
}

bool EnemyBig::SEQ_Attack(const float delta_time){
    auto target = target_.lock();
    if (!target) {return false;}

    if (tnl_sequence_.isStart()) {
        //アニメーションをAttack_1に変更
        Anim_Change(Attack_1);
    }

    attack_count_ += delta_time;
    //攻撃を与える
    if (attack_count_ >= attack_interval_) {
        attack_count_ = 0.0f;

        //se再生
        PlaySoundMem(attack_se_hdl_, DX_PLAYTYPE_BACK);

        //ターゲットのhpを減らす
        target->Setter_Hp(-attack_power_);
    }

    //シーケンス移動条件
    //体力が0以下の場合
    if (hp_ <= 0) {
        tnl_sequence_.change(&EnemyBig::SEQ_Death);
    }
    //ターゲットと離れた時
    else if (Distance_target() >= trans_attack_distance_) {
        tnl_sequence_.change(&EnemyBig::SEQ_Move);
    }
    //プレイヤーの攻撃を受けた時
    else if (is_HitRecieve_) {
        tnl_sequence_.change(&EnemyBig::SEQ_HitRecieve);
    }

    TNL_SEQ_CO_END
}

bool EnemyBig::SEQ_HitRecieve(const float delta_time){
    if (tnl_sequence_.isStart()) {
        //アニメーション変更
        Anim_Change(HitRecieve);
    }

    is_HitRecieve_ = false;

    //シーケンス移動条件
    //アニメーションが終了したら一つ前のSEQに戻る
    if (is_anim_end_) {
        tnl_sequence_.undo();
    }
    //体力が0以下の場合
    else if (hp_ <= 0) {
        tnl_sequence_.change(&EnemyBig::SEQ_Death);
    }

    TNL_SEQ_CO_END
}

bool EnemyBig::SEQ_Death(const float delta_time){
    if (tnl_sequence_.isStart()) {
        //死亡se再生
        PlaySoundMem(death_se_hdl_, DX_PLAYTYPE_BACK);

        //パーティクル生成
        death_ptcl_->setPosition(Getter_pos());
        death_ptcl_->start();
    }

    //死亡時のseが再生が終われば死
    int check = CheckSoundMem(death_se_hdl_);
    if (check != 0) {
        //消去（死亡）
        Delete();
    }

    TNL_SEQ_CO_END
}