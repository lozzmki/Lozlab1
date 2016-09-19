#ifndef GAME_H
#define GAME_H

class GameObjectManager;

//游戏主体类
class Game{
public:
	Game();
	virtual ~Game();



protected:
	GameObjectManager* m_pManager;
};

#endif