#include "Camera.h"

Camera::Camera() : dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT) {

}

void Camera::Update(tnl::Vector3 target_pos) {
    //�^�[�Q�b�g��ǔ�
    target_ = target_pos;
    //���W�X�V
    pos_ = target_pos + camera_pos;

    // dxe::camera��update
    update();
}
