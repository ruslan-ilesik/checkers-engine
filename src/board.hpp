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

#pragma once
#include <vector>
#include <array>
#include <string>
#include <stdexcept>

#include "./move.hpp"


namespace checkers{
    enum End_game{none,win,lose,draw_not_eating,draw_not_win_big_road,draw_same_positions};

    class Board{
        private:
            std::vector<Move> possible_moves;
            std::array<std::array<char,8>,8> board;
            bool is_black;
            bool is_eat_moves = false;
            std::array<std::array<int,2>,4> directions = {{{1,-1},{1,1},{-1,1},{-1,-1}}}; //x,y
            void update_possible_moves();
            std::vector<Move> get_eat_moves_by_pos(const std::array<int,2>& pos);

            int moves_without_eating =0;
            int moves_only_by_king = 0;
            int usual_w = 0;
            int usual_b = 0;
            int king_w = 0;
            int king_b = 0;

            int big_road_cond =0;

            std::vector<std::array<std::array<char,8>,8>> previous_pos =
                    {this->board,this->board,this->board,this->board,this->board,this->board,this->board,this->board};


        public:
            Board();

            std::vector<Move> get_possible_moves();
            std::array<std::array<char,8>,8> get_board();
            enum End_game check_end_game();
            void make_turn(const checkers::Move& move);


            bool is_black_turn();
            bool is_white_turn();
            char get_turn();
    };

}

