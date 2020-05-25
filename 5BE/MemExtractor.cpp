#pragma once
#include "MemExtractor.h"


std::vector<std::string> MemExtractor::GetKeyInitialStateMatrix()
{
    using namespace std;
    std::vector<std::string> key;





    MemExtractor::ObtainSeDebugPrivilege();

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    HANDLE hSnapProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    BOOL bSuccess = Process32First(hSnapProcess, &pe32);
    vector<byte> sigDef1, sigDef2;
    sigDef1.resize(160);
    sigDef2.resize(240);

    char temp[161] = "\xC7\x84\x24\xDC\x02\x00\x00\x29\xBF\x93\x13\xC7\x84\x24\x7C\x03\x00\x00\xDE\x9C\xD8\x4A\xC7\x84\x24\xA8\x01\x00\x00\xE9\x64\x33\x33\xC7\x84\x24\x4C\x02\x00\x00\x09\x2E\xA3\x2C\xC7\x84\x24\x18\x02\x00\x00\xFF\xC7\xF3\x0F\xC7\x84\x24\x30\x04\x00\x00\xBC\xDA\x45\x08\xC7\x84\x24\xD4\x01\x00\x00\xF7\x0E\xC1\x01\xC7\x84\x24\x90\x02\x00\x00\x01\xA0\x72\x08\xC7\x84\x24\xE8\x02\x00\x00\x92\xD1\x77\x21\xC7\x84\x24\xEC\x02\x00\x00\xD4\xCC\x77\x18\xC7\x84\x24\xB4\x03\x00\x00\xC6\xB9\xD8\x08\xC7\x84\x24\x28\x03\x00\x00\x13\x1D\x68\x36\xC7\x84\x24\xEC\x03\x00\x00\xE8\xCA\x5D\x43\xC7\x84\x24\xB0\x03\x00\x00\xFA\xDA\xD7\x1D\xC7\x84\x24\x60\x03\x00";
    char temp2[241] = "\xAC\xC9\xFF\xFF\xC7\x84\x24\xF4\x00\x00\x00\x7A\x0E\x1A\x66\xC7\x84\x24\x44\x01\x00\x00\x09\x20\x1E\x15\xC7\x84\x24\x68\x01\x00\x00\x99\xE4\xF2\x60\xC7\x44\x24\x60\x4E\x41\xC2\x38\xC7\x84\x24\x98\x01\x00\x00\xCE\xE7\x8F\x10\xC7\x44\x24\x54\x84\x55\xCD\x36\xC7\x84\x24\xF8\x00\x00\x00\xCF\x88\x8F\x36\xC7\x44\x24\x2C\xE5\x34\x99\x50\xC7\x84\x24\x90\x01\x00\x00\xE4\x9C\x24\x6D\xC7\x84\x24\x9C\x01\x00\x00\xC3\xB7\x8A\x29\xC7\x84\x24\x9C\x00\x00\x00\x5D\x18\x6E\x16\xC7\x44\x24\x44\xFA\x3F\xBC\x1B\xC7\x44\x24\x30\x32\xE6\x25\x21\xC7\x84\x24\x60\x01\x00\x00\x8E\xCC\x2A\x70\xC7\x84\x24\xE4\x00\x00\x00\xD7\x01\xCD\x4B\xC7\x84\x24\x48\x01\x00\x00\x49\x3D\xB3\x50\xC7\x84\x24\xA8\x00\x00\x00\xA4\xDF\xA9\x46\xC7\x84\x24\xF0\x00\x00\x00\x55\xCA\xB8\x01\xC7\x84\x24\x74\x01\x00\x00\x6C\x65\x09\x77\xC7\x84\x24\x28\x01\x00\x00\x47\x1D\x1E\x63\xC7\x84\x24\xE8\x00\x00\x00\x58\xE9\xBC\x29\xC7\x44\x24\x3C\x80\x55\xA5\x0F\xC7\x84\x24\xCC\x00\x00\x00\xE3\x3E\x65\x7C\xC7";

    for (size_t i = 0; i < 160; i++)
    {
        sigDef1[i] = temp[i];
    }
    for (size_t i = 0; i < 240; i++)
    {
        sigDef2[i] = temp2[i];
    }

    if (bSuccess)
    {
        LPSTR fileName = (LPSTR)malloc(50);

        do
        {
            if (pe32.th32ProcessID == GetCurrentProcessId())
            {
                continue;
            }
            //printf("%ws \n", pe32.szExeFile);
            HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | WRITE_DAC, 0, pe32.th32ProcessID);
            if (hProc != INVALID_HANDLE_VALUE)
            {
                memset(fileName, 0, 50);
                DWORD dwBytes;
                bSuccess = GetModuleFileNameExA(hProc, 0, fileName, 50);
                if (bSuccess)
                {
                    std::ifstream file(fileName, ios::binary);

                    if (file.is_open())
                    {
                        file.unsetf(std::ios::skipws);

                        //Getting File Size
                        std::streampos fileSize;
                        file.seekg(0, std::ios::end);
                        fileSize = file.tellg();
                        file.seekg(0, std::ios::beg);

                        vector<byte> Buffer;
                        Buffer.reserve(fileSize);

                        //Read Buffer to vector
                        Buffer.insert(Buffer.begin(),
                            istream_iterator<byte>(file),
                            istream_iterator<byte>());
                        file.close();


                        auto it2 = search(Buffer.begin(), Buffer.end(), sigDef1.begin(), sigDef1.end());
                        auto it1 = search(Buffer.begin(), Buffer.end(), sigDef2.begin(), sigDef2.end());

                        if (it1 != Buffer.end() || it2 != Buffer.end()) {
                            printf("[+] Ransomware Process Found....\n");
                            printf("PID : %d\n", pe32.th32ProcessID);
                            SYSTEM_INFO si;
                            GetSystemInfo(&si);

                            MEMORY_BASIC_INFORMATION info;
                            std::vector<char> chunk;
                            char* p = 0;
                            p += 0x1000000;
                            while ((int)p < 0x07000000)
                            {
                                if (VirtualQueryEx(hProc, p, &info, sizeof(info)) == sizeof(info))
                                {
                                    p = (char*)info.BaseAddress;
                                    if (info.RegionSize > 0x9c40000)
                                    {
                                        continue;
                                    }
                                    chunk.resize(info.RegionSize);
                                    SIZE_T bytesRead;
                                    if (ReadProcessMemory(hProc, p, &chunk[0], info.RegionSize, &bytesRead))
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
                                                for (size_t l = 0; l < 16; l++)
                                                {
                                                    if (index + l < chunk.size())
                                                    {
                                                        constant[l] = chunk[index + l];
                                                    }
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
                                else
                                {
                                    break;
                                }
                            }
                            
                        }
                    }

                }

            }
            CloseHandle(hProc);
        } while (Process32Next(hSnapProcess, &pe32));
    }
    CloseHandle(hSnapProcess);
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


BOOL MemExtractor::ObtainSeDebugPrivilege(void)
{
    HANDLE hToken;
    PTOKEN_PRIVILEGES NewPrivileges;
    BYTE OldPriv[1024];
    PBYTE pbOldPriv;
    ULONG cbNeeded;
    BOOLEAN fRc;
    LUID LuidPrivilege;

    // Make sure we have access to adjust and to get the old token privileges
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        return FALSE;
    }

    cbNeeded = 0;

    // Initialize the privilege adjustment structure
    LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &LuidPrivilege);

    NewPrivileges = (PTOKEN_PRIVILEGES)LocalAlloc(
        LMEM_ZEROINIT,
        sizeof(TOKEN_PRIVILEGES) + (1 - ANYSIZE_ARRAY) * sizeof(LUID_AND_ATTRIBUTES)
    );
    if (NewPrivileges == NULL) {
        return FALSE;
    }

    NewPrivileges->PrivilegeCount = 1;
    NewPrivileges->Privileges[0].Luid = LuidPrivilege;
    NewPrivileges->Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // Enable the privilege
    pbOldPriv = OldPriv;
    fRc = AdjustTokenPrivileges(
        hToken,
        FALSE,
        NewPrivileges,
        1024,
        (PTOKEN_PRIVILEGES)pbOldPriv,
        &cbNeeded
    );

    if (!fRc) {

        // If the stack was too small to hold the privileges
        // then allocate off the heap
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {

            pbOldPriv = (PBYTE)LocalAlloc(LMEM_FIXED, cbNeeded);
            if (pbOldPriv == NULL) {
                return FALSE;
            }

            fRc = AdjustTokenPrivileges(
                hToken,
                FALSE,
                NewPrivileges,
                cbNeeded,
                (PTOKEN_PRIVILEGES)pbOldPriv,
                &cbNeeded
            );
        }
    }
    return fRc;
}