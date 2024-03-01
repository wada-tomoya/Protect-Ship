 #include "Play_Map.h"

Play_Map::Play_Map() {	
	//背景画像読み込み
	ground_texture_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PlayScene_BackGround");
	//メッシュ生成
	ground_mesh_ = dxe::Mesh::CreatePlaneMV({ ground_size_.x, ground_size_.y, 0 },1,1);
	ground_mesh_->setTexture(ground_texture_);
	ground_mesh_->setBlendMode(DX_BLENDMODE_ALPHA);
	ground_mesh_->setSampleFilterMode(DX_DRAWMODE_NEAREST);
	ground_mesh_->setCullingMode(DX_CULLING_RIGHT);
	//地面のメッシュを90度倒す
	ground_mesh_->rot_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));

	//プレイヤーの移動限界の円
	player_map = dxe::Mesh::CreateDiskRingMV(player_move_rad_,1.0f,100,100,360.0f);
	player_map_tex = dxe::Texture::CreateFromFile("graphics/red1.bmp");
	player_map->setTexture(player_map_tex);
	player_map->pos_ = { player_move_center.x, player_move_center.y + 10.0f, player_move_center.z };
	player_map->rot_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));

	//複製元の木のmv1モデル読み込み
	tree_mhdl_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("TREE_");

	//木を複製
	for (float r = -(ground_size_.y / 2); r < (ground_size_.y / 2); r += tree_spwan_distance_) {
		for (float c = -(ground_size_.x / 2); c < (ground_size_.x / 2); c += tree_spwan_distance_) {
			//プレイエリア中心から生成位置までのベクトル
			float center_tree_vec = ((r - player_move_center.z) * (r - player_move_center.z)) + ((c - player_move_center.x) * (c - player_move_center.x));
			//プレイエリア内には木を設置しない
			if (center_tree_vec <= player_move_vec_) {
				continue ;
			}
			else {
				//木を複製
				int tree = MV1DuplicateModel(tree_mhdl_);
				//木の座標を設定
				MV1SetPosition(tree, { c,tree_pos_y_,r });
				//木のサイズを設定
				MV1SetScale(tree, tree_size_);
				//配列に複製した木を挿入
				tree_duplicate_hdl_.emplace_back(tree);
			}		
		}
	}
}

Play_Map::~Play_Map() {
	
}

void Play_Map::Map_Draw(std::shared_ptr<Camera> camera) {
	ground_mesh_->render(camera);

	//複製した木を表示
	for (int i = 0; i < tree_duplicate_hdl_.size(); i++) {
		MV1DrawModel(tree_duplicate_hdl_[i]);
	}
	/*MV1DrawModel(tree_duplicate_hdl_[1620]);
	DrawStringEx(10, 50, -1, "tree-pos x%f y%f %fz", MV1GetPosition(tree_duplicate_hdl_[1620]).x, MV1GetPosition(tree_duplicate_hdl_[1620]).y, MV1GetPosition(tree_duplicate_hdl_[1620]).z);
	DrawStringEx(10,30,-1,"tree_duplicate_hdl_.size %d", tree_duplicate_hdl_.size());*/

	player_map->render(camera);

	DrawStringEx(10,70,-1,"tree_pos x%f y%f z%f",MV1GetPosition(tree_mhdl_).x, MV1GetPosition(tree_mhdl_).y, MV1GetPosition(tree_mhdl_).z);
	DrawStringEx(10,90,-1,"material %d", MV1GetMaterialNum(tree_mhdl_));
}
