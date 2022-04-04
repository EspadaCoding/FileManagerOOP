#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdio.h>
#include <io.h>
#include <direct.h>
#include <dirent.h> 
#include <chrono>
#include <Windows.h>
#include <fstream>
#include <time.h>
#include <vector> 
#include <audiere.h> 
#include "Folder.h"
#include "File.h" 
#include "MD5.h" 
#include "audiere.h"
#pragma comment(lib, "audiere.lib")
using namespace std;  
audiere::AudioDevicePtr device = audiere::OpenDevice();
class FileManager : public Folder, public File , public MD5
{
private:
	string dir;
	vector<string> file_names;
public: 
	void Show(string name)
	{
		long groupHandle;
		if (!name.empty())
		{
			string directori = name;

			name += "\\*.*";
			_finddata_t data;
			groupHandle = _findfirst(name.data(), &data); 
			if (groupHandle != -1)
			{
				long result = groupHandle;
				int i = this->file_names.size() + 1;
				while (result != -1)
				{
					cout << i << ": Name: " << data.name << "| size: " << data.size << "| byte";
					this->file_names.push_back(directori + '\\' + data.name);

					if (data.attrib & _A_SUBDIR)
					{
						cout << " is directory, ";
					}
					else
					{
						cout << " is file, ";
					}
					tm tm;
					localtime_s(&tm, &data.time_create);
					cout <<"Time  = ["<<1900 + tm.tm_year << '.' << tm.tm_mon + 1 << '.' << tm.tm_mday <<","<<' ' << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec<<"]"<< endl;

					result = _findnext(groupHandle, &data);
					i++;
				}    
			}
			
		}
		
		_findclose(groupHandle);
	}
	void moving(int i)
	{  
		if (i>0)
		{
			long groupHandle;
			string name = file_names[i - 1] + "\\*.*";

			_finddata_t new_data;

			groupHandle = _findfirst(name.data(), &new_data);
			dir = file_names[i - 1];

			if (groupHandle != -1)
			{
				int i = this->file_names.size() + 1;

				long result = groupHandle;
				cout << "================================================================\n";
				while (result != -1)
				{

					cout << i << ": file name: " << new_data.name << " size: " << new_data.size << " byte";
					file_names.push_back(dir + '\\' + new_data.name);

					if (new_data.attrib & _A_SUBDIR)
					{
						cout << " is directory, ";
					}
					else
					{
						cout << " is file, ";
					}
					tm tm;
					localtime_s(&tm, &new_data.time_create);
					cout << 1900 + tm.tm_year << '.' << tm.tm_mon + 1 << '.' << tm.tm_mday << "," << ' ' << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << endl;

					result = _findnext(groupHandle, &new_data);
					i++;
				}
			}
			_findclose(groupHandle);
		}
		else
		{
			this->file_names.clear();
		} 
			 
		
	}

}; 
void MD5hashing(std::string path, std::string out)
{
	MD5 m;
	FILE *input = fopen(path.data(), "rb");
	FILE *output = fopen(out.data(), "wb");
	if (input != NULL && output != NULL)
	{
		char buffer[BUFSIZ];
		size_t count, i, j = 0;
		do {
			count = fread(buffer, sizeof *buffer, sizeof buffer, input);
			for (i = 0; i < count; ++i)
			{
				fwrite(m.md5(buffer).c_str(), sizeof *m.md5(buffer).c_str(), count, output);
			}
		} while (count == sizeof buffer);
		fclose(input);
		fclose(output);
	}

}
int main()
{  
	system("color 04");
	FileManager fileman; 
	bool working = true;
	int s1;
	while (working)
	{
		system("cls");
		cout << "\t\t\t\tWelcome to File Manager By Saylormoon on C++\n\n";
		cout << "\t\t\t\t___________________________________________\n\n";
		cout << "\t\t\t\t\t1.Moving by disk \n";
		cout << "\t\t\t\t\t2.Make Folder or File\n";
		cout << "\t\t\t\t\t3.Delete Folder or File\n";
		cout << "\t\t\t\t\t4.Rename Folder or File\n";
		cout << "\t\t\t\t\t5.Copy Folder or File\n";
		cout << "\t\t\t\t\t6.Search\n";
		cout << "\t\t\t\t\t7.Copy file data to another file \n";
		cout << "\t\t\t\t\t8.Replace file or folder\n";
		cout << "\t\t\t\t\t10.XOR encryption \n";
		cout << "\t\t\t\t\t11.MD5 encryption \n"; 
		cout << "\t\t\t\t\t\t99.Exit\n";
		cout << "\t\t\t\t___________________________________________\n\n";
		cout << "\t\t\t\tEnter your Selection: "; cin >> s1;
	  switch (s1)
	  {
		case 1:
		{
			system("cls");
			string d;
			bool working = true;
			cout << "Enter name of disk with ':' {Example = C:} "; cin >> d;
			fileman.Show(d);
			while (working)
			{
				int n;
				cout << "Enter : "; cin >> n;
				fileman.moving(n);
				if (n == 0)
				{
					working = false;
					system("cls");
				}
			}
			break;
		}
		case 2:
		{
			system("cls");
			int a = 0;
			cout << "1)Make folder \n2)Make File \n";
			cout << "Enter : "; cin >> a;
			if (a == 1)
			{
				system("cls");
				string path;
				string n;
				cout << "Enter the full path "; cin >> path;
				cout << "Enter the name of folder "; cin >> n;
				fileman.MakeFolder(path, n);
				system("pause");
				system("cls");
			}
			else if (a == 2)
			{
				system("cls");
				string path;
				string n;
				string m;
				cout << "Enter the full path "; cin >> path;
				cout << "Enter the name of file with expansion "; cin >> n;
				cout << "Enter the mode "; cin >> m;
				fileman.MakeFile(path, n, m);
				system("pause");
				system("cls");
			}
			else
			{
				cout << " Nope " << endl;
			}
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			system("cls");
			int a = 0;
			cout << "1)Delete folder \n2)Delete File \n";
			cout << "Enter : "; cin >> a;
			if (a == 1)
			{
				system("cls");
				string path;
				string n;
				cout << "Enter the full path with name : "; cin >> path;
				fileman.DeleteFolder(path);
				system("pause");
				system("cls");
	
			}
			else if (a == 2)
			{
				system("cls");
				string path;
				string n;
				cout << "Enter the full path "; cin >> path;
				cout << "Enter the name of file with expansion "; cin >> n;
				fileman.Delete_File(path, n);
				system("pause");
				system("cls");
			}
			else
			{
				cout << " Nope " << endl;
			}
			break;
		}
		case 4:
		{ 
			system("cls");
			int a = 0;
			cout << "1)Rename folder \n2)Rename File \n";
			cout << "Enter : "; cin >> a;
			if (a == 1)
			{
				system("cls");
				string path, name, new_name;
				cout << "Enter full path without folder name: "; cin >> path;
				cout << "Enter Name: "; cin >> name;
				cout << "Enter New Name: "; cin >> new_name;
				fileman.RenameFolder(path, name, new_name); 
				system("pause");
				system("cls");
			}
			else if (a == 2)
			{
				system("cls");
				string path, name, new_name;
				cout << "Enter full path without file name: "; cin >> path;
				cout << "Enter Name with expansion : "; cin >> name;
				cout << "Enter New Name with expansion: "; cin >> new_name;
				fileman.RenameFile(path, name, new_name);
				system("pause");
				system("cls");
			}
			else
			{
				cout << " Nope " << endl;
			}
			system("pause");
			system("cls");
			break; 
		}
		case 5:
		{ 
			system("cls");
			int a = 0;
			cout << "1)Copy folder\n2)Copy File \n";
			cout << "Enter : "; cin >> a;
			if (a == 1)
			{
				system("cls");
				string path;
				string destination;
				cout << "Enter full path of Folder : ";
				cin >> path;
				cout << "Enter new path : ";
				cin >> destination;
				fileman.CopyFolder(path.c_str(), destination.c_str());
				system("pause");
				system("cls");
			}
			else
			{
				system("cls");
				string path;
				string destination;
				cout << "Enter full path of File with name and expansion : ";
				cin >> path;
				cout << "Enter new path  with name and expansion of this file : ";
				cin >> destination;
				fileman.copyFile(path.c_str(), destination.c_str());
				system("pause");
				system("cls");
			}
			break;
		}
		case 6:
		{ 
			system("cls"); 
			int a = 0;
			cout << "1)Search folder\n2)Search File \n";
			cout << "Enter : "; cin >> a;
			if (a == 1)
			{
				system("cls");
				string path;
				string s;
				cout << "Enter path : ";
				cin >> path;
				cout << "Enter name Folder : ";
				cin >> s;
				fileman.SearchFolder(path, s);
				system("pause");
				system("cls");
			}
			else
			{
                system("cls");
				string path;
				string s;
				cout << "Enter path : ";
				cin >> path;
				cout << "Enter   name and expansion of this file : ";
				cin >> s;
				fileman.SearchFile(path, s);
				system("pause");
				system("cls");
			} 
			break;
		}
		case 7:
		{
			    system("cls"); 
				string sourcePath;
				string destPath; 
				int count; 
				cout<<"Enter source file path: ";
				cin >> sourcePath;
				cout << "Enter destination file path: ";
				cin>> destPath;  
				 fileman.CopyDataOfFile(sourcePath, destPath);
				 system("cls");
			    cout << "\nFiles copied successfully.\n";  
				system("pause");
				system("cls"); 
			    break;
		}
		case 8:
		{ 
			system("cls");
			int a = 0;
			cout << "1)Replace folder\n2)Replace File \n";
			cout << "Enter : "; cin >> a;
			if (a == 1)
			{
				system("cls");
				string path;
				string destination;
				cout << "Enter full path of Folder : ";
				cin >> path;
				cout << "Enter new path : ";
				cin >> destination;
				fileman.ReplaceFolder(path.c_str(), destination.c_str());
				system("pause");
				system("cls");
			}
			else
			{
				system("cls");
				string path;
				string destination;
				cout << "Enter full path of File : ";
				cin >> path;
				cout << "Enter new path : ";
				cin >> destination;
				fileman.ReplaceFileW(path.c_str(), destination.c_str());
				system("pause");
				system("cls"); 
			}
			break;
		}
		case 10:
		{
			system("cls");
			string key;
			string path;
			string newpath;
			cout << "Enter encryption key : ";
			cin >> key; 
			cout << "Enter path with name and expansion of file : ";
			cin >> path; 
			cout << "Enter path where will keep Encrypted file : ";
			cin >> newpath;
			fileman.XORhashing(path, newpath, key);
			system("pause");
			system("cls");
			break;
		}
		case 11:
		{
			system("cls"); 
			string path;
			string newpath; 
			cout << "Enter path with name and expansion of file : ";
			cin >> path;
			cout << "Enter path where will keep Encrypted file : ";
			cin >> newpath; 
			MD5hashing(path, newpath);
			system("cls");
			cout << "\nFiles encrypted successfully.\n";
			system("pause");
			system("cls");
			break;
		}
	    case 99: 
		{
			system("cls");  
			audiere::OutputStreamPtr sound1 = OpenSound(device, "5.mp3", false);
			sound1->setVolume(0.50);
			sound1->play();
			Sleep(11000); 
			system("cls"); 
			working = false; 
			break; 
		}
		default: 
		{
			audiere::OutputStreamPtr sound1 = OpenSound(device, "kurwa.mp3", false);
			sound1->setVolume(0.50); 
			sound1->play();
			Sleep(500);
			system("cls");  
			break;
		}
	  }
	}   
 
} 