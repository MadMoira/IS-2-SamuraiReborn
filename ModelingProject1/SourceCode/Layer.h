#pragma once

#include <vector>
#include <string>

class Layer
{
public:
	Layer(std::string name, int widthLayer, int heightLayer);
	~Layer(void);

	std::vector< std::vector <int> > getLayerMap() { return layerMap; } ;
	void setLayerMap(std::vector< std::vector <int> > map) { layerMap = map; };

	int getWidthLevelLayer() { return widthLevelLayer; }

	int getHeightLevelLayer() { return heightLevelLayer; }

private:
	std::string nameLayer;
	std::vector< std::vector <int> > layerMap;
	int widthLevelLayer, heightLevelLayer;
};

