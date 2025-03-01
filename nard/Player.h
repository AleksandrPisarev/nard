#pragma once
//функция перевода строк и колонок к номерам матрицы
void find_row_colomn(int& r, int& c) {
	if (c < 13) {
		r = 17;
		c -= 1;
	}
	else {
		r = 0;
		c = 24 - c;
	}
}
//функция перестановки фишек игрока
void swap_chips(int fromc, int inc, int& fromcolomn, int& incolomn) {
	int row;
	if (fromc < 13) {
		row = 16;
		while (board[row][fromcolomn] == '0') {
			row--;
		}
		board[row + 1][fromcolomn] = ' ';
	}
	else {
		row = 1;
		while (board[row][fromcolomn] == '0') {
			row++;
		}
		board[row - 1][fromcolomn] = ' ';
	}
	if (inc < 13) {
		row = 17;
		while (board[row][incolomn] == '0') {
			row--;
		}
		board[row][incolomn] = '0';
	}
	else {
		row = 0;
		while (board[row][incolomn] == '0') {
			row++;
		}
		board[row][incolomn] = '0';
	}
}
//функция выброс фишек из дома
int out_ofthe_houseplayer(int* die, int& sum_die) {
	//проверка возможности выброса из дома
	int fromcolomn, row, victory, indexd = 0;
	for (int d = 1; d < 4; d++) {
		if (die[indexd] < die[d]) {
			indexd = d;
		}
	}
			switch (die[indexd])
			{
			case 1:
				fromcolomn = 0;
				break;
			case 2:
				fromcolomn = 1;
				break;
			case 3:
				fromcolomn = 2;
				break;
			case 4:
				fromcolomn = 3;
				break;
			case 5:
				fromcolomn = 4;
				break;
			case 6:
				fromcolomn = 5;
				break;
			}
			int counterout1 = 0, counterout2 = 0;
			if (board[0][fromcolomn] != '0') {
				for (int i = 5; i > fromcolomn; i--) {
					if (board[0][i] == '0') {
						counterout1++;
						if (board[0][i - die[indexd]] != '#') {
							counterout2++;
						}
					}
				}
				if ((counterout1 != 0) && (counterout2 == 0)) {
					cout << "Хода нет. Пропуск хода" << endl;
					die[indexd] = 0;
					if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
						return 0;
					}
					else {
						return out_ofthe_houseplayer(die, sum_die);
					}
				}
			}
			//конец проверки возможности выброса из дома
			cout << "Ход осуществляется по кости: " << die[indexd] << endl;
			int copyfromcolomn = fromcolomn;
			cout << "Выберите номер позиции из которой нужно сделать ход: ";
			cin >> fromcolomn;
			if ((copyfromcolomn == (24 - fromcolomn)) && (board[0][copyfromcolomn] == '0')) {
				row = 1;
				while (board[row][24 - fromcolomn] == '0') {
					row++;
				}
				board[row - 1][24 - fromcolomn] = ' ';
				sum_die += die[indexd];
				die[indexd] = 0;
				show();
				victory = victory_player();
				if (victory == -1) return -1;
				if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
					return 0;
				}
				else {
					return out_ofthe_houseplayer(die, sum_die);
				}
			}
			else if ((copyfromcolomn < (24 - fromcolomn)) && (board[0][24 - fromcolomn] == '0') && (board[0][24 - fromcolomn - die[indexd] != '#'])) {
				row = 1;
				while (board[row][24 - fromcolomn] == '0') {
					row++;
				}
				board[row - 1][24 - fromcolomn] = ' ';
				row = 0;
				while (board[row][24 - fromcolomn - die[indexd]] == '0') {
					row++;
				}
				board[row][24 - fromcolomn - die[indexd]] = '0';
				sum_die += die[indexd];
				die[indexd] = 0;
				show();
				if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
					return 0;
				}
				else {
					return out_ofthe_houseplayer(die, sum_die);
				}
			}
			else if ((copyfromcolomn > (24 - fromcolomn)) && (board[0][24 - fromcolomn] == '0')) {
				int counterx = 0;
				for (int i = 5; i > (24 - fromcolomn); i--) {
					if (board[0][i] == '0') counterx++;
				}
				if (counterx == 0) {
					row = 1;
					while (board[row][24 - fromcolomn] == '0') {
						row++;
					}
					board[row - 1][24 - fromcolomn] = ' ';
					sum_die += die[indexd];
					die[indexd] = 0;
					show();
					victory = victory_player();
					if (victory == -1) return -1;
					if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
						return 0;
					}
					else {
						return out_ofthe_houseplayer(die, sum_die);
					}
				}
				else if (counterx != 0) {
					cout << "Вы не можете походить с этой позиции. Переходите" << endl;
					return out_ofthe_houseplayer(die, sum_die);
				}
			}
			else {
				cout << "Вы не можете походить с этой позиции. Переходите" << endl;
				return out_ofthe_houseplayer(die, sum_die);
			}
}
//функция проверка правильности хода игрока и перестановка фишек
int check_move(int* die, int& countermovehead, int& sum_die) {
	//проверка фишки в доме или нет
	int couterinhouse = 0;
	for (int i = 0; i < colomn; i++) {
		if (board[17][i] == '0') {
			couterinhouse++;
		}
	}
	for (int i = 6; i < colomn; i++) {
		if (board[0][i] == '0') {
			couterinhouse++;
		}
	}
	if (couterinhouse == 0) {
		int victory = out_ofthe_houseplayer(die, sum_die);
		if (victory == -1) return -1;
		return 0;
	}
	//начало проверки возможности хода
	int fromsize = 0;
	if (countermovehead != 0) {
		for (int i = 0; i < rows; i += 17) {
			for (int j = 0; j < colomn; j++) {
				if (board[i][j] == '0') fromsize++;
			}
		}
	}
	if (countermovehead == 0) {
		for (int j = 1; j < colomn; j++) {
			if (board[17][j] == '0') fromsize++;
		}
		for (int j = 0; j < colomn; j++) {
			if (board[0][j] == '0') fromsize++;
		}
	}
	int* arrfromcolomn = new int[fromsize] {};
	if (countermovehead != 0) {
		for (int i = 0, k = 0; i < rows; i += 17) {
			for (int j = 0; j < colomn; j++) {
				if (board[i][j] == '0') {
					if (i == 0) {
						arrfromcolomn[k] = 24 - j;
						k++;
					}
					if (i == 17) {
						arrfromcolomn[k] = 1 + j;
						k++;
					}
				}
			}
		}
	}
	if (countermovehead == 0) {
		for (int j = 0, k = 0; j < colomn; j++) {
			if (board[0][j] == '0') {
				arrfromcolomn[k] = 24 - j;
				k++;
			}
		}
		for (int j = 1, k = 0; j < colomn; j++) {
			if (board[17][j] == '0') {
				arrfromcolomn[k] = 1 + j;
				k++;
			}
		}
	}
	int counterpossiblemove = 0;
	for (int d = 0; d < 4; d++) {
		if (die[d] != 0) {
			for (int i = 0; i < fromsize; i++) {
				if (((arrfromcolomn[i] + die[d]) < 13) && (board[17][(arrfromcolomn[i] + die[d]) - 1] != '#')) {
					counterpossiblemove++;
				}
				if (((arrfromcolomn[i] + die[d]) > 12) && ((arrfromcolomn[i] + die[d]) < 25) && (board[0][24 - (arrfromcolomn[i] + die[d])] != '#')) {
					counterpossiblemove++;
				}
			}
		}
	}
	if (counterpossiblemove == 0) {
		for (int i = 0; i < 4; i++) {
			if (die[i] != 0) {
				cout << "кость: " << die[i] << endl;
			}
		}
		cout << "Ходов нет. Ход переходит компьютеру" << endl;
		delete[] arrfromcolomn;
		return 0;
	}
	delete[] arrfromcolomn;
	//конец проверки возможности хода
	int fromcolomn, incolomn, row;
	cout << "Выберите номер позиции из которой нужно сделать ход: ";
	cin >> fromcolomn;
	int copyfromcolomn = fromcolomn;
	//проверка хода из головы
	if ((fromcolomn == 1) && (countermovehead == 0)) {
		cout << "Вы не можете больше ходить из голвы. Перевыберите позицию." << endl;
		return check_move(die, countermovehead, sum_die);
	}
	//проверка позиции из которой делаю ход
	find_row_colomn(row, fromcolomn);
	if (board[row][fromcolomn] != '0') {
		cout << "Вы не можете походить с этой позиции. На ней нет ваших фишек. Выберите другую позицию." << endl;
		return check_move(die, countermovehead, sum_die);
	}
	cout << "Выберите номер позиции куда нужно сделать ход: ";
	cin >> incolomn;
	int copyincolomn = incolomn;
	//проверка позиции в которую делаю ход
	find_row_colomn(row, incolomn);
	if (board[row][incolomn] == '#') {
		cout << "Эта позиция занята соперником. Перевыберите позиции." << endl;
		return check_move(die, countermovehead, sum_die);
	}
	if ((copyincolomn - copyfromcolomn) == 0) {
		cout << "Вы выбрали одну и туже позицию. Перевыберите позиции." << endl;
		return check_move(die, countermovehead, sum_die);
	}
	//проверка количества позиций выпавших на кубике и перестановка элементов
	if ((copyincolomn - copyfromcolomn) == die[0]) {
		sum_die += die[0];
		die[0] = 0;
		swap_chips(copyfromcolomn, copyincolomn, fromcolomn, incolomn);
		if (copyfromcolomn == 1) countermovehead--;
		show();
		if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
			return 0;
		}
		else {
			cout << "У вас есть еще ходы" << endl;
			for (int i = 0; i < 4; i++) {
				if (die[i] != 0) {
					cout << "кость: " << die[i] << endl;
				}
			}
			return check_move(die, countermovehead, sum_die);
		}
	}
	else if ((copyincolomn - copyfromcolomn) == die[1]) {
		sum_die += die[1];
		die[1] = 0;
		swap_chips(copyfromcolomn, copyincolomn, fromcolomn, incolomn);
		if (copyfromcolomn == 1) countermovehead--;
		show();
		if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
			return 0;
		}
		else {
			cout << "У вас есть еще ходы" << endl;
			for (int i = 0; i < 4; i++) {
				if (die[i] != 0) {
					cout << "кость: " << die[i] << endl;
				}
			}
			return check_move(die, countermovehead, sum_die);
		}
	}
	else if ((copyincolomn - copyfromcolomn) == die[2]) {
		sum_die += die[2];
		die[2] = 0;
		swap_chips(copyfromcolomn, copyincolomn, fromcolomn, incolomn);
		if (copyfromcolomn == 1) countermovehead--;
		show();
		if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
			return 0;
		}
		else {
			cout << "У вас есть еще ходы" << endl;
			for (int i = 0; i < 4; i++) {
				if (die[i] != 0) {
					cout << "кость: " << die[i] << endl;
				}
			}
			return check_move(die, countermovehead, sum_die);
		}
	}
	else if ((copyincolomn - copyfromcolomn) == die[3]) {
		sum_die += die[3];
		die[3] = 0;
		swap_chips(copyfromcolomn, copyincolomn, fromcolomn, incolomn);
		if (copyfromcolomn == 1) countermovehead--;
		show();
		if ((die[0] == 0) && (die[1] == 0) && (die[2] == 0) && (die[3] == 0)) {
			return 0;
		}
		else {
			cout << "У вас есть еще ходы" << endl;
			for (int i = 0; i < 4; i++) {
				if (die[i] != 0) {
					cout << "кость: " << die[i] << endl;
				}
			}
			return check_move(die, countermovehead, sum_die);
		}
	}
	else {
		cout << "Количество выбранных позиций не совпадает с числами выпавших на костях" << endl;
		cout << "Перевыберите позиции хода" << endl;
		return check_move(die, countermovehead, sum_die);
	}
}
//функция ход игрока
int move_player() {
	static int counter_move = 0; // счетчик ходов игрока
	static int sum_die = 0; // счетчик суммы выпавших костей
	cout << "Ход игрока. Кости выпали." << endl;
	const int sizedie = 4;
	int die[sizedie]{};
	die[0] = roll_dice();
	die[1] = roll_dice();
	if (die[0] == die[1]) {
		die[2] = die[3] = die[0];
		cout << "первая кость: " << die[0] << endl;
		cout << "вторая кость: " << die[1] << endl;
		cout << "третья кость: " << die[2] << endl;
		cout << "четвертая кость: " << die[3] << endl;
	}
	else {
		cout << "первая кость: " << die[0] << endl;
		cout << "вторая кость: " << die[1] << endl;
	}
	int copy_d0 = die[0], copy_d1 = die[1];
	int countermovehead = 1;
	if (counter_move == 0) {
		if (die[0] == die[1]) {
			if ((die[0] == 3) || (die[0] == 4) || (die[0] == 6)) {
				countermovehead = 2;
			}
		}
	}
	counter_move++;
	int victory = check_move(die, countermovehead, sum_die);
	const int size = 4;
	int arrstatic[size] = {counter_move, copy_d0, copy_d1, sum_die}; //создание массива статистики
	file_player(arrstatic); // запись статистики в файл
	if (victory == -1) return -1;
	return 0;
}
//функция проверки на победу игрока
int victory_player() {
	int counterouthouse = 0;
	for (int i = 0; i < rows; i += 17) {
		for (int j = 0; j < colomn; j++) {
			if (board[i][j] == '0') counterouthouse++;
		}
	}
	if (counterouthouse == 0) {
		cout << "Победил игрок!!!" << endl;
		return -1;
	}
	return 0;
}
// функция записи статистики в файл
void file_player(int* arrstatic) {
	ofstream out("statistics.txt", ios::app);
	string str = "  Игрок  |    |     |     |";
	int flag = 1; // определяет какая часть строки записывается в файл
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
