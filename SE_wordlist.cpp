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
* 在cur_node所在链上找是否出现过word，出现过则返回true
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
* 递归生成树，返回循环标志loop_flag。如果loop_flag为true，不再生成。
*/
bool gen_tree(node* cur_node, char* words[], int len, bool enable_loop) {
	node *temp_root;
	char cur_tail;
	int j;
	bool find_node, loop_flag = false;
	cur_tail = cur_node->word[strlen(cur_node->word) - 1];
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
* head和tail无约束时为0，不允许成环时enable_loop为false
*/
int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
	// TODO:generate tree, find chain which has max words
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
	char *words[10000], *result[10000];
	bool enable_loop = false, word_style = true;
	int index, len;
	cin >> command;
	// 解析指令
	for (index = 0; index < command.size(); index++) {
		if (command[index] == '-') {
			index++;
			// TODO:handle error
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
	//char tmp1[50] = "apple";
	//words[0] = tmp1;
	//char tmp2[50] = "team";
	//words[1] = tmp2;
	//char tmp3[50] = "elephant";
	//words[2] = tmp3;
	//char tmp4[50] = "egg";
	//words[3] = tmp4;
	//len = 4;

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

