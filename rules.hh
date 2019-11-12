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
# File: rules.hh                                                   #
# Description: Declaring a class implementing a UI for the rules.  #
#                                                                  #
# Author: Sergei Panarin,281652, sergei.panarin@tuni.fi            #
####################################################################
*/


#ifndef RULES_HH
#define RULES_HH

#include <QDialog>

namespace Ui {
class Rules;
}

class Rules : public QDialog
{
    Q_OBJECT

public:
    explicit Rules(QWidget *parent = 0);
    ~Rules();

private:
    Ui::Rules *ui;
    QString text_ = "The rules for the Snake game (v2.0):\n\
    - The goal of the game is to fill the entirety of the playing field with the body of the Snake or at least get 500 points.\n\
     (for some playable areas one of the 2 is not possible)\n\
    - The player loses if the snake crashes into itself by accident or the timer at the top right corner reaches 10 minutes.\n\
    - There are 2 types of food in the game:\n\
    - red food makes the snake elongate by 1 extra part and gives + 1 score. If the snake is accelerated, returns its speed to the initial value.\n\
    - blue food makes the snake elongate by 2 extra parts, gives + 2 score and speeds the snake up two times.\n\
    - The borders do not crash the snake, the snake simply teleports to the opposite side of the field.\n\
    - The controls for the Snake are WASD. The space will activate the selected button so dont press it without need.\n\
    \n\
    Functionalities:\n\
    \n\
    - You can Pause and Resume your game with the appropiate buttons in the buttons bar.\n\
    - You can choose the difficulty level which affects the snake's movement speed from the menu bar on top left.\n\
    - You can open the rules with this exact same text from the same menu bar.\n\
    - You can select the size of your playing area with the resize labels, they are disabled if playing.\n\
    - You can see your current and best scores during one session.\n\
    - You can press Play to start your game and Stop to finish playing but keep the GUI active.\n\
    - You can see the time you've spent playing one particular round on top right.\n\
    - You can restart your game while playing with Restart button.";
};

#endif // RULES_HH
