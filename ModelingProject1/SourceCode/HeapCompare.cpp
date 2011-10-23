#include "HeapCompare.h"


HeapCompare::HeapCompare(void)
{
}

bool HeapCompare::operator() ( const PathNode* x, const PathNode* y ) const{
	return x->scoreFunction < y->scoreFunction;
}

HeapCompare::~HeapCompare(void)
{
}
