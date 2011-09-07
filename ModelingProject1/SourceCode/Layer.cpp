#include "Layer.h"


Layer::Layer(std::string name, int widthLayer, int heightLayer)
{
	nameLayer = name;
	widthLevelLayer = widthLayer;
	heightLevelLayer = heightLayer;

	layerMap.resize(heightLayer);
	
	for (int i = 0; i < heightLayer; i++)
	{
		layerMap[i].resize(widthLayer);
	}
}

Layer::~Layer(void)
{
	layerMap.clear();
}
