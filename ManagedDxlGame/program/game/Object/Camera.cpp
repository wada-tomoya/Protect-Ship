#include "Camera.h"

Camera::Camera() 
	: dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, dxe::Camera::eDimension::Type2D) {

}

void Camera::Update(tnl::Vector3 target_pos) {
    //カメラの位置を更新する
    pos_ = target_pos;

    // dxe::cameraのupdate
    update();
}
