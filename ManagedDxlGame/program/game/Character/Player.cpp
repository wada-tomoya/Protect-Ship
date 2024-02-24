#include "Player.h"

Player::Player(tnl::Vector3 upleft, tnl::Vector3 downright) {
	//移動速度
	speed_ = 8;
	//画像サイズ
	size_ = { 32,32,0 };
	//初期座標
	pos_ = { -48,0,0 };
	//プレイヤーが動ける画面の端
	up_edge_ = upleft.y + size_.y;
	down_edge_ = downright.y - size_.y;
	right_edge_ = downright.x - size_.x;
	left_edge_ = upleft.x + size_.x;

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
			mesh_right_[i]->dxe::Mesh::setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_right_[i]->dxe::Mesh::setSampleFilterMode(DX_DRAWMODE_NEAREST);

			//左向き
			mesh_left_[i] = dxe::Mesh::CreatePlaneMV(size_, 1, 1, false, { ltop_x,0,0 }, { rbottom_x,1,0 });
			mesh_left_[i]->setTexture(texture_hdl_left_);
			mesh_left_[i]->dxe::Mesh::setBlendMode(DX_BLENDMODE_ALPHA);
			mesh_left_[i]->dxe::Mesh::setSampleFilterMode(DX_DRAWMODE_NEAREST);
		}
	}

	//カーソルのmesh生成
	cursor_mesh_ = dxe::Mesh::CreateSphereMV(10,10,10);
	cursor_texture_ = dxe::Texture::CreateFromFile("graphics/red1.bmp");
	cursor_mesh_->setTexture(cursor_texture_);
}

void Player::Update(float delta_time) {
	Move(delta_time, up_edge_, down_edge_, right_edge_, left_edge_);
	
	//メッシュの座標を合わせる
	for (int i = 0; i < mesh_index_; ++i) {
		mesh_right_[i]->pos_ = pos_;
		mesh_left_[i]->pos_ = pos_;
	}

	//マウスの座標
	tnl::Vector3 aaa = tnl::Input::GetMousePosition();
	DrawStringEx(10, 10, -1, "マウス x%f y%f z%f", aaa.x, aaa.y, aaa.z);

	//カーソルの座標移動
	cursor_mesh_->pos_ = { pos_.x + Cursor_Move_Dir_().x, pos_.y, pos_.z + -Cursor_Move_Dir_().y };

	////各攻撃実行
	//AttackManager::Instance_AttackManager()->Update(delta_time);
	//
	////Normal_Attack生成
	//Normal_Attack();
}

void Player::Draw(float delta_time, std::shared_ptr<Camera> camera) {
	//右向き
	if (chara_dir_ == DIRECTION::RIGHT) {
		mesh_right_[render_]->render(camera);
	}
	//左向き
	else if (chara_dir_ == DIRECTION::LEFT) {
		mesh_left_[render_]->render(camera);
	}

	//カーソル
	cursor_mesh_->render(camera);
};

void Player::Move(float delta_time, float up_edge, float down_edge, float right_edge, float left_edge) {	
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
	////上端以上に行かない
	//if (pos_.y < up_edge) pos_.y = up_edge;
	////下端以上に行かない
	//if (pos_.y > down_edge) pos_.y = down_edge;
	////右端以上に行かない
	//if (pos_.x > right_edge) pos_.x = right_edge;
	////左端以上に行かない
	//if (pos_.x < left_edge) pos_.x = left_edge;

	//移動アニメーション再生
	Texture_Anim_Play(mesh_index_, delta_time);
	is_move_ = false;
}

tnl::Vector3 Player::Cursor_Move_Dir_() {
	//移動量
	tnl::Vector3 move_dir;
	//マウスの座標
	tnl::Vector3 mouse_pos = tnl::Input::GetMousePosition();
	//画面の中心
	tnl::Vector3 center_screen = tnl::Vector3{ DXE_WINDOW_WIDTH / 2,DXE_WINDOW_HEIGHT / 2,0.0f };
	//マウスへの移動量計算（正規化）
	move_dir = tnl::Vector3::Normalize(mouse_pos - center_screen) * distance_cursor_player_;

	return move_dir;
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

tnl::Vector3 Player::GetterPos() {
	return pos_;
}