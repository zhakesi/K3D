#pragma once

#define KLIB_EXPORT _declspec(dllexport)
#define KInterface class

enum 
{
	KR_INVALID = -1,
	KR_FAILED = 0,
	KR_SUCCESS = 1,
};
