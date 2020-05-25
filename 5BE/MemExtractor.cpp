#pragma once
#include "MemExtractor.h"


std::vector<std::string> MemExtractor::GetKeyInitialStateMatrix(DWORD pid)
{
    std::vector<std::string> key;
    HANDLE process = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (process)
    {
        SYSTEM_INFO si;
        GetSystemInfo(&si);

        MEMORY_BASIC_INFORMATION info;
        std::vector<char> chunk;
        char* p = 0;
        p += 0x1000000;
        while (p < si.lpMaximumApplicationAddress)
        {
            if (VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info))
            {
                p = (char*)info.BaseAddress;
                chunk.resize(info.RegionSize);
                SIZE_T bytesRead;
                if (ReadProcessMemory(process, p, &chunk[0], info.RegionSize, &bytesRead))
                {
                    std::vector<char>::iterator start = chunk.begin();
                    do
                    {

                        auto i = std::find(start, chunk.end(), 'e');
                        if (i != chunk.end())
                        {
                            int index = std::distance(chunk.begin(), i);
                            std::string constant;
                            constant.resize(16);
                            for (size_t i = 0; i < 16; i++)
                            {
                                constant[i] = chunk[index + i];
                            }
                            if (constant == "expand 32-byte k")
                            {
                                key.resize(16);
                                for (size_t g = 0; g < 16; g++)
                                {
                                    std::string data = "";
                                    data += chunk[index + g * 4];
                                    data += chunk[index + g * 4 + 1];
                                    data += chunk[index + g * 4 + 2];
                                    data += chunk[index + g * 4 + 3];
                                    key[g] = data;
                                }
                                return key;
                            }
                            start = i + 1;
                        }
                        else
                        {
                            break;
                        }
                    } while (true);

                }
                p += info.RegionSize;
            }
        }
    }
    return key;
}

LPVOID MemExtractor::GetKey(std::vector<std::string> keymatrix) {
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
            printf("Key %d Matrix %d : 0x%.8x\n", i, i, final);
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
    std::cout << "Encryption Key : " << key_s << std::endl;
    byte key_t[32];

    unsigned int t = 0;
    for (size_t i = 0; i < 64; i += 2)
    {
        std::stringstream ss;
        char tmp_1[3];
        wsprintfA(tmp_1, "%c%c", key_s[i], key_s[i + 1]);
        ss << std::hex << tmp_1;
        ss >> t;
        key_t[i / 2] = t;
    }
    LPVOID key_addr = malloc(sizeof(key_t));
    memset(key_addr, 0, sizeof(key_t));
    memcpy(key_addr, key_t, sizeof(key_t));
    return key_addr;
}