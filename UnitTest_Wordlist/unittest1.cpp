#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../Wordlist/Wordlist.h"
#include "../Core/Core.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{


	TEST_CLASS(UnitTest_gen_tree)
	{
		std::string cur_word = "aj";
		char* words[5] = { "aj", "hdfdrs", "jhgjh", "kjhjh", "sdfghi" };
		char *result[10000];
		Core core_test;
		node *node1, *word_max_node, *char_max_node;
		int cur_word_num = 0, cur_character_num = 0;


	public:

		TEST_METHOD(UnitTest_gen_tree1)
		{
			// TODO: 在此输入测试代码
			//disable
			node1 = new node(cur_word, cur_word_num, cur_character_num);
			word_max_node = new node("", 0, 0);
			char_max_node = new node("", 0, 0);
			char head = 0, tail = 0;
			int len = 5;
			int  words_index[26][2] = { 0 };
			words_index['a' - 'a'][0] = 0;
			words_index['a' - 'a'][1] = 0;
			words_index['h' - 'a'][0] = 1;
			words_index['h' - 'a'][1] = 1;
			words_index['j' - 'a'][0] = 2;
			words_index['j' - 'a'][1] = 2;
			words_index['k' - 'a'][0] = 3;
			words_index['k' - 'a'][1] = 3;
			words_index['s' - 'a'][0] = 4;
			words_index['s' - 'a'][1] = 4;
			Assert::IsFalse(core_test.gen_tree(node1, words, len, false, 0, word_max_node, char_max_node, words_index));
			string word = "djkg";
			Assert::IsFalse(core_test.find_in_chain(node1, word));
			//word = "jhgjh";
			//Assert::IsTrue(core_test.find_in_chain(node1, word));
			//able
			Assert::IsFalse(core_test.gen_tree(node1, words, len, true, 0, word_max_node, char_max_node, words_index));
			Assert::AreEqual(core_test.gen_chain_word(words, len, result, head, tail, true), 4);
			Assert::AreEqual(core_test.gen_chain_word(words, len, result, 'k', tail, true), 3);
			Assert::AreEqual(core_test.gen_chain_word(words, len, result, head, 's', true), 3);
			char* words[5] = { "aj", "hdfdrs", "jhgjh", "kjhjh", "sdfghj" };
			Assert::IsTrue(core_test.gen_tree(node1, words, len, false, 0, word_max_node, char_max_node, words_index));
			try
			{
				core_test.gen_chain_char(words, len, result, head, tail, false);
				Assert::IsTrue(false);
			}
			catch(struct LoopException &e)
			{
				Assert::IsTrue(true);
			}
			catch(...)
			{
				Assert::IsTrue(false);
			}
			


		}
		TEST_METHOD(UnitTest_gen_tree2)
		{
			// TODO: 在此输入测试代码
			//disable
			node1 = new node(cur_word, cur_word_num, cur_character_num);
			word_max_node = new node("", 0, 0);
			char_max_node = new node("", 0, 0);
			int len = 5;
			int  words_index[26][2] = { 0 };
			words_index['a' - 'a'][0] = 0;
			words_index['a' - 'a'][1] = 0;
			words_index['h' - 'a'][0] = 1;
			words_index['h' - 'a'][1] = 2;
			words_index['j' - 'a'][0] = 3;
			words_index['j' - 'a'][1] = 3;
			words_index['k' - 'a'][0] = 4;
			words_index['k' - 'a'][1] = 4;
			//able
			char* words[5] = { "aj", "hdfdrs", "hjhjh", "jhgjh", "kdfghj" };
			string word = "hdfdrs";

			Assert::IsFalse(core_test.gen_tree(node1, words, len, false, 0, word_max_node, char_max_node, words_index));

			//Assert::IsTrue(core_test.find_in_chain(node1->first_child, word));
			Assert::IsTrue(core_test.find_in_chain(node1->first_child->first_child, word));


		}
		TEST_METHOD(UnitTest_gen_tree3)
		{
			// TODO: 在此输入测试代码
			//disable
			node1 = new node(cur_word, cur_word_num, cur_character_num);
			word_max_node = new node("", 0, 0);
			char_max_node = new node("", 0, 0);
			int len = 5;
			int  words_index[26][2] = { 0 };
			words_index['a' - 'a'][0] = 0;
			words_index['a' - 'a'][1] = 0;
			words_index['h' - 'a'][0] = 1;
			words_index['h' - 'a'][1] = 3;
			words_index['j' - 'a'][0] = 4;
			words_index['j' - 'a'][1] = 4;
			//able
			char* words[5] = { "aj", "hdfdrs", "hdfghj", "hjhjh", "jhgjh" };
			Assert::IsTrue(core_test.gen_tree(node1, words, len, false, 0, word_max_node, char_max_node, words_index));
		}
		TEST_METHOD(UnitTest_gen_tree4)
		{
			// TODO: 在此输入测试代码
			//disable
			node1 = new node(cur_word, cur_word_num, cur_character_num);
			word_max_node = new node("", 0, 0);
			char_max_node = new node("", 0, 0);
			int len = 5;
			int  words_index[26][2] = { 0 };
			words_index['a' - 'a'][0] = 0;
			words_index['a' - 'a'][1] = 0;
			words_index['c' - 'a'][0] = 1;
			words_index['c' - 'a'][1] = 1;
			words_index['d' - 'a'][0] = 2;
			words_index['d' - 'a'][1] = 2;
			words_index['h' - 'a'][0] = 3;
			words_index['h' - 'a'][1] = 3;
			words_index['s' - 'a'][0] = 4;
			words_index['s' - 'a'][1] = 4;
			//able
			char* words[5] = { "aj", "cdfdrp", "ddfghj", "hhgjh", "sjhjb" };
			Assert::IsFalse(core_test.gen_tree(node1, words, len, false, 0, word_max_node, char_max_node, words_index));
		}
		TEST_METHOD(UnitTest_gen_tree5)
		{
			// TODO: 在此输入测试代码
			//disable
			node1 = new node(cur_word, cur_word_num, cur_character_num);
			word_max_node = new node("", 0, 0);
			char_max_node = new node("", 0, 0);
			char head = 0, tail = 0;
			int len = 6;
			//able
			char* words[6] = { "aj", "jhgjh","hjhjbdkjhaksjdfhkjhkjhjd" ,"hdfdrp","pd","ddfghj" };
			Assert::AreEqual(core_test.gen_chain_word(words, len, result, head, tail, true), 5);
			Assert::AreEqual(core_test.gen_chain_char(words, len, result, head, tail, true), 5);
		}
		TEST_METHOD(UnitTest_gen_chain_word_and_char)
		{
			// TODO: 在此输入测试代码
			//disable
			node1 = new node(cur_word, cur_word_num, cur_character_num);
			word_max_node = new node("", 0, 0);
			char_max_node = new node("", 0, 0);
			char head = 0, tail = 0;
			int len = 7;
			//able
			char* words[7] = { "ajsdjfhkhlkjhlakjshduhcuhuhuhuhvuhjhdkajsdfnajksdjkfhksdjahkjdhjdhje","ddfghj","ei","hdfdrp", "hjhjbdkjhaksjd","jhgjh" ,"pd" };
			Assert::AreEqual(core_test.gen_chain_char(words, len, result, head, tail, true), 2);
			Assert::AreEqual(core_test.gen_chain_word(words, len, result, head, tail, true), 5);
			
			
		}
		TEST_METHOD(UnitTest_gen_chain_word_and_char2)
		{
			// TODO: 在此输入测试代码
			//disable
			node1 = new node(cur_word, cur_word_num, cur_character_num);
			word_max_node = new node("", 0, 0);
			char_max_node = new node("", 0, 0);
			char head = 0, tail = 0;
			int len = 1;
			//able
			char* words[7] = { "ajsdjfhkhlkjhlakjshduhcuhuhuhuhvuhjhdkajsdfnajksdjkfhksdjahkjdhjdhje" };
			try
			{
				Assert::AreEqual(core_test.gen_chain_char(words, len, result, head, tail, true), 2);
				
				Assert::IsTrue(false);
			}
			catch (struct ChainLessThen2Exception &e)
			{
				Assert::IsTrue(true);
			}
			catch (...)
			{
				Assert::IsTrue(false);
			}

		}

		TEST_METHOD(UnitTest_command_line15)
		{
			// TODO: 在此输入测试代码
			node1 = new node(cur_word, cur_word_num, cur_character_num);
			word_max_node = new node("", 0, 0);
			char_max_node = new node("", 0, 0);
			char head = 0, tail = 0;
			int len = 1;
			//able
			char* words[7] = { "ajsdjfhkhlkjhlakjshduhcuhuhuhuhvuhjhdkajsdfnajksdjkfhksdjahkjdhjdhje" };
			try
			{
				Assert::AreEqual(core_test.gen_chain_char(words, len, result, 1, tail, true), 2);

				Assert::IsTrue(false);
			}
			catch (struct HeadInvalidException &e)

			{
				Assert::IsTrue(true);
			}
			catch (...)
			{
				Assert::IsTrue(false);
			}
		}
		TEST_METHOD(UnitTest_command_line16)
		{
			// TODO: 在此输入测试代码
			node1 = new node(cur_word, cur_word_num, cur_character_num);
			word_max_node = new node("", 0, 0);
			char_max_node = new node("", 0, 0);
			char head = 0, tail = 0;
			int len = 1;
			//able
			char* words[7] = { "ajsdjfhkhlkjhlakjshduhcuhuhuhuhvuhjhdkajsdfnajksdjkfhksdjahkjdhjdhje" };
			try
			{
				Assert::AreEqual(core_test.gen_chain_char(words, len, result, head, 2, true), 2);

				Assert::IsTrue(false);
			}
			catch (struct TailInvalidException &e)

			{
				Assert::IsTrue(true);
			}
			catch (...)
			{
				Assert::IsTrue(false);
			}
		}

	};



	TEST_CLASS(UnitTest_command_line)
	{
		bool valid_flag, enable_loop = false, w_para = false;
		int argc = 5, len = 0, index, chain_length;
		char* argv[5] = { "Wordlist.exe", "-h","a" ,"-w", "../Wordlist/file.txt" };
		char *result[10000], *words[10000];
		char head = 0, tail = 0;

	public:

		TEST_METHOD(UnitTest_command_line1)
		{
			// TODO: 在此输入测试代码
			char* argv[5] = { "Wordlist.exe", "-h","a" ,"-w", "../Wordlist/file.txt" };//必须是这样的斜杠

			Assert::IsTrue(command_handler(argc, argv, words, len, head, tail, enable_loop, w_para));

		}
		TEST_METHOD(UnitTest_command_line2)
		{
			// TODO: 在此输入测试代码
			argc = 4;
			char* argv[4] = { "Wordlist.exe","-w","-r","../Wordlist/file.txt" };
			Assert::IsTrue(command_handler(argc, argv, words, len, head, tail, enable_loop, w_para));

		}
		TEST_METHOD(UnitTest_command_line3)
		{
			// TODO: 在此输入测试代码
			argc = 5;
			char* argv[5] = { "Wordlist.exe", "-c","-t","a", "../Wordlist/file.txt" };
			Assert::IsTrue(command_handler(argc, argv, words, len, head, tail, enable_loop, w_para));
		}
		TEST_METHOD(UnitTest_command_line4)
		{
			// TODO: 在此输入测试代码
			argc = 5;
			char* argv[5] = { "Wordlist.exe", "-c","a","-t","../Wordlist/file.txt" };
			Assert::IsFalse(command_handler(argc, argv, words, len, head, tail, enable_loop, w_para));
		}

		TEST_METHOD(UnitTest_command_line9)
		{
			// TODO: 在此输入测试代码
			argc = 5;
			char* argv[5] = { "Wordlist.exe", "-c","a","-h","../Wordlist/file.txt" };
			Assert::IsFalse(command_handler(argc, argv, words, len, head, tail, enable_loop, w_para));
		}
		TEST_METHOD(UnitTest_command_line5)
		{
			// TODO: 在此输入测试代码
			argc = 5;
			char* argv[5] = { "Wwordlist.exe", "-c","-c","-t","../Wordlist/file.txt" };
			Assert::IsFalse(command_handler(argc, argv, words, len, head, tail, enable_loop, w_para));
		}

		TEST_METHOD(UnitTest_command_line7)
		{
			// TODO: 在此输入测试代码
			argc = 5;
			char* argv[5] = { "Wordlist.exe", "-w","-w","-t","../Wordlist/file.txt" };
			Assert::IsFalse(command_handler(argc, argv, words, len, head, tail, enable_loop, w_para));
		}

		TEST_METHOD(UnitTest_command_line6)
		{
			// TODO: 在此输入测试代码
			argc = 5;
			char* argv[5] = { "Wordlist.exe", "-c","a","-t","../Wordlist/file.txt" };
			Assert::IsFalse(command_handler(argc, argv, words, len, head, tail, enable_loop, w_para));
		}

		TEST_METHOD(UnitTest_command_line10)
		{
			// TODO: 在此输入测试代码
			argc = 5;
			char* argv[5] = { "Wordlist.exe", "-c","-h","asfd","../Wordlist/file.txt" };
			Assert::IsFalse(command_handler(argc, argv, words, len, head, tail, enable_loop, w_para));
		}
		TEST_METHOD(UnitTest_command_line11)
		{
			// TODO: 在此输入测试代码
			argc = 6;
			char* argv[6] = { "Wordlist.exe", "-c","-h","r","aksdjfh","../Wordlist/file.txt" };
			Assert::IsFalse(command_handler(argc, argv, words, len, head, tail, enable_loop, w_para));
		}
		TEST_METHOD(UnitTest_command_line12)
		{
			// TODO: 在此输入测试代码
			argc = 5;
			char* argv[5] = { "Wordlist.exe", "-c","-h","r","aksdjfh" };
			Assert::IsFalse(command_handler(argc, argv, words, len, head, tail, enable_loop, w_para));
		}
		TEST_METHOD(UnitTest_command_line13)
		{
			// TODO: 在此输入测试代码
			argc = 8;
			char* argv[8] = { "Wordlist.exe", "-c","-h","r","-t","a","-r","../Wordlist/file.txt" };
			Assert::IsTrue(command_handler(argc, argv, words, len, head, tail, enable_loop, w_para));
		}
		TEST_METHOD(UnitTest_command_line14)
		{
			// TODO: 在此输入测试代码
			argc = 3;
			char* argv[3] = { "Wordlist.exe", "-r","../Wordlist/file.txt" };
			Assert::IsFalse(command_handler(argc, argv, words, len, head, tail, enable_loop, w_para));
		}
		

	};




}