#include "ProjectManager.h"
#include "CRenderComponent.h"
#include "CMesh.h"
#include "CMaterial.h"


void CE::Core::ProjectManager::SetInitParams(const ProjectParams & params)
{

}

void CE::Core::ProjectManager::LoadLevel(CLevel * currLevel)
{
}

void CE::Core::ProjectManager::NewLevel(const std::string & name, const uint32_t & resX, const uint32_t & resY)
{
	m_pCurrLevel = new CLevel(name, resX, resY);
}

void CE::Core::ProjectManager::Release()
{
	m_pCurrLevel->Release();
	delete this;
}

CE::Core::ProjectManager::ProjectManager(const std::string & name, CLevel* pCurrLevel, const bool& newProj)
	:m_name(name)
	,m_pCurrLevel(m_pCurrLevel)
	,m_isDirty(true)
{
	if (!newProj)
		LoadProjectFile();
	else
	{
		if (!pCurrLevel)
		{
			NewLevel("level", 1024, 1024);
		}
	}
}

CE::Core::ProjectManager::~ProjectManager()
{
}

CE::Core::ProjectParams CE::Core::ProjectManager::LoadProjectFile()
{
	ProjectParams params;
	return params;
}

bool CE::Core::ProjectManager::Init()
{
	CE::Physics::Transform transform;
	ICObject* object = new ICObject(0, "object", transform);
	CE::Components::CRenderComponent* renderComponent = new CE::Components::CRenderComponent(0);
	renderComponent->Init();
	CE::Rendering::CMaterial* material = new CE::Rendering::CMaterial();
	//material->ReadFile("../assets//textures//default.jpg");
	material->AddNewTexture("../assets//textures//chalet.jpg");
	CE::Rendering::CMesh* mesh = new CE::Rendering::CMesh();
	mesh->LoadModel("../assets//models//chalet.obj");
	renderComponent->AddMesh(mesh);
	renderComponent->AddMaterial(material);
	object->AddComponent(renderComponent);
	m_pCurrLevel->AddObject(object);
	return true;
}


void CE::Core::ProjectManager::Save()
{

}