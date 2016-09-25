#ifndef SCENE_H
#define SCENE_H


typedef int MapCell;
typedef int MapTile;

//��Ϸ��ͼ��һ��Tile 32*32��С
class SceneMap{

public:
	SceneMap():d_tiles(0),d_nWidth(0),d_nHeight(0){}
	SceneMap(unsigned int width,unsigned int height):d_nHeight(height),d_nWidth(width){
		d_tiles = new MapTile[width*height];
	}
	MapTile getTile(int x, int y);

	//bool loadMap(file)
private:
	int d_nWidth, d_nHeight;
	MapTile* d_tiles;
};
//Ѱ·���߼���ͼ��Cellֵ�����м���barrier��������
class LogicMap{

};

//��Ϸ����
class Scene{

public:
	Scene(){}
	virtual ~Scene();

	//void bakelogicmap()

private:

};

#endif