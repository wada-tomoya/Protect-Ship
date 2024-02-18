#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "SceneBace.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/GameManager.h"
#include "PlayScene.h"

class TitleScene : public SceneBace {
private:
	//画像ハンドル
	int background_hdl = 0;
	//シーン遷移シーケンス
	tnl::Sequence<TitleScene> sequence_ = tnl::Sequence<TitleScene>(this, &TitleScene::SeqIdle);
	bool SeqIdle(float delta_time);

public:
	TitleScene();

	//実行関数
	void Update(float delta_time) override;
	//表示関数
	void Draw(float delta_time) override;
};
