#include"Headers.h"

KdModel* ResourceManager::GetModel(std::string _fileName)
{
	KdModel* tmpModel;

	//_flleName�Ƃ��������L�[�ōŌ�܂Ō�����Ȃ������ꍇ
	if (m_modelList.find(_fileName) == m_modelList.end())
	{
		//_flleName�Ƃ��������L�[�ōŌ�܂Ō�����Ȃ������ꍇ
		//����܂ň�x�����̉摜���ǂݍ��܂�Ă��Ȃ��ꍇ�̏���
		tmpModel = new KdModel;
		tmpModel->Load(_fileName);
		//			�@�������L�[
		m_modelList[_fileName] = tmpModel;
		//m_textureList��_filename�Ƃ������ځi�����L�[�j
		//���̉摜��ۑ����Ă���A�h���X���֘A�t���ċL�^����
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

	//_flleName�Ƃ��������L�[�ōŌ�܂Ō�����Ȃ������ꍇ
	if (m_soundList.find(_fileName) == m_soundList.end())
	{
		//_flleName�Ƃ��������L�[�ōŌ�܂Ō�����Ȃ������ꍇ
		//����܂ň�x�����̉摜���ǂݍ��܂�Ă��Ȃ��ꍇ�̏���
		tmpSound = std::make_shared<KdSoundEffect>();
		tmpSound->Load(_fileName);
		//			�@�������L�[
		m_soundList[_fileName] = tmpSound;
		//m_textureList��_filename�Ƃ������ځi�����L�[�j
		//���̉摜��ۑ����Ă���A�h���X���֘A�t���ċL�^����
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
		//itr->first�@�F�����L�[�i����̓t�@�C�����j
		//itr->second�@�F�l�i�摜���ۑ�����Ă���A�h���X�j
	
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
