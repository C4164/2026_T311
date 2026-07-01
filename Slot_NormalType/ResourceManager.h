#pragma once
#include "Render.h"
#include <unordered_map>

class ResourceManager
{
public:
	//ƒVƒ“ƒOƒ‹ƒgƒ“
	static ResourceManager& Instance()
	{
		static ResourceManager instance;
		return instance;
	}

	static TextureSRV* LoadTexture(const std::wstring& path);

	static Mesh* GetQuadMesh();
	static PipelineState* GetSpritePSO();

	static Mesh* GetLineMesh();
	static PipelineState* GetLinePSO();

private:
	ResourceManager() = default;

	static Mesh* CreateQuadMesh();
	static Mesh* CreateLineMesh();

	Mesh* quadMesh = nullptr;
	Mesh* lineMesh = nullptr;
	PipelineState* spritePSO = nullptr;
	PipelineState* linePSO = nullptr;
	std::unordered_map<std::wstring, TextureSRV*> textures;
};