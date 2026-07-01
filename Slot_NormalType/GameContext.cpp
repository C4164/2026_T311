#include "GameContext.h"

void GameContext::Init() 
{
	GameScene::Instance().Init();
}

void GameContext::Update(float deltaTime)
{
	GameScene::Instance().Update(deltaTime);
}

void GameContext::Draw(ID3D12GraphicsCommandList* commandList)const
{
	GameScene::Instance().DrawBackGround(commandList);
	GameScene::Instance().DrawObjects(commandList);
	GameScene::Instance().DrawUI(commandList);
}