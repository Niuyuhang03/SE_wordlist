#pragma once
#include <string>

using namespace std;

struct HeadInvalidException : public exception
{
	const char * what() const throw ()
	{
		return "head is invalid!";
	}
};

struct TailInvalidException : public exception
{
	const char * what() const throw ()
	{
		return "tail is invalid!";
	}
};

struct LoopException : public exception
{
	const char * what() const throw ()
	{
		return "loop exists!";
	}
};

struct ChainLessThen2Exception : public exception
{
	const char * what() const throw ()
	{
		return "length of chain is less than 2!";
	}
};

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

int compare(const void *a, const void *b);