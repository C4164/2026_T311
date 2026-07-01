#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <string>
#include "TextureSRV.h"
#include "PipelineState.h"

class Material
{
public:
    Material() = default;
    ~Material() = default;

    //描画時に呼ぶ
    void Bind(ID3D12GraphicsCommandList* cmdList);

    //ゲッター
    TextureSRV* GetTexture()const { return texture; }

    //セッター
    void SetPipelineState(PipelineState* state) { pso = state; }
    void SetTexture(TextureSRV* tex) { texture = tex; }
	void SetTopology(D3D12_PRIMITIVE_TOPOLOGY topo) { topology = topo; }

private:
    PipelineState* pso = nullptr;
    TextureSRV* texture = nullptr;

	D3D12_PRIMITIVE_TOPOLOGY topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

