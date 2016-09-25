#ifndef BASEGAMELOGIC_H
#define BASEGAMELOGIC_H

#include<string>
#include<map>

enum ObjectType{
	OBJECT_UNKNOWN = -1,
	OBJECT_DEFAULT = 0,
	OBJECT_LIVING,//����ʵ��
	OBJECT_BARRIER,//������
	OBJECT_PROJECTILE,//Ͷ����
	OBJECT_ABSTRACT,//�����������������Ч��
};

//������Ԫ�����Զ��������߼�����ĸ���
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
	virtual void render(){/*�������µ�Ӧ����update����*/}
protected:
	inline void setID(int id){m_nID = id;}

	int m_nID;
	ObjectType m_nType;
	bool m_bDestroy;
};

class QuadTree;
//��Ϸ��Ԫ������,Ψһ��
class GameObjectManager{
public:
	typedef std::map<int, GameObject*> ObjectMap;
	typedef ObjectMap::const_iterator ObjectIterator;
	GameObjectManager();
	virtual ~GameObjectManager();

	//����Ŀ�����Ͷ����ָ�벢ע��
	template<class T> inline T* createObject(){
		T* pObj = new T();
		GameObject* pVal = static_cast<GameObject*>(pObj);
		pVal->setID(m_nNumber);
		m_vObjects.insert(std::make_pair<int,GameObject*>(m_nNumber++,pVal));
		return pObj;
	}

	//void bakelogicmap(mapsize)

	//����ID���ҷ���ָ��object
	GameObject* getObject(int id);

	//�������ж���
	void updateAll(double);

	//�����ײ
	void checkCollision();

	//��Ⱦ���п���Ⱦ����
	void renderAll();
	
	//�������ж���
	void cleanUp();

protected:
	void buildTree();

	std::map<int, GameObject*> m_vObjects;
	QuadTree* m_pTree;//��ײ���ʹ��
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