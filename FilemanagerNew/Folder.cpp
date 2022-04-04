#define _CRT_SECURE_NO_WARNINGS
#include "Folder.h"
#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <io.h> 
#include <chrono>
#include "File.h"
using namespace std;
void Folder::MakeFolder(std::string f, std::string name)
{
	if (_access(f.data(), 0) == 0)
	{
		f += name;
		cout << "Making...\n";
		Sleep(300);
		_mkdir(f.data());
		system("cls");
		cout << "Succsefuly done\n";
	}
	else
	{
		cout << "Sorry but you entered the wrong way " << endl;
	}
}
void Folder::DeleteFolder(std::string f)
{
	if (_access(f.data(), 0) == 0)
	{
		char answer;
		cout << "\t\tWARNING!!!\n";
		cout << "All data in this folder will be deleted too\n";
		cout << "Are you sure ? Y\\N : "; cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			cout << "Deleting...\n";
			Sleep(300);
			_rmdir(f.data());
			system("cls");
			cout << "Succsefuly done\n";
		}
		else
		{
			cout << "be careful ^_^\n";
		}
	}
}
void Folder::RenameFolder(std::string path, std::string name, std::string new_name)
{
	if (_access(path.data(), 0) == 0)
	{
		_finddata_t data;
		long handle = _findfirst((path + name).data(), &data);
		if (handle != -1)
		{
			if (data.attrib == _A_SUBDIR)
			{
				cout << "Loading...\n";
				Sleep(600);
				rename((path + name).data(), (path + new_name).data());
				system("cls");
				cout << "Succsefuly done\n";
				 
			}
			else
			{
				std::cout << "It isnt directory\n";
			}
		}
	 
	}
	else
	{
		cout << "Sorry but you entered the wrong way " << endl;
	}
}
void Folder::CopyFolder(std::string path, std::string new_path)
{
  if (_access(path.data(), 0) == 0)
  {
    File f;
    long groupHandle;

    std::string directori = path;
    std::string directori2 = new_path;

    path += "\\*.*";
    _finddata_t data;
    groupHandle = _findfirst(path.data(), &data);

    _mkdir(new_path.data());
    int i = 0;
    if (groupHandle != -1)
    {
        long result = groupHandle;
        while (result != -1)
        {

            if (data.attrib & _A_SUBDIR )
            {
                i++;
                if (i > 2)
                {
                    CopyFolder(directori + '\\' + data.name, directori2 +'\\' + data.name);
                }
            }
            else
            {
                std::string str = directori;
			    str += '\\';
				str += data.name;
				std::string str2 = directori2;
			    str2 += '\\';
				str2 += data.name;
                f.copyFile(str.data(), str2.data());
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
void Folder::ReplaceFolder(std::string path, std::string new_path)
{
  if (_access(path.data(), 0) == 0)
  {
	File file;
	long groupHandle;
	std::string old_path = path;
	std::string dir = path;
	std::string dir2 = new_path;

	path += "\\*.*";
	_finddata_t data;
	groupHandle = _findfirst(path.data(), &data);

	_mkdir(new_path.data());
	int i = 0;
	if (groupHandle != -1)
	{
		long result = groupHandle;
		while (result != -1)
		{

			if (data.attrib & _A_SUBDIR)
			{ 
			   CopyFolder(dir + '\\' + data.name, dir2 + '\\' + data.name);	
			   _rmdir((dir + '\\' + data.name).data());
			}
			else
			{
				std::string str = dir;
				str += '\\';
				str += data.name;
				std::string str2 = dir2;
				str2 += '\\';
				str2 += data.name;
				file.ReplaceFileW(str.data(), str2.data());
			}


			result = _findnext(groupHandle, &data);
		}
	}
	 _rmdir(old_path.data());
	_findclose(groupHandle);
  }
  else
  {
	  cout << "Sorry but you entered the wrong way " << endl;
  }

}
void Folder::SearchFolder(std::string path, std::string s)
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

			if (data.attrib & _A_SUBDIR)
			{
				i++;
				if (s == data.name)
				{
					system("cls");
					cout << "\t\tIts  Found!!!!\n";
					cout << "Here = {" << path << "}\n";
					std::cout << "Folder name: " << data.name;
					localtime_s(&tm, &data.time_create);
					std::cout << "\t" << 1900 + tm.tm_year << '.' << tm.tm_mon + 1 << '.' << tm.tm_mday << ' ' << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << std::endl;

				}
				if (i > 2)
				{
					SearchFolder((directori + '\\' + data.name), s);
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
 