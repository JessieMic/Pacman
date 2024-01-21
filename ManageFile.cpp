#include "ManageFile.h"

void ManageFile::setFileName(string str)
{
	fileName = str;
}
bool ManageFile::openFileForWriting()
{
	if (fileName == "")
	{
		cout << "No File name detacted";
		return false;
	}
	outFile.open(fileName, std::ios::out);
	if (!outFile.is_open())
	{
		cout << "Coudn't open the file for writing";
		return false;
	}
	return true;
}

bool ManageFile::openFileForReading()
{
	if (fileName == "")
	{
		cout << "No File name detacted";
		return false;
	}
	outFile.open(fileName, std::ios::in);
	if (!outFile.is_open())
	{
		cout << "Coudn't open the file for reading";
		return false;
	}
	return true;
}

bool ManageFile::eof()
{
	return outFile.eof();
}


void ManageFile::getString(string& str)
{
	outFile >> str;
}

void ManageFile::getChar(char& c)
{
	outFile.get(c);
}


void ManageFile::closeFile()
{
	outFile.close();
}

void ManageFile::WriteToFile(string str)
{
	outFile << str;
}

void ManageFile::WriteToFile(char c)
{
	outFile << c << " ";
}

void ManageFile::WriteToFile(int num)
{
	outFile << num << " ";
}