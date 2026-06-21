#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "ComPtr.h"

class DeviceManager
{
public:
	DeviceManager() = default;
	~DeviceManager() = default;


	bool Init();

	//ゲッター
	ID3D12Device6* GetDevice()const { return device.Get(); }
	IDXGIFactory6* GetFactory()const { return factory.Get(); }

private:
	//生成関数
	bool CreateFactory();
	bool CreateDevice();

	//ファクトリー
	ComPtr<IDXGIFactory6>factory = nullptr;
	//デバイス
	ComPtr<ID3D12Device6> device = nullptr;
};