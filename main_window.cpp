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
# File: main_window.cpp                                            #
# Description: Defines a class implementing a UI for the game.     #
#                                                                  #
# Author: Sergei Panarin,281652, sergei.panarin@tuni.fi            #
####################################################################
*/


#include "main_window.hh"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTime>
#include <QMenu>
#include <rules.hh>

/*
 * Big comment before the actual code:
 * This is a version of the snake game. Rules can be accessed via in-game
 * or through instructions.txt file
 *
 * The program uses a linked list which is the snake struct
 * which is then filled with pointers to Snakepart structs.
 * While this might be not the most efficient solution, I stand by
 * this choice and think that practising linked lists is important.
 * I suppose a vector of QGraphicsItem objects could also work and
 * I'm aware that other solutions exist. A linked list was the first idea
 * and due to the time constraints I implemented that.
 * */

//setup the gui main window
MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent) {

    ui_.setupUi(this);
    ui_.graphicsView->setScene(&scene_);

    //timer for the movement of the snake
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(move1()));

    //timer for the external timer on the gui window
    time_ = new QTimer(this);
    connect(time_, SIGNAL(timeout()), this, SLOT(time()));


    //setting colors for some of the ui elements
    ui_.ScorelcdNunber->setStyleSheet("background-color: rgb(150, 0, 200)");
    ui_.BestlcdNumber->setStyleSheet("background-color: rgb(250, 50, 50)");
    ui_.lcdNumbersec->setStyleSheet("background-color: rgb(0, 0, 200)");
    ui_.lcdNumbermin->setStyleSheet("background-color: rgb(0, 0, 200)");

    //setting buttons and fields to disabled and enabled respectively
    ui_.StopButton->setDisabled(true);
    ui_.RestartButton->setDisabled(true);
    ui_.PauseButton->setDisabled(true);
    ui_.ResumeButton->setDisabled(true);
    ui_.pushButtonAdjust->setDisabled(false);
    ui_.lineEditX->setDisabled(false);
    ui_.lineEditY->setDisabled(false);
}


//Check for keyEvents (WASD) and set the direction of the snake accordingly
//also check if the direction is opposite, then do nothing
void MainWindow::keyPressEvent(QKeyEvent* event) {

    if (snake_ != nullptr) {
        if(event->key() == Qt::Key_W && snake_->head_->direction != "DOWN") {
                dir_ = "UP";
            }
            else if(event->key() == Qt::Key_S && snake_->head_->direction != "UP") {
                dir_ =  "DOWN";
            }
            else if(event->key() == Qt::Key_D && snake_->head_->direction != "LEFT") {
                dir_ =  "RIGHT";
            }
            else if(event->key() == Qt::Key_A && snake_->head_->direction != "RIGHT") {
                dir_ =  "LEFT";
            }
    }
}

// starts the game
void MainWindow::on_playButton_clicked() {

    start();

}

//adjusts the scene, creates the snake and its food, sets both timers
void MainWindow::start() {

    if (snake_ == nullptr) {
        adjustSceneArea();
        velocity_ = 90;

        create_snake();

        add_snake_part();
        add_snake_part();
        add_snake_part();

        create_food1();
        create_food2();

        timer_->start(velocity_);
        time_->start(1000);

        ui_.lcdNumbermin->display(minutes_);
        ui_.lcdNumbersec->display(seconds_);

        //enable buttons and disable fields when actually playing
        ui_.StopButton->setDisabled(false);
        ui_.RestartButton->setDisabled(false);
        ui_.PauseButton->setDisabled(false);
        ui_.ResumeButton->setDisabled(false);
        ui_.pushButtonAdjust->setDisabled(true);
        ui_.lineEditX->setDisabled(true);
        ui_.lineEditY->setDisabled(true);
    }
}

//create food type 1 (red food)
void MainWindow::create_food1() {
    const QRectF food_rect(0, 0, 10, 10);
    const QPen pen(Qt::white, 0);
    const QBrush food1brush(Qt::red);

    //randomly selecting food position
    int x1 = x_+1;
    int y1= y_+1;
    std::uniform_int_distribution<int> distx(1, x_);
    std::uniform_int_distribution<int> disty(1, y_);

    while (x1 > x_ || y1 > y_ ) {

       x1 = distx(rng_) ;
       y1 = disty(rng_) ;
    }

    food1_ = scene_.addRect(food_rect, pen, food1brush);
    food1_->setPos(x1, y1);

}

//change food1 position after its been eaten by the snake
void MainWindow:: change_food1_pos() {
    int x1 = x_+1;
    int y1= y_+1;
    std::uniform_int_distribution<int> distx(1, x_);
    std::uniform_int_distribution<int> disty(1, y_);

    while (x1 > x_ || y1 > y_ ) {
       x1 = distx(rng_) ;
       y1 = disty(rng_) ;
    }

    food1_->setPos(x1, y1);

}



