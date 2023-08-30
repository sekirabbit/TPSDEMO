#pragma once

struct Vertex
{
	Math::Vector3 pos;	//座標
	Math::Vector2 uv;	//テクスチャ座標
	Math::Vector4 color;//色
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
