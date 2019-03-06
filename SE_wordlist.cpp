#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

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
	char* temp_word;
	int i = -1;
	node* temp_node = cur_node->first_child;

	while (word[i++])
		word[i] = tolower(word[i]);
	while (cur_node != NULL) {
		temp_word = cur_node->word;
		i = -1;
		while (temp_word[i++])
			temp_word[i] = tolower(temp_word[i]);
		if (strcmp(temp_word, word) == 0) {
			return true;
		}
		cur_node = cur_node->parent;
	}
	while (temp_node != NULL) {
		temp_word = temp_node->word;
		i = -1;
		while (temp_word[i++])
			temp_word[i] = tolower(temp_word[i]);
		if (strcmp(temp_word, word) == 0) {
			return true;
		}
		temp_node = temp_node->next;
	}
	return false;
}

/*
* 递归生成树
* param:cur_node：当前节点
* param:words：文件中所有单词列表
* param:len：文件中所有单词数量
* param:enable_loop：是否允许出现环标志
* return：出现环标志，enable_loop为false且出现环则返回true，不再生成树。否则返回false
*/
bool gen_tree(node* cur_node, char* words[], int len, bool enable_loop) {
	node *temp_root;
	char cur_tail = (char)tolower(cur_node->word[strlen(cur_node->word) - 1]);
	int j;
	bool find_node, loop_flag = false;
	for (j = 0; j < len; j++) {
		if (loop_flag)
			return loop_flag;
		if ((char)tolower(words[j][0]) == cur_tail) {
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
					while (temp_root->next != NULL)
						temp_root = temp_root->next;
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
* 指令合法性检查
* param:argc：指令项目个数
* param:argv：指令二维数组
* return：指令是否合法，若合法返回true，否则返回false
*/
bool command_check(int argc, char* argv[]) {
	bool r_para = false, w_para = false, c_para = false, h_para = false, t_para = false, error_flag = false;
	int index;
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
					if (h_para) {
						error_flag = true;
						cout << "-h already exists!\n";
						return false;
					}
					else if (index + 1 == argc - 1 || strlen(argv[index + 1]) > 1) {
						error_flag = true;
						cout << "there's no head character or file name!\n";
						return false;
					}
					else {
						index++;
						h_para = true;
					}
					break;
				}
				case('t'): {
					if (t_para) {
						error_flag = true;
						cout << "-t already exists!\n";
						return false;
					}
					else if (index + 1 == argc - 1 || strlen(argv[index + 1]) > 1) {
						error_flag = true;
						cout << "there's no tail character or file name!\n";
						return false;
					}
					else {
						index++;
						t_para = true;
					}
					break;
				}
				case('r'): {
					if (r_para) {
						error_flag = true;
						cout << "-r already exists!\n";
						return false;
					}
					else
						r_para = true;
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
	return true;
}

/*
* 解析指令
* param:argc：指令项目个数
* param:argv：指令二维数组
* param:words：单词数组
*/
void command_handler(int argc, const char* argv[]) {
	char *result[10000], *words[10000];
	char head, tail;
	int len, index;
	bool enable_loop, w_para = false;
	string file_name = argv[argc - 1];

	for (index = 1; index < argc - 1; index++) {
		if (argv[index][0] == '-') {
			switch (argv[index][1]) {
				case('w'): {
					w_para = true;
					break;
				}
				case('c'): {
					break;
				}
				case('h'): {
					index++;
					head = argv[index][0];
					break;
				}
				case('t'): {
					index++;
					tail = argv[index][0];
					break;
				}
				case('r'): {
					enable_loop = true;
					break;
				}
			}
		}
	}

	ifstream in(file_name);
	ostringstream buffer;
	buffer << in.rdbuf();
	string contents(buffer.str());

	// TODO:get words and len from contents.
	int i = 0, top = 0;
	string s="";
	while (i < contents.length()) {
		if ((contents[i] >= 'a'&&contents[i] <= 'z') || (contents[i] >= 'A'&&contents[i] <= 'Z')) {
			s = s + contents[i];
		}
		else if(s!=""){
			words[top] = new char[s.length() + 1]();
			strcpy(words[top++], s.c_str());
			
			s="";
		}
		i++;
	}
	if (s != "") {
		words[top] = new char[s.length() + 1]();
		strcpy(words[top++], s.c_str());

		s = "";
	}
	for (int i = 0; i < top; i++)
		cout << words[i] << endl;
	// 构造测试集
	char tmp1[50] = "apple";
	words[0] = tmp1;
	char tmp2[50] = "team";
	words[1] = tmp2;
	char tmp3[50] = "elephant";
	words[2] = tmp3;
	char tmp4[50] = "egg";
	words[3] = tmp4;
	len = 4;
	
	if (w_para) {
		gen_chain_word(words, len, result, head, tail, enable_loop);
	}
	else {
		gen_chain_char(words, len, result, head, tail, enable_loop);
	}
}


int main()//int argc, char* argv[]
{
	bool valid_flag;
	int argc = 3;
	const char* argv[3] = {"SE_wordlist.exe","-w", "file.txt"};
	//valid_flag = command_check(argc, argv);
	//if (!valid_flag)
		//return 0;

	command_handler(argc, argv);

	return 0;
}

