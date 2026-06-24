#include "PipelineState.h"
#include "d3dx12.h"

bool PipelineState::Init(
    ID3D12Device* device,               //デバイスのポインター
    ID3D12RootSignature* rootSignature, //ルートシグネチャのポインター
    ID3DBlob* vsBlob,                   //頂点シェーダー
    ID3DBlob* psBlob,                   //ピクセルシェーダー
    DXGI_FORMAT rtvFormat               //バックバッファのフォーマット
)
{
    //入力レイアウト
    D3D12_INPUT_ELEMENT_DESC inputLayout[] =
    {
        {
            "POSITION",                                 //セマンティクス名
            0,                                          //インデックス
            DXGI_FORMAT_R32G32B32_FLOAT,                //float3
            0,                                          //スロット番号
            0,                                          //先頭からのオフセット
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, //頂点ごとにデータ
            0                                           //同じインスタンスごとのデータを使用して描画するインスタンスの数
        }
    };

    //グラフィックスパイプラインの設定
    D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
    desc.pRootSignature = rootSignature;
    //シェーダー
    desc.VS = { vsBlob->GetBufferPointer(), vsBlob->GetBufferSize() };
    desc.PS = { psBlob->GetBufferPointer(), psBlob->GetBufferSize() };
    //入力レイアウト
    desc.InputLayout.pInputElementDescs = inputLayout;
    desc.InputLayout.NumElements = _countof(inputLayout);
    //ラスタライザ
    desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    //ブレンド
    desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    //深度ステンシル
    desc.DepthStencilState.DepthEnable = FALSE;
    desc.DepthStencilState.StencilEnable = FALSE;
    //サンプルマスク
    desc.SampleMask = UINT_MAX;
    //プリミティブタイプ
    desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    //レンダーターゲット
    desc.NumRenderTargets = 1;
    desc.RTVFormats[0] = rtvFormat;
    desc.SampleDesc.Count = 1;

    //パイプラインエステートを作成
    HRESULT hr = device->CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(&pso));
    return SUCCEEDED(hr);
}
