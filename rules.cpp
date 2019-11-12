/*
####################################################################
# TIE-02201 Ohjelmointi 2: Perusteet, K2019                        #
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project4: Snake:                                                 #
# Program description: "This is a version of the snake game        #
#                        for 1 player using the Qt Creator GUI     #
#                                                                  #
#                                                                  #
#                                                                  #
#                                                                  #
# File: rules.cpp                                                  #
# Description: Defines a class implementing a UI for the rules.    #
#                                                                  #
# Author: Sergei Panarin,281652, sergei.panarin@tuni.fi            #
####################################################################
*/



#include "rules.hh"
#include "ui_rules.h"

Rules::Rules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rules)
{
    ui->setupUi(this);
    ui->textBrowser->setText(text_);
}

Rules::~Rules()
{
    delete ui;
}
