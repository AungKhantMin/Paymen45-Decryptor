#pragma once
#include <Windows.h>

class Decryptor
{
private:
	static byte* key;
	byte iv[8];
public:
	void RecursiveDecrypt();
	void setIV(byte iv[8]);
	~Decryptor();
};

