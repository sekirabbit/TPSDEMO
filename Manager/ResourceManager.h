#pragma once

class ResourceManager
{
public:
	//指定されたファイル名のモデルのゲッター
	KdModel* GetModel(std::string _fileName);
	//指定したファイル名の画像データのゲッター
	KdTexture* GetTexture(std::string _fileName);
	//指定したファイル名の音声データのゲッター
	std::shared_ptr<KdSoundEffect> GetSound(std::string _fileName);

	void AllRelease();

	~ResourceManager();

	static ResourceManager& GetInstance();


private:
	
	ResourceManager() {};

	std::map<std::string, KdModel*>m_modelList;
	std::map<std::string, KdTexture*>m_textureList;
	//	　検索キーの型，値の型
	std::map<std::string, std::shared_ptr<KdSoundEffect>>m_soundList;

};

#define RESOURCE ResourceManager::GetInstance()