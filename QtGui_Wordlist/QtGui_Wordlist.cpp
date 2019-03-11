#include "QtGui_Wordlist.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "../Core/Core.h"

using namespace std;

QtGui_Wordlist::QtGui_Wordlist(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_generate_chain, SIGNAL(clicked()), this, SLOT(gen_chain()));
	connect(ui.pushButton_save_in_file, SIGNAL(clicked()), this, SLOT(save_file()));
}

/*
* 比较函数，用于对words排序
*/
int compare_it(const void *a, const void *b) {
	return strcmp(*(char **)a, *(char **)b);
}

void QtGui_Wordlist::gen_chain()
{
	QString file_name = "";
	char head = 0, tail = 0;
	bool w_para = false, enable_loop = false;
	char *result[10000], *words[10000];
	int len = 0, chain_length;
	string contents;
	Core core;

	// handle error
	if (ui.radioButton_upload_file->isChecked()) {
		if (ui.lineEdit_filename->text().size() == 0) {
			ui.textEdit_result->setPlainText("please input file path!");
			return;
		}
		file_name = ui.lineEdit_filename->text();
		ifstream in(string((const char *)file_name.toLocal8Bit()));
		if (!in) {
			ui.textEdit_result->setPlainText("file doesn't exist!");
			return;
		}
	}
	if (ui.radioButton_input_words->isChecked() && ui.lineEdit_words->text().size() == 0) {
		ui.textEdit_result->setPlainText("please input words!");
		return;
	}
	if (ui.checkBox_h->isChecked() && (ui.lineEdit_h->text().size() > 1 || ui.lineEdit_h->text().size() == 0)) {
		ui.textEdit_result->setPlainText("-h parameter is empty or too long!");
		return;
	}
	if (ui.checkBox_t->isChecked() && (ui.lineEdit_t->text().size() > 1 || ui.lineEdit_t->text().size() == 0)) {
		ui.textEdit_result->setPlainText("-t parameter is empty or too long!");
		return;
	}
	ui.textEdit_result->setPlainText("");

	// handle input
	if (ui.radioButton_upload_file->isChecked()) {
		file_name = ui.lineEdit_filename->text();
		ifstream in(string((const char *)file_name.toLocal8Bit()));
		ostringstream buffer;
		buffer << in.rdbuf();
		string content(buffer.str());
		contents = content;
	}
	else
		contents = string((const char *)ui.lineEdit_words->text().toLocal8Bit());
	ui.textEdit_result->setPlainText(QString::fromStdString(contents));
	int contents_length = contents.length(), index;
	string s = "";
	for (index = 0; index < contents_length; index++) {
		if ((contents[index] >= 'a'&&contents[index] <= 'z') || (contents[index] >= 'A'&&contents[index] <= 'Z'))
			s = s + contents[index];
		else if (s != "") {
			words[len] = new char[s.length() + 1]();
			transform(s.begin(), s.end(), s.begin(), ::tolower);
			strcpy(words[len++], s.c_str());
			s = "";
		}
	}
	if (s != "") {
		words[len] = new char[s.length() + 1]();
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		strcpy(words[len++], s.c_str());
	}
	if (len == 0) {
		ui.textEdit_result->setPlainText("no word exists!\n");
		return;
	}
	qsort(words, len, sizeof(words[0]), compare_it);
	int cnt = 1;
	for (index = 1; index < len; index++) {
		if (strcmp(words[index], words[index - 1]) != 0) {
			strcpy(words[cnt++], words[index]);
		}
	}
	len = cnt;
	if (ui.radioButton_w->isChecked())
		w_para = true;
	if (ui.checkBox_h->isChecked())
		head = tolower(ui.lineEdit_h->text()[0].unicode());
	if (ui.checkBox_t->isChecked())
		tail = tolower(ui.lineEdit_t->text()[0].unicode());
	if (ui.checkBox_r->isChecked())
		enable_loop = true;

	if (w_para)
		chain_length = core.gen_chain_word(words, len, result, head, tail, enable_loop);
	else
		chain_length = core.gen_chain_char(words, len, result, head, tail, enable_loop);
	if (chain_length == -1) {
		ui.textEdit_result->setPlainText("loop exists!\n");
		return;
	}
	if (chain_length < 2 && chain_length >= 0) {
		ui.textEdit_result->setPlainText("no chain's length is greater than 1!");
		return;
	}
	ui.textEdit_result->setPlainText("");
	for (index = 0; index < chain_length; index++) {
		ui.textEdit_result->append(result[index]);
	}
}

void QtGui_Wordlist::save_file() {
	if (ui.lineEdit_save_in_file->text().size() == 0) {
		ui.textEdit_result->setPlainText("file path to save result is empty!");
		return;
	}
	if (ui.textEdit_result->toPlainText().size() == 0) {
		ui.textEdit_result->setPlainText("result is empty!");
		return;
	}
	string file_name = string((const char *)ui.lineEdit_save_in_file->text().toLocal8Bit());
	string content = string((const char *)ui.textEdit_result->toPlainText().toLocal8Bit());
	ofstream outfile;
	outfile.open(file_name);
	outfile << content;
	outfile.close();
	ui.textEdit_result->setPlainText("save successfully!");
}