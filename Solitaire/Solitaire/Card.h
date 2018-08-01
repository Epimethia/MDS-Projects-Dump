#pragma once

#include "Sprite.h"
class CCard {
public:
	CCard();
	~CCard();
private:
	int iCardIndex;
	CSprite* CardSprite;
};

