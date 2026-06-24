#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh
{
public:
    //コンストラクタとデストラクタ
    Mesh() = default;
    ~Mesh() = default;

    //初期化関数
    bool Init(
        ID3D12Device* device,
        ID3D12GraphicsCommandList* cmdList,
        const void* vertices,
        UINT vertexSize,
        UINT vertexCount,
        const uint16_t* indices,
        UINT indexCount
    );

    //描画関数
    void Draw(ID3D12GraphicsCommandList* commandList);

private:
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
    UINT indexCount = 0;
};
