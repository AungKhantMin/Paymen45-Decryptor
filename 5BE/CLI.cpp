#pragma once


#include "MemExtractor.h"
#include "Decryptor.h"

#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
//".g8R4rqWIp9"


int main(int argc, char* argv[])
{

    printf("%s DirectoryToDecrypt\n",argv[0]);
    printf("%s -k 32ByteDecryptionKey directory_to_decrypt\n", argv[0]);
    printf("Example: CLI.exe C:\\Users\\{username}\\Desktop\\\n");
    printf(".\\CLI.exe -k AA06E65714F2482BBA05B2336956552829AB7268B41F83186AB9E278A0926D84 C:\\  \n");
    if (argc < 3)
    {
        std::vector<std::string> keymatrix = MemExtractor::GetKeyInitialStateMatrix();
        if (keymatrix.size() < 32)
        {
            printf("Error Code : %d", GetLastError());
            return 0;
        }

        byte* key_t = (byte*)MemExtractor::GetKey(keymatrix);

        Decryptor::key = key_t;
        Decryptor* decryptor = new Decryptor();
        std::string startDir = argv[1]; //"C:\\Users\\hades\\Desktop\\Ransomwaer GG\\"
        decryptor->RecursiveSearch(startDir);
        delete key_t;
    }
    else
    {
        byte* key_t = (byte*)argv[2];
        Decryptor::key = key_t;
        Decryptor* decryptor = new Decryptor();
        std::string startDir = argv[3]; //"C:\\Users\\hades\\Desktop\\Ransomwaer GG\\"
        decryptor->RecursiveSearch(startDir);
    }


    return 0;
}