typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t b32;
typedef float r32;
typedef double r64;
typedef intptr_t intptr;
typedef uintptr_t uintptr;
typedef unsigned char uchar;


union DateTime
{
	struct {
		s32 year;
		s32 month;
		s32 day;
		s32 hour;
		s32 minute;
	};
};