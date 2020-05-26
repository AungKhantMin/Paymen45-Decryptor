#pragma once

#include <string>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <iterator>
#include <algorithm>
#include <minwinbase.h>
#include <fstream>
#include <sstream>
#include <cliext/vector>
#include <msclr\marshal_cppstd.h>





namespace GUIT {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	value struct imp
	{
	public:
		[System::Runtime::InteropServices::DllImport("DLL.dll")]
		static bool DecFileW(std::string,byte*);
	};

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		System::Void RecursiveSearch(std::string StartDir);
		System::String^ GetKeyInitialStateMatrix();
		System::String^ GetKey(std::vector<std::string> keymatrix);
		byte* GetKeyByte(System::String^);
    private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
    private: System::Windows::Forms::Button^ btnSetKey;
    public:
           byte* gkey;
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	public: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ lbKey;
	private: System::Windows::Forms::Button^ btnDecrypt;
	public: System::Windows::Forms::TextBox^ outPut;
    private: System::ComponentModel::IContainer^ components;
    public:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->components = (gcnew System::ComponentModel::Container());
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->lbKey = (gcnew System::Windows::Forms::Label());
            this->btnDecrypt = (gcnew System::Windows::Forms::Button());
            this->outPut = (gcnew System::Windows::Forms::TextBox());
            this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
            this->btnSetKey = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // textBox1
            // 
            this->textBox1->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
            this->textBox1->BackColor = System::Drawing::Color::Black;
            this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
            this->textBox1->Cursor = System::Windows::Forms::Cursors::IBeam;
            this->textBox1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->textBox1->ForeColor = System::Drawing::Color::LimeGreen;
            this->textBox1->Location = System::Drawing::Point(117, 28);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(521, 14);
            this->textBox1->TabIndex = 1;
            this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            // 
            // lbKey
            // 
            this->lbKey->AutoSize = true;
            this->lbKey->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
            this->lbKey->Location = System::Drawing::Point(12, 27);
            this->lbKey->Name = L"lbKey";
            this->lbKey->Size = System::Drawing::Size(99, 16);
            this->lbKey->TabIndex = 2;
            this->lbKey->Text = L"Decryption Key";
            // 
            // btnDecrypt
            // 
            this->btnDecrypt->Location = System::Drawing::Point(644, 12);
            this->btnDecrypt->Name = L"btnDecrypt";
            this->btnDecrypt->Size = System::Drawing::Size(113, 22);
            this->btnDecrypt->TabIndex = 3;
            this->btnDecrypt->Text = L"Decrypt";
            this->btnDecrypt->UseVisualStyleBackColor = true;
            this->btnDecrypt->Click += gcnew System::EventHandler(this, &Form1::btnDecrypt_Click);
            // 
            // outPut
            // 
            this->outPut->BackColor = System::Drawing::Color::Black;
            this->outPut->BorderStyle = System::Windows::Forms::BorderStyle::None;
            this->outPut->Cursor = System::Windows::Forms::Cursors::IBeam;
            this->outPut->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->outPut->ForeColor = System::Drawing::Color::LimeGreen;
            this->outPut->Location = System::Drawing::Point(0, 73);
            this->outPut->Multiline = true;
            this->outPut->Name = L"outPut";
            this->outPut->ReadOnly = true;
            this->outPut->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
            this->outPut->Size = System::Drawing::Size(769, 414);
            this->outPut->TabIndex = 0;
            // 
            // contextMenuStrip1
            // 
            this->contextMenuStrip1->Name = L"contextMenuStrip1";
            this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
            // 
            // btnSetKey
            // 
            this->btnSetKey->Location = System::Drawing::Point(644, 36);
            this->btnSetKey->Name = L"btnSetKey";
            this->btnSetKey->Size = System::Drawing::Size(113, 22);
            this->btnSetKey->TabIndex = 4;
            this->btnSetKey->Text = L"Set Key";
            this->btnSetKey->UseVisualStyleBackColor = true;
            this->btnSetKey->Click += gcnew System::EventHandler(this, &Form1::btnSetKey_Click);
            // 
            // Form1
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::White;
            this->ClientSize = System::Drawing::Size(769, 487);
            this->Controls->Add(this->btnSetKey);
            this->Controls->Add(this->btnDecrypt);
            this->Controls->Add(this->lbKey);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->outPut);
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Name = L"Form1";
            this->Text = L"Paymen45 (.g8R4rqWIp9) Decryptor";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
	private: System::Void btnDecrypt_Click(System::Object^ sender, System::EventArgs^ e) {
        if ( sizeof(this->gkey) / sizeof(byte) == 32  && this->textBox1->Text->Length == 32)
        {
            this->gkey = this->GetKeyByte(this->textBox1->Text);
		    this->RecursiveSearch("C:\\");
        }
        else
        {
            System::String^ keymatrix = this->GetKeyInitialStateMatrix();
            this->textBox1->Text = keymatrix;
            this->RecursiveSearch("C:\\");
        }

	}

