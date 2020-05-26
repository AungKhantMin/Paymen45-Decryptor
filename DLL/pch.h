// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.
#pragma once
#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#include "cryptlib.h"
#include "secblock.h"
#include "filters.h"
#include "salsa.h"
#include "osrng.h"
#include "files.h"
#include "hex.h"


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


#endif //PCH_H
