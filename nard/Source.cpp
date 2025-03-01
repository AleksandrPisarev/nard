#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;
#define rows 18
#define colomn 12
char board[rows][colomn];
void made_file();                           //�������� ����� ���������� ����
void init();                                //������� ��������� ������������� ������� �����
int roll_dice();                            //������� ������ �������
void show();                                //������� ����� ��������� ����� �� �����
void find_row_colomn(int&, int&);           //������� �������� ����� � ������� � ������� �������
void swap_chips(int, int, int&, int&);      //������� ������������ ����� ������
void swap_chips(int, int);                  //������������� ������� ������������ ����� ��� ����������
int check_move(int*, int&, int&);           //������� �������� ������������ ���� ������ � ������������ �����
int out_ofthe_houseplayer(int*, int&);      //������� ������ ����� �� ���� ������
int victory_player();                       //������� �������� �� ������ ������
int move_player();                          // �������� ������� ��� ������
void file_player(int*);                     //������ � ���� ����������� ������
int* move_computer_fromcolomn(int&);        //������� �������� ������� ���������� ������ ������� ������ ����� ������� ��� ���������
int move_computer_fromhead(int*, int&);     //������� ���� ���������� �� ������ 
int move_computer_nextfromhead(int*, int&); //������� ���� ���������� ����� ���� �� ������
int move_computer_house(int*, int&);        //������� ��� ���������� � ���
int out_ofthe_house(int*, int&);            //������ ����� ���������� �� ���� 
int victory_computer();                     //������� �������� �� ������ ����������
int move_computer();                        //�������� ������� ��� ����������
void file_computer(int*);                   //������ � ���� ���������� ����������
int play();                                 //�������� ������� ����
int right_first_move();                     //����� ������� ����
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