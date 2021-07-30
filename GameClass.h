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
static int whitescore, blackscore, kills[2], ruleKo[4];      //kills -кол убийств(0- черные 1-белые)   ruleKo сохраняет значение последней умершей клетки {i,j,black,turn}

std::string bTs, wTs;

bool check(const int i,const int j,const bool black); //Проверка 4 сторон на наличие свободных/союзных клеток

void del(const bool delCheck);  //Удаление умерших клеток или обнуляет значение checked для них

bool checkAll(const int i, const int j, const bool black);  //Проверка всех соседних клеток

void checkForStruc(const int i, const int j,const bool black);   //добавляет значение структуры каждому камню

void calc(const int i, const int j, const bool black, const int strucNum);   //добавляет квадраты подсчёта

void score();   //Подсчёт очков во время выбора пленных

void tempDel(const bool black, const int strucNum);  //удаляет пленные камни

void recovery(const bool black,const int strucNum);  //восстанавливает пленные камни

void delRecs();                  //удаляет все квадраты и обнуляет счет для переподсчёта

void updateScoreText(const bool passed);        //Изменяет текст счёта

void load();  //Загружает игру

public:

void turn_(int& passed, const int i, const int j);  //Обычный ход

void passButClick(int &passed);  //Если кнопка пасс была нажата

void twoPasses(const int i, const int j);   //Логика игры при подсчёте очков и указывании пленных

void newGame(int& passed, bool& gameOver);    //Обнуляет все переменные

void save(); //Сохраняет игру

void continueButClick(int& passed, bool& gameOver); //При нажатии на кнопку продолжить

void endButClick(bool& gameOver); //При нажатии на кнопку енд

std::map<std::string,int[numOfM][numOfM]> getObjects();

};  // /Game

#endif // GAMECLASS_H_INCLUDED
