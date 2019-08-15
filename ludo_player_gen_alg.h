#ifndef LUDO_PLAYER_GEN_ALG_H
#define LUDO_PLAYER_GEN_ALG_H
#include <QObject>
#include <iostream>
#include "positions_and_dice.h"
#include <cstdlib>
#include <vector>
#include <random>
#include <string>
#include <chrono>
//#include "game.h"

#define POPULATION_SIZE 2
#define VERBOSE false
#define MAX_GENERATION 100
#define GAMES_PER_CHROMOZONES 2

#define SAFE 99
#define HOME -1
#define FIRST_ON_BOARD 0
#define LAST_ON_BOARD 56
#define FIRST_IN_GOAL_STRETCH 51
#define ACTIONS 11


#define chromosomeLifeTime 1500
#define Training false
#define TOTALGAMES 1000

using namespace std;

struct Chromosome{

    Chromosome(){}

        double enterBoard = 0.0;
        //double move2Safety = 0.0;
        double sendOpponentHome = 0.0;
        double block = 0.0;
        double moveNormal = 0.0;
        double move2Star = 0.0;
        double move2Globe = 0.0;
        double move2Endzone = 0.0;
        double moveInEndzone = 0.0;
        double finish = 0.0;
        double mv2OpponentHome = 0.0;
        //double mvFromOpponentHome = 0.0;
        double selfHome = 0.0;



        //container for genes
        vector<double> Genes {enterBoard, sendOpponentHome, block, moveNormal, move2Star, move2Globe, move2Endzone, moveInEndzone, finish, mv2OpponentHome, /*mvFromOpponentHome,*/ selfHome};

        int fitnessScore = 0;

};

class ludo_player_gen_alg : public QObject {
    Q_OBJECT
private:
    std::vector<int> pos_start_of_turn;
    std::vector<int> pos_end_of_turn;
    int dice_roll;
    int make_decision();
    Chromosome choose_best();



public:
    ludo_player_gen_alg();
    //vector<Chromosome> population;
    void update_population();
    void mutate_population(float mutation_rate, float mutation_probability);
    vector<float> fitness;
    vector<Chromosome> init_pop();
    //void init_pop();
    void print_pop();
    void print_available_actions(vector<vector<bool>>);
    void set_fitness(vector<float> wins);
    void print_best_chromozone();
    vector<vector<bool>> check_board();
    int choose_piece(vector<vector<bool>> moves, int chrCnt);
    Chromosome crossover(Chromosome parent_mother, Chromosome parent_father);
    int chrCnt;
    std::vector<int> player_wins = {0, 0, 0, 0};
    vector<Chromosome> population;
    void printChromoFitness();
    void resetFitness();

    //void statistics()


signals:
    void select_piece(int);
    void turn_complete(bool);
public slots:
    void start_turn(positions_and_dice relative);
    void post_game_analysis(std::vector<int> relative_pos);
};

#endif // LUDO_PLAYER_GEN_ALG_H
