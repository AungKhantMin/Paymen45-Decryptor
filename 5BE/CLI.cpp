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
        printf("Example: CLI.exe 1809 C:\\Users\\{username}\\Desktop\\\n");
    }
    else
    {
        DWORD pid = (int)argv[1];
        std::vector<std::string> keymatrix = MemExtractor::GetKeyInitialStateMatrix(pid);
        byte* key_t = (byte*)MemExtractor::GetKey(keymatrix);
        Decryptor::key = key_t;
        Decryptor* decryptor = new Decryptor();
        decryptor->RecursiveSearch(argv[2]);
        delete key_t;
    }


    return 0;
}