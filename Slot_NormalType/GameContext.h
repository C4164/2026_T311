#pragma once
#include "GameScene.h"

class GameContext
{
public:
	static GameContext& Instance()
	{
		static GameContext instance;
		return instance;
	}

	void Init();
	void Update(float deltaTime);
	void Draw(ID3D12GraphicsCommandList* commandList)const;

private:
	GameContext() = default;
};