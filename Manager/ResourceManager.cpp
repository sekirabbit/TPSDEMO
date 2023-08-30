#include"Headers.h"

KdModel* ResourceManager::GetModel(std::string _fileName)
{
	KdModel* tmpModel;

	//_flleNameという検索キーで最後まで見つからなかった場合
	if (m_modelList.find(_fileName) == m_modelList.end())
	{
		//_flleNameという検索キーで最後まで見つからなかった場合
		//これまで一度もその画像が読み込まれていない場合の処理
		tmpModel = new KdModel;
		tmpModel->Load(_fileName);
		//			　↓検索キー
		m_modelList[_fileName] = tmpModel;
		//m_textureListの_filenameという項目（検索キー）
		//その画像を保存しているアドレスを関連付けて記録する
	}
	else
	{
		tmpModel = m_modelList[_fileName];
	}

	return tmpModel;
}

KdTexture* ResourceManager::GetTexture(std::string _fileName)
{
	KdTexture* tmpTex;

	if (m_textureList.find(_fileName) == m_textureList.end())
	{
		tmpTex = new KdTexture;
		tmpTex->Load(_fileName);
		m_textureList[_fileName] = tmpTex;
	}
	else
	{
		tmpTex = m_textureList[_fileName];
	}

	return tmpTex;
}

std::shared_ptr<KdSoundEffect> ResourceManager::GetSound(std::string _fileName)
{
	std::shared_ptr<KdSoundEffect> tmpSound;

	//_flleNameという検索キーで最後まで見つからなかった場合
	if (m_soundList.find(_fileName) == m_soundList.end())
	{
		//_flleNameという検索キーで最後まで見つからなかった場合
		//これまで一度もその画像が読み込まれていない場合の処理
		tmpSound = std::make_shared<KdSoundEffect>();
		tmpSound->Load(_fileName);
		//			　↓検索キー
		m_soundList[_fileName] = tmpSound;
		//m_textureListの_filenameという項目（検索キー）
		//その画像を保存しているアドレスを関連付けて記録する
	}
	else
	{
		tmpSound = m_soundList[_fileName];
	}

	return tmpSound;
}

void ResourceManager::AllRelease()
{

	for (auto itr = m_textureList.begin(); itr != m_textureList.end(); itr++)
	{
		//itr->first　：検索キー（今回はファイル名）
		//itr->second　：値（画像が保存されているアドレス）
	
		(itr->second)->Release();
		delete (itr->second);
		
	}
	for (auto itr = m_modelList.begin(); itr != m_modelList.end(); itr++)
	{
		(itr->second)->Release();
		delete (itr->second);
	}
	//for (auto itr = m_soundList.begin(); itr != m_soundList.end(); itr++)
	//{
	//	(itr->second)->~KdSoundEffect();
	//	delete (itr->second);
	//}

	m_textureList.clear();
	m_modelList.clear();
	m_soundList.clear();

}

ResourceManager::~ResourceManager()
{
	AllRelease();
}

ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager resource;

	return resource;
}
