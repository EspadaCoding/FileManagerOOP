#pragma once
#include <string>
#include <iostream> 
 
class File 
{
public: 
	void MakeFile(std::string f, std::string name, std::string mode);
	void Delete_File(std::string f, std::string name);
	void RenameFile(std::string path, std::string name, std::string new_name);
	bool copyFile(const char* source, const char* destination);
	void CopyDataOfFile(std::string path, std::string out);
	void XORhashing(std::string path, std::string out, std::string key);
	bool ReplaceFileW(const char* source, const char* destination);
	void SearchFile(std::string path, std::string s);
};