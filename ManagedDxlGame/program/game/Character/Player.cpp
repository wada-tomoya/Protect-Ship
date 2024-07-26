#include "Player.h"
#include "../Object/Camera.h"
#include "../Manager/ResourceManager.h"

Player::Player(const tnl::Vector3& map_center, const float& map_rad, std::weak_ptr<dxe::Mesh> ground, std::weak_ptr<Camera> camera){
	//移動速度
	speed_ = 4;
	ori_speed_ = speed_;
	//画像サイズ
	size_ = { 32,32,0 };
	//初期座標
	pos_ = { -48,(size_.y / 2),0 };
	//移動できるマップの半径
	map_rad_ = map_rad;
	//マップの中央からの外周までの値の2乗
	map_rad_root_ = map_rad_ * map_rad_;
	//移動できるマップの中心
	map_center_ = map_center;
	//敵との当てり判定用サイズの設定
	colli_size_ = { size_.x,size_.y,colli_thickness_ };
	//プレイヤーのテクスチャをロード
	texture_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PLAYER");

	//攻撃se読み込み
	attack_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("PlayerAttack_SE");
	//爆弾攻撃se読み込み
	bomattack_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("BombAttack");
	//敵と当たった時のse読み込み
	enemy_hit_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Enemy_Hit");
	//敵と当たった時のパーティクル
	enemy_hit_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("Player_Enemy_Hit");

	//テクスチャの分割位置
	float div = 1.0f / texture_div_;
	//テクスチャの縦分割位置
	float high_div = 1.0f / texture_height_div_;
	//前向きのｙ分割位置の下端
	float flont_div_down = high_div * (float)DIRECTION::FRONT;
	//左向きのｙ分割位置の下端
	float left_div_down = high_div * (float)DIRECTION::LEFT;
	//右向きのｙ分割位置の下端
	float right_div_down = high_div * (float)DIRECTION::RIGHT;
	//後ろ向きのｙ分割位置の下端
	float back_div_down = high_div * (float)DIRECTION::BACK;

	//メッシュ生成
	for (int i = 0; i < player_mesh_index_; ++i) {
		//テクスチャの切り取る位置計算
		const float ltop_x = div * i;
		const float rbottom_x = div * (i + 1);
		
		if (i < player_mesh_index_) {
			//前向き
			mesh_front_[i] = dxe::Mesh::CreatePlaneMV(size_, 10, 10, false, { ltop_x, 0, 0 }, { rbottom_x, flont_div_down, 0 });
			mesh_front_[i]->setTexture(texture_hdl_);
			mesh_front_[i]->setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_front_[i]->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			mesh_front_[i]->setCullingMode(DX_CULLING_RIGHT);
			//左向き
			mesh_left_[i] = dxe::Mesh::CreatePlaneMV(size_, 10, 10, false, { ltop_x, left_div_down, 0 }, { rbottom_x, right_div_down, 0 });
			mesh_left_[i]->setTexture(texture_hdl_);
			mesh_left_[i]->setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_left_[i]->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			mesh_left_[i]->setCullingMode(DX_CULLING_RIGHT);
			//右向き
			mesh_right_[i] = dxe::Mesh::CreatePlaneMV(size_, 10, 10, false, { ltop_x, flont_div_down, 0 }, { rbottom_x, left_div_down, 0 });
			mesh_right_[i]->setTexture(texture_hdl_);
			mesh_right_[i]->setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_right_[i]->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			mesh_right_[i]->setCullingMode(DX_CULLING_RIGHT);
			//後ろ向き
			mesh_back_[i] = dxe::Mesh::CreatePlaneMV(size_, 10, 10, false, { ltop_x, right_div_down, 0 }, { rbottom_x, back_div_down, 0 });
			mesh_back_[i]->setTexture(texture_hdl_);
			mesh_back_[i]->setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_back_[i]->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			mesh_back_[i]->setCullingMode(DX_CULLING_RIGHT);
		}
	}

//攻撃関係-----------------------------------------------------------------------------------------------------------------------------------------
	attack_map_center_ = map_center_;
	attack_map_rad_ = map_rad_;

	//攻撃のテクスチャをロード
	atk_textures_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("NORMALATTACK_1"));
	atk_textures_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("BombAttack"));

	//NormalAttack関連
	//NormalAttack複製元メッシュ
	noratk_.origine_mesh_ = dxe::Mesh::CreateCubeMV(noratk_.size_, (int)10, (int)10);
	//メッシュ複製
	noratk_.mesh_pool_ = dxe::InstMeshPool::Create(noratk_.origine_mesh_, noratk_.instmax_, &atk_textures_);
	//メッシュの色設定
	noratk_.mesh_pool_->dxe::InstMeshPool::setMtrlEmissive({ 1,1,1 });
	//ヒット時パーティクル
	noratk_.hit_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("Attack_Hit_Ptcl");
	//移動中のパーティクル
	noratk_.move_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("player_Attack_Move");

	ori_noratk_size_ = noratk_.size_;

	//BombAttack関係
	bomatk_.size_ = 10.0f;
	bomatk_.instmax_ = 20;
	//BombAttack複製元メッシュ
	bomatk_.origine_mesh_ = dxe::Mesh::CreateSphereMV(bomatk_.size_);
	//メッシュ複製
	bomatk_.mesh_pool_ = dxe::InstMeshPool::Create(bomatk_.origine_mesh_, bomatk_.instmax_, &atk_textures_);
	//メッシュ色設定
	bomatk_.mesh_pool_->dxe::InstMeshPool::setMtrlEmissive({ 1,1,1 });
	//ヒット時のパーティクル
	bomatk_.hit_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("Player_BombAttack");
	//移動中のパーティクル
	bomatk_.move_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("Player_BombAttackMove");
	//ヒット時のse読み込み
	bomatk_.hit_se_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Explosion");
