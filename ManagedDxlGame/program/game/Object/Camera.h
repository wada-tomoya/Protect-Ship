#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Camera : public dxe::Camera {
private:
	
public:
	Camera();
	//カメラのアップデートの処理
	//引数（追従するターゲット座標、描画の上端、描画の下端、描画の右端、描画の左端）
	void Update(tnl::Vector3 target_pos, float up_edge, float down_edge, float right_edge, float left_edge);
};