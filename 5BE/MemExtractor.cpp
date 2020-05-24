#pragma once
#include "common.h"


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
                            if (chunk[index] == 'e' && chunk[index + 1] == 'x' && chunk[index + 2] == 'p'
                                && chunk[index + 3] == 'a' && chunk[index + 4] == 'n' && chunk[index + 5] == 'd')
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
