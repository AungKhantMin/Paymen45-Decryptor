#include "Decryptor.h"

using namespace CryptoPP;


byte* Decryptor::key = nullptr;

Decryptor::~Decryptor() {
	delete Decryptor::key;
}


void Decryptor::DecryptFile(decrypt_ dec_args) {

	DWORD dwFileAttributes = GetFileAttributesA(dec_args.absFilePath.c_str());
	HANDLE hFile = CreateFileA(dec_args.absFilePath.c_str(), GENERIC_ALL, 0,
		NULL, OPEN_EXISTING, dwFileAttributes, NULL);
	BY_HANDLE_FILE_INFORMATION file;
	BOOL bSuccess = GetFileInformationByHandle(hFile, &file);
	std::string orgFile = dec_args.absFilePath;
	if (bSuccess)
	{
		if (hFile != INVALID_HANDLE_VALUE)
		{
			DWORD dwPtr = SetFilePointer(hFile, -520, NULL, 2);
			if (dwPtr != INVALID_SET_FILE_POINTER)
			{
				byte IV[8];
				DWORD dwByteRead;
				bSuccess = ReadFile(hFile, IV, 8, &dwByteRead, NULL);
				dwPtr = SetFilePointer(hFile, -520, NULL, 2);
				SetEndOfFile(hFile);
				if (bSuccess)
				{
					dwPtr = SetFilePointer(hFile, 0, NULL, 0);
					
					INT dwSize = file.nFileSizeHigh;

					if ( dwSize != 0)
					{
						dwSize =((file.nFileSizeHigh * (MAXDWORD + 1)) + file.nFileSizeLow ) - 520;
					}
					else
					{
						dwSize = file.nFileSizeLow - 520;
					}

					if (dwSize > 0x19000)
					{
						dwSize = 0x19000;
					}
					LPVOID lpBuffer = malloc(dwSize);
					memset(lpBuffer, 0, dwSize);
					LPVOID lpOutPut = malloc(dwSize);
					memset(lpBuffer, 0, dwSize);
					bSuccess = ReadFile(hFile, lpBuffer, dwSize, &dwByteRead, NULL);
					if (bSuccess)
					{
						Salsa20::Decryption salsa20;
						AlgorithmParameters params = MakeParameters("Rounds", 8)
							("IV", ConstByteArrayParameter(IV, 8, false));
						salsa20.SetKey(Decryptor::key, 32, params);
						salsa20.ProcessData((byte*)lpOutPut, (byte*)lpBuffer, dwByteRead);
						SetFilePointer(hFile, 0, NULL, 0);
						bSuccess = WriteFile(hFile, lpOutPut, dwByteRead, NULL, NULL);
						if (bSuccess)
						{
							orgFile = orgFile.replace(
								orgFile.begin() + orgFile.find(".g8R4rqWIp9"),
								orgFile.end(), "");
							CloseHandle(hFile);
							bSuccess = MoveFileA(dec_args.absFilePath.c_str(), orgFile.c_str());
							if (!bSuccess)
							{
								//printf("%d\n", GetLastError());
							}
						}
					}
					free(lpBuffer);
					free(lpOutPut);
				}
			}
			else
			{
				bSuccess = FALSE;
			}
		}

	}
	dec_args.dec->printMsg(bSuccess, orgFile.c_str());
}

void Decryptor::printMsg(BOOL bSuccess, LPCSTR file) {
	HANDLE hConsole;
	// Get Console Handle
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!bSuccess)
	{
		//Set Color
		SetConsoleTextAttribute(hConsole, RB);
		printf("[!] Failed To Recvoer File : %s\n", file);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, GB);
		printf("[+] Successfully Recvoer File : %s\n",file);
	}
}

void Decryptor::RecursiveSearch(std::string StartDir = "C:\\") {
	HANDLE hFile;
	WIN32_FIND_DATAA file;
	std::string dir = StartDir + "*";

	hFile = FindFirstFileA(dir.c_str(), &file);

	do {
		decrypt_ dec_args;
		if ( hFile == INVALID_HANDLE_VALUE)
		{
			
		}
		else
		{
			if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				std::string dir = file.cFileName;
				if (dir != "." && dir != "..")
				{
					this->RecursiveSearch(StartDir + dir + "\\");
				}
			}
			else
			{
				std::string fileName = file.cFileName;
				size_t found = fileName.find(".g8R4rqWIp9");
				if (found != std::string::npos)
				{
					dec_args.absFilePath = StartDir + fileName;
					dec_args.dec = this;
					Decryptor::DecryptFileW(dec_args);
				}
			}
		}
	} while (FindNextFileA(hFile,&file));
	
	FindClose(hFile);
}