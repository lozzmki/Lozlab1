#include "BaseGameLogic.h"
#include "../../Utilities/Common.h"

GameObjectManager::GameObjectManager(){
	m_nNumber=0;
	m_vObjects.clear();
}
GameObjectManager::~GameObjectManager(){
	ObjectIterator it = m_vObjects.begin();
	for(;it!=m_vObjects.end();){
		GameObject* pObj = it->second;
		SAFE_DELETE(pObj);
		it = m_vObjects.erase(it);
	}
	m_vObjects.clear();
}

GameObject* GameObjectManager::getObject(int id){
	ObjectIterator it = m_vObjects.find(id);
	if(it != m_vObjects.end()){
		GameObject* pObj = it->second;
		if(!pObj) return 0;
		else if(pObj->ifDestroy()) return 0;//目标对象将于下一逻辑帧销毁
		else return pObj;
	}else
		return 0;
}

void GameObjectManager::updateAll(double deltaTime){
	ObjectIterator it = m_vObjects.begin();
	for(;it!=m_vObjects.end();){
		GameObject* pObj = it->second;
		if(!pObj || pObj->ifDestroy()){
			SAFE_DELETE(pObj);
			it = m_vObjects.erase(it);
		}else{
			pObj->update(deltaTime);
			++it;
		}
	}
}

void GameObjectManager::renderAll(){
	ObjectIterator it = m_vObjects.begin();
	for(;it!=m_vObjects.end();){
		GameObject* pObj = it->second;
		if(!pObj || pObj->ifDestroy()){
			//do nothing
		}else{
			pObj->render();
		}
		++it;
	}
}