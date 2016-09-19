#include "GameConsole.h"
#include "../../Utilities/Common.h"
#include "../../Engine/ThirdParty/CEGUI/CEGUIHelper.h"
#include "../../Utilities/Transfers.h"

GameConsole* g_pConsole = 0;

const GameConsole::ConsoleManipulaor GameConsole::out={101};

GameConsole::GameConsole(){
	
	CEGUI::FrameWindow* pFrame=0;
	CEGUI::MultiLineEditbox* pScreen=0;
	CEGUI::Editbox* pCmdline=0;

	pFrame = CreateCEFrame(0,"WindowsLook/FrameWindow","GameConsole",CEGUI::UVector2(cegui_reldim(0.2),cegui_reldim(0.2)),CEGUI::USize(cegui_reldim(0.6),cegui_reldim(0.6)));
	pScreen = CreateCEMultiLineEditbox(pFrame,"TaharezLook/MultiLineEditbox","ConsoleScreen",CEGUI::UVector2(cegui_reldim(0.05),cegui_reldim(0.05)),CEGUI::USize(cegui_reldim(0.9),cegui_reldim(0.8)));
	pCmdline = CreateCEEditbox(pFrame,"TaharezLook/Editbox","ConsoleCmdline",CEGUI::UVector2(cegui_reldim(0.05),cegui_reldim(0.9)),CEGUI::USize(cegui_reldim(0.9),cegui_reldim(0.05)));

	pScreen->setReadOnly(true);
	
	pFrame->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&GameConsole::handleHideEvent,this));
	pCmdline->subscribeEvent(CEGUI::Editbox::EventTextAccepted, CEGUI::Event::Subscriber(&GameConsole::handleCmdInput,this));
}

GameConsole::~GameConsole(){}

bool GameConsole::handleCmdInput(const CEGUI::EventArgs& e){

	CEGUI::MultiLineEditbox* pScreen = static_cast<CEGUI::MultiLineEditbox*>(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("GameConsole/ConsoleScreen"));
	CEGUI::Editbox* pCmdline = static_cast<CEGUI::Editbox*>(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("GameConsole/ConsoleCmdline"));
	
	//parse here
	std::string msg = pCmdline->getText().c_str();

	//test code
	static int x=0;
	g_Console<<x++<<" "<<msg<<out;
	//test end

	pCmdline->setText("");

	return true;
}
bool GameConsole::handleHideEvent(const CEGUI::EventArgs&){
	CEGUI::FrameWindow* pFrame = static_cast<CEGUI::FrameWindow*>(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("GameConsole"));
	pFrame->setVisible(false);
	return true;
}
void GameConsole::updateScroll(){
	CEGUI::MultiLineEditbox* pScreen = static_cast<CEGUI::MultiLineEditbox*>(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("GameConsole/ConsoleScreen"));
	CEGUI::Scrollbar* pScroll = pScreen->getVertScrollbar();
	float scrollpos = pScroll->getDocumentSize()-pScroll->getPageSize();
	if(scrollpos<0.0) scrollpos=0.0;
	pScroll->setScrollPosition(scrollpos);
}

void GameConsole::showConsole(){
	CEGUI::FrameWindow* pFrame = static_cast<CEGUI::FrameWindow*>(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("GameConsole"));
	pFrame->setVisible(true);
}

GameConsole& GameConsole::operator<<(std::string msg){
	m_obuffer+=msg;
	return *this;
}
GameConsole& GameConsole::operator<<(int i){
	m_obuffer+=Transfer::i2s(i);
	return *this;
}
GameConsole& GameConsole::operator<<(double d){
	m_obuffer+=Transfer::d2s(d);
	return *this;
}
GameConsole& GameConsole::operator<<(GameConsole::ConsoleManipulaor manipulator){
	CEGUI::MultiLineEditbox* pScreen = static_cast<CEGUI::MultiLineEditbox*>(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("GameConsole/ConsoleScreen"));
	switch (manipulator.code)
	{
	case 101://endl
		pScreen->appendText(m_obuffer);
		updateScroll();
		flush();
		break;
	default:
		break;
	}
	return *this;
}