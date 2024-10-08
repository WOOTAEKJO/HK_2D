﻿// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include<cstdlib> //rand(), srand()
#include<ctime> //time()

#include <ole2.h>
#pragma comment(lib, "gdiplus.lib") //gdiplus라이브러리
#include <gdiplus.h> //gdiplus사용을 위한 헤더

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")



#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

#include <io.h>
// 사운드 f모드

#include "define.h"

using namespace std;

