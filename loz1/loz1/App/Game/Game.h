#ifndef GAME_H
#define GAME_H

class GameObjectManager;

//��Ϸ������
class Game{
public:
	Game();
	virtual ~Game();



protected:
	GameObjectManager* m_pManager;
};

#endif