//-----------------------------------------------------------------------------------------------------------------------------------------

	//影生成
	shadow_mesh_ = dxe::Mesh::CreatePlaneMV({ size_.x,size_.x,0 }, 10,10);
	//影のテクスチャをロード
	shadow_texture_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("SHADOW");
	//テクスチャセット
	shadow_mesh_->setTexture(shadow_texture_);
	shadow_mesh_->setBlendMode(DX_BLENDMODE_ALPHA);
	shadow_mesh_->setSampleFilterMode(DX_DRAWMODE_NEAREST);
	shadow_mesh_->setCullingMode(DX_CULLING_RIGHT);
	//座標設定
	shadow_mesh_->pos_ = { pos_.x, shadow_pos_y_, pos_.z };
	//90度回転
	shadow_mesh_->rot_ = shadow_down_;

	//カーソルのmesh生成
	cursor_mesh_ = dxe::Mesh::CreateConeMV(10,30,10,10,360.0f);
	//カーソルのテクスチャ読み込み
	cursor_texture_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("ATTACK_CURSOR");
	//テクスチャセット
	cursor_mesh_->setTexture(cursor_texture_);
	//座標設定
	cursor_mesh_->pos_ = pos_;

	//AttackCursor_ptcl_読み込み
	//attackcursor_ptcl_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("AttackCursor");

	//地面
	ground_ = ground;
	//カメラ
	camera_ = camera;
}

Player::~Player(){
	DeleteSoundMem(attack_se_hdl_);
	DeleteSoundMem(bomattack_se_hdl_);
	DeleteSoundMem(enemy_hit_se_hdl_);
	//attackcursor_ptcl_.reset();
	statusup_itemlist_.clear();

	noratk_.mesh_pool_.reset();
	noratk_.hit_ptcl_.reset();
	noratk_.move_ptcl_.reset();

	bomatk_.mesh_pool_.reset();
	bomatk_.hit_ptcl_.reset();
	bomatk_.move_ptcl_.reset();
	DeleteSoundMem(bomatk_.hit_se_hdl_);
}

