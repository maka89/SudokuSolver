#include "board.hpp"
#include <iostream>

#ifndef SUDOKU_DISABLE_TIMESTAMP
#include <chrono>
#endif

enum return_code
{
	SOLVED = 0,
	CONTINUE = 1,
	WRONG = 2,
	INVALID = 3,
	DUMMY = 4
};

std::tuple<Board,return_code> solve(Board b, std::default_random_engine *rng = NULL) {

	b.fast_forward();
	return_code rc;
	if (b.checkDone()) {
		rc = SOLVED;
		return std::make_tuple(b, rc);
	}
	else if (!b.checkBoard()) {
		rc = WRONG;
		return std::make_tuple(b, rc);
	}
	else if (!b.checkValid()) {
		rc = INVALID;
		return std::make_tuple(b, rc);
	}
	else {
		
		auto t = b.getBestOptions().front();
		uint8_t i = std::get<0>(t);
		uint8_t j = std::get<1>(t);

		auto pv = b.getSquare(i, j).get_possible_values();
		
		std::vector<uint8_t> v;
		for (auto it = pv.begin(); it != pv.end(); it++)
			v.push_back(*it);
		
		if (rng != NULL) 
			std::shuffle(std::begin(v), std::end(v), *rng);
		
		for (auto it = v.begin(); it != v.end(); it++) {
			Board bnew = b;
			
			bnew.setSquare(i, j, *it);
			auto t = solve(bnew);
			return_code r = std::get<1>(t);
			if (r == SOLVED)
				return t;
		}
		return std::make_tuple(b, WRONG);
	}
}

std::string StringSolution(std::tuple<Board, return_code> t) {
	Board b_solved = std::get<0>(t);
	return_code rc = std::get<1>(t);

	std::stringstream output;
	output << "SUDOKU SOLVER OUTPUT" << std::endl;

#ifndef SUDOKU_DISABLE_TIMESTAMP 
	const auto now = std::chrono::system_clock::now();
	const auto time_zone = std::chrono::current_zone();
	const auto local_time = time_zone->to_local(now);
	const auto time_point = std::chrono::time_point_cast<std::chrono::days>(local_time);
	const auto year_month_day = std::chrono::year_month_day{ time_point };
	const auto time = std::chrono::hh_mm_ss{ local_time -time_point};


	int year = static_cast<int>(year_month_day.year());
	int month = static_cast<unsigned>(year_month_day.month());
	int day = static_cast<unsigned>(year_month_day.day());


	output << "SOLUTION DATE/TIME: " << year << "-"<<month<<"-"<<day <<"  " << time.hours() << ":" <<time.minutes()<<":"<<time.seconds() << std::endl;
#endif

	if (rc == 0)
		output << "STATUS: BOARD SOLVED SUCCESSFULLY";
	else if (rc == 3)
		output << "STATUS: INVALID BOARD";
	else
		output << "STATUS: SOLVE FAILED";

	output << std::endl << std::endl;
	output << "SOLUTION: " << std::endl;
	output << b_solved.printBoard() << std::endl;

	output << std::endl << "INITIAL BOARD: " << std::endl;
	b_solved.reset();
	output << b_solved.printBoard() << std::endl;
	return output.str();
}
int printSolution(std::tuple<Board, return_code> t, std::string filename) {
	
	std::ofstream file(filename);
	if (file.is_open()) {
		std::string text = StringSolution(t);
		file << text << std::endl;
		file.close();
		return 0;
	}
	else {
		return 1;
	}
}