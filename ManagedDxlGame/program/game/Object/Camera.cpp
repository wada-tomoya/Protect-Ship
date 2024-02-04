#include "Camera.h"

Camera::Camera() 
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, dxe::Camera::eDimension::Type2D) {

}


void Camera::Update(tnl::Vector3 target_pos, float up_edge, float down_edge, float right_edge, float left_edge) {
	//target_を追いかける
	//pos_ += (target_pos - pos_) * 0.1f;
	pos_ = target_pos;

	////上端表示補正 画面の上端より上を表示しない
	//if (pos_.y < up_edge + (DXE_WINDOW_HEIGHT / 2 )) {
	//	pos_.y = up_edge + (DXE_WINDOW_HEIGHT / 2);
	//}
	////下端表示補正 画面の下端より下を表示しない
	//if (pos_.y > down_edge - (DXE_WINDOW_HEIGHT / 2)) {
	//	pos_.y = down_edge - (DXE_WINDOW_HEIGHT / 2);
	//}
	////右端表示補正 画面の右端より右を表示しない
	//if (pos_.x > right_edge - (DXE_WINDOW_WIDTH / 2)) {
	//	pos_.x = right_edge - (DXE_WINDOW_WIDTH / 2);
	//}
	////左端表示補正 画面の左端より左を表示しない
	//if (pos_.x < left_edge + (DXE_WINDOW_WIDTH / 2)) {
	//	pos_.x = left_edge + (DXE_WINDOW_WIDTH / 2);
	//}

	//dxe::cameraのupdate
	update();

	DrawStringEx(10, 50, -1, "camera_pos.x %f.2 y %f.2", pos_.x, pos_.y);
}