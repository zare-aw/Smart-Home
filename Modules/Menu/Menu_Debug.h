#ifndef _Menu_Debug_h
#define _Menu_Debug_h

#define _MENU_INFO             1
#define _MENU_DEBUG            1
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

#ifdef _MENU_LOW_LEVEL_DEBUG
#define MENU_LL_DEBUG(a) a
#else
#define MENU_LL_DEBUG(a)
#endif

#endif
