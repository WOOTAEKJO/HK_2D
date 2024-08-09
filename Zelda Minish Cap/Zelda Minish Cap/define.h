#pragma once

#define		WINCX		1920
#define		WINCY		1080

#define		WINCXHALF	float(WINCX/2)
#define		WINCYHALF	float(WINCY/2)

#define		BACKCX		9448
#define		BACKCY		2160

#define		GROUNDCX	9448
#define		GROUNDCY	2160

#define		GROUNDCX2	7998
#define		GROUNDCY2	2160

#define		STAGE1X		9448.f
#define		STAGE1Y		2160.f

#define		STAGE2X		4519.f
#define		STAGE2Y		2600.f

#define		STAGE3X		3793.f
#define		STAGE3Y		2200.f

#define		STAGE4X		7998.f
#define		STAGE4Y		2160.f

#define		STAGE5X		3725.f
#define		STAGE5Y		1700.f

#define		STAGE6X		1958.f
#define		STAGE6Y		3000.f

#define		PURE		= 0
#define		PI			3.141592f
#define		G			9.8f

#define		OBJ_DEAD	 1
#define		OBJ_NOEVENT	 0

#define		VK_MAX		0xff

#define		TILEX		148		//타일 가로 갯수
#define		TILEY		34		//타일 세로 갯수

#define		TILECX		64		// 타일 가로 크기
#define		TILECY		64		//타일 세로 크기

#define		TURNLEFT	1
#define		TURNRIGHT	0

#define		ATTACKRANGE	1
#define		COLLIDER	0

struct fPOINT
{
	float x;
	float y;
	fPOINT() {}
	fPOINT(float x, float y) :x(x), y(y) {}
};

typedef struct tagInfo
{
	float	fX;		// 중점 X
	float	fY;		// 중점 Y
	float	fCX;	// 가로 길이
	float	fCY;	// 세로 길이	

	float	fPrevX = 0.f;	// 이전 X
	float	fPrevY = 0.f;	// 이전 Y
	float	fRatioX = 1.f;	// 비율 X
	float	fRatioY = 1.f;	// 비율 Y
}INFO, POINT_RECT;

enum DIRECTION { LEFT, RIGHT, UP, DOWN, DIR_END };

enum OBJID { PLAYER, PMELEE,PBULLET, MMELEE, MBULLET, MBULLET2, MONSTER,NPC,STRUCT, MOUSE, SHIELD, BUTTON,PUI, PEFFECT,PWALL,PORTAL, OBJID_END };

enum RENDERID { BACKGROUND, BACKGROUND2, GAMEOBJECT, EFFECT, UI,UI2, RENDER_END };

enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE1, SC_STAGE2,SC_STAGE3, SC_STAGE4,
				SC_STAGE5, SC_STAGE6, SC_STAGE7,SC_END };

enum STAGEID {STAGE1, STAGE2,STAGE3,STAGE4, STAGE5, STAGE6, STAGE7, STAGEID_END};

enum LINEID { WALLLINE, GROUNDLINE, LINE_END };

enum TILEOPTION {NON,WALL,GROUND,TILEOPTION_END};

enum CHANNELID { SOUND_EFFECT,PLAYER_EFFECT,PLAYER_SWORD,WALLSOUND,MONSTER_EFFECT, MONSTER_EFFECT2,
	BOSS_ATTACK1,BOSS_RUN,BOSS_HIT,
	BOSS_ATTACK2,BOSS_VOICE, BOSS_VOICE2,STRUCTSOUND,BSTRUCTSOUND,NPC_SOUND, SOUND_BGM, MAXCHANNEL };

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

class CDeleteObj
{
public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};
class CDeleteMap
{
public:
	template<typename T>
	void operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};

class CTag_Finder
{
public:
	CTag_Finder(const TCHAR* pString) : m_pString(pString) {}
	CTag_Finder(STAGEID _StageID): m_pStageID(_StageID){}
public:
	template<typename T>
	bool operator()(T& Pair)
	{
		return !lstrcmp(m_pString, Pair.first);
	}

private:
	const TCHAR* m_pString;
	STAGEID m_pStageID;
};

typedef struct tagFrame
{
	int			iFrameStart;
	int			iFrameEnd;
	int			iMotion;
	DIRECTION			iDirection;

	DWORD		dwSpeed;
	DWORD		dwTime;

}FRAME;

/******************************LINE******************************/
// Line용 float Point
typedef	struct tagLinePoint
{
	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

	float	fX;
	float	fY;

}LINEPOINT;

//Line 구조체 (왼쪽 점, 오른쪽 점)
typedef struct tagLine
{
	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLpoint, LINEPOINT& _tRpoint, LINEID _LineID)
		: tLpoint(_tLpoint), tRpoint(_tRpoint), m_LineID(_LineID) { }

	LINEPOINT	tLpoint;
	LINEPOINT	tRpoint;

	//const char* m_LineName;
	LINEID		m_LineID;

}LINE;

extern HWND g_hWnd;