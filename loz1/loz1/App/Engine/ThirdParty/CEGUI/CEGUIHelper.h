#ifndef CETEST_H
#define CETEST_H


#include<CEGUI/CEGUI.h>
#include<CEGUI/RendererModules/Direct3D9/Renderer.h>
#include"../../../Utilities/Vector2D.h"

#define ZeroUVector CEGUI::UVector2(CEGUI::UDim(0.0f,0.0f), CEGUI::UDim(0.0f,0.0f))
#define DefaultUSize CEGUI::USize(CEGUI::UDim(0.1f, 0.0f), CEGUI::UDim(0.1f,0.0f))

//封装CEGUI操作的类

class CEGUIHelper{
public:
	CEGUIHelper();
	virtual ~CEGUIHelper();

	void renderGUI();
	void injectMouseInput();
	void injectKeyInput();
	void injectCharEvent(char);

	inline CEGUI::WindowManager* getWndMgr(){return m_pWndMgr;}
	inline CEGUI::Window* getRootWnd(){return m_pWnd;}

protected:
	CEGUI::Direct3D9Renderer* m_pRenderer;
	CEGUI::WindowManager* m_pWndMgr;
	CEGUI::Window* m_pWnd;
};

template<class T>
T* createCEobject(CEGUI::Window* parent,CEGUI::String style, CEGUI::String name, CEGUI::UVector2 pos=ZeroUVector,CEGUI::USize size=DefaultUSize){
	T* pObj = 0;

	pObj = static_cast<T*>( g_GUI->getWndMgr()->createWindow(style, name) );

	if(!pObj)return 0;
	pObj->setPosition(pos);
	pObj->setSize(size);
	if(parent)
		parent->addChild(pObj);
	else
		g_GUI->getRootWnd()->addChild(pObj);

	return pObj;
}

#define CreateCEFrame(parent, style, name, pos, size) createCEobject<CEGUI::FrameWindow>(parent, style, name, pos, size)
#define CreateCEPushButton(parent, style, name, pos, size) createCEobject<CEGUI::PushButton>(parent, style, name, pos, size)
#define CreateCEEditbox(parent, style, name, pos, size) createCEobject<CEGUI::Editbox>(parent, style, name, pos, size)
#define CreateCEMultiLineEditbox(parent, style, name, pos, size) createCEobject<CEGUI::MultiLineEditbox>(parent, style, name, pos, size)
/*
class CEFrame{
public:
	CEFrame(){}
	CEFrame(CEGUI::Window* parent,CEGUI::String style, CEGUI::String name, CEGUI::UVector2 pos=ZeroUVector,CEGUI::USize size=DefaultUSize);
	virtual ~CEFrame(){}

	virtual bool handleCloseEvent(const CEGUI::EventArgs& e);

	inline CEGUI::Window* getWindow(){return m_pWnd;}
protected:
	CEGUI::FrameWindow* m_pWnd;
};

class CEPushButton{
public:
	CEPushButton(){}
	CEPushButton(CEGUI::Window* parent, CEGUI::String style, CEGUI::String name, CEGUI::UVector2 pos=ZeroUVector,CEGUI::USize size=DefaultUSize );
	virtual ~CEPushButton(){}

	virtual bool handleClickEvent(const CEGUI::EventArgs& e){return true;} 

	inline CEGUI::PushButton* getButton(){return m_pButton;}
protected:
	CEGUI::PushButton* m_pButton;
};


//just a example inheritance
class CETestButton : public CEPushButton{
public:
	CETestButton(CEGUI::Window* parent, CEGUI::String style, CEGUI::String name, CEGUI::UVector2 pos=ZeroUVector,CEGUI::USize size=DefaultUSize );
	virtual ~CETestButton(){}

	virtual bool handleClickEvent(const CEGUI::EventArgs& e);
};
//example above
*/
extern CEGUIHelper* g_GUI;

#endif