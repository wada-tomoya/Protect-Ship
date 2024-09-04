#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class Camera : public dxe::Camera {
private:
	//ターゲットとカメラの距離
	tnl::Vector3 camera_pos{ 0,300,-500 };
	
public:
	Camera();
	//カメラのアップデートの処理
	//引数１：追従するターゲット座標
	void Update(const tnl::Vector3& target_pos = {0,0,0});
};