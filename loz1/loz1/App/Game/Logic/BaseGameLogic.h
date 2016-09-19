#ifndef BASEGAMELOGIC_H
#define BASEGAMELOGIC_H

#include<string>
#include<map>

//基础单元
class GameObject{
public:
	GameObject(){m_nID=0;m_bDestroy=false;m_sName="default name";}
	virtual ~GameObject(){}

	//get functions
	inline int getID(){return m_nID;}
	inline std::string getName(){return m_sName;}
	inline bool ifDestroy(){return m_bDestroy;}

	//set functions
	inline void destroy(){m_bDestroy = true;}

	//virtual functions
	virtual void update(double deltaTime){}
	virtual void render(){/*动画更新等应该在update中做*/}
protected:
	int m_nID;
	std::string m_sName;
	bool m_bDestroy;
};

//游戏单元管理器,唯一！
class GameObjectManager{
public:
	typedef std::map<int, GameObject*> ObjectMap;
	typedef ObjectMap::const_iterator ObjectIterator;
	GameObjectManager();
	virtual ~GameObjectManager();

	//创建目标类型对象的指针并注册
	template<class T> inline T* createObject(){
		T* pObj = new T();
		m_vObjects.insert(std::make_pair<int,T*>(m_nNumber++,pObj));
		return pObj;
	}

	void updateAll(double);
	void renderAll();

	GameObject* getObject(int id);

protected:
	std::map<int, GameObject*> m_vObjects;
	int m_nNumber;
};

//需要渲染的单元
class RenderObject : public GameObject{
public:
	RenderObject(){}
	virtual ~RenderObject(){}

	virtual void render(){}
protected:
	// a sprite an animation controller, maybe should write to another file..
};

#endif