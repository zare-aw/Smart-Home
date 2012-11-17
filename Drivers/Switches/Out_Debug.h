#ifndef _Out_Debug_h
#define _Out_Debug_h

#define _OUT_INFO
#define _OUT_DEBUG


#ifdef _OUT_INFO
#define OUT_INFO(a) a
#else
#define OUT_INFO(a)
#endif

#ifdef _OUT_DEBUG
#define OUT_DEBUG(a) a
#else
#define OUT_DEBUG(a)
#endif

#endif
