


#ifndef __INFRA3_INT_TYPES_H__
#define __INFRA3_INT_TYPES_H__






#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#     define DAHUA_HAS_STDINT_H

#elif (defined(__GNUC__) && (__GNUC__ >= 3)) || defined(__HP_aCC)
#  define DAHUA_HAS_STDINT_H





#elif defined(__GLIBC__) && ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 1)))
   
   
   
#  if defined __GNUC__
#    define DAHUA_HAS_STDINT_H
#  endif

#elif defined(__MINGW32__) && ((__MINGW32_MAJOR_VERSION > 2) || ((__MINGW32_MAJOR_VERSION == 2) && (__MINGW32_MINOR_VERSION >= 0)))
#  define DAHUA_HAS_STDINT_H

#endif





#ifdef _MSC_VER

	#if (_MSC_VER >= 1200)
	#   define DAHUA_HAS_MS_INT64
	#endif
	#if (_MSC_VER >= 1310) && defined(_MSC_EXTENSIONS)
	#   define DAHUA_HAS_LONG_LONG
	#endif
	#if (_MSC_VER >= 1400) && !defined(_DEBUG)
	#   define DAHUA_HAS_NRVO
	#endif

#else
	#define DAHUA_HAS_LONG_LONG
#endif




#ifdef DAHUA_HAS_STDINT_H


# ifdef __hpux

#   include <inttypes.h>
#   ifdef __STDC_32_MODE__
      
#     define DAHUA_NO_INT64_T
#   endif
# elif defined(__FreeBSD__) || defined(__IBMCPP__)
#   include <inttypes.h>
# elif defined(__KERNEL__)
#   include <linux/types.h>
# else
#   include <stdint.h>
#   include <inttypes.h>


#   if defined(__STDC_CONSTANT_MACROS) && defined(__CYGWIN__)
#     undef INTMAX_C
#     undef UINTMAX_C
#     define INTMAX_C(c) c##LL
#     define UINTMAX_C(c) c##ULL
#   endif

# endif

#ifdef __QNX__




typedef intleast8_t int_least8_t;
typedef intfast8_t int_fast8_t;
typedef uintleast8_t uint_least8_t;
typedef uintfast8_t uint_fast8_t;

typedef intleast16_t int_least16_t;
typedef intfast16_t int_fast16_t;
typedef uintleast16_t uint_least16_t;
typedef uintfast16_t uint_fast16_t;

typedef intleast32_t int_least32_t;
typedef intfast32_t int_fast32_t;
typedef uintleast32_t uint_least32_t;
typedef uintfast32_t uint_fast32_t;

# ifndef DAHUA_NO_INT64_T

typedef intleast64_t int_least64_t;
typedef intfast64_t int_fast64_t;
typedef uintleast64_t uint_least64_t;
typedef uintfast64_t uint_fast64_t;

# endif

#endif

#elif defined(__FreeBSD__) && (__FreeBSD__ <= 4) || defined(__osf__)

# include <inttypes.h>

#else


# include <limits.h>         











# if UCHAR_MAX == 0xff
	typedef signed char     int8_t;
	typedef signed char     int_least8_t;
	typedef signed char     int_fast8_t;
	typedef unsigned char   uint8_t;
	typedef unsigned char   uint_least8_t;
	typedef unsigned char   uint_fast8_t;
# else
#    error defaults not correct; you must hand modify boost/cstdint.hpp
# endif



# if USHRT_MAX == 0xffff
#  if defined(__crayx1)
	
	
	typedef short           int16_t;
	typedef short           int_least16_t;
	typedef int             int_fast16_t;
	typedef unsigned short  uint16_t;
	typedef unsigned short  uint_least16_t;
	typedef unsigned int    uint_fast16_t;
#  else
	typedef short           int16_t;
	typedef short           int_least16_t;
	typedef short           int_fast16_t;
	typedef unsigned short  uint16_t;
	typedef unsigned short  uint_least16_t;
	typedef unsigned short  uint_fast16_t;
#  endif
# elif (USHRT_MAX == 0xffffffff) && defined(CRAY)
	
	typedef short           int_least16_t;
	typedef short           int_fast16_t;
	typedef unsigned short  uint_least16_t;
	typedef unsigned short  uint_fast16_t;
