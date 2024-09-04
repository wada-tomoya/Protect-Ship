#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class ResourceManager {
private:
	//一枚画像関連LoadGraphで読み込むもの
	//画像のパスのcsv用
	std::vector <std::vector<tnl::CsvCell>> graphics_csv_;
	//画像を保存するmap
	std::unordered_map <std::string, int> graphics_map_;

public:
	//画像を読み込む関数
	//引数１：画像の名前
	int LoadGraph_(const std::string& graph_name);

//-----------------------------------------------------------------------------------------------
 
private:
	//アニメーション関連とマップチップLoadDivGraphで読み込むもの
	//アニメーションのパスのcsv
	std::vector <std::vector<tnl::CsvCell>> animation_csv_;
	//アニメーションを保存するmap
	std::unordered_map <std::string, std::shared_ptr<std::vector<int>>> animation_map_;
	//csvファイルのアイテム
	enum ANIMATION_CSV_ITEM {
		PATH = 1,
		TOTAL_DIV_NUM,
		X_DIV_NUM,
		Y_DIV_NUM,
		X_SIZE,
		Y_SIZE,
	};

public:
	//アニメーションとマップチップを読み込む関数
	//引数１：アニメーション画像の名前
	std::shared_ptr<std::vector<int>> LoadAnim_(const std::string& animation_name);

//------------------------------------------------------------------------------------------------

private:
	//テクスチャ関係
	//テクスチャのパスのcsv
	std::vector <std::vector<tnl::CsvCell>> texture_csv_;
	//テクスチャを保存するmap
	std::unordered_map <std::string, Shared<dxe::Texture>> texture_map_;
	
public:
	//テクスチャを読み込む関数
	//引数１：テクスチャの名前
	Shared<dxe::Texture > LoadTexture_(const std::string& texture_name);

//-----------------------------------------------------------------------------------------------

private:
	//音関係
	//音のパスのcsv
	std::vector <std::vector<tnl::CsvCell>> sound_csv_;
	//音を保存するmap
	std::unordered_map <std::string, int> sound_map_;

public:
	//音を読み込む関数
	//引数１：音の名前
	int LoadSound_(const std::string& sound_name);

//-----------------------------------------------------------------------------------------------

private:
	//mv1の3Dモデル関係
	//モデルのパスのcsv
	std::vector <std::vector<tnl::CsvCell>> mv1model_csv_;
	//モデルを保存するmap
	std::unordered_map <std::string, int> mv1model_map_;
	//csvファイルのアイテム
	enum MV1MODEL_CSV_ITEM {
		MODEL_NAME = 0,
		MODEL_FILE_PATH
	};

public:
	//モデルを読み込む関数
	//引数１：モデルの名前
	int LoadMV1Model_(const std::string& model_name);

//-----------------------------------------------------------------------------------------------

private:
	//パーティクル関係
	//パーティクルのパスのcsv
	std::vector<std::vector<tnl::CsvCell>> ptcl_csv_;
	//パーティクルを保存するmap
	std::unordered_map < std::string, Shared<dxe::Particle>> ptcl_map_;

public:
	//パーティクルを読み込む関数
	//引数１：パーティクルの名前
	Shared<dxe::Particle> LoadPtcl_(const std::string& ptcl_name);

//-----------------------------------------------------------------------------------------------

private:
	//コンストラクタ
	ResourceManager();
	//デストラクタ
	~ResourceManager();

public:
	//staticクラスにアクセスする関数
	static ResourceManager* GetInstance_ResourceManager();
	//staticクラスのdelete
	static void Destroy();
};
