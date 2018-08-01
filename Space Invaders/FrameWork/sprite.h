//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#if !defined(__SPRITE_H__)
#define __SPRITE_H__

// Library Includes
#include "windows.h"

// Local Includes

// Types

// Constants

// Prototypes
class CSprite {
public:
    CSprite();
    ~CSprite();

    bool Initialise(int _iResourceID, int _iMaskResourceID);
    void Draw();
    void Process(float _fDeltaTick);
    int GetWidth() const;
    int GetHeight() const;
    float GetX() const;
	float GetY() const;
    void SetXPos(float _i);
    void SetYPos(float _i);

    void TranslateRelative(float _iX, float _iY);
    void TranslateAbsolute(float _iX, float _iY);

private:
    CSprite(const CSprite& _kr);
    CSprite& operator= (const CSprite& _kr);

protected:
    //Center handle
    float m_iX;
	float m_iY;

    HBITMAP m_hSprite;
    HBITMAP m_hMask;

    BITMAP m_bitmapSprite;
    BITMAP m_bitmapMask;

    static HDC s_hSharedSpriteDC;

};

#endif    // __SPRITE_H__
