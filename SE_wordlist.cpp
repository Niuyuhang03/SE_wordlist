#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class node {
public:
	string word;
	node* parent;
	node* first_child;		// 该节点的首个子节点
	node* next;				// 用作找其父节点的全部子节点
	int word_num;			// 树根节点到此节点的链的单次总数
	int character_num;		// 树根节点到此节点的链的字母总数
	
	node(string cur_word, int cur_word_num, int cur_character_num);
};

node::node(string cur_word, int cur_word_num, int cur_character_num) {
	word = cur_word;
	parent = NULL;
	first_child = NULL;
	next = NULL;
	word_num = cur_word_num;
	character_num = cur_character_num;
}

/*
* 在cur_node所在链上找是否出现过lower_word
* param:cur_node：当前节点
* param:lower_word：要查找的单词
* return:lower_word出现在cur_node所在链上返回true，否则返回false
*/
bool find_in_chain(node* cur_node, string lower_word) {
	string temp_word;
	int i = 0;
	node *child_node = cur_node->first_child, *parent_node = cur_node;

	while (parent_node != NULL) {
		temp_word = parent_node->word;
		i = 0;
		while (temp_word[i]) {
			temp_word[i] = tolower(temp_word[i]);
			i++;
		}
		if (temp_word == lower_word)
			return true;
		parent_node = parent_node->parent;
	}
	while (child_node != NULL) {
		temp_word = child_node->word;
		i = 0;
		while (temp_word[i]) {
			temp_word[i] = tolower(temp_word[i]);
			i++;
		}
		if (temp_word == lower_word) {
			return true;
		}
		child_node = child_node->next;
	}
	return false;
}

/*
* 递归生成树
* param:cur_node：当前节点
* param:words：文件中所有单词列表
* param:len：文件中所有单词数量
* param:enable_loop：是否允许出现环标志
* param:tail：要求的结尾字母
* param:word_max_node：单词最多节点指针
* param:char_max_node：字母最多节点指针
* return：出现环标志，enable_loop为false且出现环则返回true，不再生成树。否则返回false
*/
bool gen_tree(node* cur_node, char* words[], int len, bool enable_loop, char tail, node* word_max_node, node* char_max_node) {
	node *temp_root;
	char cur_tail = (char)tolower(cur_node->word[cur_node->word.size() - 1]);
	int j;
	bool find_node, loop_flag = false, leaf_flag = true;
	string lower_word, lower_curnode_word;

	for (j = 0; j < len; j++) {
		if (loop_flag)
			return loop_flag;
		lower_word = words[j];
		transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
		if ((char)tolower(words[j][0]) == cur_tail) {
			find_node = find_in_chain(cur_node, lower_word);
			if (find_node == true) {
				lower_curnode_word = cur_node->word;
				transform(lower_curnode_word.begin(), lower_curnode_word.end(), lower_curnode_word.begin(), ::tolower);
				if (enable_loop == false && lower_curnode_word != lower_word) {
					cout << "loop exists!\n";
					loop_flag = true;
					return loop_flag;
				}
			}
			else {
				leaf_flag = false;
				if (cur_node->first_child == NULL) {
					temp_root = new node(words[j], cur_node->word_num + 1, cur_node->character_num + strlen(words[j]));
					cur_node->first_child = temp_root;
					temp_root->parent = cur_node;
					loop_flag = gen_tree(temp_root, words, len, enable_loop, tail, word_max_node, char_max_node);
				}
				else {
					temp_root = cur_node->first_child;
					while (temp_root->next != NULL)
						temp_root = temp_root->next;
					temp_root->next = new node(words[j], cur_node->word_num + 1, cur_node->character_num + strlen(words[j]));
					temp_root->next->parent = cur_node;
					loop_flag = gen_tree(temp_root->next, words, len, enable_loop, tail, word_max_node, char_max_node);
				}
			}
		}
	}
	if ((tail == 0 && leaf_flag) || (tail != 0 && tolower(cur_node->word[cur_node->word.size() - 1]) == tail)){
		if (cur_node->character_num > char_max_node->character_num) {
			char_max_node->word = cur_node->word;
			char_max_node->parent = cur_node->parent;
			char_max_node->character_num = cur_node->character_num;
		}
		if (cur_node->word_num > word_max_node->word_num) {
			word_max_node->word = cur_node->word;
			word_max_node->parent = cur_node->parent;
			word_max_node->word_num = cur_node->word_num;
		}
	}
	return loop_flag;
}

/*
* 计算最多单词数量的最长单词链
* param:words：文件中所有单词列表
* param:len：文件中所有单词数量
* param:result：最长链结果列表
* param:head：要求开头字母，无要求为0
* param:tail：要求结尾字母，无要求为0
* param:enable_loop：是否允许出现环标志，不允许成环时为false，否则为true
* return：若没有链或enable_loop为false时出现环，返回0。否则返回环长度
*/
int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
	int max_length = 0, cur_length = 0, i, root_node_cnt = 0;
	node *root_node = NULL, *word_max_node, *char_max_node;
	node* root_node_list[10000];
	bool loop_flag;
	char* pre_result[10000];
	word_max_node = new node("", 0, 0);
	char_max_node = new node("", 0, 0);
	for (i = 0; i < len; i++) {
		if (head != 0 && tolower(words[i][0]) != head)
			continue;
		root_node = new node(words[i], 1, strlen(words[i]));
		root_node_list[root_node_cnt++] = root_node;
		loop_flag = gen_tree(root_node, words, len, enable_loop, tail, word_max_node, char_max_node);
		if (loop_flag)
			return 0;
	}

	if (word_max_node->parent == NULL || word_max_node->word == "")
		return 0;
	int top = -1;
	while (word_max_node != NULL) {
		pre_result[++top] = new char[word_max_node->word.length() + 1]();
		strcpy(pre_result[top], word_max_node->word.c_str());
		word_max_node = word_max_node->parent;
	}
	for (i = 0; i < top + 1; i++) {
		result[i] = new char[strlen(pre_result[top - i])]();
		strcpy(result[i], pre_result[top - i]);
	}
	return top + 1;
}

