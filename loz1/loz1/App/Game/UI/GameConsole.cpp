#include "GameConsole.h"
#include "../../Utilities/Common.h"
#include "../../Engine/ThirdParty/CEGUI/CEGUIHelper.h"
#include "../../Utilities/Transfers.h"

GameConsole* g_pConsole = 0;

const std::string GameConsole::endl = "\n";

GameConsole::GameConsole(){
	
	CEGUI::FrameWindow* pFrame=0;
	CEGUI::MultiLineEditbox* pScreen=0;
	CEGUI::Editbox* pCmdline=0;

	pFrame = CreateCEFrame(0,"WindowsLook/FrameWindow","GameConsole",CEGUI::UVector2(cegui_reldim(0.2),cegui_reldim(0.2)),CEGUI::USize(cegui_reldim(0.6),cegui_reldim(0.6)));
	pScreen = CreateCEMultiLineEditbox(pFrame,"TaharezLook/MultiLineEditbox","ConsoleScreen",CEGUI::UVector2(cegui_reldim(0.05),cegui_reldim(0.05)),CEGUI::USize(cegui_reldim(0.9),cegui_reldim(0.7)));
	pCmdline = CreateCEEditbox(pFrame,"TaharezLook/Editbox","ConsoleCmdline",CEGUI::UVector2(cegui_reldim(0.05),cegui_reldim(0.8)),CEGUI::USize(cegui_reldim(0.9),cegui_reldim(0.1)));

	pScreen->setReadOnly(true);
	

	pCmdline->subscribeEvent(CEGUI::Editbox::EventTextAccepted, CEGUI::Event::Subscriber(&GameConsole::handleCmdInput,this));
}

GameConsole::~GameConsole(){}

bool GameConsole::handleCmdInput(const CEGUI::EventArgs& e){

	CEGUI::MultiLineEditbox* pScreen = static_cast<CEGUI::MultiLineEditbox*>(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("GameConsole/ConsoleScreen"));
	CEGUI::Editbox* pCmdline = static_cast<CEGUI::Editbox*>(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("GameConsole/ConsoleCmdline"));
	
	//parse here
	std::string msg = pCmdline->getText().c_str();

	g_Console<<msg<<endl;
	//default output to screen
	//static int x=0;
	//pScreen->appendText(Transfer::i2s(x++) + " : ");
	//pScreen->appendText(pCmdline->getText()+"\n");
	pCmdline->setText("");

	return true;
}

GameConsole& GameConsole::operator<<(std::string msg){
	CEGUI::MultiLineEditbox* pScreen = static_cast<CEGUI::MultiLineEditbox*>(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("GameConsole/ConsoleScreen"));
	pScreen->appendText(msg);
	return *this;
}
GameConsole& GameConsole::operator<<(int i){
	CEGUI::MultiLineEditbox* pScreen = static_cast<CEGUI::MultiLineEditbox*>(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("GameConsole/ConsoleScreen"));
	pScreen->appendText(Transfer::i2s(i));
	return *this;
}
GameConsole& GameConsole::operator<<(double d){
	CEGUI::MultiLineEditbox* pScreen = static_cast<CEGUI::MultiLineEditbox*>(CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("GameConsole/ConsoleScreen"));
	pScreen->appendText(Transfer::d2s(d));
	return *this;
}