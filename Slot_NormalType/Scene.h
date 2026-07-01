#pragma once
#include <vector>
#include "GameObject.h"

class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    //シーン開始時に一度だけ呼ばれる
    virtual void Init() = 0;

    //毎フレーム更新
    virtual void Update(float deltaTime) {}

    //毎フレーム描画
    virtual void DrawBackGround(ID3D12GraphicsCommandList* commandList)
    {
        for (auto o : backGroundObjects)
        {
            o->Draw(commandList);
        }
    }

    virtual void DrawObjects(ID3D12GraphicsCommandList* commandList) 
    {
        for (auto o : gameObjects) 
        {
            o->Draw(commandList);
        }
    }

    virtual void DrawUI(ID3D12GraphicsCommandList* commandList)
    {
        for (auto o : UIObjects)
        {
            o->Draw(commandList);
        }
    }

    //シーン終了時に呼ばれる
    virtual void End() {}

    void AddGameObject(GameObject* obj)
    {
        gameObjects.push_back(obj);
    }

    void AddUIObject(GameObject* obj)
    {
        UIObjects.push_back(obj);
    }

protected:
    std::vector<GameObject*> backGroundObjects;
    std::vector<GameObject*> gameObjects;
    std::vector<GameObject*> UIObjects;
};

