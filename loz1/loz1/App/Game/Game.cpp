#include"Game.h"
#include"UI\GameConsole.h"
#include"Logic\BaseGameLogic.h"

Game::Game(){
	//initial everything
	m_pManager = new GameObjectManager();
}
Game::~Game(){
	//clean up everything
}

void Game::update(double deltaTime){
	//render scene here
	//bake map here too
	m_pManager->checkCollision();
	m_pManager->updateAll(deltaTime);
	m_pManager->renderAll();
}

void Game::render(){

}