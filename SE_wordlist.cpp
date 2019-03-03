#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class node {
public:
	string word;
	node* parent;
	node* first_child;		// 该节点的首个子节点
	node* next;				// 用作找其父节点的全部子节点
	int word_num;			// 树根节点到此节点的链的单次总数
	int character_num;		// 树根节点到此节点的链的字母总数
};

/*
* 计算最多单词数量的最长单词链
* head和tail无约束时为0，不允许成环时enable_loop为false
*/
int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
	// TODO:generate tree, find chain which has max words
	return 0;
}

/*
* 计算最多字母数量的最长单词链
* head和tail无约束时为0，不允许成环时enable_loop为false
*/
int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
	// TODO:generate tree, find chain which has max characters
	return 0;
}

/*
* 处理指令
*/
void handle_command() {
	string command, file_name;
	char head = 0, tail = 0;
	char **words, **result;
	bool enable_loop = false, word_style = true;
	int index, len;
	cin >> command;
	// 解析指令
	for (index = 0; index < command.size(); index++) {
		if (command[index] == '-') {
			index++;
			switch (command[index]) {
				case('w'): {
					index++;
					break;
				}
				case('c'): {
					word_style = false;
					index++;
					break;
				}
				case('h'): {
					index += 2;
					head = command[index];
					index++;
					break;
				}
				case('t'): {
					index += 2;
					tail = command[index];
					index++;
					break;
				}
				case('r'): {
					enable_loop = true;
					index++;
					break;
				}
			}
		}
		else {
			file_name = command.substr(index);
			break;
		}
	}
	// 解析文件
	ifstream in(file_name);
	ostringstream buffer;
	buffer << in.rdbuf();
	string contents(buffer.str());
	// TODO:get words(type:char**) and len from contents(type:string)

	if (word_style) {
		gen_chain_word(words, len, result, head, tail, enable_loop);
	}
	else {
		gen_chain_char(words, len, result, head, tail, enable_loop);
	}
}

int main()
{
	handle_command();
	return 0;
}

