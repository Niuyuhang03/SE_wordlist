#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Wordlist.h"
#include <time.h>
#include "../Core/Core.h"

int main(int argc, char* argv[])//int argc, char* argv[]
{
	bool valid_flag, enable_loop = false, w_para = false;
	int len = 0, index, chain_length;
	char *result[10000], *words[10000];
	char head = 0, tail = 0;
	Core core;

	valid_flag = command_handler(argc, argv, words, len, head, tail, enable_loop, w_para);
	if (!valid_flag)
		return 0;
	try {
		if (w_para)
			chain_length = core.gen_chain_word(words, len, result, head, tail, enable_loop);
		else
			chain_length = core.gen_chain_char(words, len, result, head, tail, enable_loop);
	}
	catch (HeadInvalidException& e) {
		cout << e.what();
		return 0;
	}
	catch (TailInvalidException& e) {
		cout << e.what();
		return 0;
	}
	catch (LoopException& e) {
		cout << e.what();
		return 0;
	}
	catch (ChainLessThen2Exception& e) {
		cout << e.what();
		return 0;
	}
	ofstream outfile;
	outfile.open("solution.txt");
	for (index = 0; index < chain_length; index++) {
		cout << result[index] << endl;
		outfile << result[index] << endl;
	}
	outfile.close();
	return 0;
}