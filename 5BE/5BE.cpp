#pragma once

#include "cryptlib.h"
#include "secblock.h"
#include "filters.h"
#include "salsa.h"
#include "osrng.h"
#include "files.h"
#include "hex.h"
#include "MemExtractor.h"


#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
//".g8R4rqWIp9"


int main()
{
    using namespace CryptoPP;

    DWORD pid = 1100;
    std::vector<std::string> keymatrix = MemExtractor::GetKeyInitialStateMatrix(pid);
    byte* key_t = (byte*)MemExtractor::GetKey(keymatrix);

    
    byte iv[8] = { 0x45,0x34,0x32,0x12,0x33,0x55,0x66 };

    HexEncoder encoder(new FileSink(std::cout));

    AlgorithmParameters params = MakeParameters("Rounds", 8)
    ("IV", ConstByteArrayParameter(iv, 8,0));
    Salsa20::Decryption salsa;
    Salsa20::Encryption enc;
    salsa.SetKey(key_t, 32, params);
    enc.SetKey(key_t, 32, params);
    std::string plain("Salsa20 stream cipher test"), cipher, recover;
    StringSource ss1(plain, true, new StreamTransformationFilter(enc, new StringSink(cipher)));
    StringSource ss2(cipher, true, new StreamTransformationFilter(salsa, new StringSink(recover)));
    std::cout << "Plain: " << plain << std::endl;

    std::cout << "Cipher: ";
    encoder.Put((const byte*)cipher.data(), cipher.size());
    encoder.MessageEnd();
    std::cout << std::endl;

    std::cout << "Recovered: " << recover << std::endl;
    delete key_t;
    return 0;
}