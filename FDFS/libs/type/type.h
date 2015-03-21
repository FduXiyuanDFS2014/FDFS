#ifndef __TYPE_H__
#define __TYPE_H__	1

#if defined __x86_64__ && !defined __ILP32__
#	define __WORDSIZE	64
#else
#	define __WORDSIZE	32
#endif

#ifdef __x86_64__
#	define __WORDSIZE_TIME64_COMPAT32	1
#	define __SYSCALL_WORDSIZE			64
#endif

typedef unsigned char __uchar;
typedef unsigned short int __ushort;
typedef unsigned int __uint;
typedef unsigned long int __ulong;

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

#if __WORDSIZE == 64
	typedef signed long int __int64_t;
	typedef unsigned long int __uint64_t;
#else
	__extension__ typedef signed long long int __int64_t;
	__extension__ typedef unsigned long long int __uint64_t;
#endif

#if __WORDSIZE == 64
	typedef long int __quad_t;
	typedef unsigned long int __u_quad_t;
#else
	__extension__ typedef long long int __quad_t;
	__extension__ typedef unsigned long long int __u_quad_t;
#endif

#endif
