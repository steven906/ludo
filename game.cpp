#include "game.h"
#define DEBUG 0

game::game(){
    fitness.resize(POPULATION_SIZE);
    game_delay = 1000;
    game_complete = false;
    turn_complete = true;
    for(int i = 0; i < 16; ++i){
         player_positions.push_back(-1);
    }
    color = 3;
}

game::game(ludo_player_gen_alg* player){
    fitness.resize(POPULATION_SIZE);
    game_delay = 1000;
    game_complete = false;
    turn_complete = true;
    for(int i = 0; i < 16; ++i){
         player_positions.push_back(-1);
    }
    color = 3;
    GA = player;
}


void game::reset(){
    game_complete = false;
    turn_complete = true;
    for(auto &i : player_positions){
        i = -1;
    }
    color = 3;
}


int game::rel_to_fixed(int relative_piece_index){
    return relative_piece_index + color * 4;
}

int game::isStar(int index){
    if(index == 5  ||
       index == 18 ||
       index == 31 ||
       index == 44){
        return 6;
    } else if(index == 11 ||
              index == 24 ||
              index == 37 ||
              index == 50){
        return 7;
    }
    return 0;
}

int game::isOccupied(int index){ //returns number of people
    int number_of_people = 0;
    if(index != 99){
        for(auto i : player_positions){
            if(i == index){
                ++number_of_people;
            }
        }
    }
    return number_of_people;
}

bool game::isGlobe(int index){
    if(index % 13 == 0 || (index - 8) % 13 == 0 || isOccupied(index) > 1){
        return true;
    }
    return false;
}

void game::send_them_home(int index){
    for(size_t i = 0; i < player_positions.size(); ++i){
        if(i < color*4 || i > color*4 + 4){ //different color
            if(player_positions[i] == index){
                player_positions[i] = -1;
            }
        }
    }
}

void game::move_start(int fixed_piece){
    if(dice_result == 6 && player_positions[fixed_piece] < 0){
        player_positions[fixed_piece] = color*13; //move me to start
        send_them_home(color*13); //send pieces home if they are on our start
    }
}

int game::next_turn(unsigned int delay = 0){
    if(game_complete){
        return 0;
    }
    switch(color){
        case 0:
        case 1:
        case 2:
            ++color;
            break;
        case 3:
        default:
            color = 0;
            break;
    }
    global_color = color;
    rollDice();
    relative.dice = getDiceRoll();
    relative.pos = relativePosition();
    emit set_color(color);
    emit set_dice_result(dice_result);

    msleep(delay);
    switch(color){
        case 0:
            emit player1_start(relative);
            break;
        case 1:
            emit player2_start(relative);
            break;
        case 2:
            emit player3_start(relative);
            break;
        case 3:
            emit player4_start(relative);
        default:
            break;
    }

    return 0;
}

void game::movePiece(int relative_piece){
    int fixed_piece = rel_to_fixed(relative_piece);
    int modifier = color * 13;
    int relative_pos = player_positions[fixed_piece];
    int target_pos = 0;
    if(player_positions[fixed_piece] == -1){
        move_start(fixed_piece);
    } else {
        //convert to relative position
        if(relative_pos == 99){
            //cout << "I thought this would be it ";
        } else if(relative_pos < modifier) {
            relative_pos = relative_pos + 52 - modifier;
        } else if( relative_pos > 50) {
            relative_pos = relative_pos - color * 5 - 1;
        } else {//if(relative >= modifier)
            relative_pos = relative_pos - modifier;
        }
        if(DEBUG) cout << "color: " << color << " pos: " << relative_pos << " + " << dice_result << " = " << relative_pos + dice_result;
        //add dice roll
        relative_pos += dice_result;

        int jump = isStar(relative_pos); //return 0 | 6 | 7
        if(jump){
            if(jump + relative_pos == 57){
                relative_pos = 56;
            } else {
                relative_pos += jump;
            }
        }
        //special case checks
        if(relative_pos > 56 && relative_pos < 72){ // go back
            target_pos = 56-(relative_pos-56) + color * 5 + 1; //trust me
        }else if(relative_pos == 56 || relative_pos >= 99){
            target_pos = 99;
        }else if(relative_pos > 50){ // goal stretch
            target_pos = relative_pos + color * 5 + 1;
        } else {
            int new_pos = relative_pos + color * 13;
            if(new_pos < 52){
                target_pos = new_pos;
            } else { //wrap around
                target_pos = new_pos - 52;
            }
        }
        //check for game stuff

        if(isOccupied(target_pos)){
            if(isGlobe(target_pos)){
                target_pos = -1; //send me home
            } else {
                send_them_home(target_pos);
            }
        }
        if(DEBUG) std::cout << " => " << target_pos << std::endl;
        player_positions[fixed_piece] = target_pos;
    }
    std::vector<int> new_relative = relativePosition();
    switch(color){
        case 0:
            emit player1_end(new_relative);
            break;
        case 1:
            emit player2_end(new_relative);
            break;
        case 2:
            emit player3_end(new_relative);
            break;
        case 3:
            emit player4_end(new_relative);
        default:
            break;
    }
    emit update_graphics(player_positions);
}

