#include "Camera.h"

Camera::Camera() 
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, dxe::Camera::eDimension::Type2D) {

}

void Camera::Update(tnl::Vector3 target_pos, float up_edge, float down_edge, float right_edge, float left_edge) {
    //カメラの位置を更新する
    pos_ = target_pos;
    
    //// 上端表示補正 マップの上端より上を表示しない
    //if (pos_.y < up_edge + (DXE_WINDOW_HEIGHT / 2)) {
    //    pos_.y = up_edge + (DXE_WINDOW_HEIGHT / 2);
    //}
    //// 下端表示補正 マップの下端より下を表示しない
    //if (pos_.y > down_edge - (DXE_WINDOW_HEIGHT / 2)) {
    //    pos_.y = down_edge - (DXE_WINDOW_HEIGHT / 2);
    //}
    // 右端表示補正 マップの右端より右を表示しない
    if (pos_.x > right_edge - (DXE_WINDOW_WIDTH / 2)) {
        pos_.x = right_edge - (DXE_WINDOW_WIDTH / 2);
    }
    // 左端表示補正 マップの左端より左を表示しない
    if (pos_.x < left_edge + (DXE_WINDOW_WIDTH / 2)) {
        pos_.x = left_edge + (DXE_WINDOW_WIDTH / 2);
    }
    
    // dxe::cameraのupdate
    update();
}
