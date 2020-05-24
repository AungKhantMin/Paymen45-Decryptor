#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include <sstream>
#include <iostream>



class MemExtractor
{
public:
	static std::vector<std::string> GetKeyInitialStateMatrix(DWORD pid);
	static LPVOID GetKey(std::vector<std::string> keymatrix);
protected:
};

