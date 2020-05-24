#pragma once

#include "common.h"

//".g8R4rqWIp9"


int main()
{
    using namespace CryptoPP;

    DWORD pid = 1228;
    std::vector<std::string> keymatrix = MemExtractor::GetKeyInitialStateMatrix(pid);
    std::string keyConstant = "";
    std::vector<int> keyTemp;
    std::vector<int> key;
    key.resize(8);
    keyTemp.resize(16);

 
    if (keymatrix.begin() != keymatrix.end())
    {
        for (size_t i = 0; i < 16; i++)
        {
            const char* test = keymatrix[i].c_str();
            UINT8 f = test[0];
            UINT8 s = test[1];
            UINT8 t = test[2];
            UINT8 fo = test[3];
            UINT32 final = (f * 0x1000000 + s * 0x10000 + t * 0x100 + fo);
            keyTemp[i] = final;
            printf("Key %d Matrix %d : 0x%.8x\n",i,i,final);
        }
    }
    else
    {
        std::cout << "Not found\n";
    }

    key[0] = keyTemp[13];
    key[1] = keyTemp[10];
    key[2] = keyTemp[7];
    key[3] = keyTemp[4];
    key[4] = keyTemp[15];
    key[5] = keyTemp[12];
    key[6] = keyTemp[9];
    key[7] = keyTemp[6];
    char key_s[65]; 
    wsprintfA(key_s, "%4.X%4.X%4.X%4.X%4.X%4.X%4.X%4.X", key[0], key[1], key[2], key[3], key[4]
        , key[5], key[6], key[7]);
    std::cout << "Encryption Key : " <<key_s << std::endl;
    byte key_t[32];
        
    unsigned int t = 0;
    for (size_t i = 0; i < 64; i+=2)
    {
        std::stringstream ss;
        char tmp_1[3];
        wsprintfA(tmp_1, "%c%c", key_s[i], key_s[i + 1]);
        ss << std::hex << tmp_1;
        ss >> t;
        key_t[i / 2] = t;
    }

    
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
    return 0;
}