void Player::Update(const float& delta_time) {
	//無敵状態のカウントダウン
	if (invincible_ > 0.0f) {
		invincible_ -= delta_time;

		//invincible_が0より多ければ当たり判定無効
		is_colli_ = false;
		//プレイヤー点滅
		Flashing(delta_time, flash_interval_);
	}
	else {
		//invincible_が0以下なら当たり判定有効
		is_colli_ = true;
		//プレイヤー明るく表示
		//PlayerLighting(true);

		is_flash_ = true;

	}
	
	//移動
	Move(delta_time);
	
	//プレイヤーメッシュの座標を合わせる
	for (int i = 0; i < player_mesh_index_; ++i) {
		mesh_front_[i]->pos_ = pos_;
		mesh_left_[i]->pos_ = pos_;
		mesh_right_[i]->pos_ = pos_;
		mesh_back_[i]->pos_ = pos_;
	}
	//影の座標を合わせる
	shadow_mesh_->pos_ = { pos_.x, shadow_pos_y_, pos_.z };

	try {
		//カーソルの移動、回転
		cursor_mesh_->pos_ = pos_ + tnl::Vector3::TransformCoord({ 0,distance_cursor_player_,0 }, cursor_mesh_->rot_);
		cursor_mesh_->rot_ = cursor_down_ * tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(Angle_Center_Mouse()));
	}
	catch (int error) {
		assert(error );
	}
	
	//攻撃不能が終わるまでのカウント
	//can_attack_が0より多ければ攻撃できない
	if (can_attack_ > 0.0f) {
		can_attack_ -= delta_time;
	}
	else {
		can_attack_ = 0.0f;

		//攻撃生成
		Attack_Create(delta_time);
	}

	//各攻撃の実行関数
	Attack_Update(delta_time, attacks_);
}

void Player::Draw(const float& delta_time, const std::shared_ptr<Camera>& camera) {
	//影描画
	shadow_mesh_->render(camera);
	//カーソル描画
	cursor_mesh_->render(camera);
	
	if (is_flash_) {
		//プレイヤーの向き
		switch (chara_dir_) {
			//前向き
		case DIRECTION::FRONT:
			mesh_front_[render_]->render(camera);
			break;
			//左向き
		case DIRECTION::LEFT:
			mesh_left_[render_]->render(camera);
			break;
			//右向き
		case DIRECTION::RIGHT:
			mesh_right_[render_]->render(camera);
			break;
			//後ろ向き
		case DIRECTION::BACK:
			mesh_back_[render_]->render(camera);
			break;
		}
	}

	dxe::DirectXRenderBegin();

	//パーティクル描画
	//敵と接触した時
	enemy_hit_ptcl_->render(camera);
	//マウスカーソル座標のパーティクル
	//attackcursor_ptcl_->render(camera);

	dxe::DirectXRenderEnd();
}

void Player::AttackDraw(const std::shared_ptr<Camera>& camera) {
	//各攻撃の描画
	Attack_Draw(camera, attacks_, noratk_);
}

void Player::Flashing(const float& delta_tim, const float& flash_interval){
	flash_count_ += delta_tim;
	if (flash_count_ <= flash_interval) {
		//プレイヤーを暗くする
		//PlayerLighting(false);

		is_flash_ = false;
	}
	else if (flash_count_ <= (flash_interval * 2)) {
		//プレイヤー明るく表示
		//PlayerLighting(true);
		is_flash_ = true;
	}
	else {
		flash_count_ = 0.0f;
	}
}

void Player::PlayerLighting(const bool& lighting){
	for (auto& player : mesh_front_) {
		player->setDefaultLightEnable(lighting);
	}
	for (auto& player : mesh_back_) {
		player->setDefaultLightEnable(lighting);
	}
	for (auto& player : mesh_left_) {
		player->setDefaultLightEnable(lighting);
	}
	for (auto& player : mesh_right_) {
		player->setDefaultLightEnable(lighting);
	}
	//明るさの状態
	//is_flash_ = lighting;
}

