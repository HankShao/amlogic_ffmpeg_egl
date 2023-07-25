#ifndef __MODULE_VERSION_H__
#define __MODULE_VERSION_H__

#define API_VERSION_SET(version, reserve, magic) \
        ((((version) & 0xFFFF) << 16U) | (((reserve) & 0xFF) << 8U) |  ((magic) & 0xFF))

typedef enum API_VERSION_RET_E
{
    API_VERSION_RET_SUCCESS = 0,    
	API_VERSION_RET_NOT_IMPLET = -1,
	API_VERSION_RET_ERROR = -2,     
}API_VERSION_RET_E;

#endif
