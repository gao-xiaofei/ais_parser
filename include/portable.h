
#ifndef _AIS_PORTABLE_H_
#define _AIS_PORTABLE_H_

#ifndef _WIN32
#ifndef __cygwin__
#define __cdecl    /* nothing */
#define __stdcall  /* nothing */
#define __fastcall /* nothing */
#endif             /* __cygwin__ */
#endif             /* _WIN32 */

#endif