void Player::Move(const float& delta_time) {
	//移動前座標を設定
	prev_pos_ = pos_;

	//プレイヤーの移動
	//移動　上
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		is_move_ = true;
		//移動
		pos_.z += speed_;
		//向きを変換　前
		chara_dir_ = DIRECTION::FRONT;
	}
	//移動　左
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		is_move_ = true;
		//移動
		pos_.x -= speed_;
		//向き変換　左
		chara_dir_ = DIRECTION::LEFT;
	}
	//移動　右
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		is_move_ = true;
		//移動
		pos_.x += speed_;
		//向き変換　右
		chara_dir_ = DIRECTION::RIGHT;
	}
	//移動　下
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		is_move_ = true;
		//移動
		pos_.z -= speed_;
		//向きを変換　後ろ
		chara_dir_ = DIRECTION::BACK;
	}
	//中心からの現座標までの長さ ベクトル
	float center_pos_vec = ((float)std::pow((pos_.x - map_center_.x),2) + (float)std::pow((pos_.z - map_center_.z),2));
	//移動エリアより外には行かない
	if (center_pos_vec >= map_rad_root_) {
		pos_ = prev_pos_;
	}

	//移動アニメーション再生
	Texture_Anim_Play(player_mesh_index_, delta_time);
	is_move_ = false;
}

tnl::Vector3 Player::Cursor_Move_Norm_() {
	//正規化した値
	tnl::Vector3 norm_;
	//マウスの座標
	tnl::Vector3 mouse_pos = tnl::Input::GetMousePosition();
	//画面の中心
	tnl::Vector3 center_screen = tnl::Vector3{ DXE_WINDOW_WIDTH / 2,DXE_WINDOW_HEIGHT / 2,0.0f };
	//計算（正規化）
	norm_ = tnl::Vector3::Normalize(mouse_pos - center_screen);

	return norm_;
}

float Player::Angle_Center_Mouse() {
	auto ground = ground_.lock();
	if (ground == nullptr) { throw - 1; }
	auto camera = camera_.lock();
	if (camera == nullptr) { throw - 1; }

	//角度
	float rad_;
	float angle_;

	//マウス座標
	tnl::Vector3 mouse_pos = tnl::Input::GetMousePosition();
	//マウスカーソルのレイ
	tnl::Vector3 ray_nml = tnl::Vector3::CreateScreenRay(static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y),
														DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, camera->view_, camera->proj_);
	//マウスのレイと地面の当たった座標を取得
	tnl::IsIntersectRayAABB(camera->pos_, ray_nml, tnl::ToMaxAABB(ground->pos_, ground->scl_), tnl::ToMinAABB(ground->pos_, ground->scl_), &ground_hit_pos_);
	//ラジアンで角度計算
	rad_ = atan2((ground_hit_pos_.x - pos_.x), (ground_hit_pos_.z - pos_.z));

	//度数法に直す
	angle_ = rad_ * (180.0f / (float)DX_PI);

	return angle_;
}

void Player::Attack_Create(const float& delta_time) {
	//通常攻撃　左クリック
	if (tnl::Input::IsMouseDown(eMouse::LEFT)) {
		if (is_normalattack_) {
			is_normalattack_ = false;
			//se再生
			PlaySoundMem(attack_se_hdl_, DX_PLAYTYPE_BACK);

			//攻撃生成
			NormalAttack_Create(cursor_mesh_->pos_, cursor_mesh_->rot_, itemupstatus_.speed_attack_,itemupstatus_.power_,itemupstatus_.Penetration_,
				attacks_, noratk_, attack_map_center_, attack_map_rad_, static_cast<int>(TEXTURENUM::normalattack), itemupstatus_.size_scale_);
			//attack_addnum_の数値に応じて追加で出る攻撃生成
			for (int i = 0; i < attack_addnum_; i++) {
				NormalAttack_Create(cursor_mesh_->pos_, cursor_mesh_->rot_ * tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(addattack_rad_[i])),
					itemupstatus_.speed_attack_, itemupstatus_.power_, itemupstatus_.Penetration_,
					attacks_, noratk_, attack_map_center_, attack_map_rad_, static_cast<int>(TEXTURENUM::normalattack), itemupstatus_.size_scale_);

				NormalAttack_Create(cursor_mesh_->pos_, cursor_mesh_->rot_ * tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(-(addattack_rad_[i]))),
					itemupstatus_.speed_attack_, itemupstatus_.power_, itemupstatus_.Penetration_,
					attacks_, noratk_, attack_map_center_, attack_map_rad_, static_cast<int>(TEXTURENUM::normalattack), itemupstatus_.size_scale_);
			}
		}	
	}
	if (!is_normalattack_) {
		//攻撃インターバルカウント
		attack_count_ += delta_time;
		if (attack_count_ >= attack_interval_) {
			//攻撃可能にする
			is_normalattack_ = true;
			//攻撃カウントリセット
			attack_count_ = 0.0f;
		}
	}
	
	//爆破攻撃　右クリック
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT)) {
		if (bombstock_ > 0) {
			//爆破攻撃生成
			BombAttack_Create(cursor_mesh_->pos_, cursor_mesh_->rot_, ground_hit_pos_,
				attacks_, bomatk_, attack_map_center_, attack_map_rad_, static_cast<int>(TEXTURENUM::bombattack));
			//se再生
			PlaySoundMem(bomattack_se_hdl_, DX_PLAYTYPE_BACK);

			//爆弾ストックデクリメント
			bombstock_--;
		}
	}
}

