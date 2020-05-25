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
    if (argc < 3)
    {

        printf("%s ransomware_process_id directory_to_decrypt\n",argv[0]);
        printf("%s -k 32ByteDecryptionKey directory_to_decrypt\n", argv[0]);
        printf("Example: CLI.exe 1809 C:\\Users\\{username}\\Desktop\\\n");
    }
    else if (argc == 3)
    {
        DWORD pid = atoi(argv[1]);
        std::vector<std::string> keymatrix = MemExtractor::GetKeyInitialStateMatrix(pid);
        if (keymatrix.size() < 32)
        {
            //printf("Error Code : %d", GetLastError());
            return 0;
        }

        byte* key_t = (byte*)MemExtractor::GetKey(keymatrix);

        Decryptor::key = key_t;
        Decryptor* decryptor = new Decryptor();
        std::string startDir = argv[2]; //"C:\\Users\\hades\\Desktop\\Ransomwaer GG\\"
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