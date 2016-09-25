#ifndef BASEGAMELOGIC_H
#define BASEGAMELOGIC_H

#include<string>
#include<map>

enum ObjectType{
	OBJECT_UNKNOWN = -1,
	OBJECT_DEFAULT = 0,
	OBJECT_LIVING,//生命实体
	OBJECT_BARRIER,//地形物
	OBJECT_PROJECTILE,//投射物
	OBJECT_ABSTRACT,//抽象对象，如声音、特效等
};

//基础单元，可以独立存在逻辑个体的根本
class GameObject{
	friend class GameObjectManager;

protected:
	//create only by child
	GameObject(){m_nID=0;m_bDestroy=false;m_nType=OBJECT_DEFAULT;}

public:
	virtual ~GameObject(){}
	//get functions
	inline int getID(){return m_nID;}
	inline ObjectType getType(){return m_nType;}
	inline bool ifDestroy(){return m_bDestroy;}

	//set functions
	inline void destroy(){m_bDestroy = true;}

	//virtual functions
	virtual void update(double deltaTime){}
	virtual void render(){/*动画更新等应该在update中做*/}
protected:
	inline void setID(int id){m_nID = id;}

	int m_nID;
	ObjectType m_nType;
	bool m_bDestroy;
};

class QuadTree;
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
		GameObject* pVal = static_cast<GameObject*>(pObj);
		pVal->setID(m_nNumber);
		m_vObjects.insert(std::make_pair<int,GameObject*>(m_nNumber++,pVal));
		return pObj;
	}

	//void bakelogicmap(mapsize)

	//根据ID查找返回指定object
	GameObject* getObject(int id);

	//更新所有对象
	void updateAll(double);

	//检测碰撞
	void checkCollision();

	//渲染所有可渲染对象
	void renderAll();
	
	//清理所有对象
	void cleanUp();

protected:
	void buildTree();

	std::map<int, GameObject*> m_vObjects;
	QuadTree* m_pTree;//碰撞检测使用
	int m_nNumber;
};

struct GameMsg{
	int nSrcID;
	int nTarID;
	int nValue1, nValue2, nValue3;
	double dValue1, dValue2, dValue3;
	std::string sValue1, sValue2, sValue3;

	GameMsg(){
		nSrcID=nTarID=nValue1=nValue2=nValue3=0;
		dValue1=dValue2=dValue3=0.0;
		sValue1=sValue2=sValue3="";
	}
};

//typedef void (*GameCallback)(GameMsg&);

template<class T>
class CallbackFunction : public ICallback{

public:
	CallbackFunction(){
		d_function = 0;
		d_object = 0;
	}
	CallbackFunction(T* pObj, void (T::*func)(GameMsg&)){
		d_function = func;
		d_object = pObj;
	}
	void operator ()(GameMsg& msg){
		if(!d_function || !d_object) return ;
		d_object->*d_function(msg);
	}

private:
	void (T::*d_function)(GameMsg&);
	T* d_object;
};

#endif