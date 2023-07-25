#ifndef __UNIS_TYPES_H__
#define __UNIS_TYPES_H__

#include "IntTypes.h"

#ifndef DEFINED_float32
#define DEFINED_float32
typedef float float32; 
#endif

#ifndef DEFINED_float64
#define DEFINED_float64
typedef double float64; 
#endif

#ifndef UNIS_GENERAL_TYPES_GUARD
#define UNIS_GENERAL_TYPES_GUARD

#ifndef DEFINED_BOOL
#define DEFINED_BOOL
typedef int32_t						BOOL;
#endif

typedef struct Rect
{
	int32_t left;
	int32_t top;
	int32_t right;
	int32_t bottom;
} Rect;

typedef struct Point
{
	int32_t x;
	int32_t y;
} Point;

typedef struct Size
{
	int32_t w;
	int32_t h;
} Size;

typedef struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} Color;

typedef struct Polygon
{
	uint32_t	pointNumber; 
	Point*		points;		 
}Polygon;
#endif 

#ifndef DAHUA2_GENERAL_TYPES_GUARD
#define DAHUA2_GENERAL_TYPES_GUARD

#ifndef _DEFINED_BYTE
#define _DEFINED_BYTE
typedef uint8_t		BYTE;
#endif

#ifndef _DEFINED_HANDLE
#define _DEFINED_HANDLE
typedef void *					HANDLE;
#endif

#ifndef DEFINED_HDC
#define DEFINED_HDC
typedef void *					HDC;
#endif

#endif	

#ifndef DEFINED_CPCHAR
#define DEFINED_CPCHAR
typedef const char *            CPCHAR;
#endif

#ifndef DEFINED_PCHAR
#define DEFINED_PCHAR
typedef char *                  PCHAR;
#endif

#ifndef DEFINED_CHAR
#define DEFINED_CHAR
typedef char                    CHAR;
#endif

#ifndef DEFINED_Float32
#define DEFINED_Float32
    
    typedef float Float32;                          
#endif

#ifndef DEFINED_Float64
#define DEFINED_Float64
    typedef double Float64;                         
#endif

#ifndef DEFINED_Handle
#define DEFINED_Handle
    
    typedef void *Handle;                           
#endif


#ifndef DEFINED_DWORD
#define DEFINED_DWORD
typedef unsigned int			DWORD;
#endif

#ifndef DEFINED_PARAM
#define DEFINED_PARAM
typedef unsigned int			PARAM;
#endif

#ifndef DEFINED_BOOL
#define DEFINED_BOOL
typedef int						BOOL;
#endif

#ifndef DEFINED_uint32
#define DEFINED_uint32
typedef unsigned int			uint32;
#endif

#ifndef DEFINED_schar
#define DEFINED_schar
typedef signed char				schar;	
#endif

typedef unsigned char			uchar;	

#ifndef DEFINED_uint
#define DEFINED_uint
typedef unsigned int			uint;	
#endif

#ifndef DEFINED_ushort
#define DEFINED_ushort
typedef unsigned short			ushort;	
#endif

#ifndef DEFINED_ulong
#define DEFINED_ulong
typedef unsigned long			ulong;	
#endif

typedef unsigned long			uint64;

#ifndef UNIS_SYSTEM_TIME_GUARD
#define UNIS_SYSTEM_TIME_GUARD
typedef struct SYSTEM_TIME{
	int32_t  year;			
	int32_t  month;			
	int32_t  day;			
	int32_t  wday;			
	int32_t  hour;			
	int32_t  minute;		
	int32_t  second;		
	int32_t  isdst;			
}SYSTEM_TIME;
#endif

#endif
