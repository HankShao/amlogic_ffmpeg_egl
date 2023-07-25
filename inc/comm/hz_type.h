
#ifndef __BASIC_H__
#define __BASIC_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef signed short        int16_t;
typedef unsigned short      uint16_t;
typedef signed  int			int32_t;
typedef long int            int64_t;
typedef unsigned int        uint32_t;
typedef unsigned  long      uint64_t;

typedef  char               Int8;
typedef unsigned char       Uint8;
typedef signed short        Int16;
typedef unsigned short      Uint16;
typedef signed  int         Int32;
typedef long long           Int64;
typedef unsigned int        Uint32;
typedef unsigned long long  Uint64;



#define HZ_SUCCESS 0
#define HZ_FAILURE -1

#define INVALID_FD -2
#define FD_INVALID(fd) ( INVALID_FD == fd)

#define IS_FAILURE(iRet) (HZ_SUCCESS != iRet)

#define IA_UNUSED_ARG(x)                   ((VOID) x)

#define PUB_MAX_FILE_NAME_LEN 108
#define PUB_MAX_MD5SUM_LEN 24

#define HZ_DEBUG		4
#define HZ_INFO		    3
#define HZ_ERR		    2
#define HZ_FATAL		1
#define HZ_LOG_LEVEL  	2
#define HZ_PRINT(level, s, params...) do{ if(level <= HZ_LOG_LEVEL)\
	printf("[%s, %d]: " s "\n", __FUNCTION__, __LINE__, ##params);\
}while(0)

#define IA_PRINT(fmt...)   \
do {\
    printf("[%s]-%d: ", __FUNCTION__, __LINE__);\
    printf(fmt);\
}while(0)

#define IA_ASSERT(expr) 			  \
   do{									 \
	   if (!(expr)) {					 \
		   printf("\nASSERT failed at:\n"\
				  "  >File name: %s\n"	 \
				  "  >Function : %s\n"	 \
				  "  >Line No. : %d\n"	 \
				  "  >Condition: %s\n",  \
				   __FILE__,__FUNCTION__, __LINE__, #expr);\
		   _exit(-1);\
	   } \
   }while(0)


typedef void * HANDLE;  

typedef enum tagHZ_BOOL
{
    HZ_BOOL_FALSE = 0,
    HZ_BOOL_TRUE,
}HZ_BOOL_E;




#ifdef __cplusplus
}
#endif

#endif
