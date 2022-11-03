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

#include "./move.hpp"

checkers::Move::Move(int from_x, int from_y, int to_x, int to_y){
    this->from_x = from_x;
    this->from_y = from_y;
    this->to_x = to_x;
    this->to_y = to_y;
}

checkers::Move::Move(const std::string &uci) {
    //check for input
    const std::regex move_regex("([a-h][1-8]){2}");
    if (!std::regex_match(uci, move_regex)){
        throw std::invalid_argument( "incorrect text move format: '"+uci + "'. Expected input: '([a-h][1-8]){2}', example: 'a1h8'" );
    }
    this->from_x = std::distance(this->convert.begin(), std::find(this->convert.begin(), this->convert.end(), uci[0]));
    this->from_y = std::stoi(std::string(1,uci[1]))-1;
    this->to_x = std::distance(this->convert.begin(), std::find(this->convert.begin(), this->convert.end(), uci[2]));;
    this->to_y = std::stoi(std::string(1,uci[3]))-1;
}

std::string checkers::Move::to_uci() {
    return  std::string(1,this->convert[this->from_x+1]) + std::to_string(this->from_y+1)
    + std::string (1,this->convert[this->to_x+1]) + std::to_string(this->to_y+1);
}
