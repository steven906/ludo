#ifndef LUDO_PLAYER_RANDOM_H
#define LUDO_PLAYER_RANDOM_H
#include <QObject>
#include <iostream>
#include "positions_and_dice.h"
#include <random>

class ludo_player_random : public QObject {
    Q_OBJECT
private:
    std::vector<int> pos_start_of_turn;
    std::vector<int> pos_end_of_turn;
    int dice_roll;
    int make_decision();
public:
    ludo_player_random();
signals:
    void select_piece(int);
    void turn_complete(bool);
public slots:
    void start_turn(positions_and_dice relative);
    void post_game_analysis(std::vector<int> relative_pos);
};

#endif // LUDO_PLAYER_RANDOM_H
