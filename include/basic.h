#ifndef BASIC_H
#define BASIC_H
#include <stdint.h>


#define HZ_CHECK_MEMORY_LEAKS


#ifdef HZ_CHECK_MEMORY_LEAKS
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif // HZ_CHECK_MEMORY_LEAKS

#define _VARIADIC_MAX 10

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

enum class MsgType {
	kText = 0,
	kInit = 1,
	kResponse = 2,
	kRequest = 3,

	kError = 255,
};

#define DISALLOW_COPY_AND_ASSIGN(Type) \
    Type(const Type&) = delete; \
    void operator=(const Type&) = delete

#endif // BASIC_H
