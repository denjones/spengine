#pragma once
#include <string>

using namespace std;

class PackFile
{
public:
	string GetFileName();
	void SetFileName(string name);
	bool IsPackExist();
private:
	string fileName;
};