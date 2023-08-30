#pragma once

struct Vertex
{
	Math::Vector3 pos;	//���W
	Math::Vector2 uv;	//�e�N�X�`�����W
	Math::Vector4 color;//�F
};
struct ModelVertex
{
	Math::Vector3 pos;
	Math::Vector2 uv;
	Math::Vector3 normal;
	UINT color;
};

static const int ScrW = 1280;
static const int ScrH = 720;
static const float ChangeSceneWaitTime = 60.0f;
