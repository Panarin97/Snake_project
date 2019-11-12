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
# File: main_window.hh                                             #
# Description: Declaring a class implementing a UI for the game.   #
#                                                                  #
# Author: Sergei Panarin,281652, sergei.panarin@tuni.fi            #
####################################################################
*/

#ifndef PRG2_SNAKE2_MAINWINDOW_HH
#define PRG2_SNAKE2_MAINWINDOW_HH

#include "ui_main_window.h"
#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>
#include <random>
#include <QBrush>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QMessageBox>
#include <memory>




struct Snakepart {
    QString direction;
    QString name;
    Snakepart* previous;
    Snakepart* next;
    QGraphicsItem* image;

};

struct Snake {
    Snakepart* head_ = nullptr;
    Snakepart* tail_ = nullptr;
};

/* \class MainWindow
 * \brief Implements the main window through which the game is played.
 */
class MainWindow: public QMainWindow {
    Q_OBJECT

public:

    /* \brief Construct a MainWindow.
     *
     * \param[in] parent The parent widget of this MainWindow.
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /* \brief Destruct a MainWindow.
     */
    ~MainWindow() override = default;

    /* \brief Change the Snake's bearing when certain keys get pressed.
     *
     * \param[in] event Contains data on pressed and released keys.
     */
    void keyPressEvent(QKeyEvent* event);



private slots:

    /* \brief Start the game.
     */
    void on_playButton_clicked();

    /* \brief Set the direction and trigger move function
     *
     */
    void move1();

    /* \brief Defines the mechanics of the movement.
     *
     * \param[in] Snakepart* Pointer to Snakepart which image is to be moved
     */


    /* \brief update the score label
     *
     */
    void update_score();

    /* \brief update best score label
     *
     */
    void update_best_score();



    /* \brief Calculate time passed playing
     *
     */
    void time();

    /* \brief Set easy mode
     *
     */
    void on_actionEasy_triggered();

    /* \brief Set normal mode
     *
     */
    void on_actionNormal_triggered();

    /* \brief Set hard mode
     *
     */
    void on_actionHard_triggered();

    /* \brief Restart the game
     *
     */
    void on_RestartButton_clicked();

    /* \brief Pause the game
     *
     */
    void on_PauseButton_clicked();

    /* \brief Resume paused game
     *
     */
    void on_ResumeButton_clicked();

    /* \brief Make subwindow with rules appear
     *
     */
    void on_actionRules_triggered();

    /* \brief Stop playing but dont exit
     *
     */
    void on_StopButton_clicked();

    /* \brief edit x coor of the scene
     *
     * param[in] QString edited text, value of x
     */
    void on_lineEditX_textEdited(const QString &arg1);

    /* \brief edit y coor of the scene
     *
     * param[in] QString edited text, value of y
     */
    void on_lineEditY_textEdited(const QString &arg1);

    /* \brief adjust the scene
     *
     */
    void on_pushButtonAdjust_clicked();

private:

    /* \brief Create the snake object and its head.
     *
     */
    void create_snake();

    /* \brief Add Snakepart object to the Snake
     *
     */
    void add_snake_part();

    /* \brief Start the game
     *
     */
    void start();

    /* \brief Set Snakepart's image accordingly
     *
     * \param[in] Snakepart* Pointer to Snakepart to add.
     */
    void set_images(Snakepart* part);

    /* \brief make every Snakepart move
     *
     */
    void move();

    /* \brief Make the play field visible and fit it into the view.
     *
     * Should be called every time the field's size changes.
     */
    void adjustSceneArea();

    /* \brief Defines the mechanics of the movement.
     *
     * \param[in] Snakepart* Pointer to Snakepart which image is to be moved
     */
    void movement(Snakepart* part);

    /* \brief Check for the head collisions with other objects + conditions
     *
     */
    void check_collision();

    /* \brief Create food type 1 object
     *
     */
    void create_food1();

    /* \brief Create food type 2 object
     *
     */
    void create_food2();

    /* \brief Move food type 1 object
     *
     */
    void change_food1_pos();

    /* \brief Move food type 2 object
     *
     */
    void change_food2_pos();

    /* \brief Return Snake's length
     *
     * \return int length of linked list
     */
    int snake_length();

    /* \brief Finish the game session
     *
     */
    void game_over();

    /* \brief Check for victory condition
     *
     */
    void check_victory();

    /* \brief Check for defeat condition
     *
     */
    void check_defeat();

    /* \brief Remove the snake object from board and memory
     *
     */
    void empty_snake();



    Ui::MainWindow ui_;                 /**< Accesses the UI widgets. */
    QGraphicsItem *food1_ = nullptr;    /**< The food type 1 item in the scene. */
    QGraphicsItem *food2_ = nullptr;    /**< The food type 2 item in the scene. */
    QString dir_ = "UP";                /**< The current direction of the snake. */
    QGraphicsScene scene_;              /**< Manages drawable objects. */
    QTimer* timer_;                     /**< Triggers the Snake to move. */
    QTimer* time_;                      /**< Triggers the time for the timer in the main. */
    std::default_random_engine rng_;    /**< Randomizes food locations. */
    int score_ = 0;                     /**< Current score. */
    int best_score_ = 0;                /**< Best score in one opening of main. */
    int minutes_ = 0;                   /**< Minutes for the timer. */
    int seconds_ = 0;                   /**< TSeconds for the timer. */

    Snake* snake_ = nullptr;            /**< The base for the Snake. */
    int velocity_ = 90;                 /**< Current velocity. */
    int x_ = 1000;                      /**< X coordinate for scene. */
    int y_ = 1000;                      /**< Y coordinate for scene. */


};  // class MainWindow


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
