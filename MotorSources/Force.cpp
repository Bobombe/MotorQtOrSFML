
#include "Force.h"

Force::Force()
{
}

Force::~Force()
{
}

void Force::apply()
{
	for (unsigned int i = 0; i<_worldElements.size(); i++) {
		_worldElements[i]->moveAcceleration(calculateAccelToAdd(_worldElements[i]));
	}
}

void Force::addWorldElement(WorldElement* we)
{
	_worldElements.push_back(we);
}

void Force::removeWorldElement(WorldElement* we)
{
	for (unsigned int i = 0; i < _worldElements.size(); i++) {
		if (_worldElements[i] == we) {
			_worldElements.erase(_worldElements.begin()+i);
			i = _worldElements.size();
		}
	}
}

void Force::emptyWorldElementList()
{
	_worldElements.clear();
}
