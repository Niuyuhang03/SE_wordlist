#pragma once
#include <string>

using namespace std;

class node {
public:
	string word;
	node* parent;
	node* first_child;		// �ýڵ���׸��ӽڵ�
	node* next;				// �������丸�ڵ��ȫ���ӽڵ�
	int word_num;			// �����ڵ㵽�˽ڵ�����ĵ�������
	int character_num;		// �����ڵ㵽�˽ڵ��������ĸ����

	__declspec(dllexport) node(string cur_word, int cur_word_num, int cur_character_num);
};

class Core {
public:
	__declspec(dllexport) int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	__declspec(dllexport) int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	__declspec(dllexport) bool gen_tree(node* cur_node, char* words[], int len, bool enable_loop, char tail, node* word_max_node, node* char_max_node, int words_index[][2]);
	__declspec(dllexport) bool find_in_chain(node* cur_node, string word);
};