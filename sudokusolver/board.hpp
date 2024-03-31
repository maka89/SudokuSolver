#include <set>
//#include <iostream>
#include <tuple>
#include <list>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
class Square {

public:
    Square() {
        value = 0;
        reset_possible();
    }
    Square(const Square &s0) {
        value = s0.value;
        possible_values = s0.possible_values;
    }
    void setSquare(uint8_t v) {
        value = v;
        reset_possible();
    }
    void erase_possible(uint8_t v) {
        possible_values.erase(v);
    }
    void reset_possible() {
        
        if (value == 0) {
            possible_values.clear();
            for (uint8_t k = 1; k < 10; k++)
                possible_values.insert(k);
        }
        else 
            possible_values.clear();
        
    }
    uint8_t get() { return value; }
    uint8_t getNumVals() { return (uint8_t)possible_values.size(); }
    std::set<uint8_t> get_possible_values(){ return possible_values; }

private:
    uint8_t value;
    std::set<uint8_t> possible_values;
};

class Board {

public:
    Board() {
        for (uint8_t i = 0; i < 9; i++) {
            for (uint8_t j = 0; j < 9; j++) {
                squares[i][j].setSquare(0);
                init_squares[i][j].setSquare(0);
            }
        }
    }
    Board(const Board &b0) {
        for (uint8_t i = 0; i < 9; i++) {
            for (uint8_t j = 0; j < 9; j++) {
                squares[i][j] = b0.squares[i][j];
                init_squares[i][j] = b0.init_squares[i][j];
            }
        }
    }
    void setBoard(uint8_t board[9][9]) {
        for (uint8_t i = 0; i < 9; i++) {
            for (uint8_t j = 0; j < 9; j++) {
                squares[i][j].setSquare(board[i][j]);
                init_squares[i][j].setSquare(board[i][j]);
            }
        }
    }
    
