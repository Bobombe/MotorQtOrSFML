
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

	} else if (_subRectangles.find(animationId) == _subRectangles.end()) {
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


void AnimatedSprite::setAnimation(int animationId)
{
	if (_subRectangles.find(animationId) != _subRectangles.end()) {
		_actualSubRect.x = animationId;
		_actualSubRect.y = 0;
		_tempo = (1./_framePerSecs[_actualSubRect.x]) +1;
	}
}


int AnimatedSprite::update(double seconds)
{
	int framePerSec = _framePerSecs[_actualSubRect.x];
	int animSize = _subRectangles[_actualSubRect.x].size();
	if (framePerSec > 0 && animSize > 0) {
		_tempo+=seconds;

	}
	return 0;
}

int AnimatedSprite::draw(Vector2d pos, float scale)
{
    if (_tempo > (1./_framePerSecs[_actualSubRect.x])) {
        _actualSubRect.y++;
        if (_actualSubRect.y>=_subRectangles[_actualSubRect.x].size()) {
            _actualSubRect.y = 0;
        }
        _tempo = 0;
        setSubRect(_subRectangles[_actualSubRect.x][_actualSubRect.y].pos(),
                _subRectangles[_actualSubRect.x][_actualSubRect.y].size());
    }
    return Sprite::draw(pos, scale);
}
