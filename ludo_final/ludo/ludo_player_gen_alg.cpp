#include "ludo_player_gen_alg.h"
#include <random>


ludo_player_gen_alg::ludo_player_gen_alg(){
}

void random_genes(vector<Chromosome> &chromosome){
    for(int i = 0; i < chromosome.size(); i++){
        for(int j = 0; j < chromosome[0].Genes.size(); j++){
            chromosome[i].Genes[j] = ((double) rand() / (RAND_MAX));
            if(VERBOSE == true){
                cout << "Gene value:\t" << chromosome[i].Genes[j] << endl;
            }

        }
    }
}

vector<Chromosome> ludo_player_gen_alg::init_pop(){
    //vector<Chromosome> population_holder;
    for (int i =0; i<POPULATION_SIZE; i++) {
        population.push_back(Chromosome());
    }
    return population;
}



void ludo_player_gen_alg::print_pop(){
    for(int i = 0; i < population.size(); i++){
        cout << "Chromosome " << i << endl;
        cout << "Enter\tMove2Safe\tSendOpHome\tBlock\tMoveNorm\tMove2Star\tMove2Globe\tMove2End\tFinish\tMv2OppHome\tMvFromOppHome" << endl;
        for(int j = 0; j < population[0].Genes.size(); j++){
            cout << population[i].Genes[j] << "\t";
        }
        cout << endl;
    }
}


void ludo_player_gen_alg::print_available_actions(std::vector<std::vector<bool>> actions){
    cout<<"\tEnter\tMove2Safe\tSndOppHom\tBlock\tMvNormal\tMv2Star\tMv2Globe\tMvEndzone\tFinish\tMv2OppHome\tMvFromOppHome"<<std::endl;
    for (int pieces = 0; pieces < actions.size(); ++pieces) {
            cout<<"Piece "<<pieces<<" :\t";
            for (int i = 0; i< actions[pieces].size() ;i++) {
                if(actions[pieces][i] == 1){
                    cout<<population[0].Genes[i]<<"\t";
                }
                else {
                    cout<<actions[pieces][i]<<"\t";
                }

            }
            cout<<std::endl;
    }
}

int ludo_player_gen_alg::choose_piece(std::vector<std::vector<bool> > moves, int chrCnt){
    std::vector<int> candidates;        //Candidate holder
    for (int piece = 0; piece < moves.size(); ++piece) {            // Loop pieces
        for (int action = 0; action < moves[0].size(); ++action) {  // Loop actions
            //Find max value gene if the move is allowed
            int tmpAction = 0;
            int tmpPiece = 0;
            // Comparison of the boolean action matrix and the Gene-value
            if(moves[piece][action]==true && population[chrCnt].Genes[action]>tmpAction){
                tmpAction =population[chrCnt].Genes[action];
                //std::cout<<"tmpAction "<<tmpAction<<std::endl;

                /*
                auto it = std::max_element(std::begin(population[0].Genes),std::end(population[0].Genes));  //Pointer iterator for finding max
                //std::cout<<"MAX"<<*it<<std::endl;
                ptrdiff_t pos = std::find(population[0].Genes.begin(),population[0].Genes.end(), *it)-population[0].Genes.begin(); //Finding position for the max-pointer
                std::cout<<"pos "<<pos<<std::endl;
                std::cout<<"High score"<<piece<<std::endl;
                */

                candidates.push_back(piece);
            }
        }
    }
    if(candidates.size()==0){   // Return "void" answer as to which piece
        return -1;
    }
    if(candidates.size()==1){   // Choose the only candidate there is
        return candidates[0];
    }
    if(candidates.size()>1){    // Choice a random candidate of those who scored equally
        std::random_shuffle(candidates.begin(),candidates.end());
        int choice = *candidates.begin();
        return choice;
    }

}

