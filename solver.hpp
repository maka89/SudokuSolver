#include "board.hpp"
enum return_code
{
	SOLVED = 0,
	CONTINUE = 1,
	WRONG = 2,
	INVALID = 3,
	DUMMY = 4
};

std::tuple<Board,return_code> solve(Board b) {

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

		for (auto it = pv.begin(); it != pv.end(); it++) {
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