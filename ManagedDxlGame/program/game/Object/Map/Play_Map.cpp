 #include "Play_Map.h"

Play_Map::Play_Map() {	
	//地面のテクスチャ読み込み
	ground_texture_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PlayScene_BackGround");
	//地面のメッシュ生成
	ground_mesh_ = dxe::Mesh::CreateCubeMV(1);
	ground_mesh_->scl_ = ground_scale_;
	ground_mesh_->pos_.y -= (ground_scale_.y / 2);
	//地面の色彩設定など
	ground_mesh_->setTexture(ground_texture_);
	ground_mesh_->setSampleFilterMode(DX_DRAWMODE_NEAREST);
	ground_mesh_->setCullingMode(DX_CULLING_RIGHT);
	
	//プレイヤーの移動限界の円関係
	player_map = dxe::Mesh::CreateDiskRingMV(player_move_rad_,1.0f,10,10,360.0f);
	player_map->setTexture(dxe::Texture::CreateFromFile("graphics/red1.bmp"));
	player_map->pos_ = { player_move_center.x, (player_move_center.y + circle_pos_y_), player_move_center.z };
	player_map->rot_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));

	//複製元の木のmv1モデル読み込み
	tree_mhdl_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("TREE_");

	//木を複製
	for (float r = -(ground_scale_.z / 2); r < (ground_scale_.z / 2); r += tree_spawn_distance_) {
		for (float c = -(ground_scale_.x / 2); c < (ground_scale_.x / 2); c += tree_spawn_distance_) {

			//少し座標をずらす
			float move_x = static_cast<float>(GetRand(shift_x_ * 2)) - shift_x_;
			float move_z = static_cast<float>(GetRand(shift_z_ * 2)) - shift_z_;
			//生成座標を設定
			DxLib::VECTOR spawn_pos = { c + move_x, tree_pos_y_, r + move_z };
			//プレイエリア中心から木の生成位置までのベクトル
			float center_tree_vec = static_cast<float>(std::pow((spawn_pos.z - player_move_center.z), 2))
									+ static_cast<float>(std::pow((spawn_pos.x - player_move_center.x), 2));
			//プレイエリア内には木を設置しない
			if (center_tree_vec <= player_move_vec_) {
				continue;
			}
			else {
				//木を複製
				int tree = MV1DuplicateModel(tree_mhdl_);
				//木の座標を設定
				MV1SetPosition(tree, spawn_pos);
				//木のサイズを設定
				MV1SetScale(tree, tree_size_);
				//配列に複製した木を挿入
				tree_duplicate_hdl_.emplace_back(tree);
			}
		}
	}
}

Play_Map::~Play_Map() {
	MV1DeleteModel(tree_mhdl_);
	for (int i = 0; i < tree_duplicate_hdl_.size(); i++) {
		MV1DeleteModel(tree_duplicate_hdl_[i]);
	}
}

void Play_Map::Map_Draw(std::shared_ptr<Camera> camera) {
	//地面描画
	ground_mesh_->render(camera);
	//複製した木を描画
	for (int i = 0; i < tree_duplicate_hdl_.size(); i++) {
		MV1DrawModel(tree_duplicate_hdl_[i]);
	}
	//マップ範囲の円描画
	player_map->render(camera);
}
