
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite() : Sprite(), _tempo(0)
{
}
AnimatedSprite::AnimatedSprite(std::string texturePath) : Sprite(texturePath), _tempo(0)
{

}

AnimatedSprite::AnimatedSprite(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize) :
		Sprite(texturePath, subRectPos, subRectSize), _tempo(0)
{
	addSubRect(0, Rectangle(subRectPos, subRectSize) );
}

AnimatedSprite::~AnimatedSprite()
{
}



void AnimatedSprite::addSubRect(int animationId, Rectangle subRect)
{
	if (_subRectangles.empty()) {

		_subRectangles[animationId] = std::vector<Rectangle>();
		_framePerSecs[animationId] = 2;
		setSubRect(subRect.pos(), subRect.size());
	}
	else if (_subRectangles.find(animationId) == _subRectangles.end()) {
		_subRectangles[animationId] = std::vector<Rectangle>();
		_framePerSecs[animationId] = 2;
	}
	_subRectangles[animationId].push_back(subRect);
}
void AnimatedSprite::setFramePerSecs(int animationId, int framePerSecs)
{
	if (_subRectangles.find(animationId) != _subRectangles.end()) {
		_framePerSecs[animationId] = framePerSecs;
	}
}

int AnimatedSprite::update(double seconds)
{
	int framePerSec = _framePerSecs[_actualSubRect.x];
	int animSize = _subRectangles[_actualSubRect.x].size();
	if (framePerSec > 0 && animSize > 1) {
		_tempo+=seconds;
		if (_tempo > (1./framePerSec)) {
			_actualSubRect.y++;
			if (_actualSubRect.y>=animSize) {
				_actualSubRect.y = 0;
			}
			_tempo = 0;
			setSubRect(_subRectangles[_actualSubRect.x][_actualSubRect.y].pos(),
					_subRectangles[_actualSubRect.x][_actualSubRect.y].size());
		}

	}
	return 0;
}
