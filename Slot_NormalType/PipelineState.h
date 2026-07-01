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
		D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType);

	bool Init(
		ID3D12Device* device,
		ID3D12RootSignature* rootSignature,
		const D3D12_INPUT_ELEMENT_DESC* inputLayout,
		UINT inputLayoutCount,
		ID3DBlob* vsBlob,
		ID3DBlob* psBlob,
		DXGI_FORMAT rtvFormat,
		D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType,
		bool enableDepth = false,
		bool enableAlphaBlend = false
	);

	//ゲッター
	ID3D12PipelineState* Get() const { return pso.Get(); }

private:
	//パイプラインステート
	ComPtr<ID3D12PipelineState> pso;
};

