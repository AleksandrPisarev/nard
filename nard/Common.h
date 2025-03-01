#pragma once
//функция первичная инициализация
void init() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < colomn - 1; j++) {
			board[i][j] = ' ';
		}
		board[i][11] = '#';
	}
	for (int i = 3; i < rows - 3; i++) {
		board[i][0] = '0';
		for (int j = 1; j < colomn - 1; j++) {
			board[i][j] = ' ';
		}
		board[i][11] = '#';
	}
	for (int i = 15; i < rows; i++) {
		board[i][0] = '0';
		for (int j = 1; j < colomn; j++) {
			board[i][j] = ' ';
		}
	}
}
//функция бросок кубиков
int roll_dice() {
	int number;
	number = rand() % 10;
	if ((number == 0) || (number > 6)) return roll_dice();
	else return number;
}
//функция вывод игральной доски
void show() {
	cout << "|";
	for (int i = 24; i >= 13; i--) {
		cout << i << "|";
	}
	cout << endl;
	for (int i = 0; i < rows; i++) {
		cout << "|";
		for (int j = 0; j < colomn - 1; j++) {
			cout << board[i][j] << "  ";
		}
		cout << board[i][11] << " |" << endl;
	}
	cout << "|";
	for (int i = 1; i < 13; i++) {
		if (i < 10) {
			cout << '0' << i << "|";
		}
		else cout << i << "|";
	}
	cout << endl;
}
//основная функция игры
int play() {
	int victorycomputer, victoryplayer;
	static int counterfirstmove = 0, rightfirstmove;
	if (counterfirstmove == 0) {
		rightfirstmove = right_first_move();
		counterfirstmove++;
	}
	if (rightfirstmove == 1) {
		victoryplayer = move_player();
		if (victoryplayer == -1) {
			return 0;
		}
		victorycomputer = move_computer();
		if (victorycomputer == -1) {
			return 0;
		}
		return play();
	}
	else {
		victorycomputer = move_computer();
		if (victorycomputer == -1) {
			return 0;
		}
		victoryplayer = move_player();
		if (victoryplayer == -1) {
			return 0;
		}
		return play();
	}
}
void made_file() {
	ofstream out("statistics.txt", ios::out);
	if (out.is_open()) {
		out << "__________________________" << endl;
		out << "кто ходит|ход№|кости|сумма|" << endl;
		out << "--------------------------" << endl;
		out.close();
	}
	else cout << "Error openfile." << endl;
}
//функция право первого хода
int right_first_move() {
	int die1, die2, sum_diep, sum_diec;
	die1 = roll_dice();
	die2 = roll_dice();
	sum_diep = die1 + die2;
	cout << "Кто будет ходить первым? " << endl;
	cout << "Кубики игрока выпали " << die1 << " : " << die2 << endl;
	die1 = roll_dice();
	die2 = roll_dice();
	sum_diec = die1 + die2;
	cout << "Кубики компьютера выпали " << die1 << " : " << die2 << endl;
	if (sum_diep > sum_diec) {
		cout << "Первым ходит игрок: " << endl;
		return 1;
	}
	if (sum_diep < sum_diec) {
		cout << "Первым ходит компьютер: " << endl;
		return 0;
	}
	if (sum_diep == sum_diec) {
		cout << "Переброс кубиков: " << endl;
		return right_first_move();
	}
}