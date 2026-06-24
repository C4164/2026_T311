#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "ComPtr.h"

class DescriptorHeap_CBV_SRV
{
public:
    //シングルトン
    static DescriptorHeap_CBV_SRV& Instance()
    {
        static DescriptorHeap_CBV_SRV instance;
        return instance;
    }

    //初期化関数
    bool Init(ID3D12Device* device, UINT numDescriptors);

    //ゲッター
    D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(UINT index) const;
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle(UINT index) const;
    ID3D12DescriptorHeap* GetHeap() const { return heap.Get(); }
    UINT GetDescriptorSize() const { return descriptorSize; }

private:
    //コンストラクタ
    DescriptorHeap_CBV_SRV() = default;

    ComPtr<ID3D12DescriptorHeap> heap;
    UINT descriptorSize = 0;
};

