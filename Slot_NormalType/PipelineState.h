#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "ComPtr.h"

class PipelineState
{
public:
    //コンストラクタとデストラクタ
    PipelineState() = default;
    ~PipelineState() = default;

    //初期化関数
    bool Init(
        ID3D12Device* device,
        ID3D12RootSignature* rootSignature,
        ID3DBlob* vsBlob,
        ID3DBlob* psBlob,
        DXGI_FORMAT rtvFormat
    );

    //ゲッター
    ID3D12PipelineState* Get() const { return pso.Get(); }

private:
    //パイプラインエステート
    ComPtr<ID3D12PipelineState> pso;
};

