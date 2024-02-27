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
	//移動できるマップの中心
	map_center_ = map_center;
	//右向きと左向きのテクスチャをロード
	texture_hdl_right_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PLAYER_RIGHT");
	texture_hdl_left_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PLAYER_LEFT");

	//テクスチャの分割位置
	float dir = 1.0f / texture_dir;

	//メッシュ生成
	for (int i = 0; i < mesh_index_; ++i) {
		//テクスチャの切り取る位置計算
		const float ltop_x = dir * i;
		const float rbottom_x = dir * (i + 1);
		
		if (i < mesh_index_) {
			//右向き
			mesh_right_[i] = dxe::Mesh::CreatePlaneMV(size_, 1, 1, false, { ltop_x,0,0 }, { rbottom_x,1,0 });
			mesh_right_[i]->setTexture(texture_hdl_right_);
			mesh_right_[i]->setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_right_[i]->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			mesh_right_[i]->setCullingMode(DX_CULLING_RIGHT);

			//左向き
			mesh_left_[i] = dxe::Mesh::CreatePlaneMV(size_, 1, 1, false, { ltop_x,0,0 }, { rbottom_x,1,0 });
			mesh_left_[i]->setTexture(texture_hdl_left_);
			mesh_left_[i]->setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_left_[i]->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			mesh_left_[i]->setCullingMode(DX_CULLING_RIGHT);
		}
	}

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
	Move(delta_time, map_center_, map_rad_);
	
	//メッシュの座標を合わせる
	for (int i = 0; i < mesh_index_; ++i) {
		mesh_right_[i]->pos_ = pos_;
		mesh_left_[i]->pos_ = pos_;
	}

	//マウスの座標
	tnl::Vector3 aaa = tnl::Input::GetMousePosition();
	DrawStringEx(10, 10, -1, "マウス x%f y%f z%f", aaa.x, aaa.y, aaa.z);

	//カーソルの移動、回転
	cursor_mesh_->pos_ = pos_ + tnl::Vector3::TransformCoord({ 0,distance_cursor_player_,0 }, cursor_mesh_->rot_);
	cursor_mesh_->rot_ = cursor_down_ * tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(Angle_Center_Mouse()));

	////各攻撃実行
	//AttackManager::Instance_AttackManager()->Update(delta_time);
	//
	////Normal_Attack生成
	//Normal_Attack();

	DrawStringEx(10, 30, -1, "angle %f", Angle_Center_Mouse());
}

void Player::Draw(float delta_time, std::shared_ptr<Camera> camera) {
	//カーソル
	cursor_mesh_->render(camera);

	//右向き
	if (chara_dir_ == DIRECTION::RIGHT) {
		mesh_right_[render_]->render(camera);
	}
	//左向き
	else if (chara_dir_ == DIRECTION::LEFT) {
		mesh_left_[render_]->render(camera);
	}

	DrawStringEx(10,50,-1,"x%f y%f z%f",pos_.x, pos_.y, pos_.z);
}

void Player::Move(float delta_time, tnl::Vector3 map_center, float map_rad) {
	//移動　上
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		is_move_ = true;
		//移動
		pos_.z += speed_;
	}
	//移動　下
	if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		is_move_ = true;
		//移動
		pos_.z -= speed_;	
	}
	//移動　右
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		is_move_ = true;
		//移動
		pos_.x += speed_; 
		//向き変換　右
		chara_dir_ = DIRECTION::RIGHT;
	}
	//移動　左
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		is_move_ = true;
		//移動
		pos_.x -= speed_;
		//向き変換　左
		chara_dir_ = DIRECTION::LEFT;
	}
	//移動エリア内より外には行かない

	//移動アニメーション再生
	Texture_Anim_Play(mesh_index_, delta_time);
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