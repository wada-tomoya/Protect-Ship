#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Camera : public dxe::Camera {
private:

public:
	Camera();
	//カメラのアップデートの処理
	//引数（追従するターゲット座標、画面の上端、画面の下端、画面の右端、画面の左端）
	void Update(tnl::Vector3 target_pos, float up_edge, float down_edge, float right_edge, float left_edge);
};