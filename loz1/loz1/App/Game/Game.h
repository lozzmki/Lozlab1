#ifndef GAME_H
#define GAME_H

class GameObjectManager;

//��Ϸ������
class Game{
public:
	Game();
	virtual ~Game();

	void update(double deltaTime);
	void render();

protected:
	GameObjectManager* m_pManager;
};

#endif