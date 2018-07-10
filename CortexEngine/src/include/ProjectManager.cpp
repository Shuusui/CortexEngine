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
	CE::Physics::Transform transform = {};
	transform.Position = glm::vec3(0, 0, 150);
	CE::Physics::Transform transform2 = {};
	transform2.Position = glm::vec3(200, 0, -150);
	ICObject* object = new ICObject(0, "object", transform);
	ICObject* object2 = new ICObject(1, "object2", transform2);
	CE::Components::CRenderComponent* renderComponent = new CE::Components::CRenderComponent(0);
	CE::Components::CRenderComponent* renderComponent2 = new CE::Components::CRenderComponent(1);
	renderComponent->Init();
	renderComponent2->Init();
	CE::Rendering::CMaterial* material = new CE::Rendering::CMaterial();
	material->AddDiffuse("../assets//textures//CubeBasecolor.jpg");
	material->AddNormal("../assets//textures//CubeNormal.jpg");
	material->Init();
	CE::Rendering::CMesh* mesh = new CE::Rendering::CMesh();
	renderComponent->AddMesh(mesh);
	renderComponent2->AddMesh(mesh);
	renderComponent->AddMaterial(material);
	renderComponent2->AddMaterial(material);
	object->AddComponent(renderComponent);
	object2->AddComponent(renderComponent2);
	m_pCurrLevel->AddObject(object);
	m_pCurrLevel->AddObject(object2);
	return true;
}


void CE::Core::ProjectManager::Save()
{

}