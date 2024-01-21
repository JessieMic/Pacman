#ifndef _ManageFile
#define _ManageFile

#include "General.h"

class ManageFile
{

	bool save = false;
	string fileName = "";
	std::fstream outFile;
public:
	void setFileName(string str);
	bool openFileForWriting();
	bool openFileForReading();
	void closeFile();
	void WriteToFile(string str);
	void WriteToFile(char c);	
	void WriteToFile(int num);
	void getChar(char& c);
	void getString(string& str);
	bool eof();
};

#endif