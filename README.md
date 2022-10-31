# checkers-engine
simple checkers engine which you can use for your projects 

requirements: C++11

#usage

```cpp
  
#include <iostream>
#include "./src/board.hpp"

int main(){
    checkers::Board a; //creating board
    auto nm = checkers::Move("a2h1"); //generating move from text
    std::cout << nm.to_uci() << '\n'; //getting text version of move
    while(1){
        std::cout << a.get_turn() << '\n'<<'\n'; // 'w'|'b' - whoose turn
        a.is_black() // bool - is black turn
        a.is_white() // bool - is white turn

        auto b = a.get_board(); // getting board, std::array<std::array<char,8>,8>, containing '.'|'b'|'B'|'w'|'W' characters
        for (auto i : b){  //printing board to console
            for (auto c : i){
                std::cout << c;
            }
            std::cout << '\n';
        }
        auto m = a.get_possible_moves(); // getting vector of possible moves ,std::vector <checkers::Move>, 
        for (auto& c : m) { //printing moves
            std::cout << '[' << c.from_x << ' ' << c.from_y << ' ' << c.to_x << ' ' << c.to_y << "], \n";  // all information which moves contains
        }
        std::cout << a.check_end_game('w') << ' ' << a.check_end_game('b'); /* check end of game, gets 'w'|'b' to check conditions for specific player, without arguments returns states for player now. enum End_game{
        none //anyone do not win
        ,win
        ,lose
        ,draw_not_eating // anyone do not eating anyone for specific time (can be founded in rules of checkers)
        ,draw_not_win_big_road // when games do not end on big road with 5 moves (can be founded in rules of checkers)
        ,draw_same_positions // when 3 times in a row players getting in same position (can be founded in rules of checkers)
        };*/

        int id;
        std::cin >>id;
        a.make_turn(a.get_possible_moves()[id]); // make turn get`s move and makes move. updating win/lose/draw condiutions, changes whoose turn and updates possible moves
    }

}

```
