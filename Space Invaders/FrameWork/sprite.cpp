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

// Library Includes

// Local Includes
#include "Game.h"
#include "BackBuffer.h"
#include "utils.h"

// This include
#include "Sprite.h"

// Static Variables
HDC CSprite::s_hSharedSpriteDC = 0;

// Static Function Prototypes

// Implementation

CSprite::CSprite()
: m_iX(0)
, m_iY(0)
{
}

CSprite::~CSprite()
{
    DeleteObject(m_hSprite);
    DeleteObject(m_hMask);
}

bool
CSprite::Initialise(int _iSpriteResourceID, int _iMaskResourceID)
{
    HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();

    if (!s_hSharedSpriteDC)
    {
        s_hSharedSpriteDC = CreateCompatibleDC(NULL);
    }

    m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(_iSpriteResourceID));
    VALIDATE(m_hSprite);
    m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(_iMaskResourceID));
    VALIDATE(m_hMask);

    GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
    GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);

    return (true);
}

void
CSprite::Draw()
{
    int iW = GetWidth();
    int iH = GetHeight();

    int iX = static_cast<int>(m_iX - (iW / 2));
    int iY = static_cast<int>(m_iY - (iH / 2));

    CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

    HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

    BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCAND);

    SelectObject(s_hSharedSpriteDC, m_hSprite);

    BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCPAINT);

    SelectObject(s_hSharedSpriteDC, hOldObj);
}

void CSprite::Process(float _fDeltaTick) {

}

int
CSprite::GetWidth() const
{
    return (m_bitmapSprite.bmWidth);
}

int
CSprite::GetHeight() const
{
    return (m_bitmapSprite.bmHeight);
}

float
CSprite::GetX() const
{
    return (m_iX);
}

float 
CSprite::GetY() const
{
    return (m_iY);
}

void 
CSprite::SetXPos(float _i)
{
    m_iX = _i;
}

void 
CSprite::SetYPos(float _i)
{
    m_iY = _i;
}

void 
CSprite::TranslateRelative(float _iX, float _iY) {
    m_iX += _iX;
    m_iY += _iY;
}

void 
CSprite::TranslateAbsolute(float _iX, float _iY)
{
    m_iX = _iX;
    m_iY = _iY;
}
