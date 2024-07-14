#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Manager/GameManager.h"
#include "TitleScene.h"
#include "SceneBace.h"

class Camera;
class Play_Map;
class Player;
class Spawner;
class ProtectObject;
class Collision;
class UIManager;

class PlayScene : public SceneBace {
private:
	//シーケンス
	tnl::Sequence<PlayScene> play_sequence_ = tnl::Sequence<PlayScene>(this, &PlayScene::Seq_Explanation);
	//ゲーム説明シーケンス
	bool Seq_Explanation(float delat_time);
	//実行シーケンス
	bool Seq_Update(float delta_time);
	//ゲームオーバーシーケンス
	bool Seq_Gameover(float delta_time);
	//ゲームクリアシーケンス
	bool Seq_GameClear(float delta_time);
	//メニュー画面シーケンス
	bool Seq_Menu(float delta_time);

	enum class NOWSEQUENCE {
		play,
		gameover,
		gameclear,
		explanation,
		menu,
	};
	NOWSEQUENCE nowsequence_ = NOWSEQUENCE::explanation;

	//オブジェクトのプレハブ
	std::shared_ptr<Camera> camera_ = nullptr;
	std::shared_ptr<Play_Map> map_ = nullptr;
	std::shared_ptr<Player> player_ = nullptr;
	std::shared_ptr<Spawner> spawner_ = nullptr;
	std::shared_ptr<ProtectObject> protectobject_ = nullptr;
	std::shared_ptr<Collision> collision_ = nullptr;
	std::shared_ptr<UIManager> ui_ = nullptr;

	//ゲームの制限時間
	float gametime_ = 121.0f;

	//ゲームクリア時のbgm
	int gameclear_bgm_ = 0;
	//ゲームオーバー時のbgm
	int gameover_bgm_ = 0;

public:
	PlayScene(ENDCLASS_NAME class_name);
	~PlayScene();
	//実行関数
	void Update(float delta_time) override;
	//表示関数
	void Draw(float delta_time) override;
};