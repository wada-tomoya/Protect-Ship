#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class ResourceManager {
private:
	//�ꖇ�摜�֘ALoadGraph�œǂݍ��ނ���
	//�摜�̃p�X��csv�p
	std::vector <std::vector<tnl::CsvCell>> graphics_csv_;
	//�摜��ۑ�����map
	std::unordered_map <std::string, int> graphics_map_;

public:
	//�摜��ǂݍ��ފ֐�
	//�����P�F�摜�̖��O
	int LoadGraph_(const std::string& graph_name);

//-----------------------------------------------------------------------------------------------
 
private:
	//�A�j���[�V�����֘A�ƃ}�b�v�`�b�vLoadDivGraph�œǂݍ��ނ���
	//�A�j���[�V�����̃p�X��csv
	std::vector <std::vector<tnl::CsvCell>> animation_csv_;
	//�A�j���[�V������ۑ�����map
	std::unordered_map <std::string, std::shared_ptr<std::vector<int>>> animation_map_;
	//csv�t�@�C���̃A�C�e��
	enum ANIMATION_CSV_ITEM {
		PATH = 1,
		TOTAL_DIV_NUM,
		X_DIV_NUM,
		Y_DIV_NUM,
		X_SIZE,
		Y_SIZE,
	};

public:
	//�A�j���[�V�����ƃ}�b�v�`�b�v��ǂݍ��ފ֐�
	//�����P�F�A�j���[�V�����摜�̖��O
	std::shared_ptr<std::vector<int>> LoadAnim_(const std::string& animation_name);

//------------------------------------------------------------------------------------------------

private:
	//�e�N�X�`���֌W
	//�e�N�X�`���̃p�X��csv
	std::vector <std::vector<tnl::CsvCell>> texture_csv_;
	//�e�N�X�`����ۑ�����map
	std::unordered_map <std::string, Shared<dxe::Texture>> texture_map_;
	
public:
	//�e�N�X�`����ǂݍ��ފ֐�
	//�����P�F�e�N�X�`���̖��O
	Shared<dxe::Texture > LoadTexture_(const std::string& texture_name);

//-----------------------------------------------------------------------------------------------

private:
	//���֌W
	//���̃p�X��csv
	std::vector <std::vector<tnl::CsvCell>> sound_csv_;
	//����ۑ�����map
	std::unordered_map <std::string, int> sound_map_;

public:
	//����ǂݍ��ފ֐�
	//�����P�F���̖��O
	int LoadSound_(const std::string& sound_name);

//-----------------------------------------------------------------------------------------------

private:
	//mv1��3D���f���֌W
	//���f���̃p�X��csv
	std::vector <std::vector<tnl::CsvCell>> mv1model_csv_;
	//���f����ۑ�����map
	std::unordered_map <std::string, int> mv1model_map_;
	//csv�t�@�C���̃A�C�e��
	enum MV1MODEL_CSV_ITEM {
		MODEL_NAME = 0,
		MODEL_FILE_PATH
	};

public:
	//���f����ǂݍ��ފ֐�
	//�����P�F���f���̖��O
	int LoadMV1Model_(const std::string& model_name);

//-----------------------------------------------------------------------------------------------

private:
	//�p�[�e�B�N���֌W
	//�p�[�e�B�N���̃p�X��csv
	std::vector<std::vector<tnl::CsvCell>> ptcl_csv_;
	//�p�[�e�B�N����ۑ�����map
	std::unordered_map < std::string, Shared<dxe::Particle>> ptcl_map_;

public:
	//�p�[�e�B�N����ǂݍ��ފ֐�
	//�����P�F�p�[�e�B�N���̖��O
	Shared<dxe::Particle> LoadPtcl_(const std::string& ptcl_name);

//-----------------------------------------------------------------------------------------------

private:
	//�R���X�g���N�^
	ResourceManager();
	//�f�X�g���N�^
	~ResourceManager();

public:
	//static�N���X�ɃA�N�Z�X����֐�
	static ResourceManager* GetInstance_ResourceManager();
	//static�N���X��delete
	static void Destroy();
};
