// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the DLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// DLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

// This class is exported from the dll

#include "pch.h"

using namespace CryptoPP;
#define RB 0x0C
#define GB 0x0A

extern "C" {
	DLL_API char* GetKeyInitialStateMatrix();
	DLL_API LPVOID  GetKey(std::vector<std::string> keymatrix);
	DLL_API BOOL  ObtainSeDebugPrivilege();
	DLL_API BOOL DecFileW(std::string absFilePath,byte*);
	DLL_API void  RecursiveSearch(std::string);
	DLL_API void printMsg(BOOL, LPCSTR);
}