//create food type 2 (blue food)
//NOTE: the food type 2 can spawn inside the snake for balancing reasons
void MainWindow::create_food2() {
    const QRectF food_rect(0, 0, 10, 10);
    const QPen pen(Qt::white, 0);
    const QBrush food2brush(Qt::blue);

    int x2 = x_+1;
    int y2= y_+1;
    std::uniform_int_distribution<int> distx(1, x_);
    std::uniform_int_distribution<int> disty(1, y_);

    while (x2 > x_ || y2 > y_  ||
           (food1_->x() != x2 && food1_->y() != y2) ) {
       x2 = distx(rng_) ;
       y2 = disty(rng_) ;
    }

    food2_ = scene_.addRect(food_rect, pen, food2brush);
    food2_->setPos(x2, y2);

}

//change food1 position after its been eaten by the snake
void MainWindow:: change_food2_pos() {
    int x2 = x_+1;
    int y2= y_+1;
    std::uniform_int_distribution<int> dist(1, 1000);

    while (x2 > x_ || y2 > y_ ||
           (food1_->x() != x2 && food1_->y() != y2)) {
       x2 = dist(rng_) ;
       y2 = dist(rng_) ;
    }

    food2_->setPos(x2, y2);

}

//move the snake parts repeteadly, set their speed and check for collisions
void MainWindow::move() {
    /* move from the back of the snake and move snakeparts
     * this allows the snake to update each iteration of the timer accordingly
     */
    Snakepart* temp = snake_->tail_;

    while (temp != nullptr) {
        movement(temp);
        temp = temp->next;
    }

    timer_->start(velocity_);
    check_collision();
}

/* Function to set the snake's direction and start moving
 * The timer for the movement is connected to this function
 */
void MainWindow::move1() {
    snake_->head_->direction = dir_;
    move();
}

//defines the mechanics of the snake's movement
void MainWindow::movement (Snakepart* part) {
    //move the rectangles according to their directions
    if (part->direction == "UP") {
        part->image->setY(part->image->y() - 10);

    } else if (part->direction == "DOWN") {
        part->image->setY(part->image->y() + 10);

    } else if (part->direction == "RIGHT") {
        part->image->setX(part->image->x() + 10);

    } else if (part->direction == "LEFT") {
        part->image->setX(part->image->x() - 10);
    }

    //set the direction to be the direction of the next in line
    if (part->next != nullptr) {
        part->direction = part->next->direction;
    }

    //teleport the snake if it reaches the border
    if (part->image->y() > y_) {
        part->image->setY(0);

    } else if (part->image->y() < 0) {
        part->image->setY(y_);

    } else if (part->image->x() > x_) {
        part->image->setX(0);

    } else if (part->image->x() < 0) {
        part->image->setX(x_);
    }
}


//adjusts the main window playable area
void MainWindow::adjustSceneArea() {
    const QRectF area(0, 0, x_, y_);
    scene_.setSceneRect(area);
    ui_.graphicsView->fitInView(area);
}

//creates a Snake struct and implemets the linked list
void MainWindow::create_snake() {
    //creating a linked list snake, starting with head, then going by "previous" to the tail.
    Snake* snake = new Snake;

    //creating the head
    Snakepart *Head = new Snakepart;

    Head->direction = "UP";
    Head->name = "HEAD";
    Head->next = nullptr;
    Head->previous = nullptr;

    snake->head_ = Head;
    snake->tail_ = Head;

    set_images(snake->head_);

    snake_= snake;
}

//attach a snakepart object to the linked list and set the image
void MainWindow::add_snake_part() {
    Snakepart *part = new Snakepart;
    Snakepart *temp = snake_->tail_;
    temp->previous = part;
    part->next = temp;
    part->previous = nullptr;

    //choosing coordinates for the picture
    int x = 0;
    int y = 0;

    if (part->next->direction == "UP") {
        x = part->next->image->x();
        y = part->next->image->y() + 10;

    } else if (part->next->direction == "RIGHT") {
        x = part->next->image->x() - 10;
        y = part->next->image->y();

    } else if (part->next->direction == "DOWN") {
        x = part->next->image->x();
        y = part->next->image->y() - 10;

    } else if (part->next->direction == "LEFT") {
        x = part->next->image->x() + 10;
        y = part->next->image->y();
    }

    part->direction = temp->direction;

    snake_->tail_ = part;
    part->name = "PART";

    //set_images(temp);
    set_images(part);

    part->image->setPos(x, y);



}
//setting the images
void MainWindow::set_images(Snakepart* part) {
    const QRectF part_rect(0, 0, 10, 10);
    const QPen pen(Qt::white, 0);
    const QBrush headbrush(QColor(170, 0, 255));
    const QBrush partbrush(QColor(0, 200, 150));


    if (part->name == "HEAD") {
        part->image = scene_.addRect(part_rect, pen, headbrush);
    } else if (part->name == "PART") {
        part->image = scene_.addRect(part_rect, pen, partbrush);
    }
}

