
#ifndef SRC_MOT_ANIMATEDSPRITE_H_
#define SRC_MOT_ANIMATEDSPRITE_H_

#include "Sprite.h"
#include "Vector2d.h"
#include "Rectangle.h"

#include <map>
#include <vector>

class AnimatedSprite : public Sprite
{

protected:
	std::map<int, std::vector<Rectangle> > _subRectangles;
	Vector2d _actualSubRect;
	std::map<int, int >  _framePerSecs;
	double _tempo;


public:
	AnimatedSprite();
	AnimatedSprite(std::string texturePath);
	AnimatedSprite(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize);

	virtual ~AnimatedSprite();


	void addSubRect(int animationId, Rectangle subRect);
	void setFramePerSecs(int animationId, int framePerSecs);

	void setAnimation(int animationId);

protected:
    virtual int update(double seconds);
    virtual int draw(Vector2d pos = Vector2d(), double scale = 1);

};

#endif
