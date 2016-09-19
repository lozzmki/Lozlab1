#include"CEGUIHelper.h"
#include"../../Video/Dx.h"
#include"../../Input/GameInput.h"
#include"../../../Utilities/Common.h"


#ifdef _DEBUG
#pragma comment( lib, "CEGUIBase-0_d.lib" )
 #pragma comment( lib, "CEGUIDirect3D9Renderer-0_d.lib" )
 
#else
 #pragma comment( lib, "CEGUIBase-0.lib" )
 #pragma comment( lib, "CEGUIDirect3D9Renderer-0.lib" )
#endif

CEGUIHelper* g_GUI = 0;

CEGUI::UVector2 toUVec(Vec2f scale, Vec2f offset){
	CEGUI::UDim ux = CEGUI::UDim(scale.x, offset.x);
	CEGUI::UDim uy = CEGUI::UDim(scale.y, offset.y);
	return CEGUI::UVector2(ux, uy);
}

CEGUIHelper::CEGUIHelper(){

	//创建D3D9Renderer和System
	m_pRenderer = &(CEGUI::Direct3D9Renderer::bootstrapSystem( g_Device ));

	//设置图片解析模块setImageCodec
	//CEGUI::System::getSingleton().setImageCodec("FreeImageImageCodec");

	//set default resource path
	CEGUI::DefaultResourceProvider* resPro = static_cast<CEGUI::DefaultResourceProvider*>
       (CEGUI::System::getSingleton().getResourceProvider());
    resPro->setResourceGroupDirectory("schemes", "../datafiles/schemes/");
    resPro->setResourceGroupDirectory("imagesets", "../datafiles/imagesets/");
    resPro->setResourceGroupDirectory("fonts", "../datafiles/fonts/");
    resPro->setResourceGroupDirectory("layouts", "../datafiles/layouts/");
    resPro->setResourceGroupDirectory("looknfeels", "../datafiles/looknfeel/");
    resPro->setResourceGroupDirectory("lua_scripts", "../datafiles/lua_scripts/");
    resPro->setResourceGroupDirectory("schemas", "../datafiles/xml_schemas/");
    resPro->setResourceGroupDirectory("animations", "../datafiles/animations/");
    CEGUI::AnimationManager::setDefaultResourceGroup("animations");
    //CEGUI::Imageset::setDefaultResourceGroup("imagesets"); ---------out of date
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();

    if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
       parser->setProperty("SchemaDefaultResourceGroup", "schemas");
	//创建样式等
	CEGUI::SchemeManager::getSingleton().createFromFile( "TaharezLook.scheme" );
	CEGUI::SchemeManager::getSingleton().createFromFile( "WindowsLook.scheme" );
	CEGUI::FontManager::getSingleton().createFromFile( "DejaVuSans-10.font" );

	//设置默认字体和鼠标
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont( "DejaVuSans-10" );
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage( "TaharezLook/MouseArrow" );
	//默认tooltip(?)
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType( "TaharezLook/Tooltip" );

	//窗口管理器
	m_pWndMgr = &CEGUI::WindowManager::getSingleton();

	//默认根窗口
	m_pWnd = m_pWndMgr->createWindow( "DefaultWindow", "root" );
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow( m_pWnd );

	//新建一个窗口，放到根窗口里
	//CEGUI::FrameWindow* fWnd = static_cast<CEGUI::FrameWindow*>( m_pWndMgr->createWindow( "WindowsLook/FrameWindow", "testWindow" ));
	//m_pWnd->addChild( fWnd );

	//设置子窗口位置和大小以及标题
	//fWnd->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.25f, 0.0f ), CEGUI::UDim( 0.25f, 0.0f ) ) );
	//fWnd->setSize( CEGUI::USize( CEGUI::UDim( 0.5f, 0.0f ), CEGUI::UDim( 0.5f, 0.0f ) ) );
	//fWnd->setText("Hello World");
	
	//以上内容可以由XML文件读取来防止硬编码

}
CEGUIHelper::~CEGUIHelper(){}

void CEGUIHelper::renderGUI(){
	CEGUI::System::getSingleton().renderAllGUIContexts();
}

void CEGUIHelper::injectMouseInput(){
	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
	
	context.injectMousePosition(g_Input->m_MousePos.x, g_Input->m_MousePos.y);
	if(MOUSECLICK(LBUTTON))
		context.injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
	if(MOUSEUP(LBUTTON))
		context.injectMouseButtonUp(CEGUI::MouseButton::LeftButton);

}
void CEGUIHelper::injectKeyInput(){

	
	

	//if(e==WM_KEYDOWN)
	//	context.injectKeyDown((CEGUI::Key::Scan)key);
	//else
	//	context.injectKeyUp((CEGUI::Key::Scan)key);
}

void CEGUIHelper::injectCharEvent(char c){
	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

	context.injectChar(c);
}


/*
CEGUI::PushButton* CEGUIHelper::createPushButton(Vec2f scale, Vec2f offset){
	CEGUI::PushButton* pButton = 0;

	pButton = static_cast<CEGUI::PushButton*>( g_GUI->m_pWndMgr->createWindow("TaharezLook/Button", "button" ));
	pButton->setPosition(CEGUI::UVector2(cegui_reldim(0.81f), cegui_reldim( 0.32f)));
    pButton->setSize(CEGUI::USize(cegui_reldim(0.15f), cegui_reldim( 0.2f)));
	pButton->setText("Start");
	g_GUI->m_pWnd->addChild( pButton );

	return pButton;
}*/
/*
CEFrame::CEFrame(CEGUI::Window* parent, CEGUI::String style, CEGUI::String name, CEGUI::UVector2 pos, CEGUI::USize size){
	m_pWnd = static_cast<CEGUI::FrameWindow*> ( g_GUI->getWndMgr()->createWindow( style, name));
	m_pWnd->setPosition(pos);
	m_pWnd->setSize(size);
	if(parent)
		parent->addChild(m_pWnd);
	else
		g_GUI->getRootWnd()->addChild(m_pWnd);
	
	m_pWnd->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&CEFrame::handleCloseEvent,this));
}

//关闭按钮默认销毁窗口
bool CEFrame::handleCloseEvent(const CEGUI::EventArgs& e){
	m_pWnd->destroy();
	return true;
}


CEPushButton::CEPushButton(CEGUI::Window* parent,CEGUI::String style, CEGUI::String name, CEGUI::UVector2 pos, CEGUI::USize size){
	m_pButton = static_cast<CEGUI::PushButton*>( g_GUI->getWndMgr()->createWindow(style, name ));
	m_pButton->setPosition(pos);
	m_pButton->setSize(size);
	if(parent)
		parent->addChild(m_pButton);
	else
		g_GUI->getRootWnd()->addChild(m_pButton);
	m_pButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEPushButton::handleClickEvent,this));
}

//example inheritance
CETestButton::CETestButton(CEGUI::Window* parent,CEGUI::String style, CEGUI::String name, CEGUI::UVector2 pos, CEGUI::USize size):CEPushButton(parent,style, name, pos, size)
{}

bool CETestButton::handleClickEvent(const CEGUI::EventArgs& e){
	static CEGUI::String s= "test";
	s.append("+");
	CEFrame* frame= new CEFrame(0, "WindowsLook/FrameWindow", s, 
								CEGUI::UVector2( CEGUI::UDim( 0.25f, 0.0f ), CEGUI::UDim( 0.25f, 0.0f ) ),
								CEGUI::USize( CEGUI::UDim( 0.5f, 0.0f ), CEGUI::UDim( 0.5f, 0.0f ) )
								);
	frame->getWindow()->setText(s);
	return true;
}

*/