int ludo_player_gen_alg::make_decision(){
    //std::vector<int> valid_moves;

    static int draw_cnt = 0;
    draw_cnt ++;
    if(draw_cnt == 1){
        population = init_pop();
        random_genes(population);
        if(VERBOSE == true){
            cout << "Population size:\t" << population.size() << endl;
            cout << "Gene length:\t" << population[0].Genes.size() << endl;
        }
        print_pop();
    }


    vector<vector<bool>> moves = check_board();
    //print_available_actions(moves);
    //cout << "Dice " << dice_roll << endl;



//    if(dice_roll == 6){
//        for(int i = 0; i < 4; ++i){
//            if(pos_start_of_turn[i]<0){
//                valid_moves.push_back(i);
//            }
//        }
//    }
//    for(int i = 0; i < 4; ++i){
//        if(pos_start_of_turn[i]>=0 && pos_start_of_turn[i] != 99){
//            valid_moves.push_back(i);
//        }
//    }
//    if(valid_moves.size()==0){
//        for(int i = 0; i < 4; ++i){
//            if(pos_start_of_turn[i] != 99){
//                valid_moves.push_back(i);
//            }
//        }
//    }
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> piece(0, valid_moves.size()-1);
//    int select = piece(gen);
//    return valid_moves[select];

    int piece = choose_piece(moves,chrCnt);
    //cout<< "Chromo # " << ChromosomeNr << endl;
    //cout << "Piece Choosen: " << piece << endl;

    return piece;

}

void ludo_player_gen_alg::mutate_population(float mutation_rate, float mutation_probability){
    for(int i = 0; i < population.size(); i++){
        int random_integer = rand()%100;
        if (random_integer < mutation_probability*100){
            int mutation_gene = rand()%ACTIONS;
            int mutation_direction = rand()%100;

            if (mutation_direction < 51)
            mutation_rate = -mutation_rate;
            std::cout << "mutating chromozone: " << i << " with: " << mutation_rate << std::endl;
            if (population[i].Genes[mutation_gene] + mutation_rate < 1.0)
            population[i].Genes[mutation_gene] = 1.0;
            else
            population[i].Genes[mutation_gene] += mutation_rate;
        }
    }
}


void ludo_player_gen_alg::update_population()
{

}
/**
 * @brief ludo_player_gen_alg::selection
 * The function finds the best and second best chromosome in the population and returns those.
 * This is based on the RANK SELECTION
 */

vector<Chromosome> ludo_player_gen_alg::selection(){
    vector<Chromosome> parents;
    Chromosome bestFitness;
    Chromosome secondBestFitness;
    bestFitness = population[0];
    for (int chr = 1; chr < population.size(); chr ++) {
        if(population[chr].fitnessScore > bestFitness.fitnessScore){
            secondBestFitness = bestFitness;
            bestFitness = population[chr];
        }
    }
        parents.push_back(bestFitness);
        parents.push_back(secondBestFitness);
        return parents;
}
vector<int> ludo_player_gen_alg::binaryMask(){
    vector<int> mask;
    for (int i = 0; i < population[0].Genes.size(); ++i) {
        mask.push_back(rand() % 1);
    }
    return mask;
}

vector<Chromosome> ludo_player_gen_alg::crossover(vector<Chromosome> parents){
    vector<int> mask = binaryMask();
    if(VERBOSE == true){
        for (int i = 0;i<mask.size();i++) {
            std::cout<<i<<" "<<std::endl;
        }
    }
}


/*
    Chromosome Cross;
    Chromosome Cross_gene;


    int parent = rand()%2;
    if (parent > 0)
    {
        Cross = parent_father;
        Cross_gene = parent_mother;
    }
    else
    {
        Cross = parent_mother;
        Cross_gene = parent_father;
    }

    //std::cout << "Cross_gene fitness: " << Cross_gene.fitness << std::endl;

    int Gene_chooser = rand()%Cross.Genes.size();
    cout << "Gene Chooser: " << Gene_chooser << endl;
    if (((Cross.Genes[Gene_chooser] + Cross_gene.Genes[Gene_chooser])/2.0) > 1)
        Cross.Genes[Gene_chooser] = 1;
    else
        Cross.Genes[Gene_chooser] = (Cross.Genes[Gene_chooser] + Cross_gene.Genes[Gene_chooser])/2.0;
  */

void ludo_player_gen_alg::start_turn(positions_and_dice relative){
    pos_start_of_turn = relative.pos;
    dice_roll = relative.dice;
    int decision = make_decision();
    emit select_piece(decision);
}


