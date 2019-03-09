#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "SE_wordlist.h"

int main()//int argc, char* argv[]
{
	bool valid_flag, enable_loop = false, w_para = false;
	int argc = 5, len = 0, index, chain_length;
	const char* argv[5] = { "SE_wordlist.exe", "-h", "t", "-w", "file.txt" };
	char *result[10000], *words[10000];
	char head = 0, tail = 0;
	Core core;

	valid_flag = command_handler(argc, argv, words, len, head, tail, enable_loop, w_para);
	if (!valid_flag)
		return 0;
	if (w_para)
		chain_length = core.gen_chain_word(words, len, result, head, tail, enable_loop);
	else
		chain_length = core.gen_chain_char(words, len, result, head, tail, enable_loop);
	if (chain_length == -1) {
		cout << "loop exists!\n";
		return 0;
	}
	if (chain_length < 2 && chain_length >= 0) {
		cout << "no chain's length is greater than 1!\n";
		return 0;
	}
	for (index = 0; index < chain_length; index++)
		cout << result[index] << " " << endl;
	return 0;
}