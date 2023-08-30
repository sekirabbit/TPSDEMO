#pragma once

class ResourceManager
{
public:
	//�w�肳�ꂽ�t�@�C�����̃��f���̃Q�b�^�[
	KdModel* GetModel(std::string _fileName);
	//�w�肵���t�@�C�����̉摜�f�[�^�̃Q�b�^�[
	KdTexture* GetTexture(std::string _fileName);
	//�w�肵���t�@�C�����̉����f�[�^�̃Q�b�^�[
	std::shared_ptr<KdSoundEffect> GetSound(std::string _fileName);

	void AllRelease();

	~ResourceManager();

	static ResourceManager& GetInstance();


private:
	
	ResourceManager() {};

	std::map<std::string, KdModel*>m_modelList;
	std::map<std::string, KdTexture*>m_textureList;
	//	�@�����L�[�̌^�C�l�̌^
	std::map<std::string, std::shared_ptr<KdSoundEffect>>m_soundList;

};

#define RESOURCE ResourceManager::GetInstance()