# else
#    error defaults not correct; you must hand modify boost/cstdint.hpp
# endif



# if UINT_MAX == 0xffffffff
	typedef int             int32_t;
	typedef int             int_least32_t;
	typedef int             int_fast32_t;
	typedef unsigned int    uint32_t;
	typedef unsigned int    uint_least32_t;
	typedef unsigned int    uint_fast32_t;
# elif ULONG_MAX == 0xffffffff
	typedef long            int32_t;
	typedef long            int_least32_t;
	typedef long            int_fast32_t;
	typedef unsigned long   uint32_t;
	typedef unsigned long   uint_least32_t;
	typedef unsigned long   uint_fast32_t;
# else
#    error defaults not correct; you must hand modify boost/cstdint.hpp
# endif



# if defined(DAHUA_HAS_LONG_LONG) && \
   !defined(_MSC_VER) && !defined(__BORLANDC__) && \
   (!defined(__GLIBCPP__) || defined(_GLIBCPP_USE_LONG_LONG)) && \
   (defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX))
#    if defined(__hpux)
     
#    elif (defined(ULLONG_MAX) && ULLONG_MAX == 18446744073709551615ULL) || (defined(ULONG_LONG_MAX) && ULONG_LONG_MAX == 18446744073709551615ULL) || (defined(ULONGLONG_MAX) && ULONGLONG_MAX == 18446744073709551615ULL)
                                                                 
#    else
#       error defaults not correct; you must hand modify boost/cstdint.hpp
#    endif

	
	
	
	
	
	#  ifndef __GNUC__
		#ifndef __extension
			#define __extension__
		#endif
	#  endif

	__extension__ typedef  long long			intmax_t;
	__extension__ typedef  unsigned long long	uintmax_t;
	__extension__ typedef  long long			int64_t;
	__extension__ typedef  long long			int_least64_t;
	__extension__ typedef  long long			int_fast64_t;
	__extension__ typedef  unsigned long long	uint64_t;
	__extension__ typedef  unsigned long long	uint_least64_t;
	__extension__ typedef  unsigned long long	uint_fast64_t;

# elif ULONG_MAX != 0xffffffff

#   if ULONG_MAX == 18446744073709551615 
	typedef long                 intmax_t;
	typedef unsigned long        uintmax_t;
	typedef long                 int64_t;
	typedef long                 int_least64_t;
	typedef long                 int_fast64_t;
	typedef unsigned long        uint64_t;
	typedef unsigned long        uint_least64_t;
	typedef unsigned long        uint_fast64_t;
#   else
#      error defaults not correct; you must hand modify boost/cstdint.hpp
#   endif
# elif defined(__GNUC__) && defined(DAHUA_HAS_LONG_LONG)
	__extension__ typedef long long            intmax_t;
	__extension__ typedef unsigned long long   uintmax_t;
	__extension__ typedef long long            int64_t;
	__extension__ typedef long long            int_least64_t;
	__extension__ typedef long long            int_fast64_t;
	__extension__ typedef unsigned long long   uint64_t;
	__extension__ typedef unsigned long long   uint_least64_t;
	__extension__ typedef unsigned long long   uint_fast64_t;
# elif defined(DAHUA_HAS_MS_INT64)
	
	
	
	typedef __int64             intmax_t;
	typedef unsigned __int64    uintmax_t;
	typedef __int64             int64_t;
	typedef __int64             int_least64_t;
	typedef __int64             int_fast64_t;
	typedef unsigned __int64    uint64_t;
	typedef unsigned __int64    uint_least64_t;
	typedef unsigned __int64    uint_fast64_t;
# else 
#  define DAHUA_NO_INT64_T
	typedef int32_t              intmax_t;
	typedef uint32_t             uintmax_t;
# endif


#endif



#ifdef _MSC_VER
# if (_MSC_VER <= 1400)
	#define PRIi64 "I64i"
	#define PRIu64 "I64u"
	#define PRIo64 "I64o"
	#define PRIx64 "I64x"

		typedef int ssize_t;
#  if (_MSC_VER <= 1200)
	    typedef int intptr_t;
	    typedef unsigned int uintptr_t;
#  endif
# endif
#endif 

#endif

