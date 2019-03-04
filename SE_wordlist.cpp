#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class node {
public:
	char* word;
	node* parent;
	node* first_child;		// 该节点的首个子节点
	node* next;				// 用作找其父节点的全部子节点
	int word_num;			// 树根节点到此节点的链的单次总数
	int character_num;		// 树根节点到此节点的链的字母总数
	
	node(char* cur_word, int cur_word_num, int cur_character_num);
};

node::node(char* cur_word, int cur_word_num, int cur_character_num) {
	word = cur_word;
	parent = NULL;
	first_child = NULL;
	next = NULL;
	word_num = cur_word_num;
	character_num = cur_character_num;
}

/*
* 在cur_node所在链上找是否出现过word
* param:cur_node：当前节点
* param:word：要查找的单词
* return:word出现在cur_node所在链上返回true，否则返回false
*/
bool find_in_chain(node* cur_node, char* word) {
	while (cur_node != NULL) {
		if (strcmp(cur_node->word, word) == 0) {
			return true;
		}
		cur_node = cur_node->parent;
	}
	return false;
}

/*
* 递归生成树
* param:cur_node：当前节点
* param:words：文件中所有单词列表
* param:len：文件中所有单词数量
* param:enable_loop：是否允许出现环标志
* return：出现环标志，出现则返回true，不再生成树。否则返回false
*/
bool gen_tree(node* cur_node, char* words[], int len, bool enable_loop) {
	node *temp_root;
	char cur_tail = cur_node->word[strlen(cur_node->word) - 1];
	int j;
	bool find_node, loop_flag = false;
	for (j = 0; j < len; j++) {
		if (loop_flag) {
			return loop_flag;
		}
		if (words[j][0] == cur_tail) {
			find_node = find_in_chain(cur_node, words[j]);
			if (find_node == true && enable_loop == false) {
				cout << "loop exists!\n";
				loop_flag = true;
				return loop_flag;
			}
			else if (find_node == false) {
				if (cur_node->first_child == NULL) {
					temp_root = new node(words[j], cur_node->word_num + 1, cur_node->character_num + strlen(words[j]));
					cur_node->first_child = temp_root;
					temp_root->parent = cur_node;
					loop_flag = gen_tree(temp_root, words, len, enable_loop);
				}
				else {
					temp_root = cur_node->first_child;
					while (temp_root->next != NULL) {
						temp_root = temp_root->next;
					}
					temp_root->next = new node(words[j], cur_node->word_num + 1, cur_node->character_num + strlen(words[j]));
					temp_root->next->parent = cur_node;
					loop_flag = gen_tree(temp_root->next, words, len, enable_loop);
				}
			}
		}
	}
	return loop_flag;
}

/*
* 计算最多单词数量的最长单词链
* param:words：文件中所有单词列表
* param:len：文件中所有单词数量
* param:result：最长链结果列表
* param:head：要求开头字母，无要求是为0
* param:tail：要求结尾字母，无要求是为0
* param:enable_loop：是否允许出现环标志，不允许成环时为false，否则为true
* return：若没有链或enable_loop为false时出现环，返回0。否则返回环长度
*/
int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
	int max_length = 0, cur_length = 0, i, root_node_cnt = 0;
	node *root_node = NULL;
	node* root_node_list[10000];
	bool loop_flag;
	for (i = 0; i < len; i++) {
		root_node = new node(words[i], 1, strlen(words[i]));
		root_node_list[root_node_cnt++] = root_node;
		loop_flag = gen_tree(root_node, words, len, enable_loop);
		if (loop_flag) {
			return 0;
		}
	}

	// TODO：find max_length and return, print chain in file
}

/*
* 计算最多字母数量的最长单词链
* param:words：文件中所有单词列表
* param:len：文件中所有单词数量
* param:result：最长链结果列表
* param:head：要求开头字母，无要求是为0
* param:tail：要求结尾字母，无要求是为0
* param:enable_loop：是否允许出现环标志，不允许成环时为false，否则为true
* return：若没有链或enable_loop为false时出现环，返回0。否则返回环长度
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
	char *words[10000], *result[10000];
	bool enable_loop = false, w_command = false, c_command = false, h_command = false, t_command = false, error_flag = false;
	int index, len;
	getline(cin, command);
	for (index = 0; index < command.size(); index++) {
		if (error_flag) {
			break;
		}
		if (command[index] == '-') {
			index++;
			switch (command[index]) {
				case('w'): {
					if (w_command | c_command) {
						error_flag = true;
					}
					w_command = true;
					index++;
					break;
				}
				case('c'): {
					if (w_command | c_command) {
						error_flag = true;
					}
					c_command = true;
					index++;
					break;
				}
				case('h'): {
					if (h_command) {
						error_flag = true;
					}
					h_command = true;
					index += 2;
					head = command[index];
					index++;
					break;
				}
				case('t'): {
					if (t_command) {
						error_flag = true;
					}
					t_command = true;
					index += 2;
					tail = command[index];
					index++;
					break;
				}
				case('r'): {
					if (enable_loop) {
						error_flag = true;
					}
					enable_loop = true;
					index++;
					break;
				}
				default: {
					error_flag = true;
					break;
				}
			}
		}
		else {
			file_name = command.substr(index);
			break;
		}
	}
	if (!(w_command | c_command)) {
		error_flag = true;
	}
	if (error_flag) {
		cout << "error exists in command!\n";
		return;
	}
	// 解析文件
	ifstream in(file_name);
	if (!in) {
		error_flag = true;
		cout << "file doesn't exist!\n";
		return;
	}
	ostringstream buffer;
	buffer << in.rdbuf();
	string contents(buffer.str());
	// TODO:get words(type:char**) and len from contents(type:string), one word exists once
	//char tmp1[50] = "apple";
	//words[0] = tmp1;
	//char tmp2[50] = "team";
	//words[1] = tmp2;
	//char tmp3[50] = "elephant";
	//words[2] = tmp3;
	//char tmp4[50] = "egg";
	//words[3] = tmp4;
	//len = 4;

	if (w_command) {
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

