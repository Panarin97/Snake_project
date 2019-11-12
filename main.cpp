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
# File: main.cpp                                                   #
# Description: Starts executing the program.                       #
#                                                                  #
# Author: Sergei Panarin,281652, sergei.panarin@tuni.fi            #
####################################################################
*/

#include "main_window.hh"
#include <QApplication>


int main(int argc, char** argv) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
