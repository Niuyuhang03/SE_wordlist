#pragma once
#include <string>

using namespace std;

class node {
public:
	string word;
	node* parent;
	node* first_child;		// 该节点的首个子节点
	node* next;				// 用作找其父节点的全部子节点
	int word_num;			// 树根节点到此节点的链的单次总数
	int character_num;		// 树根节点到此节点的链的字母总数

	__declspec(dllexport) node(string cur_word, int cur_word_num, int cur_character_num);
};

class Core {
public:
	__declspec(dllexport) int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	__declspec(dllexport) int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	__declspec(dllexport) bool gen_tree(node* cur_node, char* words[], int len, bool enable_loop, char tail, node* word_max_node, node* char_max_node, int words_index[][2]);
	__declspec(dllexport) bool find_in_chain(node* cur_node, string word);
};