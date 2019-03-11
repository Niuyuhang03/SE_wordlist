#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGui_wordlist.h"

class QtGui_Wordlist : public QMainWindow
{
	Q_OBJECT

public:
	QtGui_Wordlist(QWidget *parent = Q_NULLPTR);
public slots:
	void gen_chain();
	void save_file();

private:
	Ui::QtGui_WordlistClass ui;
};