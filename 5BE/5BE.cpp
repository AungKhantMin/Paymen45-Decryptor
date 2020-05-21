#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> GetAddressOfData(DWORD pid)
{
    std::vector<int> key;
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
                                key.resize(64);
                                for (size_t i = 0; i < 64; i++)
                                {
                                    key[i] = chunk[0x1d90 + i];
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

int main()
{
    //Pass whatever process id you like here instead.
    DWORD pid = 7728;
    std::vector<int> key = GetAddressOfData(pid);
    std::string keyConstant = "";

    if (key.begin() != key.end())
    {
        for (size_t i = 0; i < 16; i++)
        {
            keyConstant += (char)key[i];
        }
        std::cout << "Found: " << keyConstant << "\n";
    }
    else
    {
        std::cout << "Not found\n";
    }

    return 0;
}