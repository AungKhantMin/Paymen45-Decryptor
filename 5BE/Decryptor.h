#pragma once
#include "cryptlib.h"
#include "secblock.h"
#include "filters.h"
#include "salsa.h"
#include "osrng.h"
#include "files.h"
#include "hex.h"

#include <Windows.h>
#include <string>

using namespace CryptoPP;

#define RB 0xC0
#define GB 0xA0
class Decryptor;

typedef struct {
	std::string absFilePath;
	Decryptor *dec;
}decrypt_;

class Decryptor
{
public:
	static byte* key ;
	void RecursiveSearch(std::string);
	static void DecryptFile(decrypt_ dec_args);
	static void printMsg(BOOL, LPCSTR);
	~Decryptor();

};




