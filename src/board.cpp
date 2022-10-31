/*
  MIT License

Copyright (c) 2022 ilesik

        Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
        copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
#include "./board.hpp"


#include <iostream>

std::vector <checkers::Move> checkers::Board::get_possible_moves() {
    return this->possible_moves;
}

checkers::Board::Board() {
            this->is_black = false;
            this->board = std::array<std::array<char,8>,8>{{
            {
                    '.','b','.','b','.','b','.','b'
            },
            {
                    'b','.','b','.','b','.','b','.'
            },
            {
                    '.','b','.','b','.','b','.','b'
            },
            {
                    '.','.','.','.','.','.','.','.'
            },
            {
                    '.','.','.','.','.','.','.','.'
            },
            {
                    'w','.','w','.','w','.','w','.'
            },
            {
                    '.','w','.','w','.','w','.','w'
            },
            {
                    'w','.','w','.','w','.','w','.'
            },
    }};

    this->board = std::array<std::array<char,8>,8>{{
       {
               '.','.','.','.','.','.','.','.'
       },
       {
               '.','.','.','.','W','.','.','.'
       },
       {
               '.','.','.','b','.','.','.','.'
       },
       {
               '.','.','.','.','.','.','.','.'
       },
       {
               '.','.','.','.','.','.','.','.'
       },
       {
               '.','.','.','.','.','.','.','.'
       },
       {
               '.','.','.','.','.','.','.','.'
       },
       {
               '.','.','.','.','.','.','.','.'
       },
}};


    this->update_possible_moves();
}

bool checkers::Board::is_black_turn() {
    return this->is_black;
}

bool checkers::Board::is_white_turn() {
    return !this->is_black;
}

char checkers::Board::get_turn() {
    return (this->is_black?'b':'w');
}

std::array<std::array<char, 8>, 8> checkers::Board::get_board() {
    return this->board;
}

void checkers::Board::update_possible_moves() {
    this->possible_moves.clear();
    this->is_eat_moves = false;
    this-> usual_w = 0;
    this-> usual_b = 0;
    this-> king_w = 0;
    this-> king_b = 0;

    for (int y = 0; y < this->board.size();y++){
        for (int x = 0 ; x < this->board[y].size(); x++){
            if (this->board[y][x] !='.'){
                if(tolower(this->board[y][x]) == 'w'){
                    king_w += isupper(this->board[y][x]);
                    usual_w += !isupper(this->board[y][x]);
                }
                else{
                    king_b += isupper(this->board[y][x]);
                    usual_b += !isupper(this->board[y][x]);
                }


                for (auto& d : this->directions){
                    char me = tolower(this->board[y][x]);
                    if (isupper(this->board[y][x]) && me == this->get_turn()) {

                        int multiplication = 1;
                        bool local_eat = false;
                        while (
                              y + d[1]*multiplication >= 0 &&
                              x + d[0]*multiplication >= 0 &&
                              y + d[1]*multiplication < this->board.size() &&
                              x + d[0]*multiplication < this->board[0].size())
                        {
                             std::array<int,2> pos = { x + d[0]*multiplication, y + d[1]*multiplication};
                             if (this->board[pos[1]][pos[0]] == '.'){
                                  if (!this->is_eat_moves || local_eat){
                                      this->possible_moves.push_back(checkers::Move(x, y, pos[0], pos[1]));
                                  }
                             }
                             else if (me != tolower(this->board[pos[1]][pos[0]])){
                                   if (local_eat) {
                                       break;
                                   }
                                   if (pos[1] + d[1] < 0 || pos[0] + d[0] < 0 || pos[1] + d[1] >= this->board.size() ||
                                   pos[0] + d[0] >= this->board[0].size()) {
                                       break;
                                   }
                                   if (!this->is_eat_moves){
                                       this->is_eat_moves = true;
                                       this->possible_moves.clear();
                                   }
                                   local_eat = true;
                                   this->possible_moves.push_back(checkers::Move(x, y, pos[0]+d[0], pos[1]+d[1]));
                                   multiplication++;
                             }
                             multiplication++;

                        }

                    }
                    else{
                        if (y + d[1] < 0 || x + d[0] < 0 || y + d[1] >= this->board.size() ||
                            x + d[0] >= this->board[0].size()) {
                            continue;
                        }
                        if (me == this->get_turn()) {
                            if (this->board[y + d[1]][x + d[0]] == '.' && (this->is_black ? d[1] == 1 : d[1] == -1)) {
                                if (!this->is_eat_moves) {
                                    this->possible_moves.push_back(checkers::Move(x, y, x + d[0], y + d[1]));
                                }
                            } else if (y + d[1] * 2 < 0 || x + d[0] * 2 < 0 || y + d[1] * 2 >= this->board.size() ||
                                       x + d[0] * 2 >= this->board[0].size()) {
                                continue;
                            } else if (me != tolower(this->board[y + d[1]][x + d[0]]) &&
                                       this->board[y + d[1]][x + d[0]] != '.' &&
                                       this->board[y + d[1] * 2][x + d[0] * 2] == '.') {
                                if (!this->is_eat_moves) {
                                    this->is_eat_moves = true;
                                    this->possible_moves.clear();
                                }
                                this->possible_moves.push_back(checkers::Move(x, y, x + d[0] * 2, y + d[1] * 2));
                            }

                        }
                    }
                }
            }
        }
    }


    if ((this->king_w==1 && this->usual_w==0 && this->king_b+this->usual_b == 3)||
        (this->king_b==1 && this->usual_b==0 && this->king_w+this->usual_w == 3)
            )
    {
        bool on_big_road = false;
        char look_symbol = this->king_b+this->usual_b == 3?'W':'B';
        for (int y=0,x = 0;y < this->board.size() ; x++, y++){
            if (look_symbol == this->board[y][x]){
                on_big_road = true;
            }
        }
        for (int y= this->board.size()-1,x = 0;y >=0 ; x++, y--){
            if (look_symbol == this->board[y][x]){
                on_big_road = true;
            }
        }
        if (on_big_road){
            this->big_road_cond++;
        }
        else{
            this->big_road_cond = 0;
        }

    } else{
        this->big_road_cond = 0;
    }

}


void checkers::Board::make_turn(const checkers::Move& move) {
    this->moves_without_eating++;

    if (isupper(this->board[move.to_y][move.to_x])){
        this->moves_only_by_king++;
    }
    else{
        this->moves_only_by_king = 0;
    }
    if (abs(move.from_x - move.to_x) > 1){
        //delete element between that values
        this->moves_without_eating=0;
        this->moves_only_by_king=0;
        std::array<int,2> offset = {(move.to_x - move.from_x) >0?1:-1,move.to_y - move.from_y >0?1:-1};
        int multiplication =1;
        while (move.from_x+offset[0]*multiplication != move.to_x){
            this->board[move.from_y+offset[1]*multiplication][move.from_x+offset[0]*multiplication] = '.';
            multiplication++;
        }

    }
    this->board[move.to_y][move.to_x] = this->board[move.from_y][move.from_x];
    this->board[move.from_y][move.from_x] = '.';

    //transform to king
    if ((this->board[move.to_y][move.to_x] == 'w' && move.to_y == 0) || (this->board[move.to_y][move.to_x] == 'b' && move.to_y == this->board.size()-1)){
        this->board[move.to_y][move.to_x] = toupper(this->board[move.to_y][move.to_x]);
        this->moves_without_eating=0;
        this->moves_only_by_king=0;
    }

    auto moves = this->get_eat_moves_by_pos({move.to_x,move.to_y});

    if (moves.size() && this->is_eat_moves) {
        this->possible_moves = moves;
    }
    else{
        this->is_black = !this->is_black;
        this->update_possible_moves();
    }

    this->previous_pos.erase(this->previous_pos.begin());
    this->previous_pos.push_back(this->board);
}

std::vector<checkers::Move> checkers::Board::get_eat_moves_by_pos(const std::array<int, 2> &pos) {
    std::vector<checkers::Move> moves;
    if (isupper(this->board[pos[1]][pos[0]])){

        int x = pos[0];
        int y = pos[1];
        for (auto& d : this->directions){
            int multiplication = 1;
            bool local_eat = false;
            while (
                    y + d[1]*multiplication >= 0 &&
                    x + d[0]*multiplication >= 0 &&
                    y + d[1]*multiplication < this->board.size() &&
                    x + d[0]*multiplication < this->board[0].size()) {
                std::array<int, 2> pos = {x + d[0] * multiplication, y + d[1] * multiplication};
                if (this->board[pos[1]][pos[0]] == '.') {
                    if (local_eat) {
                        moves.push_back(checkers::Move(x, y, pos[0], pos[1]));
                    }
                } else if (tolower(this->board[y][x]) != tolower(this->board[pos[1]][pos[0]])) {
                    if (local_eat) {
                        break;
                    }
                    if (pos[1] + d[1] < 0 || pos[0] + d[0] < 0 || pos[1] + d[1] >= this->board.size() ||
                        pos[0] + d[0] >= this->board[0].size()) {
                        break;
                    }
                    local_eat = true;
                    moves.push_back(checkers::Move(x, y, pos[0] + d[0], pos[1] + d[1]));
                    multiplication++;
                }
                multiplication++;
            }
        }
    }
    else{
        for (auto& d : this->directions) {
            char me = tolower(this->board[pos[1]][pos[0]]);
            if (pos[1]+d[1] < 0 || pos[0]+d[0]  < 0 || pos[1]+d[1] >= this->board.size() || pos[0]+d[0]  >= this->board[0].size() ){
                continue;
            }
            else if (this->board[pos[1]+d[1]][pos[0]+d[0]] == '.'){
                continue;
            }
            else if (pos[1]+d[1]*2 < 0 || pos[0]+d[0]*2 < 0 || pos[1]+d[1]*2 >= this->board.size() || pos[0]+d[0]*2  >= this->board[0].size()){
                continue;
            }
            else if (me != tolower(this->board[pos[1]+d[1]][pos[0]+d[0]]) && this->board[pos[1]+d[1]*2][pos[0]+d[0]*2] == '.'){
                moves.push_back(checkers::Move(pos[0],pos[1],pos[0]+d[0]*2,pos[1]+d[1]*2));
            }
        }

    }
    return moves;
}

checkers::End_game checkers::Board::check_end_game(char who) {
    bool change = false;
    if (!(who == '.' || who== 'w' || who == 'b')){
        throw std::invalid_argument( "incorrect text move format: '"+std::string(1,who) + "'. Expected input: '.' or 'w' or 'b'" );
    }
    if (who == '.'){
        who = this->get_turn();
        change = true;
    }
    int total_count = this->king_w +this->king_b +this->usual_b + this->usual_w;
    if (this->moves_only_by_king >= 30 ||
            (this->king_b && this->king_w &&
                (
                        (((total_count ==6 || total_count==7) && this->moves_without_eating>=120))||
                        (((total_count ==4 || total_count==5) && this->moves_without_eating>=60))||
                        (((total_count ==2 || total_count==3) && this->moves_without_eating>=10))
                )
            )
    )
    {
        return draw_not_eating;
    }
    if (this->big_road_cond >= 6){
        return  draw_not_win_big_road;
    }

   if (this->previous_pos[0] == this->previous_pos[4] && this->previous_pos[4] == this->board){
       return draw_same_positions;
   }




    if (this->get_turn() != who){
        this->is_black = !this->is_black;
        this->update_possible_moves();
    }

    if (!this->possible_moves.size()){
        return lose;
    }

    this->is_black = !is_black;
    this->update_possible_moves();
    if (!this->possible_moves.size()){
        return win;
    }

    if (change){
        this->is_black = !is_black;
        this->update_possible_moves();
    }



}

