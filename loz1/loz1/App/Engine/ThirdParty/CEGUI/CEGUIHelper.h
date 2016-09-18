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
	void injectInput();

	inline CEGUI::WindowManager* getWndMgr(){return m_pWndMgr;}
	inline CEGUI::Window* getRootWnd(){return m_pWnd;}

	static CEGUI::FrameWindow* createFrameWindow(CEGUI::Window* parent,CEGUI::String style, CEGUI::String name, CEGUI::UVector2 pos=ZeroUVector,CEGUI::USize size=DefaultUSize);
	static CEGUI::PushButton* createPushButton(CEGUI::Window* parent,CEGUI::String style, CEGUI::String name, CEGUI::UVector2 pos=ZeroUVector,CEGUI::USize size=DefaultUSize);

protected:
	CEGUI::Direct3D9Renderer* m_pRenderer;
	CEGUI::WindowManager* m_pWndMgr;
	CEGUI::Window* m_pWnd;
};
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