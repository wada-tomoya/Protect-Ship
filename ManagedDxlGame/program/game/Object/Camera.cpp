#include "Camera.h"

Camera::Camera() : dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT) {

}

void Camera::Update(tnl::Vector3 target_pos) {
    //ターゲットを追尾
    target_ = target_pos;
    //座標更新
    pos_ = target_pos + camera_pos;

    // dxe::cameraのupdate
    update();
}
