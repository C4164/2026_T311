#include "Mesh.h"

bool Mesh::Init(
    ID3D12Device* device,
    ID3D12GraphicsCommandList* cmdList,
    const void* vertices,
    UINT vertexSize,
    UINT vertexCount,
    const uint16_t* indices,
    UINT indexCount
)
{
    //VBを初期化
    if (!vertexBuffer.Init(device, cmdList, vertices, vertexSize, vertexCount))
    {
        return false;
    }

    //IBを初期化
    if (!indexBuffer.Init(device, cmdList, indices, indexCount))
    {
        return false;
    }

    this->indexCount = indexCount;
    return true;
}

void Mesh::Draw(ID3D12GraphicsCommandList* commandList)
{
    //VB・IBをセット
    commandList->IASetVertexBuffers(0, 1, &vertexBuffer.GetView());
    commandList->IASetIndexBuffer(&indexBuffer.GetView());

    //描画する
    commandList->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
}
