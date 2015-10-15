#ifndef misc_types_hpp
#define misc_types_hpp

#include <stdint.h>
#include <sys/types.h>


//typedef unsigned char u8; typedef signed char s8;
//typedef unsigned short u16; typedef signed short s16;
//typedef unsigned int u32; typedef signed int s32;
//typedef unsigned long long u64; typedef signed long long s64;

typedef uint8_t u8; typedef int8_t s8;
typedef uint16_t u16; typedef int16_t s16;
typedef uint32_t u32; typedef int32_t s32;
typedef uint64_t u64; typedef int64_t s64;
//typedef u32 uint;


typedef volatile u8 vu8; typedef volatile s8 vs8;
typedef volatile u16 vu16; typedef volatile s16 vs16;
typedef volatile u32 vu32; typedef volatile s32 vs32;
typedef volatile u64 vu64; typedef volatile s64 vs64;
//typedef vu32 vuint;



// I'm not sure what to call these :/
union byte_group_16
{
	u16 data16;
	
	struct
	{
		u8 data8 [2];
	};
};

union byte_group_32
{
	u32 data32;
	
	struct
	{
		u16 data16 [2];
	};
	
	struct
	{
		u8 data8 [4];
	};
};

union byte_group_64
{
	u64 data64;
	
	struct
	{
		u32 data32 [2];
	};
	
	struct
	{
		u16 data16 [4];
	};
	
	struct
	{
		u8 data8 [8];
	};
};


#endif		// misc_types_hpp
