#include "Material.h"

void Material::Bind(ID3D12GraphicsCommandList* cmdList)
{
    //パイプラインエステートを設定
    cmdList->SetPipelineState(pso->Get());

    // テクスチャを設定
    if (texture)
    {
        cmdList->SetGraphicsRootDescriptorTable(0, texture->GetGPUHandle());
    }
}

