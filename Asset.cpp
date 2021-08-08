#include "Asset.h"


Asset::Asset(std::string id)
{
	// Populate: asset class methods, ensure in the constructor that you cache the provided id argument into _id.
	_id = id;
}
	
Asset::~Asset()
{
}

std::string Asset::id()
{
	return _id;
}


