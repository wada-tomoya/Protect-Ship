#pragma once
#include "../../library/tnl_sequence.h"
#include "../Scene/SceneBace.h"

class GameManager {
private:
	//実行中のシーン
	SceneBace* nowscene_ = nullptr;
	//次のシーン
	SceneBace* nextscene_ = nullptr;
	//フェード用の画像
	int trans_garph_hdl_ = 0;
	//フェードの時間
	float trans_time_ = 0.5f;
	//シーケンス
	tnl::Sequence<GameManager> sequence_ = tnl::Sequence<GameManager>(this, &GameManager::seqTransIn);
	//フェードイン
	bool seqTransIn(const float delta_time);
	//フェードアウト
	bool seqTransOut(const float delta_time);
	//何もしない
	bool seqRunScene(const float delta_time);

	GameManager(SceneBace* startscene);

	//α値のマックス
	const float alpha_max_ = 255.0f;

public:
	static GameManager* GetInstance_GameManager(SceneBace* startscene = nullptr);
	//各シーンのUpdateとDraw実行
	void Update(float delta_time);
	static void Destroy();
	//シーン切り替え
	void ChangeScene(SceneBace* nextscene, float delta_time = 0.5f);
};
