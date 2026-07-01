#include "ObjectFactory.h"
#include "ResourceManager.h"

GameObject* ObjectFactory::CreateObject(
	const std::wstring& path,
	const XMFLOAT3& pos,
	const XMFLOAT3& scale
)
{
	Mesh* mesh = ResourceManager::GetQuadMesh();
	TextureSRV* tex = ResourceManager::LoadTexture(path);
	PipelineState* pso = ResourceManager::GetSpritePSO();

	Material* mat = new Material();
	mat->SetTexture(tex);
	mat->SetPipelineState(pso);
	mat->SetTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	GameObject* obj = new GameObject();
	obj->SetMesh(mesh);
	obj->SetMaterial(mat);
	obj->Init(DeviceManager::Instance().GetDevice());

	obj->transform.position = pos;
	obj->transform.scale = scale;

	return obj;
}

GameObject* ObjectFactory::CreateLineObject(
	const XMFLOAT3& pos,
	const XMFLOAT3& scale
)
{
	Mesh* mesh = ResourceManager::GetLineMesh();
	PipelineState* pso = ResourceManager::GetLinePSO();

	Material* mat = new Material();
	mat->SetPipelineState(pso);
	mat->SetTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

	GameObject* obj = new GameObject();
	obj->SetMesh(mesh);
	obj->SetMaterial(mat);
	obj->Init(DeviceManager::Instance().GetDevice());

	obj->transform.position = pos;
	obj->transform.scale = scale;
	obj->transform.rotation = { 0.0f, 0.0f, 0.0f };

	return obj;
}