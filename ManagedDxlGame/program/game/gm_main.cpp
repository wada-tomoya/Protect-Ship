#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "Manager/ResourceManager.h"
#include "Manager/GameManager.h"
#include "Scene/TitleScene.h"

#if 1

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
    //マウスカーソル消去
    SetMouseDispFlag(false);

    //staticマネージャークラスインスタンス
	GameManager::GetInstance_GameManager(new TitleScene(FINALCLASS_NAME::title));
	ResourceManager::GetInstance_ResourceManager();

	//フォントの変更
	ChangeFont("コーポレート・ロゴ（ラウンド）ver3 Bold", DX_CHARSET_DEFAULT);
    //文字に枠線を付ける
    ChangeFontType(DX_FONTTYPE_EDGE);
}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {
    //シーン実行
	GameManager::GetInstance_GameManager()->Update(delta_time);

}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
    //staticマネージャークラス消去
	GameManager::GetInstance_GameManager()->Destroy();
	ResourceManager::GetInstance_ResourceManager()->Destroy();
}


#else
//パーティクル設定
//-------------------------------------------------------------------------------------------------------
//
// 座標と姿勢で制御するカメラ
//
class TransformCamera : public dxe::Camera {
public:

    TransformCamera() {};
    TransformCamera(int screen_w, int screen_h) : dxe::Camera(screen_w, screen_h) {}

    void update();


    inline tnl::Vector3 up() {
        up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
        return up_;
    }
    inline tnl::Vector3 down() { return -up(); }

    inline tnl::Vector3 forward() override {
        target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
        return tnl::Vector3::Normalize(target_ - pos_);
    }
    inline tnl::Vector3 back() override { return -forward(); }
    inline tnl::Vector3 left() override { return tnl::Vector3::Cross(forward(), up()); }
    inline tnl::Vector3 right() override { return tnl::Vector3::Cross(up(), forward()); }

    tnl::Quaternion rot_;

};

void TransformCamera::update() {

    //
    // 姿勢パラメータからターゲット座標とアッパーベクトルを計算
    //

    target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
    up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
    dxe::Camera::update();
}



Shared<TransformCamera> camera = nullptr;
std::shared_ptr<dxe::Particle> ptcl = nullptr;
bool is_draw_controller = true;

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {

    srand(time(0));
    SetBackgroundColor(32, 32, 32);

    camera = std::make_shared<TransformCamera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
    camera->pos_ = { 0, 100, -250 };

    ptcl = std::make_shared<dxe::Particle>("particle/protectobj_smoke.bin");

}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

    //----------------------------------------------------------------------------------------------------
    //
    // カメラ制御
    //
    tnl::Input::RunIndexKeyDown(
        [&](uint32_t index) {
            tnl::Vector3 v[4] = {
                camera->left(),
                camera->right(),
                tnl::Vector3::up,
                tnl::Vector3::down
            };
            camera->pos_ += v[index] * 3.0f;

        }, eKeys::KB_A, eKeys::KB_D, eKeys::KB_W, eKeys::KB_S);

    if (tnl::Input::IsMouseDown(tnl::Input::eMouse::RIGHT)) {
        tnl::Vector3 mvel = tnl::Input::GetMouseVelocity();
        camera->rot_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(mvel.x * 0.2f));
        camera->rot_ *= tnl::Quaternion::RotationAxis(camera->right(), tnl::ToRadian(mvel.y * 0.2f));
    }
    camera->pos_ += camera->forward().xz() * tnl::Input::GetMouseWheel() * 0.3f;


    // GUI 描画 ON / OFF
    if (tnl::Input::IsKeyDownTrigger(eKeys::KB_F3)) is_draw_controller = !is_draw_controller;

    // カメラアップデート
    camera->update();




    //----------------------------------------------------------------------------------------------------
    //
    // 描画処理
    //

    DrawGridGround(camera, 50, 20);


    //---------------------------------------------------------------------------
    //
    // パーティクルの描画開始
    //
    dxe::DirectXRenderBegin();

    // パーティクル A を描画
    ptcl->render(camera);

    // パーティクル B を描画
    // パーティクル C を...

    //---------------------------------------------------------------------------
    //
    // パーティクルの描画終了
    //
    dxe::DirectXRenderEnd();




    if (is_draw_controller) ptcl->drawGuiController({ 0, 0 });

    DrawFpsIndicator({ DXE_WINDOW_WIDTH - 260, 0, 0 }, delta_time);

    DrawString(DXE_WINDOW_WIDTH - 260, 20, "右クリック : 向き", -1);
    DrawString(DXE_WINDOW_WIDTH - 260, 40, "ホイール : 前後", -1);
    DrawString(DXE_WINDOW_WIDTH - 260, 60, "A D : 左右移動", -1);
    DrawString(DXE_WINDOW_WIDTH - 260, 80, "W S : 上下移動", -1);
    DrawString(DXE_WINDOW_WIDTH - 260, 100, "F3 : GUI 描画 ON/OFF", -1);

}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
    ptcl.reset();
}


#endif 