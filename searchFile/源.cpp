#include <Windows.h>
#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <vector>
#include <io.h>
using namespace std;

BOOL get_drive_info(vector<string> &drive);
void get_files(string path,vector<string>&files);
BOOL is_file_exist(string file);

int main(int argc, char* argv[])
{
	vector<string>pan;
	get_drive_info(pan);
	vector<string>files;
	for (auto path : pan)
		get_files(path, files);

	system("pause");
	return 0;
}

// 获取所有盘符的名称：C:\ D:\ ……
BOOL get_drive_info(vector<string> &drive)
{
	DWORD len = GetLogicalDriveStrings(0, NULL);
	char drivers[1000];
	GetLogicalDriveStrings(len, drivers);
	UINT32 i = 0;
	string path = "";
	while (i < len)
	{
		if (drivers[i] != '\0')
			path += drivers[i];
		else
		{
			drive.push_back(path);
			path = "";
		}
		i++;
	}
	return TRUE;
}
BOOL is_file_exist(string file)
{
	if (_access(file.c_str(), 0) != -1)
		return TRUE;
	else
		return FALSE;
}
// 获取所有目录和文件名，递归

void get_files(string path, vector<string>& files)//lxk20160302
{
	//文件句柄
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	cout << path.c_str() << endl;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		_findnext(hFile, &fileinfo);
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				cout << fileinfo.name << endl;
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					get_files(p.assign(path).append("\\").append(fileinfo.name), files);
				continue;
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}