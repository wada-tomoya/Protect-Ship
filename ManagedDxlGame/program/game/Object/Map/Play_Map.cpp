 #include "Play_Map.h"

Play_Map::Play_Map() {	
	//”wŒi‰æ‘œ“Ç‚Ýž‚Ý
	ground_texture_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PlayScene_BackGround");
	//ƒƒbƒVƒ…¶¬
	ground_mesh_ = dxe::Mesh::CreatePlaneMV({ ground_size_.x, ground_size_.y, 0 },1,1);
	ground_mesh_->setTexture(ground_texture_);
	ground_mesh_->setBlendMode(DX_BLENDMODE_ALPHA);
	ground_mesh_->setSampleFilterMode(DX_DRAWMODE_NEAREST);
	ground_mesh_->setCullingMode(DX_CULLING_RIGHT);
	//’n–Ê‚ÌƒƒbƒVƒ…‚ð90“x“|‚·
	ground_mesh_->rot_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));
}

Play_Map::~Play_Map() {
	
}

void Play_Map::Map_Draw(std::shared_ptr<Camera> camera) {
	ground_mesh_->render(camera);
}