/*
* 计算最多字母数量的最长单词链
* param:words：文件中所有单词列表
* param:len：文件中所有单词数量
* param:result：最长链结果列表
* param:head：要求开头字母，无要求为0
* param:tail：要求结尾字母，无要求为0
* param:enable_loop：是否允许出现环标志，不允许成环时为false，否则为true
* return：若没有链或enable_loop为false时出现环，返回0。否则返回环长度
*/
int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
	int max_length = 0, cur_length = 0, i, root_node_cnt = 0;
	node *root_node = NULL, *word_max_node, *char_max_node;
	node* root_node_list[10000];
	bool loop_flag;
	char* pre_result[10000];
	word_max_node = new node("", 0, 0);
	char_max_node = new node("", 0, 0);
	for (i = 0; i < len; i++) {
		if (head != 0 && tolower(words[i][0]) != head)
			continue;
		root_node = new node(words[i], 1, strlen(words[i]));
		root_node_list[root_node_cnt++] = root_node;
		loop_flag = gen_tree(root_node, words, len, enable_loop, tail, word_max_node, char_max_node);
		if (loop_flag)
			return 0;
	}

	if (char_max_node->parent == NULL || char_max_node->word == "")
		return 0;
	int top = -1;
	while (char_max_node != NULL) {
		pre_result[++top] = new char[char_max_node->word.length() + 1]();
		strcpy(pre_result[top], char_max_node->word.c_str());
		char_max_node = char_max_node->parent;
	}
	for (i = 0; i < top + 1; i++) {
		result[i] = new char[strlen(pre_result[top - i])]();
		strcpy(result[i], pre_result[top - i]);
	}
	return top + 1;
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
bool command_handler(int argc, const char* argv[], char* words[], int &len, char &head, char &tail, bool &enable_loop, bool &w_para) {
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
						cout << "-w or -c already exists!\n";
						return false;
					}
					else
						w_para = true;
					break;
				}
				case('c'): {
					if (w_para | c_para) {
						error_flag = true;
						cout << "-w or -c already exists!\n";
						return false;
					}
					else
						c_para = true;
					break;
				}
				case('h'): {
					if (head != 0) {
						error_flag = true;
						cout << "-h already exists!\n";
						return false;
					}
					else if (index + 1 == argc - 1 || strlen(argv[index + 1]) > 1) {
						error_flag = true;
						cout << "there's no head character or file name!\n";
						return false;
					}
					else
						head = tolower(argv[++index][0]);
					break;
				}
				case('t'): {
					if (tail != 0) {
						error_flag = true;
						cout << "-t already exists!\n";
						return false;
					}
					else if (index + 1 == argc - 1 || strlen(argv[index + 1]) > 1) {
						error_flag = true;
						cout << "there's no tail character or file name!\n";
						return false;
					}
					else
						tail = tolower(argv[++index][0]);
					break;
				}
				case('r'): {
					if (enable_loop) {
						error_flag = true;
						cout << "-r already exists!\n";
						return false;
					}
					else
						enable_loop = true;
					break;
				}
				default: {
					error_flag = true;
					cout << "parameter invalid!\n";
					return false;
				}
			}
		}
		else if (index == argc - 1) {
			string file_name = argv[index];
			ifstream in(file_name);
			if (!in) {
				error_flag = true;
				cout << "file doesn't exist!\n";
				return false;
			}
		}
		else {
			error_flag = true;
			cout << "file name already exists!\n";
			return false;
		}
	}
	if (!(w_para | c_para)) {
		error_flag = true;
		cout << "-w and -c all miss!\n";
		return false;
	}

	ifstream in(file_name);
	ostringstream buffer;
	buffer << in.rdbuf();
	string contents(buffer.str());
	int contents_length = contents.length();
	string s = "";
	for (index = 0; index < contents_length; index++) {
		if ((contents[index] >= 'a'&&contents[index] <= 'z') || (contents[index] >= 'A'&&contents[index] <= 'Z')) {
			s = s + contents[index];
		}
		else if (s != "") {
			words[len] = new char[s.length() + 1]();
			strcpy(words[len++], s.c_str());
			s = "";
		}
	}
	if (s != "") {
		words[len] = new char[s.length() + 1]();
		strcpy(words[len++], s.c_str());
	}
	return true;
}

int main()//int argc, char* argv[]
{
	bool valid_flag, enable_loop = false, w_para = false;
	int argc = 4, len = 0, index, chain_length;
	const char* argv[4] = {"SE_wordlist.exe", "-r", "-w", "file.txt"};
	char *result[10000], *words[10000];
	char head = 0, tail = 0;

	valid_flag = command_handler(argc, argv, words, len, head, tail, enable_loop, w_para);
	if (!valid_flag)
		return 0;
	if (w_para)
		chain_length = gen_chain_word(words, len, result, head, tail, enable_loop);
	else
		chain_length = gen_chain_char(words, len, result, head, tail, enable_loop);
	if (chain_length < 2 && chain_length > 0) {
		cout << "no chain's length is greater than 1!\n";
		return 0;
	}
	for (index = 0; index < chain_length; index++)
		cout << result[index] << " " << endl;
	return 0;
}

