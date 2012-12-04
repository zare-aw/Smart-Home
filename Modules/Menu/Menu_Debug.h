#ifndef _Menu_Debug_h
#define _Menu_Debug_h

#define _MENU_INFO             1
#define _MENU_DEBUG            1
#define _MENU_DEBUG_L1         1
#define _MENU_DEBUG_L2         1
#define _MENU_DEBUG_L3         1
//#define _MENU_LOW_LEVEL_DEBUG  1

#ifdef _MENU_INFO
#define MENU_INFO(a) a
#else
#define MENU_INFO(a)
#endif

#ifdef _MENU_DEBUG
#define MENU_DEBUG(a) a
#else
#define MENU_DEBUG(a)
#endif

#ifdef _MENU_DEBUG_L1
#define MENU_DEBUG_L1(a) a
#else
#define MENU_DEBUG_L1(a)
#endif

#ifdef _MENU_DEBUG_L2
#define MENU_DEBUG_L2(a) a
#else
#define MENU_DEBUG_L2(a)
#endif

#ifdef _MENU_DEBUG_L3
#define MENU_DEBUG_L3(a) a
#else
#define MENU_DEBUG_L3(a)
#endif

#ifdef _MENU_LOW_LEVEL_DEBUG
#define MENU_LL_DEBUG(a) a
#else
#define MENU_LL_DEBUG(a)
#endif

#endif
