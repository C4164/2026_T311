#include "PipelineState.h"
#include "d3dx12.h"
#include "Shader.h"

static const D3D12_INPUT_ELEMENT_DESC spriteLayout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },

	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,
	  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
};

static const D3D12_INPUT_ELEMENT_DESC lineLayout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },

	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
	  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
};

bool PipelineState::Init(
	ID3D12Device* device,
	ID3D12RootSignature* rootSignature,
	D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType)
{
	ID3DBlob* vsBlob = nullptr;
	ID3DBlob* psBlob = nullptr;

	const D3D12_INPUT_ELEMENT_DESC* layout = nullptr;
	UINT layoutCount = 0;

	if (primitiveType == D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE)
	{
		layout = spriteLayout;
		layoutCount = _countof(spriteLayout);
		//シェーダー読み込み
		vsBlob = Shader::Instance().LoadVS("Shaders/VS.cso");
		psBlob = Shader::Instance().LoadPS("Shaders/PS.cso");
	}
	else if (primitiveType == D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE)
	{
		layout = lineLayout;
		layoutCount = _countof(lineLayout);
		//シェーダー読み込み
		vsBlob = Shader::Instance().LoadVS("Shaders/LineVS.cso");
		psBlob = Shader::Instance().LoadPS("Shaders/LinePS.cso");
	}

	if (!vsBlob || !psBlob)
	{
		OutputDebugStringA("Shader load failed! PSO cannot be created.\n");
		return false;
	}

	return Init(
		device,
		rootSignature,
		layout,
		layoutCount,
		vsBlob,
		psBlob,
		DXGI_FORMAT_R8G8B8A8_UNORM, //RTV フォーマット
		primitiveType,
		false,                      //Depth 無効
		true                        //AlphaBlend有効
	);
}

bool PipelineState::Init(
	ID3D12Device* device,
	ID3D12RootSignature* rootSignature,
	const D3D12_INPUT_ELEMENT_DESC* inputLayout,
	UINT inputLayoutCount,
	ID3DBlob* vsBlob,
	ID3DBlob* psBlob,
	DXGI_FORMAT rtvFormat,
	D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType,
	bool enableDepth,
	bool enableAlphaBlend
)
{
	//グラフィックスパイプラインの設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
	desc.pRootSignature = rootSignature;
	//シェーダー
	desc.VS = { vsBlob->GetBufferPointer(), vsBlob->GetBufferSize() };
	desc.PS = { psBlob->GetBufferPointer(), psBlob->GetBufferSize() };
	//入力レイアウト
	desc.InputLayout = { inputLayout, inputLayoutCount };
	//ラスタライザ
	desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	//ブレンド
	if (enableAlphaBlend)
	{
		auto blend = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		blend.RenderTarget[0].BlendEnable = TRUE;
		blend.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
		blend.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
		desc.BlendState = blend;
	}
	else
	{
		desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	}
	//深度ステンシル
	if (enableDepth)
	{
		desc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	}
	else
	{
		desc.DepthStencilState.DepthEnable = FALSE;
		desc.DepthStencilState.StencilEnable = FALSE;
	}
	//サンプルマスク
	desc.SampleMask = UINT_MAX;
	//プリミティブタイプ
	desc.PrimitiveTopologyType = primitiveType;
	//レンダーターゲット
	desc.NumRenderTargets = 1;
	desc.RTVFormats[0] = rtvFormat;
	desc.SampleDesc.Count = 1;

	//パイプラインステートを作成
	HRESULT hr = device->CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(&pso));
	if (FAILED(hr))
	{
		OutputDebugStringA("PSO creation failed!\n");
	}

	return SUCCEEDED(hr);
}
