#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Wordlist.h"
#include "Core.h"

using namespace std;

/*
* 比较函数，用于对words排序
*/
int compare(const void *a, const void *b) {
	return strcmp(*(char **)a, *(char **)b);
}

/*
* 处理指令
* param:argc：指令项目个数
* param:argv：指令二维数组
* param:words：文件中所有单词列表
* param:len：文件中所有单词数量
* param:head：要求开头字母，无要求为0
* param:tail：要求结尾字母，无要求为0
* param:enable_loop：是否允许出现环标志，不允许成环时为false，否则为true
* param:w_para：-w参数出现标志，用于主函数中调用不同生成链函数
* return：指令是否合法，若合法返回true，否则返回false
*/
bool command_handler(int argc, char* argv[], char* words[], int &len, char &head, char &tail, bool &enable_loop, bool &w_para) {
	bool error_flag = false, c_para = false;
	int index;
	string file_name = argv[argc - 1];
	for (index = 1; index < argc; index++) {
		if (error_flag)
			break;
		if (argv[index][0] == '-' && index != argc - 1 && strlen(argv[index]) == 2) {
			switch (argv[index][1]) {
			case('w'): {
				if (w_para | c_para) {
					error_flag = true;
					cout << "-w or -c already exists!";
					return false;
				}
				else
					w_para = true;
				break;
			}
			case('c'): {
				if (w_para | c_para) {
					error_flag = true;
					cout << "-w or -c already exists!";
					return false;
				}
				else
					c_para = true;
				break;
			}
			case('h'): {
				if (head != 0) {
					error_flag = true;
					cout << "-h already exists!";
					return false;
				}
				else if (index + 1 == argc - 1 || strlen(argv[index + 1]) > 1) {
					error_flag = true;
					cout << "there's no head character or file name!";
					return false;
				}
				else
					head = tolower(argv[++index][0]);
				break;
			}
			case('t'): {
				if (tail != 0) {
					error_flag = true;
					cout << "-t already exists!";
					return false;
				}
				else if (index + 1 == argc - 1 || strlen(argv[index + 1]) > 1) {
					error_flag = true;
					cout << "there's no tail character or file name!";
					return false;
				}
				else
					tail = tolower(argv[++index][0]);
				break;
			}
			case('r'): {
				if (enable_loop) {
					error_flag = true;
					cout << "-r already exists!";
					return false;
				}
				else
					enable_loop = true;
				break;
			}
			default: {
				error_flag = true;
				cout << "parameter invalid!";
				return false;
			}
			}
		}
		else if (index == argc - 1) {
			string file_name = argv[index];
			ifstream in(file_name);
			if (!in) {
				error_flag = true;
				cout << "file doesn't exist!";
				return false;
			}
		}
		else {
			error_flag = true;
			cout << "file name already exists!";
			return false;
		}
	}
	if (!(w_para | c_para)) {
		error_flag = true;
		cout << "-w and -c all miss!";
		return false;
	}

	ifstream in(file_name);
	ostringstream buffer;
	buffer << in.rdbuf();
	string contents(buffer.str());
	int contents_length = int(contents.length());
	string s = "";
	for (index = 0; index < contents_length; index++) {
		if ((contents[index] >= 'a'&&contents[index] <= 'z') || (contents[index] >= 'A'&&contents[index] <= 'Z'))
			s = s + contents[index];
		else if (s != "") {
			words[len] = new char[s.length() + 1]();
			transform(s.begin(), s.end(), s.begin(), ::tolower);
			strcpy_s(words[len++], strlen(s.c_str()) + 1, s.c_str());
			s = "";
		}
	}
	if (s != "") {
		words[len] = new char[s.length() + 1]();
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		strcpy_s(words[len++], strlen(s.c_str()) + 1, s.c_str());
	}
	if (len == 0) {
		cout << "no words in file!";
		return false;
	}
	qsort(words, len, sizeof(words[0]), compare);
	int cnt = 1;
	for (index = 1; index < len; index++) {
		if (strcmp(words[index], words[index - 1]) != 0) {
			strcpy_s(words[cnt++], strlen(words[index]) + 1, words[index]);
		}
	}
	len = cnt;
	return true;
}
