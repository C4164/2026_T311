#include "UI.h"
#include "ObjectFactory.h"
#include "GameScene.h"
#include "ResourceManager.h"
#include "Resource.h"
#include "Consts.h"

void UI::Init()
{
	ResourceManager::LoadTexture(Resource::whitePath);

	for (int i = 0; i < 4; i++)
	{
		float y = Const::SYMBOLDISTANCE_HEIGHT * (1.5f - i);
		XMFLOAT3 position(0.0f, y, 0.0f);
		XMFLOAT3 scale(Const::SYMBOLDISTANCE_WIDTH * 3.0f + lineWidth, lineWidth, 0.0f);

		gridLines[i] = ObjectFactory::CreateObject(Resource::whitePath, position, scale);
		GameScene::Instance().AddUIObject(gridLines[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		float x = Const::SYMBOLDISTANCE_WIDTH * (-1.5f + i);
		XMFLOAT3 position(x, 0.0f, 0.0f);
		XMFLOAT3 scale(lineWidth, Const::SYMBOLDISTANCE_HEIGHT * 3.0f + lineWidth, 0.0f);

		gridLines[4 + i] = ObjectFactory::CreateObject(Resource::whitePath, position, scale);
		GameScene::Instance().AddUIObject(gridLines[4 + i]);
	}
}