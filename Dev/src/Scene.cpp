#include "Scene.h"
#include "Components\RenderComponent.h"
#include "Rendering\MeshFactory.h"


#include <memory>


Scene::Scene() {
	m_CurrentCamera_ = nullptr;
	m_SceneGameObjects_.reserve(100); // Temporary reservation of space, XML file loading will handle this efficiently itself.
}

Scene::Scene(std::string pName) {
	m_Name_ = pName;
	m_SceneGameObjects_.reserve(100); // Temporary reservation of space, XML file loading will handle this efficiently itself.
}

int Scene::AddGameObject(GameObject pGameObject) {
	std::cout << m_SceneGameObjects_.capacity() << std::endl;
	m_SceneGameObjects_.push_back(pGameObject);
	M_bIsDirty = true;
	return m_SceneGameObjects_.size() - 1;
}

void Scene::RemoveGameObject(GameObject * pGameObject) {
	M_bIsDirty = true;

}

void Scene::Update(double dt){

	//Standard Update.
	for (GameObjectVectorWrapper::t_GameObject_Vector_Iterator_ iter = m_SceneGameObjects_.begin(); iter != m_SceneGameObjects_.end(); ++iter) {
		(*iter).UpdateComponents(dt);
	}


	//Late update.
	for (GameObjectVectorWrapper::t_GameObject_Vector_Iterator_ iter = m_SceneGameObjects_.begin(); iter != m_SceneGameObjects_.end(); ++iter) {
		(*iter).LateUpdateComponents();

	}
}


void Scene::Start() {

	//Start the Components within the Scene.

	for (GameObjectVectorWrapper::t_GameObject_Vector_Iterator_ iter = m_SceneGameObjects_.begin(); iter != m_SceneGameObjects_.end(); ++iter) {
		for (ComponentVectorWrapper::t_Component_Iter iter2 = (*iter).getComponents().begin(); iter2 != (*iter).getComponents().end(); ++iter2) {
			(*iter2)->Start();
		}
	}
}


void Scene::Destroy() {
	//Destroy the components.
	for (GameObjectVectorWrapper::t_GameObject_Vector_Iterator_ iter = m_SceneGameObjects_.begin(); iter != m_SceneGameObjects_.end(); ++iter) {
		for (ComponentVectorWrapper::t_Component_Iter iter2 = (*iter).getComponents().begin(); iter2 != (*iter).getComponents().end(); ++iter2) {
			(*iter2)->Destroy();
		}
	}


	//Clear the GameObjects vector.
	m_SceneGameObjects_.clear();
}