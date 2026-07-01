#include "Material.h"
#include "RootSignature.h"


void Material::Bind(ID3D12GraphicsCommandList* cmdList)
{
    auto rs = RootSignature::Instance().Get();
    if (!rs)
    { 
        OutputDebugStringA("RootSignature Instance null\n");
        return; 
    }

    if (!pso || !pso->Get()) 
    { 
        OutputDebugStringA("PSO null\n");
        return; 
    }

    cmdList->SetGraphicsRootSignature(rs);
    cmdList->IASetPrimitiveTopology(topology);
    cmdList->SetPipelineState(pso->Get());

    //テクスチャをセット
    if (texture)
    {
        cmdList->SetGraphicsRootDescriptorTable(2, texture->GetGPUHandle());
    }
}


