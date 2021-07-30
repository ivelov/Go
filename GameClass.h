#ifndef GAMECLASS_H
#define GAMECLASS_H
#include "Objects.h"
#define numOfM 9
class Game{
public:
Graphics graphics;
Game();
~Game();
private:
Circles** cirBlack;
Circles** cirWhite;
CirTransAndScoreRects** cirTran, **rects;

bool turn;
std::map<std::string,int[numOfM][numOfM]> objects;
static int whitescore, blackscore, kills[2], ruleKo[4];      //kills -��� �������(0- ������ 1-�����)   ruleKo ��������� �������� ��������� ������� ������ {i,j,black,turn}

std::string bTs, wTs;

bool check(const int i,const int j,const bool black); //�������� 4 ������ �� ������� ���������/������� ������

void del(const bool delCheck);  //�������� ������� ������ ��� �������� �������� checked ��� ���

bool checkAll(const int i, const int j, const bool black);  //�������� ���� �������� ������

void checkForStruc(const int i, const int j,const bool black);   //��������� �������� ��������� ������� �����

void calc(const int i, const int j, const bool black, const int strucNum);   //��������� �������� ��������

void score();   //������� ����� �� ����� ������ �������

void tempDel(const bool black, const int strucNum);  //������� ������� �����

void recovery(const bool black,const int strucNum);  //��������������� ������� �����

void delRecs();                  //������� ��� �������� � �������� ���� ��� ������������

void updateScoreText(const bool passed);        //�������� ����� �����

void load();  //��������� ����

public:

void turn_(int& passed, const int i, const int j);  //������� ���

void passButClick(int &passed);  //���� ������ ���� ���� ������

void twoPasses(const int i, const int j);   //������ ���� ��� �������� ����� � ���������� �������

void newGame(int& passed, bool& gameOver);    //�������� ��� ����������

void save(); //��������� ����

void continueButClick(int& passed, bool& gameOver); //��� ������� �� ������ ����������

void endButClick(bool& gameOver); //��� ������� �� ������ ���

std::map<std::string,int[numOfM][numOfM]> getObjects();

};  // /Game

#endif // GAMECLASS_H_INCLUDED
