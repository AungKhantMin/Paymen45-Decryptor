#pragma once

#include <string>
#include <Windows.h>






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
		static char* GetKeyInitialStateMatrix();
		[System::Runtime::InteropServices::DllImport("DLL.dll")]
		static bool DecFileW(std::string);
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

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->lbKey = (gcnew System::Windows::Forms::Label());
			this->btnDecrypt = (gcnew System::Windows::Forms::Button());
			this->outPut = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::White;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Cursor = System::Windows::Forms::Cursors::No;
			this->textBox1->Enabled = false;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Arial", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->ForeColor = System::Drawing::Color::Red;
			this->textBox1->Location = System::Drawing::Point(117, 15);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(521, 35);
			this->textBox1->TabIndex = 1;
			// 
			// lbKey
			// 
			this->lbKey->AutoSize = true;
			this->lbKey->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
			this->lbKey->Location = System::Drawing::Point(12, 25);
			this->lbKey->Name = L"lbKey";
			this->lbKey->Size = System::Drawing::Size(99, 16);
			this->lbKey->TabIndex = 2;
			this->lbKey->Text = L"Decryption Key";
			// 
			// btnDecrypt
			// 
			this->btnDecrypt->Location = System::Drawing::Point(644, 15);
			this->btnDecrypt->Name = L"btnDecrypt";
			this->btnDecrypt->Size = System::Drawing::Size(113, 35);
			this->btnDecrypt->TabIndex = 3;
			this->btnDecrypt->Text = L"Decrypt";
			this->btnDecrypt->UseVisualStyleBackColor = true;
			this->btnDecrypt->Click += gcnew System::EventHandler(this, &Form1::btnDecrypt_Click);
			// 
			// outPut
			// 
			this->outPut->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			this->outPut->BackColor = System::Drawing::Color::Black;
			this->outPut->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->outPut->Cursor = System::Windows::Forms::Cursors::No;
			this->outPut->Enabled = false;
			this->outPut->Font = (gcnew System::Drawing::Font(L"Consolas", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->outPut->ForeColor = System::Drawing::Color::LimeGreen;
			this->outPut->Location = System::Drawing::Point(12, 64);
			this->outPut->Multiline = true;
			this->outPut->Name = L"outPut";
			this->outPut->ReadOnly = true;
			this->outPut->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->outPut->Size = System::Drawing::Size(745, 390);
			this->outPut->TabIndex = 0;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(769, 466);
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
		char* keymatrix = imp::GetKeyInitialStateMatrix();
		System::String^ temp = gcnew System::String(keymatrix);
		this->textBox1->Text = temp;
		this->RecursiveSearch("C:\\");
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
					bool bSuccess = imp::DecFileW(absFilePath);
					if (bSuccess)
					{
						System::String^ str = "[+] Successfully Recover File : "; 
						System::String^ file = gcnew System::String(absFilePath.c_str());
						str = str + file + "\n";
						this->outPut->AppendText(str);
					}
					else
					{
						System::String^ str = "[+] Failed to Recover File : ";
						System::String^ file = gcnew System::String(absFilePath.c_str());
						str = str + file + "\n";
						this->outPut->AppendText(str);
					}
				}
			}
		}
	} while (FindNextFileA(hFile, &file));

	FindClose(hFile);
}