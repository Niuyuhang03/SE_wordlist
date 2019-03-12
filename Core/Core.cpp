#include "stdafx.h"
#include "Core.h"
#include <Windows.h>

using namespace std;

node::node(string cur_word, int cur_word_num, int cur_character_num) {
	word = cur_word;
	parent = NULL;
	first_child = NULL;
	next = NULL;
	word_num = cur_word_num;
	character_num = cur_character_num;
}

/*
* 比较函数，用于对words排序
*/
int compare(const void *a, const void *b) {
	return strcmp(*(char **)a, *(char **)b);
}

/*
* 在cur_node所在链上找是否出现过word
* param:cur_node：当前节点
* param:word：要查找的单词
* return:word出现在cur_node所在链上返回true，否则返回false
*/
bool Core::find_in_chain(node* cur_node, string word) {
	string temp_word;
	int i = 0;
	/*node *child_node = cur_node->first_child;*/
	node *parent_node = cur_node;

	while (parent_node != NULL) {
		temp_word = parent_node->word;
		if (temp_word == word)
			return true;
		parent_node = parent_node->parent;
	}
	/*while (child_node != NULL) {
		temp_word = child_node->word;
		if (temp_word == word) {
			return true;
		}
		child_node = child_node->next;
	}*/
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
* param:words_index：words的首字母索引
* return：出现环标志，enable_loop为false且出现环则返回true，不再生成树。否则返回false
*/
bool Core::gen_tree(node* cur_node, char* words[], int len, bool enable_loop, char tail, node* word_max_node, node* char_max_node, int words_index[][2]) {
	node *temp_root;
	char cur_tail = cur_node->word[cur_node->word.size() - 1];
	int j;
	bool find_node, loop_flag = false, leaf_flag = true;

	for (j = words_index[cur_tail - 'a'][0]; j <= words_index[cur_tail - 'a'][1]; j++) {
		if (loop_flag)
			return loop_flag;
		if (words[j][0] == cur_tail) {
			find_node = find_in_chain(cur_node, words[j]);
			if (find_node == true) {
				if (enable_loop == false && cur_node->word != words[j]) {
					loop_flag = true;
					return loop_flag;
				}
			}
			else {
				leaf_flag = false;
				if (cur_node->first_child == NULL) {
					temp_root = new node(words[j], cur_node->word_num + 1, cur_node->character_num + int(strlen(words[j])));
					cur_node->first_child = temp_root;
					temp_root->parent = cur_node;
					// cout << words[j] << "->";
					loop_flag = gen_tree(temp_root, words, len, enable_loop, tail, word_max_node, char_max_node, words_index);
				}
				else {
					temp_root = cur_node->first_child;
					while (temp_root->next != NULL)
						temp_root = temp_root->next;
					temp_root->next = new node(words[j], cur_node->word_num + 1, cur_node->character_num + int(strlen(words[j])));
					temp_root->next->parent = cur_node;
					// cout << words[j] << "->";
					loop_flag = gen_tree(temp_root->next, words, len, enable_loop, tail, word_max_node, char_max_node, words_index);
				}
			}
		}
	}
	if (loop_flag)
		return loop_flag;
	if ((tail == 0 && leaf_flag) || (tail != 0 && cur_node->word[cur_node->word.size() - 1] == tail)) {
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
int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
	int max_length = 0, cur_length = 0, i, root_node_cnt = 0;
	node *root_node = NULL, *word_max_node, *char_max_node;
	node* root_node_list[10000];
	bool loop_flag;
	char* pre_result[10000];
	word_max_node = new node("", 0, 0);
	char_max_node = new node("", 0, 0);

	qsort(words, len, sizeof(words[0]), compare);
	/*int cnt = 1;
	for (i = 1; i < len; i++) {
		if (strcmp(words[i], words[i - 1]) != 0) {
			strcpy_s(words[cnt++], strlen(words[i]) + 1, words[i]);
		}
	}
	len = cnt;*/

	int words_index[26][2] = { 0 };
	char cur_head = 'a';
	for (i = 0; i < len; i++) {
		if (words[i][0] != cur_head) {
			if (i != 0)
				words_index[cur_head - 'a'][1] = i - 1;
			cur_head = words[i][0];
			words_index[cur_head - 'a'][0] = i;
		}
	}
	words_index[cur_head - 'a'][1] = len - 1;

	for (i = 0; i < len; i++) {
		if (head != 0 && words[i][0] != head)
			continue;
		root_node = new node(words[i], 1, int(strlen(words[i])));
		root_node_list[root_node_cnt++] = root_node;
		loop_flag = gen_tree(root_node, words, len, enable_loop, tail, word_max_node, char_max_node, words_index);
		if (loop_flag)
			return -1;
	}

	if (word_max_node->parent == NULL || word_max_node->word == "")
		return 0;
	int top = -1;
	while (word_max_node != NULL) {
		pre_result[++top] = new char[word_max_node->word.length() + 1]();
		strcpy_s(pre_result[top], strlen(word_max_node->word.c_str()) + 1, word_max_node->word.c_str());
		word_max_node = word_max_node->parent;
	}
	for (i = 0; i < top + 1; i++) {
		result[i] = new char[strlen(pre_result[top - i])]();
		strcpy_s(result[i], strlen(pre_result[top - i]) + 1, pre_result[top - i]);
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
int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
	int max_length = 0, cur_length = 0, i, root_node_cnt = 0;
	node *root_node = NULL, *word_max_node, *char_max_node;
	node* root_node_list[10000];
	bool loop_flag;
	char* pre_result[10000];
	word_max_node = new node("", 0, 0);
	char_max_node = new node("", 0, 0);

	qsort(words, len, sizeof(words[0]), compare);
	/*int cnt = 1;
	for (i = 1; i < len; i++) {
		if (strcmp(words[i], words[i - 1]) != 0) {
			strcpy_s(words[cnt++], strlen(words[i]) + 1, words[i]);
		}
	}
	len = cnt;*/

	int words_index[26][2] = { 0 };
	char cur_head = 'a';
	for (i = 0; i < len; i++) {
		if (words[i][0] != cur_head) {
			if (i != 0)
				words_index[cur_head - 'a'][1] = i - 1;
			cur_head = words[i][0];
			words_index[cur_head - 'a'][0] = i;
		}
	}
	words_index[cur_head - 'a'][1] = len - 1;

	for (i = 0; i < len; i++) {
		if (head != 0 && words[i][0] != head)
			continue;
		root_node = new node(words[i], 1, int(strlen(words[i])));
		root_node_list[root_node_cnt++] = root_node;
		loop_flag = gen_tree(root_node, words, len, enable_loop, tail, word_max_node, char_max_node, words_index);
		if (loop_flag)
			return -1;
	}

	if (char_max_node->parent == NULL || char_max_node->word == "")
		return 0;
	int top = -1;
	while (char_max_node != NULL) {
		pre_result[++top] = new char[char_max_node->word.length() + 1]();
		strcpy_s(pre_result[top], strlen(char_max_node->word.c_str()) + 1, char_max_node->word.c_str());
		char_max_node = char_max_node->parent;
	}
	for (i = 0; i < top + 1; i++) {
		result[i] = new char[strlen(pre_result[top - i])]();
		strcpy_s(result[i], strlen(pre_result[top - i]) + 1, pre_result[top - i]);
	}
	return top + 1;
}