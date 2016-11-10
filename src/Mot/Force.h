
#ifndef SRC_MOT_FORCE_H_
#define SRC_MOT_FORCE_H_

#include "WorldElement.h"
#include <vector>
#include "Vector2d.h"

class Force
{

protected:
	std::vector<WorldElement*> _worldElements;

public:
	Force();
	virtual ~Force();

	virtual Vector2d calculateAccelToAdd(WorldElement* we) = 0;
	void apply();

	void addWorldElement(WorldElement* we);
	void removeWorldElement(WorldElement* we);
	void emptyWorldElementList();
};

#endif
