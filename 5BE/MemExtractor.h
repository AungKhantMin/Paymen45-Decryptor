#pragma once

#include <string>
#include <vector>
#include <Windows.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>


#include <TlHelp32.h>
#include <Psapi.h>


class MemExtractor
{
public:
	static std::vector<std::string> GetKeyInitialStateMatrix(DWORD pid);
	static LPVOID GetKey(std::vector<std::string> keymatrix);
protected:
};