    int setBoard(std::string filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::stringstream strStream;
            strStream << file.rdbuf();
            return setBoardString(strStream.str());
        }
        else {
            return 2;
        }
    }
    int setBoardString(std::string board) {
        std::stringstream ss(board);
        std::string line;

        std::vector<std::string> lines;

        while (getline(ss, line)) {
            line = std::regex_replace(line, std::regex(R"([^0-9])"),"");
            if (line.size() == 9)
                lines.push_back(line);
        }
        if (lines.size() != 9)
            return 1;
        else{
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    init_squares[i][j].setSquare((uint8_t)((int)(lines[i][j] - '0')));
                    squares[i][j].setSquare((uint8_t)((int)(lines[i][j] - '0')));

                }
            }
        }
            return 0;

        
    }

    void setSquare(uint8_t i, uint8_t j, uint8_t v) {
        squares[i][j].setSquare(v);
    }
    Square getSquare(uint8_t i, uint8_t j) {
        return squares[i][j];
    }
    std::string printBoard() {
        std::stringstream ss;
        for (uint8_t i = 0; i < 3; i++) {
            ss << (unsigned)squares[i][0].get() << " " << (unsigned)squares[i][1].get() << " " << (unsigned)squares[i][2].get() << "\t";
            ss << (unsigned)squares[i][3].get() << " " << (unsigned)squares[i][4].get() << " " << (unsigned)squares[i][5].get() << "\t";
            ss << (unsigned)squares[i][6].get() << " " << (unsigned)squares[i][7].get() << " " << (unsigned)squares[i][8].get() << std::endl;
        }

        ss << std::endl;
        for (uint8_t i = 3; i < 6; i++) {
            ss << (unsigned)squares[i][0].get() << " " << (unsigned)squares[i][1].get() << " " << (unsigned)squares[i][2].get() << "\t";
            ss << (unsigned)squares[i][3].get() << " " << (unsigned)squares[i][4].get() << " " << (unsigned)squares[i][5].get() << "\t";
            ss << (unsigned)squares[i][6].get() << " " << (unsigned)squares[i][7].get() << " " << (unsigned)squares[i][8].get() << std::endl;
        }

        ss << std::endl;
        for (uint8_t i = 6; i < 9; i++) {
            ss << (unsigned)squares[i][0].get() << " " << (unsigned)squares[i][1].get() << " " << (unsigned)squares[i][2].get() << "\t";
            ss << (unsigned)squares[i][3].get() << " " << (unsigned)squares[i][4].get() << " " << (unsigned)squares[i][5].get() << "\t";
            ss << (unsigned)squares[i][6].get() << " " << (unsigned)squares[i][7].get() << " " << (unsigned)squares[i][8].get() << std::endl;
        }
        return ss.str();

    }
    /*
    void printNumPosVals() {
        for (uint8_t i = 0; i < 9; i++) {
            for (uint8_t j = 0; j < 9; j++)
                std::cout << (unsigned)squares[i][j].getNumVals() << " ";
            std::cout << std::endl;
        }
    }*/

    
    void scanBoard() {
        for (uint8_t i = 0; i < 9; i++) {
            for (uint8_t j = 0; j < 9; j++) {

                if (squares[i][j].get() == 0) {

                    squares[i][j].reset_possible();
                    //Horizontal scan
                    for (uint8_t k = 0; k < 9; k++) {
                        uint8_t v = squares[i][k].get();
                        if (v > 0)
                            squares[i][j].erase_possible(v);
                    }

                    //Vertical scan
                    for (uint8_t k = 0; k < 9; k++) {
                        uint8_t v = squares[k][j].get();
                        if (v > 0)
                            squares[i][j].erase_possible(v);

                    }

                    //Square scan
                    uint8_t ip = (i / 3) * 3;
                    uint8_t jp = (j / 3) * 3;

                    for (uint8_t k = ip; k < ip + 3; k++) {
                        for (uint8_t l = jp; l < jp + 3; l++) {
                            uint8_t v = squares[k][l].get();
                            if (v > 0)
                                squares[i][j].erase_possible(v);
                        }
                    }


                }

            }
        }
    }
    bool checkValid() {
        for (uint8_t i = 0; i < 9; i++) {
            std::set<uint8_t> s;
            s.clear();
            for (uint8_t j = 0; j < 9; j++) {
                if (squares[i][j].get() > 0) {

                    if (s.find(squares[i][j].get()) != s.end())
                        return false;
                    else
                        s.insert(squares[i][j].get());
                }
            }
        }

        for (uint8_t j = 0; j < 9; j++) {
            std::set<uint8_t> s;
            s.clear();
            for (uint8_t i = 0; i < 9; i++) {
                if (squares[i][j].get() > 0) {

                    if (s.find(squares[i][j].get()) != s.end())
                        return false;
                    else
                        s.insert(squares[i][j].get());
                }
            }
        }
        
        for (uint8_t i = 0; i < 3; i++) {
            for (uint8_t j = 0; j < 3; j++) {
                std::set<uint8_t> s;
                s.clear();

                for (uint8_t k = 0; k < 3; k++) {
                    for (uint8_t l = 0; l < 3; l++) {
                        uint8_t u, v;
                        u = 3 * i + k;
                        v = 3 * j + l;
                        if (squares[u][v].get() > 0) {

                            if (s.find(squares[u][v].get()) != s.end())
                                return false;
                            else
                                s.insert(squares[u][v].get());
                        }
                    }
                }

            }
        }



        return true;
    }
    void fast_forward() {

        bool flag = false;
        while (!flag) {
            scanBoard();
            auto options = getBestOptions();
            if (options.size() >= 1) {
                auto t = options.front();
                uint8_t i = std::get<0>(t);
                uint8_t j = std::get<1>(t);

                auto pv = squares[i][j].get_possible_values();
                if (pv.size() == 1)
                    squares[i][j].setSquare(*pv.begin());
                else
                    flag = true;
            }
            else
                flag = true;
        }
    }
    std::list<std::tuple<uint8_t, uint8_t>> getBestOptions() {
        uint8_t minvalue = (uint8_t)1000;

        for (uint8_t i = 0; i < 9; i++) {
            for (uint8_t j = 0; j < 9; j++) {
                if (squares[i][j].getNumVals() < minvalue && squares[i][j].get() == 0)
                    minvalue = squares[i][j].getNumVals();
            }
        }
        std::list<std::tuple<uint8_t, uint8_t>> ret;

        for (uint8_t i = 0; i < 9; i++) {
            for (uint8_t j = 0; j < 9; j++) {
                if (squares[i][j].getNumVals() == minvalue && squares[i][j].get() == 0)
                    ret.push_back(std::make_tuple(i, j));
            }
        }
        return ret;
    }

    bool checkBoard() {
        for (uint8_t i = 0; i < 9; i++) {
            for (uint8_t j = 0; j < 9; j++) {
                if (squares[i][j].getNumVals() == 0 && squares[i][j].get() == 0)
                    return false;
            }
        }
        return true;
    }
    bool checkDone() {
        for (uint8_t i = 0; i < 9; i++) {
            for (uint8_t j = 0; j < 9; j++) {
                if (squares[i][j].get() == 0)
                    return false;
            }
        }
        return true;
    }

    bool attempt_solve() {
        reset();
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6);

        


        
        bool flag = false;

       
        while (!flag) {
            fast_forward();
            if (checkDone()) {
                return true;
            }
            else if (!checkBoard()) {
                return false;
            }
            else {
                auto t = getBestOptions().front();
                uint8_t i = std::get<0>(t);
                uint8_t j = std::get<1>(t);


                auto pv = squares[i][j].get_possible_values();
                auto it = pv.begin();
                std::uniform_int_distribution<std::mt19937::result_type> dist(0, (unsigned)pv.size() - 1);
                int n = dist(rng);
                // 'advance' the iterator n times
                std::advance(it, n);

                squares[i][j].setSquare(*it);

            }
            
        }
        
    }
    void reset() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                squares[i][j].setSquare(init_squares[i][j].get());
            }
        }
    }
private:

    


    Square squares[9][9];
    Square init_squares[9][9];

};
