#include"Headers.h"


void SceneManager::DoScene()
{

	//���݂̃V�[���Ƃ͈قȂ�V�[�����o�^����Ă�����
	if (m_nextScene != m_currentScene)	//!= nullptr
	{
		if (m_currentScene != nullptr)
		{
			delete m_currentScene;	//clean
		}

		m_currentScene = m_nextScene;	//�o�^
	}

	if (m_currentScene != nullptr)
	{
		//���݂̃V�[�������s����
		m_currentScene->Frame(); //BaseScene����p������Frame

		if (m_currentScene->GetImGuiFlg() == true)
		{
			//imgui�����Œǉ�==================
			// ImGui�J�n
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			// ImGui����
			m_currentScene->ImGuiUpdate();

			APP.m_console.Draw("Log", nullptr);

			// GUI�`����s
			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
			//=========================================
		}
	}


}

void SceneManager::ChangeScene(BaseScene* _nextScene)
{
	//�ڍs���������̃V�[����o�^
	m_nextScene = _nextScene;
}

SceneManager::~SceneManager()
{
	//��������̃V�[�������s����������
	if (m_currentScene != nullptr)
	{
		//���ݎ��s���Ă����V�[�����폜����
		delete m_currentScene;
	}
}

