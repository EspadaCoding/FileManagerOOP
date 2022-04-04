#define _CRT_SECURE_NO_WARNINGS
#include "File.h"
#include "Folder.h"
#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <io.h>
#include <chrono>
using namespace std;
void File::MakeFile(std::string f, std::string name, std::string mode)
{
	if (_access(f.data(), 0) == 0)
	{
		f += name;
		cout << "Making...\n";
		Sleep(500);
		FILE* file = fopen(f.data(), mode.data());
		system("cls");
		cout << "Succsefuly done\n";
		fclose(file);
	}
	else
	{
		cout << "Sorry but you entered the wrong way " << endl;
	}
}
void File::Delete_File(std::string f, std::string name)
{
	if (_access(f.data(), 0) == 0)
	{
		char answer;
		cout << "\t\tWARNING!!!\n";
		cout << "All data in this file will be deleted too\n";
		cout << "Are you sure ? Y\\N : "; cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			f += name;
			cout << "Deleting...\n";
			Sleep(300);
			remove(f.data());
			system("cls");
			cout << "Succsefuly done\n";
		}
		else
		{
			cout << "be careful ^_^\n";
		}
	}
	else
	{
		cout << "Sorry but you entered the wrong way " << endl;
	}
}
bool File::copyFile(const char * source, const char * destination)
{
	FILE *sou;
	fopen_s(&sou, source, "rb");
	if (!sou)return false;
	FILE *des;
	fopen_s(&des, destination, "wb");
	if (!des)return false;
	char* buffer = new char[1024];
	short rsize;
	fseek(sou, SEEK_SET, 0);
	while (!feof(sou)) {
		rsize = fread(buffer, sizeof(char), 1024, sou);
		fwrite(buffer, sizeof(char), rsize, des);
	}
	fclose(sou);
	fclose(des);
	return true;
}
void File::CopyDataOfFile(std::string path, std::string out)
{
	FILE *input = fopen(path.data(), "rb");
	FILE *output = fopen(out.data(), "wb");
	if (input != NULL && output != NULL)
	{
		char buffer[BUFSIZ];
		size_t count, i, j = 0;
		do {
			count = fread(buffer, sizeof *buffer, sizeof  buffer, input);
			fwrite(buffer, sizeof *buffer, count, output);
		} while (count == sizeof buffer);
		fclose(input);
		fclose(output);
	}
	 
}
void File::XORhashing(std::string path, std::string out, std::string key)
{  
	FILE *input = fopen(path.data(), "rb");
	FILE *output = fopen(out.data(), "wb");
	if (input != NULL && output != NULL)
	{
		 char buffer[BUFSIZ];
		size_t count, i, j = 0;
		do {
			count = fread(buffer, sizeof *buffer, sizeof  key, input);
			for (i = 0; i < count; ++i)
			{
				buffer[i] ^= key[j++];
				if (key[j] == '\0')
					j = 0;
			}
			fwrite(buffer, sizeof *buffer, count, output);
		} while (count == sizeof buffer);
		fclose(input);
		fclose(output);
	} 

}
 bool File::ReplaceFileW(const char * source, const char * destination)
{

	std::string old_Fail = source;
	FILE *sou;
	fopen_s(&sou, source, "rb");
	if (!sou)return false;
	FILE *des;
	fopen_s(&des, destination, "wb");
	if (!des)return false;
	char* buffer = new char[1024];
	short rsize;
	fseek(sou, SEEK_SET, 0);
	while (!feof(sou)) {
		rsize = fread(buffer, sizeof(char), 1024, sou);
		fwrite(buffer, sizeof(char), rsize, des);
	}
	fclose(sou);
	fclose(des);
	remove(old_Fail.c_str());

}
void File::SearchFile(std::string path, std::string s)
{
	if (_access(path.data(), 0) == 0)
	{
		long groupHandle;
		tm tm;
		std::string directori = path;
		_finddata_t data;
		groupHandle = _findfirst((path + "\\*.*").data(), &data);
		int i = 0;

		if (groupHandle != -1)
		{
			long result = groupHandle;
			while (result != -1)
			{
				i++;
				if (s == data.name)
				{
					system("cls");
					cout << "\t\tIts  Found!!!!\n";
					cout << "Here = {" << path << "}\n";
					std::cout << "File name: " << data.name;
					localtime_s(&tm, &data.time_create);
					std::cout << "\t" << 1900 + tm.tm_year << '.' << tm.tm_mon + 1 << '.' << tm.tm_mday << ' ' << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << std::endl;

				}
				if (data.attrib & _A_SUBDIR)
				{
					if (i > 2)
					{
						SearchFile((directori + '\\' + data.name), s);
					}


				}

				result = _findnext(groupHandle, &data);
			}
		}

		_findclose(groupHandle);
	}
    else
    {
		cout << "Sorry but you entered the wrong way " << endl;
    }


}
void File::RenameFile(std::string path, std::string name, std::string new_name)
{
	if (_access(path.data(), 0) == 0)
	{
		_finddata_t data;
		long handle = _findfirst((path + name).data(), &data);
		if (handle != -1)
		{
			if (data.attrib == _A_NORMAL|| data.attrib == _A_RDONLY|| data.attrib == _A_HIDDEN)
			{
				cout << "Loading...\n";
				Sleep(600);
				rename((path + name).data(), (path + new_name).data());
				system("cls");
				cout << "Succsefuly done\n";

			}
			else
			{
				std::cout << "It isnt file\n";
			}
		}

	}
	else
	{
		cout << "Sorry but you entered the wrong way " << endl;
	}
}