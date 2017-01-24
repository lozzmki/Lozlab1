#include "BaseGameLogic.h"
#include "LogicGear.h"
#include "GameEntity.h"
#include "../../Utilities/Common.h"

GameObjectManager::GameObjectManager(){
	m_nNumber=0;
	m_vObjects.clear();
}
GameObjectManager::~GameObjectManager(){
	cleanUp();
}

GameObject* GameObjectManager::getObject(int id){
	ObjectIterator it = m_vObjects.find(id);
	if(it != m_vObjects.end()){
		GameObject* pObj = it->second;
		if(!pObj) return 0;
		else if(pObj->ifDestroy()) return 0;//Ŀ���������һ�߼�֡����
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

void GameObjectManager::cleanUp(){
	ObjectIterator it = m_vObjects.begin();
	for(;it!=m_vObjects.end();){
		GameObject* pObj = it->second;
		SAFE_DELETE(pObj);
		it = m_vObjects.erase(it);
	}
	m_vObjects.clear();

	m_nNumber=0;
}
/*
void GameObjectManager::buildTree(){
	m_pTree->clear();

	ObjectIterator it = m_vObjects.begin();
	for(;it!=m_vObjects.end();){
		GameObject* pObj = it->second;
		InteractEntity* pEty = dynamic_cast<InteractEntity*>(pObj);
		if(!pEty || pEty->ifDestroy()){
			//do nothing
		}else{
			BoundBox& box = pEty->getBoundBox();
			Vec2d _lt = box.getPos() + (box.getSize()*0.5).ReverseX();
			m_pTree->push(pEty->getID(), _lt, box.getSize());
		}
		++it;
	}
}
*/

/*
void GameObjectManager::checkCollision(){
	IDcheckSet _set;
	std::list<int> _list;
	std::list<int>::const_iterator _lstit;

	//�����Ĳ���
	buildTree();

	ObjectIterator it = m_vObjects.begin();
	for(;it!=m_vObjects.end();){
		GameObject* pObj = it->second;
		InteractEntity* pEty = dynamic_cast<InteractEntity*>(pObj);
		if(!pEty || pEty->ifDestroy()){
			//do nothing
		}else{
			BoundBox& box = pEty->getBoundBox();
			Vec2d _lt = box.getPos() + (box.getSize()*0.5).ReverseX();
			
			_list.clear();
			m_pTree->getList(_list, _lt, box.getSize());

			int _srcid = pEty->getID();
			for(_lstit = _list.begin(); _lstit != _list.end(); ++_lstit){
				int _tarid = *_lstit;
				if(_set.find(IDpair(_srcid, _tarid)) == _set.end()){
					//û���й���ײ��� ����м�Ⲣ���
					_set.insert(IDpair(_srcid, _tarid));
					_set.insert(IDpair(_tarid, _srcid));

					InteractEntity* pTar = dynamic_cast<InteractEntity*>(getObject(_tarid));
					if(!pTar || pTar->ifDestroy()) continue;

					bool _ifCollied = pEty->getBoundBox().checkCollide(static_cast<IBoundBox*>(&pTar->getBoundBox()));
					if(_ifCollied){
						GameMsg _msg;
						memset(&_msg,0,sizeof(GameMsg));
						_msg.nTarID = _tarid;
						pEty->onCollide(_msg);

						_msg.nTarID = _srcid;
						pTar->onCollide(_msg);
					}
				}
			}
		}
		++it;
	}
}*/

void GameObjectManager::checkCollision(){

	//����list��һ��entityһ��projectile����entity���������������entity��projectile����ײ���
	//entity��ײ�����¼��·�������֮����entity��projectile��ײ�����¼�
}