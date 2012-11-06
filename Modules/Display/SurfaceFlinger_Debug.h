#ifndef _SurfaceFlinger_Debug_h
#define _SurfaceFlinger_Debug_h

#define _SF_INFO             1
#define _SF_DEBUG            1
//#define _SF_LOW_LEVEL_DEBUG  1

#ifdef _SF_INFO
#define SF_INFO(a) a
#else
#define SF_INFO(a)
#endif

#ifdef _SF_DEBUG
#define SF_DEBUG(a) a
#else
#define SF_DEBUG(a)
#endif

#ifdef _SF_LOW_LEVEL_DEBUG
#define SF_LL_DEBUG(a) a
#else
#define SF_LL_DEBUG(a)
#endif

#endif
