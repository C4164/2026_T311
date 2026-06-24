#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <string>
#include "ComPtr.h"
#include "TextureSRV.h"
#include "PipelineState.h"

class Material
{
public:
    //コンストラクタとデストラクタ
    Material() = default;
    ~Material() = default;

    void Bind(ID3D12GraphicsCommandList* commandList);

    //セッター
    void SetPipelineState(PipelineState* state) { pso = state; }
    void SetTexture(TextureSRV* tex) { texture = tex; }

private:
    PipelineState* pso = nullptr;
    TextureSRV* texture = nullptr;
};
