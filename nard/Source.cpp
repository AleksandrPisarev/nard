#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;
#define rows 18
#define colomn 12
char board[rows][colomn];
void made_file();                           //создание файла статистики игры
void init();                                //функция первичная инициализация игровой доски
int roll_dice();                            //функция бросок кубиков
void show();                                //функция вывод игральной доски на экран
void find_row_colomn(int&, int&);           //функция перевода строк и колонок к номерам матрицы
void swap_chips(int, int, int&, int&);      //функция перестановки фишек игрока
void swap_chips(int, int);                  //перегруженная функция перестановки фишек для компьютера
int check_move(int*, int&, int&);           //функция проверка правильности хода игрока и перестановка фишек
int out_ofthe_houseplayer(int*, int&);      //функция выброс фишек из дома игрока
int victory_player();                       //функция проверки на победу игрока
int move_player();                          // основная функция ход игрока
void file_player(int*);                     //запись в файл статисктики игрока
int* move_computer_fromcolomn(int&);        //функция создания массива содержащий номера колонок откуда может сделать ход компьютер
int move_computer_fromhead(int*, int&);     //функция хода компьютера из головы 
int move_computer_nextfromhead(int*, int&); //функция хода компьютера после хода из головы
int move_computer_house(int*, int&);        //функция ход компьютера в дом
int out_ofthe_house(int*, int&);            //выброс фишек компьютера из дома 
int victory_computer();                     //функция проверки на победу компьютера
int move_computer();                        //основная функция ход компьютера
void file_computer(int*);                   //запись в файл статистики компьютера
int play();                                 //основная функция игры
int right_first_move();                     //право первого хода
#include "Common.h"
#include "Player.h"
#include "Computer.h"
int main() 
{
	setlocale(0, "ru");
	SetConsoleCP(1251);
	srand(time(0));
	made_file();
	init();
	show();
	play();
}