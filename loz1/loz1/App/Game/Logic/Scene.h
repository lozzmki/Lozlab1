#ifndef SCENE_H
#define SCENE_H


typedef int MapCell;
typedef int MapTile;

//游戏地图，一个Tile 32*32大小
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
//寻路用逻辑地图，Cell值代表有几个barrier堆在上面
class LogicMap{

};

//游戏场景
class Scene{

public:
	Scene(){}
	virtual ~Scene();

	//void bakelogicmap()

private:

};

#endif