#pragma once
#include "PathNode.h"
class HeapCompare
{
public:
	HeapCompare(void);
public:
	bool operator() ( const PathNode* x, const PathNode* y ) const;
	~HeapCompare(void);
};

