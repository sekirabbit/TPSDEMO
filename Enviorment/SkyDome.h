#pragma once

#include"ObjectBase.h"

class SkyDome :public ObjectBase
{
public:
	SkyDome();
	void Update()override;
	void Draw()override;
};
