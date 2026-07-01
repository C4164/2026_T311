#include "Reel.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "ObjectFactory.h"
#include "Input.h"
#include "GameScene.h"
#include <cmath>

void Reel::Init()
{
	//それぞれのテクスチャーをロード
	ResourceManager::LoadTexture(Resource::blankPath);
	ResourceManager::LoadTexture(Resource::bellPath);
	ResourceManager::LoadTexture(Resource::replayPath);
	ResourceManager::LoadTexture(Resource::melonPath);
	ResourceManager::LoadTexture(Resource::cherryPath);
	ResourceManager::LoadTexture(Resource::sevenPath);
	ResourceManager::LoadTexture(Resource::barPath);

	//図柄を作成し、リール配列通りに配置
	XMFLOAT3 createPos = { -Const::SYMBOLDISTANCE_WIDTH,Const::SYMBOLDISTANCE_HEIGHT,0 };
	const XMFLOAT3 createScale = { 1.5f,1.5f,1.5f };
	const XMFLOAT3 blankScale = { 0.75f,0.75f,0.75f };
	XMFLOAT3 scale = {};
	Const::Symbols symbol;
	for (int i = 0; i < Const::REELSYMBOL_NUM; i++)
	{
		symbol = Const::REELTABLE_LEFT[i];
		scale = (symbol == Const::Symbols::blankSymbol) ? blankScale : createScale;
		leftReelObjects[i] = ObjectFactory::CreateObject(Resource::SymbolPaths[symbol], createPos, scale);
		GameScene::Instance().AddGameObject(leftReelObjects[i]);
		createPos.x += Const::SYMBOLDISTANCE_WIDTH;

		symbol = Const::REELTABLE_CENTER[i];
		scale = (symbol == Const::Symbols::blankSymbol) ? blankScale : createScale;
		centerReelObjects[i] = ObjectFactory::CreateObject(Resource::SymbolPaths[symbol], createPos, scale);
		GameScene::Instance().AddGameObject(centerReelObjects[i]);
		createPos.x += Const::SYMBOLDISTANCE_WIDTH;

		symbol = Const::REELTABLE_RIGHT[i];
		scale = (symbol == Const::Symbols::blankSymbol) ? blankScale : createScale;
		rightReelObjects[i] = ObjectFactory::CreateObject(Resource::SymbolPaths[symbol], createPos, scale);
		GameScene::Instance().AddGameObject(rightReelObjects[i]);
		createPos.x -= Const::SYMBOLDISTANCE_WIDTH * 2.0f;
		createPos.y -= Const::SYMBOLDISTANCE_HEIGHT;
	}
}

void Reel::Update(float deltaTime)
{
	ActionCheck();

	ReelStop(deltaTime, leftReelObjects, isSpinLeft, isStopLeft);
	ReelStop(deltaTime, centerReelObjects, isSpinCenter, isStopCenter);
	ReelStop(deltaTime, rightReelObjects, isSpinRight, isStopRight);

	UpdatePosition(deltaTime, leftReelObjects, isSpinLeft, isStopLeft);
	UpdatePosition(deltaTime, centerReelObjects, isSpinCenter, isStopCenter);
	UpdatePosition(deltaTime, rightReelObjects, isSpinRight, isStopRight);
}

void Reel::ActionCheck()
{
	//スペースキーが押されていなければ何もしない
	if (!Input::IsKeyDown(VK_SPACE)) { return; }

	//第一停止
	if (isSpinLeft)
	{
		isStopLeft = true;
		SetTargetIndex(leftReelObjects);
	}
	//第二停止
	else if (isSpinCenter)
	{
		isStopCenter = true;
		SetTargetIndex(centerReelObjects);
	}
	//第三停止
	else if (isSpinRight)
	{
		isStopRight = true;
		SetTargetIndex(rightReelObjects);
	}
	//リール始動
	else
	{
		isSpinLeft = true;
		isSpinCenter = true;
		isSpinRight = true;

		isStopLeft = false;
		isStopCenter = false;
		isStopRight = false;
	}
}

void Reel::UpdatePosition(
	float deltaTime,
	std::array<GameObject*, Const::REELSYMBOL_NUM> reelObjects,
	bool isSpin,
	bool isStop)
{
	//リール回転中のみ移動
	if (!isSpin) { return; }

	for (int i = 0; i < Const::REELSYMBOL_NUM; i++)
	{
		//速度分移動
		reelObjects[i]->transform.position.y -= Const::REEL_SPEED * deltaTime;
		//一番下までいったら上まで移動してサイクルさせる
		if (reelObjects[i]->transform.position.y < down)
		{
			reelObjects[i]->transform.position.y += Const::SYMBOLDISTANCE_HEIGHT * Const::REELSYMBOL_NUM;
		}
	}
}

void Reel::ReelStop(
	float deltaTime,
	std::array<GameObject*, Const::REELSYMBOL_NUM> reelObjects,
	bool& isSpin,
	bool isStop)
{
	//リールが回転中かつ停止ボタンが押されている状態
	if (!isSpin) { return; }
	if (!isStop) { return; }

	//このフレームにオブジェクトが中段位置を超えるなら正しい位置にぴったり吸着させる
	if (reelObjects[targetIndex]->transform.position.y - Const::REEL_SPEED * deltaTime < 0.0f)
	{
		float stopPosY = Const::SYMBOLDISTANCE_HEIGHT;
		int index = (targetIndex - 1 + Const::REELSYMBOL_NUM) % Const::REELSYMBOL_NUM;
		//全てのオブジェクトを吸着させる
		for (int i = 0; i < Const::REELSYMBOL_NUM; i++)
		{
			reelObjects[index]->transform.position.y = stopPosY;
			stopPosY -= Const::SYMBOLDISTANCE_HEIGHT;
			index = (index + 1) % Const::REELSYMBOL_NUM;
		}
		//リールを停止
		isSpin = false;
		targetIndex = -1;
	}
}

void Reel::SetTargetIndex(std::array<GameObject*, Const::REELSYMBOL_NUM> reelObjects)
{
	for (int i = 0; i < Const::REELSYMBOL_NUM; i++)
	{
		if (reelObjects[i]->transform.position.y < 1.5f &&
			reelObjects[i]->transform.position.y > 0.0f)
		{
			targetIndex = i;
			break;
		}
	}
}