#pragma once

#define		WINCX		1900
#define		WINCY		1200

#define		PURE		= 0
#define		PI			3.141592f

#define		BACKCX		9448
#define		BACKCY		3160

#define		GROUNDCX	9448
#define		GROUNDCY	2160

#define		GROUNDCX2	7998
#define		GROUNDCY2	2160

#define		OBJ_DEAD	 1
#define		OBJ_NOEVENT	 0

#define		VK_MAX		0xff

typedef struct tagInfo
{
	float	fX;		// 중점 X
	float	fY;		// 중점 Y
	float	fCX;	// 가로 길이
	float	fCY;	// 세로 길이	

}INFO;

enum DIRECTION { LEFT, RIGHT, UP, DOWN, DIR_END };

enum OBJID { PLAYER, BULLET, MONSTER, MOUSE, SHIELD, OBJID_END };

enum LINEID {WALLLINE, GROUNDLINE, LINE_END};

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



typedef	struct tagLinePoint
{
	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

	float	fX;
	float	fY;

}LINEPOINT;

typedef struct tagLine
{
	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLpoint, LINEPOINT& _tRpoint, LINEID _LineID)
		: tLpoint(_tLpoint), tRpoint(_tRpoint),m_LineID(_LineID) { }

	LINEPOINT	tLpoint;
	LINEPOINT	tRpoint;

	//const char* m_LineName;
	LINEID		m_LineID;

}LINE;

class CTag_Finder
{
public:
	CTag_Finder(const TCHAR* pString) : m_pString(pString) {}
public:
	template<typename T>
	bool operator()(T& Pair)
	{
		return !lstrcmp(m_pString, Pair.first);
	}

private:
	const TCHAR* m_pString;
};
extern HWND g_hWnd;