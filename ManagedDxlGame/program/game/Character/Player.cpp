#include "Player.h"

Player::Player(tnl::Vector3 map_center, float map_rad){
	//移動速度
	speed_ = 8;
	//画像サイズ
	size_ = { 32,32,0 };
	//初期座標
	pos_ = { -48,(size_.y / 2),0 };
	//移動できるマップの半径
	map_rad_ = map_rad;
	//マップの中央からの外周までの値の平方根
	map_rad_root_ = map_rad_ * map_rad_;
	//移動できるマップの中心
	map_center_ = map_center;
	//プレイヤーのテクスチャをロード
	texture_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PLAYER");

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

//------------------------------------------------------------------------------

	//カーソルのmesh生成
	cursor_mesh_ = dxe::Mesh::CreateConeMV(5,20,10,10,360.0f);
	//カーソルのテクスチャ読み込み
	cursor_texture_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("ATTACK_CURSOR");
	//テクスチャセット
	cursor_mesh_->setTexture(cursor_texture_);
	//座標設定
	cursor_mesh_->pos_ = pos_;
}

void Player::Update(float delta_time) {
	//移動
	Move(delta_time, map_center_);
	
	//プレイヤーメッシュの座標を合わせる
	for (int i = 0; i < player_mesh_index_; ++i) {
		mesh_front_[i]->pos_ = pos_;
		mesh_left_[i]->pos_ = pos_;
		mesh_right_[i]->pos_ = pos_;
		mesh_back_[i]->pos_ = pos_;
	}
	//影の座標を合わせる
	shadow_mesh_->pos_ = { pos_.x, shadow_pos_y_, pos_.z };

	//カーソルの移動、回転
	cursor_mesh_->pos_ = pos_ + tnl::Vector3::TransformCoord({ 0,distance_cursor_player_,0 }, cursor_mesh_->rot_);
	cursor_mesh_->rot_ = cursor_down_ * tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(Angle_Center_Mouse()));
}

void Player::Draw(float delta_time, std::shared_ptr<Camera> camera) {
	//影描画
	shadow_mesh_->render(camera);
	
	//カーソル描画
	cursor_mesh_->render(camera);

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

	DrawStringEx(10, 10, -1, "pos_ x%f y%f z%f", pos_.x, pos_.y, pos_.z);
}

void Player::Move(float delta_time, tnl::Vector3 map_center) {
	//移動前座標を設定
	prev_pos_ = pos_;

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
	////中心からの現座標までの長さ ベクトル
	//float center_pos_vec = ((pos_.x - map_center_.x) * (pos_.x - map_center_.x)) + ((pos_.z - map_center_.z) * (pos_.z - map_center_.z));
	////移動エリアより外には行かない
	//if (center_pos_vec >= map_rad_root_) {
	//	pos_ = prev_pos_;
	//}

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
	//角度
	float rad_;
	float angle_;
	//マウスの座標
	tnl::Vector3 mouse_pos = tnl::Input::GetMousePosition();
	//画面の中心
	tnl::Vector3 center_screen = tnl::Vector3{ DXE_WINDOW_WIDTH / 2,DXE_WINDOW_HEIGHT / 2,0.0f };
	//ラジアンで角度計算
	rad_ = atan2(-(mouse_pos.y - center_screen.y), -(mouse_pos.x - center_screen.x));
	//度数法に直す
	angle_ = rad_ * (180.0f / DX_PI);

	return angle_;
}

void Player::Normal_Attack() {
	//マウス座標を取得、攻撃を生成	
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		mouse_pos_ = tnl::Input::GetMousePosition();
		//マウスの座標補正
		tnl::Vector3 a = { mouse_pos_.x - (DXE_WINDOW_WIDTH/2), mouse_pos_.y - (DXE_WINDOW_HEIGHT/2),0.0f };
		//攻撃生成
		AttackManager::Instance_AttackManager()->NormalAttack_Create(pos_, a);
	}
}

tnl::Vector3 Player::GetterPos(){
	return pos_;
}