std::vector<int> game::relativePosition(){
    std::vector<int> relative_positons;
    int modifier = color * 13;

    //from start id to end
    for(int i = color*4; i < player_positions.size(); ++i){
        relative_positons.push_back(player_positions[i]);
    }
    //from 0 to start id
    for(int i = 0; i < color*4; ++i){
        relative_positons.push_back(player_positions[i]);
    }


    for(size_t i = 0; i < relative_positons.size(); ++i){
        if(relative_positons[i] == 99 || relative_positons[i] == -1){
            relative_positons[i] = (relative_positons[i]);
        } else if(relative_positons[i] < modifier) {
            relative_positons[i] = (relative_positons[i]+52-modifier);
        } else if(relative_positons[i] > 50) {
            relative_positons[i] = (relative_positons[i]-color*5-1);
        } else if(relative_positons[i] >= modifier) {
            relative_positons[i] = (relative_positons[i]-modifier);
        }
    }
    return std::move(relative_positons);
}

void game::turnComplete(bool win){
    int tmp;
    game_complete = win;
    turn_complete = true;
    if(game_complete){
        tmp = color;
        GA->player_wins[tmp]+=1;
        //std::cout << "player: " << color << " won" << std::endl;
        emit declare_winner(color);
        msleep(1);
    }

}

void get_runtime(std::chrono::milliseconds time, std::string time_format)
{
    if (time_format == "sec")
        std::cout << "time it will take: " << time.count()*(POPULATION_SIZE)*MAX_GENERATION/1000 << " Seconds" <<std::endl;
    if (time_format == "min")
        std::cout << "time it will take: " << time.count()*(POPULATION_SIZE)*MAX_GENERATION/(1000*60) << " minutes" <<std::endl;
    if (time_format == "hour")
        std::cout << "time it will take: " << time.count()*(POPULATION_SIZE)*MAX_GENERATION/(1000*60*60) << " Hours" <<std::endl;
}

void game::run() {
    vector<int> v = {0, 0, 0, 0};
    bool first_run = true;
    if(DEBUG) std::cout << "color:     relative pos => fixed\n";
    static int gameCnt = 0;
    static int genCnt = 0;
    //wait(10);

    for(int i = 0; i < MAX_GENERATION; i++){
        genCnt +=1;
        //ludo_player_gen_alg GA;
        //GA.chrCnt = 0;
        //GA->chrCnt = 0;
        GA->chrCnt = 1;
        for(int j = 0; j < POPULATION_SIZE; j++ ){

            auto start = chrono::high_resolution_clock::now();
            for(int k = 0; k < GAMES_PER_CHROMOZONES; k++ ){

                while(!game_complete){
                    if(turn_complete){
                    turn_complete = false;
                    msleep(game_delay/4);
                    next_turn(game_delay - game_delay/4);
                    }
                }

                GA->player_wins[0];
                if (color==0)
                    //fitness[k]++;
                    GA->population[j].fitnessScore +=1;
                reset();
                // Updating chromozone number
            }

            GA->chrCnt +=1;
            GA->printChromoFitness();

        if (first_run){
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            get_runtime(duration, "min");
            first_run = false;
            }
        }

        std::cout << "Player 0 won " << GA->player_wins[0] << "times"<<std::endl <<  "Player 1 won " << GA->player_wins[1] << "times. "<<std::endl  <<  "Player 2 won " << GA->player_wins[2] << "times. "<<std::endl<<  "Player 3 won " << GA->player_wins[3] << "times. "<<std::endl;
        std::cout<<std::endl;

        //vector<int> temp = {0,0,0,0};
        //temp = GA->player_wins;
        //GA->player_wins[0] +=1;
        //std::cout << temp[0] << endl;


        //std::cout << "Player 0 won " << GA->player_wins[0] << "times"<<std::endl <<  "Player 1 won " << GA->player_wins[1] << "times. "<<std::endl  <<  "Player 2 won " << GA->player_wins[2] << "times. "<<std::endl<<  "Player 3 won " << GA->player_wins[3] << "times. "<<std::endl;
        //GA->player_wins.empty();
        //GA->set_fitness(fitness);
        //GA->updatePopulation();
        //GA->mutate_population(0.05, 0.2);
        //GA->print_best_chromozone();
        //fitness.clear();
        //fitness.resize(POPULATION_SIZE);
    }
    if(true){
           setGameDelay(5);
           std::cout<<std::endl<<"Population size:\t\t\t"<<POPULATION_SIZE<<std::endl;
           std::cout<<"Generations:\t\t\t"<<genCnt<<std::endl;
           std::cout<<"Chromosomes trained each:\t\t\t"<<GAMES_PER_CHROMOZONES<<std::endl;
           std::cout<<"total iterations:\t\t\t"<<gameCnt<<std::endl;
    }




    double player0 = 0;
    player0 = ((GA->player_wins[0] - gameCnt)*100) / gameCnt;
    //cout << "win percent " << 100 + player0 << endl;
    double player1 = 0;
    player1 = ((GA->player_wins[1] - gameCnt)*100) / gameCnt;
    //cout << "win percent " << 100 + player1 << endl;
    double player2 = 0;
    player2 = ((GA->player_wins[2] - gameCnt)*100) / gameCnt;
    //cout << "win percent " << 100 + player2 << endl;
    double player3 = 0;
    player3 = ((GA->player_wins[3] - gameCnt)*100) / gameCnt;
    //cout << "win percent " << 100 + player3 << endl;

    emit close();
    QThread::exit();
    terminate();

}