void ludo_player_gen_alg::post_game_analysis(std::vector<int> relative_pos){
    pos_end_of_turn = relative_pos;
    bool game_complete = true;
    for(int i = 0; i < 4; ++i){
        if(pos_end_of_turn[i] < 99){
            game_complete = false;
        }
    }
    emit turn_complete(game_complete);
}


/**
 * @brief ga_ludo_player::checkoutBoard
 * Takes a look at the board and returns a matrice of the possible moves that each pieces can do.
 * The matrix will be ActionsXpieces -> ActionsX4
 */

std::vector<std::vector<bool>> ludo_player_gen_alg::check_board(){
    /* This sections create the matrix of the possible moves */
    std::vector<bool> tmp;
    std::vector<std::vector<bool>> moves;
    for (int i = 0;i<4;i++) {
        for (int j = 0;j<12;j++) {
            tmp.push_back(false);
        }
        moves.push_back(tmp);
        tmp.clear();
    }

    /*****************************
          looking at board
      *****************************/
    for(int pieces = 0; pieces <4 ; pieces++){  // Lookign through each players possible moves
        int index = 0;
        std::vector<int> opponentsAtSamePos;
        if(pos_start_of_turn[pieces]!= SAFE){   // Check if piece is in goal
            index = pos_start_of_turn[pieces]+dice_roll;
            if((dice_roll == 6)&&(pos_start_of_turn[pieces]==HOME)){
                //std::cout<<"out"<<std::endl;
                moves[pieces][0]=true; //enterBoard
            }
            // Move to endzone/ goal stretch
            if(pos_start_of_turn[pieces]+dice_roll >= FIRST_IN_GOAL_STRETCH && index < LAST_ON_BOARD){
                moves[pieces][7]= true;
            }

            // SendOpponentHome && Self home
            for(int opponentPiece = 4; opponentPiece < pos_start_of_turn.size(); opponentPiece++){ //Loop over enemies
                if((index == pos_start_of_turn[opponentPiece]) && (pos_start_of_turn[pieces] != HOME )){
                    moves[pieces][2]= true;
                }

            // Self home P1
                if(index == pos_start_of_turn[opponentPiece]){
                    opponentsAtSamePos.push_back(opponentPiece);
                }
            }
            // Self home P2
            if(opponentsAtSamePos.size()>1){
                moves[pieces][12] = true;
            }
            // Block with own piece
            for (int i = 0; i < 4; ++i) {
                if(pos_start_of_turn[pieces]+dice_roll ==pos_start_of_turn[i] && pos_start_of_turn[pieces] !=HOME){
                    moves[pieces][3]= true;
                    }
            }
            // moveNormal forward, !! Tjek der ikke står 2 brikker !!
            if(pos_start_of_turn[pieces] != HOME && index != SAFE){
                moves[pieces][4]= true;
                //moveNormalCounter+=1;
            }

            // Move onto a star if possible
            if( (index == 5  ||
                index == 18 ||
                index == 31 ||
                index == 44 ||
                index == 11 ||
                index == 24 ||
                index == 37 ||
                    index == 50 ) && pos_start_of_turn[pieces] !=HOME){
                 moves[pieces][5]= true;
                 //move2StarCounter+=1;
            }
            // Move onto globe - using index instead of Piece vector container
            if((index == 8 ||
                index == 21 ||
                index == 34 ||
                    index== 47)&& (pos_start_of_turn[pieces] !=HOME)){  //doesn't check for more people at same spot
                    moves[pieces][6]= true;
            }

            // Move in endzone
            if(pos_start_of_turn[pieces] >= FIRST_IN_GOAL_STRETCH  ){
                moves[pieces][8]= true;
                //moveInSafeZoneCounter+=1;
            }
            // Finish piece
            if(pos_start_of_turn[pieces]+dice_roll == LAST_ON_BOARD ){
                moves[pieces][9]= true;
                //finishPieceCounter+=1;
            }
            // Another players home

            if( index == 13 ||
                index == 26 ||
                    index == 39){
                moves[pieces][10] = true;
            }
            /*for(int oppPiece = 4; oppPiece < pos_start_of_turn.size(); oppPiece++){
                if(pos_start_of_turn[pieces])
            }*/

        }

    }
    return moves;

}