private: System::Void btnSetKey_Click(System::Object^ sender, System::EventArgs^ e) {
    this->gkey = this->GetKeyByte(this->textBox1->Text);
    this->textBox1->Text = this->textBox1->Text;
}   
};
}

System::Void GUIT::Form1::RecursiveSearch(std::string StartDir){
	HANDLE hFile;
	WIN32_FIND_DATAA file;
	std::string dir = StartDir + "*";

	hFile = FindFirstFileA(dir.c_str(), &file);

	do {
		if (hFile == INVALID_HANDLE_VALUE)
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
					std::string absFilePath = StartDir + fileName;
					bool bSuccess = imp::DecFileW(absFilePath,(byte*)this->GetKeyByte(this->textBox1->Text));
					if (bSuccess)
					{
						System::String^ str = "[+] Successfully Recover File : "; 
						this->outPut->ForeColor = System::Drawing::Color::LimeGreen;
						System::String^ file = gcnew System::String(absFilePath.c_str());
						str = str + file + "\n";
						this->outPut->AppendText(str);
					}
					else
					{
						System::String^ str = "[+] Failed to Recover File : ";
						this->outPut->ForeColor = System::Drawing::Color::Red;
						System::String^ file = gcnew System::String(absFilePath.c_str());
						str = str + file + "\n";
						this->outPut->AppendText(str);
                        this->outPut->ForeColor = System::Drawing::Color::LimeGreen;
					}
				}
			}
		}
	} while (FindNextFileA(hFile, &file));

	FindClose(hFile);
}



System::String^ GUIT::Form1::GetKeyInitialStateMatrix()
{
    using namespace std;
    vector<string> key;
	System::String^ key_s;
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
                            this->outPut->AppendText("[+] Ransomware Process Found....\n");
                            this->outPut->AppendText(String::Format("PID : {0:d}\n", pe32.th32ProcessID));
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
                                                    key_s = GetKey(key);
                                                    return key_s;
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
    return  key_s;
}

System::String^ GUIT::Form1::GetKey(std::vector<std::string> keymatrix) {
	cliext::vector<int> keyTemp;
	cliext::vector<int> key;
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
            this->outPut->AppendText(String::Format("Key {0:d} Matrix {1:d} : 0x{2:X8}\n",i,i,final));
            //printf("Key %d Matrix %d : 0x%.8x\n", i, i, final);
        }
    }


    key[0] = keyTemp[13];
    key[1] = keyTemp[10];
    key[2] = keyTemp[7];
    key[3] = keyTemp[4];
    key[4] = keyTemp[15];
    key[5] = keyTemp[12];
    key[6] = keyTemp[9];
    key[7] = keyTemp[6];
	System::String^ key_s = String::Format("{0:X4}{1:X4}{2:X4}{3:X4}{4:X4}{5:X4}{6:X4}{7:X4}",
		key[0], key[1], key[2], key[3], key[4], key[5], key[6], key[7]);

    this->gkey = this->GetKeyByte(key_s);
    return key_s;
}

byte* GUIT::Form1::GetKeyByte(System::String^ key_s) {
	byte key_t[33];

	unsigned int t = 0;
	for (size_t i = 0; i < 64; i += 2)
	{
		std::stringstream ss;
		System::String^ tmp1 = String::Format("{0}{1}", char(key_s[i]), char(key_s[i + 1]));
		std::string tmp_1 = msclr::interop::marshal_as<std::string>(tmp1);
		ss << std::hex << tmp_1;
		ss >> t;
		key_t[i / 2] = t;
	}
	return key_t;
}