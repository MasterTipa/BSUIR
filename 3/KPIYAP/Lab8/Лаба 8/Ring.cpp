#include "Ring.h"

ostream& operator<<(ostream& out, const Node& node)
{
	out << node.data;
	return out;
}

ostream& operator<<(ostream& out, const Iterator& it)
{
	out << it.node;
	return out;
}