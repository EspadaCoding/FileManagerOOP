#pragma once
#include <string>
#include <iostream> 
class Folder
{
 public:
	void MakeFolder(std::string f, std::string name);
	void DeleteFolder(std::string f);
	void RenameFolder(std::string path, std::string name, std::string new_name);
	void CopyFolder(std::string path, std::string new_path); 
	void ReplaceFolder(std::string path, std::string new_name);
	void SearchFolder(std::string path, std::string s);
};