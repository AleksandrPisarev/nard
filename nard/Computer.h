#pragma once
//перегруженная функция перестановки фишек для компьютера
void swap_chips(int f, int d) {
	int row, fromcolomn = f, incolomn = f + d;
	if (fromcolomn > 12) {
		row = 1;
		while (board[row][24 - fromcolomn] == '#') {
			row++;
		}
		board[row - 1][24 - fromcolomn] = ' ';
	}
	else {
		row = 16;
		while (board[row][fromcolomn - 1] == '#') {
			row--;
		}
		board[row + 1][fromcolomn - 1] = ' ';
	}
	if (fromcolomn > 12) {
		if (incolomn < 25) {
			row = 0;
			while (board[row][24 - incolomn] == '#') {
				row++;
			}
			board[row][24 - incolomn] = '#';
		}
		else if (incolomn > 24) {
			incolomn -= 24;
			row = 17;
			while (board[row][incolomn - 1] == '#') {
				row--;
			}
			board[row][incolomn - 1] = '#';
		}
	}
	if (fromcolomn < 13) {
		if (incolomn < 13) {
			row = 17;
			while (board[row][incolomn - 1] == '#') {
				row--;
			}
			board[row][incolomn - 1] = '#';
		}
	}
}
//функция создания массива содержащий номера колонок откуда может сделать ход компьютер
int* move_computer_fromcolomn(int& fromsize) {
	for (int i = 0; i < rows; i += 17) {
		for (int j = 0; j < colomn; j++) {
			if (board[i][j] == '#') fromsize++;
		}
	}
	int* fromcolomn = new int[fromsize] {};
	for (int i = 0, k = 0; i < rows; i += 17) {
		for (int j = 0; j < colomn; j++) {
			if (board[i][j] == '#') {
				if (i == 0) {
					fromcolomn[k] = 24 - j;
					k++;
				}
				if (i == 17) {
					fromcolomn[k] = 1 + j;
					k++;
				}
			}
		}
	}
	return fromcolomn;
}
//функция хода из головы
int move_computer_fromhead(int* die, int& sum_die) {
	if (die[0] == die[1]) {
		if (board[0][24 - 13 - die[0]] != '0') {
			swap_chips(13, die[0]);
			sum_die += die[0];
			die[0] = 0;
			return 0;
		}
	}
	if ((die[0] < die[1]) && (board[0][24 - 13 - die[0]] == ' ')) {
		swap_chips(13, die[0]);
		sum_die += die[0];
		die[0] = 0;
		return 0;
	}
	if ((die[1] < die[0]) && (board[0][24 - 13 - die[1]] == ' ')) {
		swap_chips(13, die[1]);
		sum_die += die[1];
		die[1] = 0;
		return 0;
	}
	if ((die[0] > die[1]) && (board[0][24 - 13 - die[0]] == ' ')) {
		swap_chips(13, die[0]);
		sum_die += die[0];
		die[0] = 0;
		return 0;
	}
	if ((die[1] > die[0]) && (board[0][24 - 13 - die[1]] == ' ')) {
		swap_chips(13, die[1]);
		sum_die += die[1];
		die[1] = 0;
		return 0;
	}
	if ((die[0] < die[1]) && (board[0][24 - 13 - die[0]] == '#')) {
		swap_chips(13, die[0]);
		sum_die += die[0];
		die[0] = 0;
		return 0;
	}
	if ((die[1] < die[0]) && (board[0][24 - 13 - die[1]] == '#')) {
		swap_chips(13, die[1]);
		sum_die += die[1];
		die[1] = 0;
		return 0;
	}
	if ((die[0] > die[1]) && (board[0][24 - 13 - die[0]] == '#')) {
		swap_chips(13, die[0]);
		sum_die += die[0];
		die[0] = 0;
		return 0;
	}
	if ((die[1] > die[0]) && (board[0][24 - 13 - die[1]] == '#')) {
		swap_chips(13, die[1]);
		sum_die += die[1];
		die[1] = 0;
		return 0;
	}
}
//функция хода компьютера после хода из головы
int move_computer_nextfromhead(int* die, int& sum_die) {
	int fromsize = 0;
	int* fromcolomn = move_computer_fromcolomn(fromsize);
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 23) || (fromcolomn[i] == 22) || (fromcolomn[i] == 21) || (fromcolomn[i] == 20)) {
					if ((fromcolomn[i] + die[d]) > 24) {
						if (board[17][(fromcolomn[i] + die[d]) - 25] == ' ') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_nextfromhead(die, sum_die);
							}
						}
					}
					else if ((fromcolomn[i] + die[d]) < 25) {
						if (board[0][24 - fromcolomn[i] - die[d]] == ' ') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_nextfromhead(die, sum_die);
							}
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 23) || (fromcolomn[i] == 22) || (fromcolomn[i] == 21) || (fromcolomn[i] == 20)) {
					if ((fromcolomn[i] + die[d]) > 24) {
						if (board[17][(fromcolomn[i] + die[d]) - 25] == '#') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_nextfromhead(die, sum_die);
							}
						}
					}
					else if ((fromcolomn[i] + die[d]) < 25) {
						if (board[0][24 - fromcolomn[i] - die[d]] == '#') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_nextfromhead(die, sum_die);
							}
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if (fromcolomn[i] == 24) {
					if (board[17][(fromcolomn[i] + die[d]) - 25] == ' ') {
						swap_chips(fromcolomn[i], die[d]);
						sum_die += die[d];
						die[d] = 0;
						if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
							delete[] fromcolomn;
							return 0;
						}
						else {
							delete[] fromcolomn;
							return move_computer_nextfromhead(die, sum_die);
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if (fromcolomn[i] == 24) {
					if (board[17][(fromcolomn[i] + die[d]) - 25] == '#') {
						swap_chips(fromcolomn[i], die[d]);
						sum_die += die[d];
						die[d] = 0;
						if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
							delete[] fromcolomn;
							return 0;
						}
						else {
							delete[] fromcolomn;
							return move_computer_nextfromhead(die, sum_die);
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 18) || (fromcolomn[i] == 17) || (fromcolomn[i] == 16) || (fromcolomn[i] == 15) || (fromcolomn[i] == 14)) {
					if (board[0][24 - fromcolomn[i] - die[d]] == ' ') {
						swap_chips(fromcolomn[i], die[d]);
						sum_die += die[d];
						die[d] = 0;
						if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
							delete[] fromcolomn;
							return 0;
						}
						else {
							delete[] fromcolomn;
							return move_computer_nextfromhead(die, sum_die);
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if (fromcolomn[i] == 19) {
					if (die[d] == 6) {
						if (board[17][(fromcolomn[i] + die[d]) - 25] == ' ') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_nextfromhead(die, sum_die);
							}
						}
					}
					else if (die[d] != 6) {
						if (board[0][24 - fromcolomn[i] - die[d]] == ' ') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_nextfromhead(die, sum_die);
							}
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 18) || (fromcolomn[i] == 17) || (fromcolomn[i] == 16) || (fromcolomn[i] == 15) || (fromcolomn[i] == 14)) {
					if (board[0][24 - fromcolomn[i] - die[d]] == '#') {
						swap_chips(fromcolomn[i], die[d]);
						sum_die += die[d];
						die[d] = 0;
						if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
							delete[] fromcolomn;
							return 0;
						}
						else {
							delete[] fromcolomn;
							return move_computer_nextfromhead(die, sum_die);
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if (fromcolomn[i] == 19) {
					if (die[d] == 6) {
						if (board[17][(fromcolomn[i] + die[d]) - 25] == '#') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_nextfromhead(die, sum_die);
							}
						}
					}
					else if (die[d] != 6) {
						if (board[0][24 - fromcolomn[i] - die[d]] == '#') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_nextfromhead(die, sum_die);
							}
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 1) || (fromcolomn[i] == 2) || (fromcolomn[i] == 3) || (fromcolomn[i] == 4) || (fromcolomn[i] == 5) || (fromcolomn[i] == 6)) {
					if (board[17][(fromcolomn[i] - 1) + die[d]] == ' ') {
						swap_chips(fromcolomn[i], die[d]);
						sum_die += die[d];
						die[d] = 0;
						if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
							delete[] fromcolomn;
							return 0;
						}
						else {
							delete[] fromcolomn;
							return move_computer_nextfromhead(die, sum_die);
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 1) || (fromcolomn[i] == 2) || (fromcolomn[i] == 3) || (fromcolomn[i] == 4) || (fromcolomn[i] == 5) || (fromcolomn[i] == 6)) {
					if (board[17][(fromcolomn[i] - 1) + die[d]] == '#') {
						swap_chips(fromcolomn[i], die[d]);
						sum_die += die[d];
						die[d] = 0;
						if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
							delete[] fromcolomn;
							return 0;
						}
						else {
							delete[] fromcolomn;
							return move_computer_nextfromhead(die, sum_die);
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 7) || (fromcolomn[i] == 8) || (fromcolomn[i] == 9) || (fromcolomn[i] == 10) || (fromcolomn[i] == 11)) {
					if (fromcolomn[i] + die[d] < 13) {
						if (board[17][(fromcolomn[i] - 1) + die[d]] != '0') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_nextfromhead(die, sum_die);
							}
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			cout << "Кость: " << die[d] << endl;
		}
	}
	cout << "Ходить некуда. Ход переходит игроку." << endl;
	delete[] fromcolomn;
}
//функция ход компьютера в дом
int move_computer_house(int* die, int& sum_die) {
	//проверка фишек в доме
	int counterhouse = 0;
	for (int i = 0; i < colomn; i++) {
		if (board[0][i] == '#') {
			counterhouse++;
		}
	}
	for (int i = 0; i < 6; i++) {
		if (board[17][i] == '#') {
			counterhouse++;
		}
	}
	if (counterhouse == 0) {
		int victory = out_ofthe_house(die, sum_die);
		if (victory == -1) return -1;
		return 0;
	}
	int fromsize = 0;
	int* fromcolomn = move_computer_fromcolomn(fromsize);
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 18) || (fromcolomn[i] == 17) || (fromcolomn[i] == 16) || (fromcolomn[i] == 15) || (fromcolomn[i] == 14)) {
					if (board[0][24 - fromcolomn[i] - die[d]] == ' ') {
						swap_chips(fromcolomn[i], die[d]);
						sum_die += die[d];
						die[d] = 0;
						if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
							delete[] fromcolomn;
							return 0;
						}
						else {
							delete[] fromcolomn;
							return move_computer_house(die, sum_die);
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 18) || (fromcolomn[i] == 17) || (fromcolomn[i] == 16) || (fromcolomn[i] == 15) || (fromcolomn[i] == 14)) {
					if (board[0][24 - fromcolomn[i] - die[d]] == '#') {
						swap_chips(fromcolomn[i], die[d]);
						sum_die += die[d];
						die[d] = 0;
						if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
							delete[] fromcolomn;
							return 0;
						}
						else {
							delete[] fromcolomn;
							return move_computer_house(die, sum_die);
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 24) || (fromcolomn[i] == 23) || (fromcolomn[i] == 22) || (fromcolomn[i] == 21) || (fromcolomn[i] == 20) || (fromcolomn[i] == 19)) {
					if ((fromcolomn[i] + die[d]) > 24) {
						if (board[17][(fromcolomn[i] + die[d]) - 25] == ' ') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_house(die, sum_die);
							}
						}
					}
					else if ((fromcolomn[i] + die[d]) < 25) {
						if (board[0][24 - fromcolomn[i] - die[d]] == ' ') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_house(die, sum_die);
							}
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 24) || (fromcolomn[i] == 23) || (fromcolomn[i] == 22) || (fromcolomn[i] == 21) || (fromcolomn[i] == 20) || (fromcolomn[i] == 19)) {
					if ((fromcolomn[i] + die[d]) > 24) {
						if (board[17][(fromcolomn[i] + die[d]) - 25] == '#') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_house(die, sum_die);
							}
						}
					}
					else if ((fromcolomn[i] + die[d]) < 25) {
						if (board[0][24 - fromcolomn[i] - die[d]] == '#') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_house(die, sum_die);
							}
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 1) || (fromcolomn[i] == 2) || (fromcolomn[i] == 3) || (fromcolomn[i] == 4) || (fromcolomn[i] == 5) || (fromcolomn[i] == 6)) {
					if (board[17][(fromcolomn[i] - 1) + die[d]] == ' ') {
						swap_chips(fromcolomn[i], die[d]);
						sum_die += die[d];
						die[d] = 0;
						if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
							delete[] fromcolomn;
							return 0;
						}
						else {
							delete[] fromcolomn;
							return move_computer_house(die, sum_die);
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 1) || (fromcolomn[i] == 2) || (fromcolomn[i] == 3) || (fromcolomn[i] == 4) || (fromcolomn[i] == 5) || (fromcolomn[i] == 6)) {
					if (board[17][(fromcolomn[i] - 1) + die[d]] == '#') {
						swap_chips(fromcolomn[i], die[d]);
						sum_die += die[d];
						die[d] = 0;
						if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
							delete[] fromcolomn;
							return 0;
						}
						else {
							delete[] fromcolomn;
							return move_computer_house(die, sum_die);
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if ((fromcolomn[i] == 7) || (fromcolomn[i] == 8) || (fromcolomn[i] == 9) || (fromcolomn[i] == 10) || (fromcolomn[i] == 11)) {
					if (fromcolomn[i] + die[d] < 13) {
						if (board[17][(fromcolomn[i] - 1) + die[d]] != '0') {
							swap_chips(fromcolomn[i], die[d]);
							sum_die += die[d];
							die[d] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								delete[] fromcolomn;
								return 0;
							}
							else {
								delete[] fromcolomn;
								return move_computer_house(die, sum_die);
							}
						}
					}
				}
			}
		}
	}
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			cout << "Кость: " << die[d] << endl;
		}
	}
	cout << "Ходить некуда. Ход переходит игроку." << endl;
	delete[] fromcolomn;
	return 0;
}
//выброс фишек из дома компьютера
int out_ofthe_house(int* die, int& sum_die) {
	int fromcolomn, row, victory, indexd = 0;
	for (int d = 0; d < 4; d++) {
		if (die[indexd] < die[d]) {
			indexd = d;
		}
	}
			switch (die[indexd])
			{
			case 1:
				fromcolomn = 11;
				break;
			case 2:
				fromcolomn = 10;
				break;
			case 3:
				fromcolomn = 9;
				break;
			case 4:
				fromcolomn = 8;
				break;
			case 5:
				fromcolomn = 7;
				break;
			case 6:
				fromcolomn = 6;
				break;
			}
			if (board[17][fromcolomn] == '#') {
				row = 16;
				while (board[row][fromcolomn] == '#') {
					row--;
				}
				board[row + 1][fromcolomn] = ' ';
				sum_die += die[indexd];
				die[indexd] = 0;
				victory = victory_computer();
				if (victory == -1) return -1;
				if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
					return 0;
				}
				else {
					return out_ofthe_house(die, sum_die);
				}
			}
			else if (board[17][fromcolomn] != '#') {
				int counter_chance_move = 0;//счетчик есть ли фишки перед 
				for (int i = 6; i < fromcolomn; i++) {
					if (board[17][i] == '#') {
						counter_chance_move++;
						if (board[17][i + die[indexd]] != '0') {
							row = 16;
							while (board[row][i] == '#') {
								row--;
							}
							board[row + 1][i] = ' ';
							row = 17;
							while (board[row][i + die[indexd]] == '#') {
								row--;
							}
							board[row][i + die[indexd]] = '#';
							sum_die += die[indexd];
							die[indexd] = 0;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								return 0;
							}
							else {
								return out_ofthe_house(die, sum_die);
							}
						}
					}
				}
				if (counter_chance_move == 0) {
					for (int i = fromcolomn + 1; i <= 11; i++) {
						if (board[17][i] == '#') {
							row = 16;
							while (board[row][i] == '#') {
								row--;
							}
							board[row + 1][i] = ' ';
							sum_die += die[indexd];
							die[indexd] = 0;
							victory = victory_computer();
							if (victory == -1) return -1;
							if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
								return 0;
							}
							else {
								return out_ofthe_house(die, sum_die);
							}
						}
					}
				}
				else if (counter_chance_move != 0) {
					cout << "кость: " << die[indexd] << endl;
					cout << "Хода нет. Пропуск хода." << endl;
					die[indexd] = 0;
					if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
						return 0;
					}
					else {
						return out_ofthe_house(die, sum_die);
					}
				}
			}
}
//функция проверки на победу компьютера
int victory_computer() {
	int counter_outhouse = 0;
	for (int i = 0; i < rows; i += 17) {
		for (int j = 0; j < colomn; j++) {
			if (board[i][j] == '#') counter_outhouse++;
		}
	}
	if (counter_outhouse == 0) {
		cout << "Победил компьютер!!!" << endl;
		return -1;
	}
}
//функция ход компьютера
int move_computer() {
	static int counter_move = 0; // счетчик ходов компьютера
	static int sum_die = 0; // счетчик суммы выпавших костей
	cout << "Ход компьютера. Кости выпали." << endl;
	const int sizedie = 4;
	int die[sizedie]{};
	die[0] = roll_dice();
	die[1] = roll_dice();
	if (die[0] == die[1]) {
		die[2] = die[0];
		die[3] = die[0];
		cout << "первая кость: " << die[0] << endl;
		cout << "вторая кость: " << die[1] << endl;
		cout << "третья кость: " << die[2] << endl;
		cout << "четвнртая кость: " << die[3] << endl;
	}
	else {
		cout << "первая кость: " << die[0] << endl;
		cout << "вторая кость: " << die[1] << endl;
	}
	int copy_d0 = die[0], copy_d1 = die[1];
	//первый ход
	if (counter_move == 0) {
		if (die[0] != die[1]) {
			if (board[0][3] != '0') {
				board[14][11] = ' ';
				board[0][11 - (die[0] + die[1])] = '#';
				show();
				sum_die += die[0] + die[1];
				counter_move++;
				const int size = 4;
				int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
				file_computer(arrstatic);
				return 0;
			}
			else if (board[0][3] == '0') {
				if (11 - (die[0] + die[1]) == 3) {
					if (die[0] > die[1]) {
						board[14][11] = ' ';
						board[0][11 - die[0]] = '#';
						show();
						sum_die += die[0];
						counter_move++;
						const int size = 4;
						int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
						file_computer(arrstatic);
						return 0;
					}
					else {
						board[14][11] = ' ';
						board[0][11 - die[1]] = '#';
						show();
						sum_die += die[1];
						counter_move++;
						const int size = 4;
						int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
						file_computer(arrstatic);
						return 0;
					}
				}
				else {
					board[14][11] = ' ';
					board[0][11 - (die[0] + die[1])] = '#';
					show();
					sum_die += die[0] + die[1];
					counter_move++;
					const int size = 4;
					int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
					file_computer(arrstatic);
					return 0;
				}
			}
		}
		else if (die[0] == die[1]) {
			if ((die[0] == die[1]) && (die[0] == 1)) {
				board[14][11] = ' ';
				board[0][7] = '#';
				show();
				sum_die += die[0] * 4;
				counter_move++;
				const int size = 4;
				int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
				file_computer(arrstatic);
				return 0;
			}
			else if ((die[0] == die[1]) && (die[0] == 2)) {
				if (board[0][3] == '0') {
					board[14][11] = ' ';
					board[0][5] = '#';
					show();
					sum_die += die[0] * 3;
					counter_move++;
					const int size = 4;
					int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
					file_computer(arrstatic);
					return 0;
				}
				else {
					board[14][11] = ' ';
					board[0][3] = '#';
					show();
					sum_die += die[0] * 4;
					counter_move++;
					const int size = 4;
					int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
					file_computer(arrstatic);
					return 0;
				}
			}
			else if ((die[0] == die[1]) && (die[0] == 3)) {
				board[14][11] = ' ';
				board[13][11] = ' ';
				board[0][2] = '#';
				board[0][8] = '#';
				show();
				sum_die += die[0] * 4;
				counter_move++;
				const int size = 4;
				int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
				file_computer(arrstatic);
				return 0;
			}
			else if ((die[0] == die[1]) && (die[0] == 4)) {
				if (board[0][3] != '0') {
					board[14][11] = ' ';
					board[13][11] = ' ';
					board[0][3] = '#';
					board[1][3] = '#';
					show();
					sum_die += die[0] * 2;
					counter_move++;
					const int size = 4;
					int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
					file_computer(arrstatic);
					return 0;
				}
				else {
					board[14][11] = ' ';
					board[0][7] = '#';
					show();
					sum_die += die[0] * 4;
					counter_move++;
					const int size = 4;
					int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
					file_computer(arrstatic);
					return 0;
				}
			}
			else if ((die[0] == die[1]) && (die[0] == 5)) {
				board[14][11] = ' ';
				board[0][1] = '#';
				sum_die += die[0] + die[1];
				if (board[17][3] == ' ') {
					board[0][1] = ' ';
					board[17][3] = '#';
					sum_die += die[0];
					if (board[17][8] == ' ') {
						board[17][3] = ' ';
						board[17][8] = '#';
						sum_die += die[0];
					}
				}
				show();
				counter_move++;
				const int size = 4;
				int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
				file_computer(arrstatic);
				return 0;
			}
			else if ((die[0] == die[1]) && (die[0] == 6)) {
				board[14][11] = ' ';
				board[13][11] = ' ';
				board[0][5] = '#';
				board[1][5] = '#';
				show();
				sum_die += die[0] + die[1];
				counter_move++;
				const int size = 4;
				int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
				file_computer(arrstatic);
				return 0;
			}
		}
	}// конец первого хода
	counter_move++;
	//логика ходов когда в голове есть фишки
	if (board[0][11] == '#') {
		move_computer_fromhead(die, sum_die);
		move_computer_nextfromhead(die, sum_die);
		show();
		const int size = 4;
		int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
		file_computer(arrstatic);
		return 0;
	}
	//когда в голове нет фишек
	else {
		int victory = move_computer_house(die, sum_die);
		show();
		const int size = 4;
		int arrstatic[size] = { counter_move, copy_d0, copy_d1, sum_die }; //создание массива статистики
		file_computer(arrstatic);
		if (victory == -1) return -1;
		return 0;
	}
}
// функция записи статистики в файл
void file_computer(int* arrstatic) {
	ofstream out("statistics.txt", ios::app);
	string str = "Компьютер|    |     |     |";
	int flag = 1; // определяет какая часть строки записывается в str
	for (int i = 0; i < 4; i++) {
		int size = 0, value = arrstatic[i];
		while (value > 0) {
			value /= 10;
			size++;
		}
		char* symstatic = new char[size];
		for (int j = size - 1; j >= 0; j--) {
			int number = arrstatic[i] % 10;
			switch (number)
			{
			case 0:
				symstatic[j] = 48;
				break;
			case 1:
				symstatic[j] = 49;
				break;
			case 2:
				symstatic[j] = 50;
				break;
			case 3:
				symstatic[j] = 51;
				break;
			case 4:
				symstatic[j] = 52;
				break;
			case 5:
				symstatic[j] = 53;
				break;
			case 6:
				symstatic[j] = 54;
				break;
			case 7:
				symstatic[j] = 55;
				break;
			case 8:
				symstatic[j] = 56;
				break;
			case 9:
				symstatic[j] = 57;
				break;
			}
			arrstatic[i] /= 10;
		}
		if (flag == 1) {
			int k = 11;
			for (int j = 0; j < size; j++) {
				str[k] = symstatic[j];
				k++;
			}
			str[k] = '.';
		}
		if (flag == 2) {
			int k = 16;
			for (int j = 0; j < size; j++) {
				str[k] = symstatic[j];
				k++;
			}
			str[k] = ':';
		}
		if (flag == 3) {
			int k = 18;
			for (int j = 0; j < size; j++) {
				str[k] = symstatic[j];
				k++;
			}
		}
		if (flag == 4) {
			int k = 22;
			for (int j = 0; j < size; j++) {
				str[k] = symstatic[j];
				k++;
			}
		}
		flag++;
		delete[] symstatic;
	}
	if (out.is_open()) {
		out << str << endl;
		out.close();
	}
	else cout << "Error openfile." << endl;
}
