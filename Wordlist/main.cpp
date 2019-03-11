#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Wordlist.h"
#include <time.h>

int main(int argc, char* argv[])//int argc, char* argv[]
{
	// clock_t t1 = clock();
	bool valid_flag, enable_loop = false, w_para = false;
	int len = 0, index, chain_length;
	// const char* argv[5] = { "Wordlist.exe", "-h", "t", "-w", "file.txt" };
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
		cout << "loop exists!";
		return 0;
	}
	if (chain_length < 2 && chain_length >= 0) {
		cout << "no chain's length is greater than 1!";
		return 0;
	}
	ofstream outfile;
	outfile.open("solution.txt");
	for (index = 0; index < chain_length; index++) {
		cout << result[index] << endl;
		outfile << result[index] << endl;
	}
	outfile.close();
	// cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC << endl;
	return 0;
}