//checking for collisions and victory/defeat conditions
void MainWindow::check_collision() {

    //it is also possible to check with coordinates directly but i prefer this
    if (snake_->head_->image->collidesWithItem(food1_)) {
        score_++;
        change_food1_pos();
        add_snake_part();
        update_score();
        //check velocity values and set them accordingly
        if (velocity_ == 45 || velocity_ == 25 || velocity_ == 15) {
            velocity_ =velocity_*2;
        }

    } else if (snake_->head_->image->collidesWithItem(food2_)) {
        score_++;
        score_++;
        change_food2_pos();
        add_snake_part();
        add_snake_part();
        update_score();
        if (velocity_ != 45 && velocity_ != 25 && velocity_ != 15) {
            velocity_ = velocity_/2;
        }
    }

    check_defeat();
    check_victory();
}

//returns the length of the linked list
int MainWindow::snake_length() {
    int count = 0;
    Snakepart* current = snake_->head_;

    while (current != nullptr) {
        count++;
        current = current->previous;
    }
    return count;
}

void MainWindow::update_score() {
    ui_.ScorelcdNunber->display(score_);
}

void MainWindow::update_best_score() {
    ui_.BestlcdNumber->display(best_score_);
}

//check for victory conditions and call game_over if needed
void MainWindow::check_victory() {
    if (snake_length() == x_*y_ || score_ >= 5) {
        timer_->stop();
        time_->stop();
        QMessageBox::information(this, "Victory!", "Congratulations, you must feel pride and accomplishement now!");
        game_over();

    }
}

//check for defeat conditions and call game_over if needed
void MainWindow::check_defeat() {
    Snakepart* current = snake_->tail_;

    //go through the snake and check conditions on every iteration of the timer
    while (current!= snake_->head_) {
        if (current->image->pos() == snake_->head_->image->pos() ||
                minutes_ == 10) {
            timer_->stop();
            time_->stop();

            QMessageBox::information(this, "Oops!", "Better luck next time");
            game_over();
            break;
        }
        current = current->next;
    }
}

//deletes the snake and sets the direction to its initial value
void MainWindow::empty_snake() {
    Snakepart* current = snake_->head_;
    Snakepart* previous = nullptr;

    //wipe the linked list
    while (current != nullptr) {
        previous = current->previous;
        delete current->image;
        delete current;
        current = previous;
    }
    delete snake_;

    dir_="UP";
}


//finishes the game and puts it in the waiting stance
void MainWindow::game_over() {

    timer_->stop();

    seconds_ = 0;
    minutes_ = 0;

    //reset the snake and foods
    empty_snake();
    snake_ = nullptr;

    delete food1_;
    delete food2_;
    food1_ = nullptr;
    food2_ = nullptr;

    //update the best score if needed
    if (score_ > best_score_) {
        best_score_ = score_;
        score_ = 0;
        update_best_score();
        update_score();
    }

    //disable buttons and enable fields if not playing
    ui_.StopButton->setDisabled(true);
    ui_.RestartButton->setDisabled(true);
    ui_.PauseButton->setDisabled(true);
    ui_.ResumeButton->setDisabled(true);
    ui_.pushButtonAdjust->setDisabled(false);
    ui_.lineEditX->setDisabled(false);
    ui_.lineEditY->setDisabled(false);

}

//sets the timer for the time displayed in the main window
void MainWindow::time() {
    if (seconds_ == 60)
    {
        minutes_+=1;
        seconds_ = 0;
        ui_.lcdNumbermin->display(minutes_);
        ui_.lcdNumbersec->display(seconds_);

    } else {
        seconds_+=1;
        ui_.lcdNumbermin->display(minutes_);
        ui_.lcdNumbersec->display(seconds_);
    }
}


//series of functions triggered by certian buttons
void MainWindow::on_actionEasy_triggered() {
    velocity_ = 90;
}

void MainWindow::on_actionNormal_triggered() {
    velocity_ = 50;
}

void MainWindow::on_actionHard_triggered() {
    velocity_ = 30;
}

void MainWindow::on_RestartButton_clicked()
{   if (snake_ != nullptr) {
        game_over();
        start();
    }
}

void MainWindow::on_PauseButton_clicked()
{
    timer_->stop();
    time_->stop();
}

void MainWindow::on_ResumeButton_clicked()
{
    if (snake_ != nullptr) {
        timer_->start(velocity_);
        time_->start(1000);
    }
}

void MainWindow::on_actionRules_triggered()
{
    Rules rules;
    rules.setModal(true);
    rules.exec();
}

void MainWindow::on_StopButton_clicked()
{
    if (snake_ != nullptr) {
        game_over();
        time_->stop();
    }
}

//editing the playable area
void MainWindow::on_lineEditX_textEdited(const QString &arg1)
{
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
    if (re.exactMatch(arg1)) {
        x_ = arg1.toInt();
    } else {
        QMessageBox::warning(this, "Error", "Input an int");
    }

}

void MainWindow::on_lineEditY_textEdited(const QString &arg1)
{
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
    if (re.exactMatch(arg1)) {
        y_ = arg1.toInt();
    } else {
        QMessageBox::warning(this, "Error", "Input an int");
    }

}

void MainWindow::on_pushButtonAdjust_clicked()
{
    if (snake_ == nullptr) {
        adjustSceneArea();
    }
}
