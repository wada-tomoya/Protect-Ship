#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "SceneBace.h"
#include "../Manager/GameManager.h"

class UIManager;

class TitleScene : public SceneBace {
private:
	//uiインスタンス
	std::shared_ptr<UIManager> ui_ = nullptr;

	//画像ハンドル
	int background_hdl = 0;
	//クリックしてからシーン遷移にかかる時間
	float scenechange_time_ = 1.0f;

	int click_se_ = 0;

	//タイトル
	const std::string title_name_ = "Protect-Ship";
	const int fontsize_title_ = 100;
	tnl::Vector2i title_pos_{ 0,80 };

	//中央揃え用
	int str_len_ = 0, str_wid_ = 0;

public:
	TitleScene() = default;

	//引数１：シーンクラス名
	TitleScene(const FINALCLASS_NAME& classname);
	~TitleScene();

	//実行関数
	//引数１：時間
	void Update(const float& delta_time) override;
	//表示関数
	//引数１：時間
	void Draw(const float& delta_time) override;

	//中央揃え関数
	//引数１：表示する文字、２：文字のｘ座標
	void Centered(const std::string& str, int& x_pos);
};