void Player::Enemy_Hit(){
	//無敵時間時間設定
	invincible_ = invincible_time_;
	//攻撃不能時間設定
	can_attack_ = cooldown_time_;
	//パティクル生成
	enemy_hit_ptcl_->setPosition(pos_);
	enemy_hit_ptcl_->start();

	PlaySoundMem(enemy_hit_se_hdl_, DX_PLAYTYPE_BACK);
}

void Player::AttackStatus_Set(){
	//list内のそれぞれのアイテムの数
	int redcount = 0,bluecount = 0, greencount = 0;
	//それぞれのアイテムの数カウント
	for (int i = 0; i < statusup_itemlist_.size(); i++) {
		if (statusup_itemlist_[i] == ITEMTYPE::Red) {
			redcount++;
		}
		else if (statusup_itemlist_[i] == ITEMTYPE::Blue) {
			bluecount++;
		}
		else if (statusup_itemlist_[i] == ITEMTYPE::Green) {
			greencount++;
		}
	}

	//攻撃ステータス設定
	//攻撃力設定
	itemupstatus_.power_ = (itemupstatus_.power_up_ * redcount) - (itemupstatus_.power_down_ * greencount);
	//攻撃スピード設定
	itemupstatus_.speed_attack_ = (itemupstatus_.speed_attack_up_ * redcount);
	//攻撃インターバル設定
	itemupstatus_.interval_ = ori_attack_interval_ - (itemupstatus_.interval_down_ * redcount);
	attack_interval_ = itemupstatus_.interval_;
	//貫通力設定
	itemupstatus_.Penetration_ = ori_attack_penetration_ + (itemupstatus_.penetration_up_ * redcount);

	//攻撃サイズ設定
	itemupstatus_.size_scale_ = 1.0f + (itemupstatus_.size_scale_up_ * redcount);
	noratk_.size_ = ori_noratk_size_ * itemupstatus_.size_scale_;

	//プレイヤー移動速度
	itemupstatus_.speed_player_ = ori_speed_ + (itemupstatus_.speed_player_up_ * bluecount);
	speed_ = itemupstatus_.speed_player_;

	//追加攻撃の個数設定
	attack_addnum_ = greencount;
}

void Player::Setter_Item(const ITEMTYPE& itemtype){
	//要素を追加
	statusup_itemlist_.emplace_back(itemtype);

	//listの要素がitemmax以上ならば先頭の要素を消去
	if (statusup_itemlist_.size() > itemmax_) {
		statusup_itemlist_.erase(statusup_itemlist_.begin());
	}
}

void Player::Item_Hit(const ITEMTYPE& itemtype) {
	if (itemtype == ITEMTYPE::Bomb) {
		//爆弾追加
		bombstock_++;
	}
	else if (itemtype == ITEMTYPE::Red || itemtype == ITEMTYPE::Blue || itemtype == ITEMTYPE::Green) {
		//listにセット
		Setter_Item(itemtype);
	}
	else {
		return;
	}

	//所持アイテムでの攻撃ステータスup
	AttackStatus_Set();
}
