
#include "GameClass.h"
#include <fstream>
#include <iostream>
#define numOfM 9    //Размер сетки



Game::Game(){
    turn=1;
    bTs="Black:"+std::to_string(blackscore);
    wTs="White:"+std::to_string(whitescore)+'.'+'5';

    cirBlack = new Circles*[numOfM];
    cirWhite = new Circles*[numOfM];
    cirTran = new CirTransAndScoreRects*[numOfM];
    rects = new CirTransAndScoreRects*[numOfM];
    for(int i=0;i<numOfM;i++){
        cirBlack[i] = new Circles[numOfM];
        cirWhite[i] = new Circles[numOfM];
        cirTran[i] = new CirTransAndScoreRects[numOfM];
        rects[i] = new CirTransAndScoreRects[numOfM];
    }
    for(int i=0;i<numOfM;i++)
    {
        for(int j=0;j<numOfM;j++)
        {
        objects["cirB"][i][j]=0;
        objects["cirW"][i][j]=0;
        objects["recW"][i][j]=0;
        objects["recB"][i][j]=0;
        objects["cirTB"][i][j]=0;
        objects["cirTW"][i][j]=0;
        }
    }


};
Game::~Game(){
    for(int i=0;i<numOfM;i++){
        delete[] cirBlack[i];
        delete[] cirWhite[i];
        delete[] cirTran[i];
        delete[] rects[i];
    }
    delete[] cirBlack;
    delete[] cirWhite;
    delete[] cirTran;
    delete[] rects;
};

bool Game::check(const int i,const int j,const bool black) //Проверка 4 сторон на наличие свободных/союзных клеток
{
    if(cirBlack[i][j].enabled==0&&cirWhite[i][j].enabled==0)return 0;   //Если проверяется пустая клетка то скип
    cirBlack[i][j].checked=1;

    for(int ij[]={i-1,i+1,i,i,j,j,j-1,j+1},k=0; k<4; k++)
        {
            if(ij[k]>=0 && ij[k]<numOfM && ij[k+4]>=0 && ij[k+4]<numOfM && cirBlack[ij[k]][ij[k+4]].checked==0) //Проверка верхней клетки и тд
            {
                if(cirBlack[ij[k]][ij[k+4]].enabled==0&&cirWhite[ij[k]][ij[k+4]].enabled==0){return 0;}
                else if(cirBlack[ij[k]][ij[k+4]].enabled&&black){
                    if(check(ij[k],ij[k+4],black)==0){return 0;};}
                else if(cirWhite[ij[k]][ij[k+4]].enabled&&black==0){
                    if(check(ij[k],ij[k+4],black)==0){return 0;};};
            }
        }

    return 1;
};

void Game::del(const bool delCheck)  //Удаление умерших клеток или обнуляет значение checked для них
{
  for(int i=0;i<numOfM;i++){
    for(int j=0;j<numOfM;j++){
        if(cirBlack[i][j].checked){
                if(delCheck){
            if(cirBlack[i][j].enabled){
                cirBlack[i][j].enabled=0;
                kills[1]++;
                cirBlack[i][j].checked=0;
                ruleKo[0]=i;
                ruleKo[1]=j;
                ruleKo[2]=1;
                ruleKo[3]=1;
            }else if(cirWhite[i][j].enabled){
                cirWhite[i][j].enabled=0;
                kills[0]++;
                cirBlack[i][j].checked=0;
                ruleKo[0]=i;
                ruleKo[1]=j;
                ruleKo[2]=0;
                ruleKo[3]=1;
            };
                }else{cirBlack[i][j].checked=0;};
        };
    };
  };
};

bool Game::checkAll(const int i, const int j, const bool black)   //Проверка всех соседних клеток
{
    if(i==ruleKo[0]&&j==ruleKo[1]&&black==ruleKo[2]&&ruleKo[3]!=3&&check(i,j,cirBlack[i][j].enabled)){         //KO
        return 1;
    }
    del(0);
    if(ruleKo[3]==1)ruleKo[3]=2;
    else ruleKo[3]=3;
    int deleted=0;

    for(int ij[]={i-1,i+1,i,i,j,j,j-1,j+1},k=0; k<4; k++)
        {
            if(ij[k]>=0 && ij[k]<numOfM && ij[k+4]>=0 && ij[k+4]<numOfM && deleted!=2) //Проверка верхней клетки и тд
            {
                if(cirBlack[ij[k]][ij[k+4]].enabled||cirWhite[ij[k]][ij[k+4]].enabled)    //Если клетка не пустая
                {
                if(check(ij[k],ij[k+4],cirBlack[ij[k]][ij[k+4]].enabled))                //Проверка клетки на смерть
                {
                    if(cirBlack[ij[k]][ij[k+4]].enabled==black || cirWhite[ij[k]][ij[k+4]].enabled!=black){   //Если самоубийство
                        del(0);
                        deleted=2;
                    }else
                    {
                        del(1);
                        deleted=1;
                    }
                }else{del(0);}
                }
            }
        }

    if(!deleted){
    if(check(i,j,cirBlack[i][j].enabled)){          //Проверка на самоубийство
        del(0);
        return 1;
    };
    }else if(deleted==2){return 1;};

    del(0);
    return 0;
};

void Game::checkForStruc(const int i, const int j,const bool black)   //добавляет значение структуры каждому камню
{

    Circles*** cirWB = new Circles**[2];
    cirWB[0]=cirWhite;
    cirWB[1]=cirBlack;
    if(black)
        cirBlack[i][j].struc=cirBlack[i][j].strucCountB;
    else
        cirWhite[i][j].struc=cirWhite[i][j].strucCountW;

    for(int ij[]={i-1,i+1,i,i,j,j,j-1,j+1},k=0; k<4; k++)
        {
            if(ij[k]>=0 && ij[k]<numOfM && ij[k+4]>=0 && ij[k+4]<numOfM) //Проверка верхней клетки и тд
            {
                if(cirWB[black][ij[k]][ij[k+4]].enabled&&cirWB[black][ij[k]][ij[k+4]].struc==0){
                checkForStruc(ij[k],ij[k+4],black);
                }
            }
        }
    delete[] cirWB;
   return;
};

void Game::calc(const int i, const int j, const bool black, const int strucNum){  //добавляет квадраты подсчёта
    if(!cirBlack[i][j].enabled&&!cirWhite[i][j].enabled)
    {
        if(black)
            rects[i][j].enB=1;
        else
            rects[i][j].enW=1;
    };
    if(black)
        cirBlack[i][j].checked=1;
    else
        cirBlack[i][j].checked=1;
    for(int ij[]={i-1,i+1,i,i,j,j,j-1,j+1},k=0; k<4; k++)
        {
            if(ij[k]>=0 && ij[k]<numOfM && ij[k+4]>=0 && ij[k+4]<numOfM) //Проверка верхней клетки и тд
            {
                if(!black)
                {
                    if(!cirBlack[ij[k]][ij[k+4]].enabled&&!cirWhite[ij[k]][ij[k+4]].enabled&&!rects[ij[k]][ij[k+4]].enW){
                        calc(ij[k],ij[k+4],black,strucNum);
                    }else if(strucNum==cirWhite[ij[k]][ij[k+4]].struc&&!cirBlack[ij[k]][ij[k+4]].checked){
                        calc(ij[k],ij[k+4],black,strucNum);
                    }
                }else{
                    if(!cirBlack[ij[k]][ij[k+4]].enabled&&!cirWhite[ij[k]][ij[k+4]].enabled&&!rects[ij[k]][ij[k+4]].enB){
                        calc(ij[k],ij[k+4],black,strucNum);
                    }else if(strucNum==cirBlack[ij[k]][ij[k+4]].struc&&!cirBlack[ij[k]][ij[k+4]].checked){
                        calc(ij[k],ij[k+4],black,strucNum);
                    }
                }
            }
        }
};


void Game::score()
{

for(int i=0,strucNumB=0,strucNumW=0;i<numOfM;i++){              //Подсчёт количества пустых клеток в структуре и заполнение их квадратами
    for(int j=0;j<numOfM;j++)
    {
        if(cirBlack[i][j].enabled&&strucNumB<cirBlack[i][j].struc){
                calc(i,j,1,cirBlack[i][j].struc);
                del(0);
                strucNumB++;
        }else if(cirWhite[i][j].enabled&&strucNumW<cirWhite[i][j].struc){
                calc(i,j,0,cirWhite[i][j].struc);
                del(0);
                strucNumW++;
        };
    };
};
for(int i=0;i<numOfM;i++){                      //Подсчет очков
    for(int j=0;j<numOfM;j++)
    {
        if(cirBlack[i][j].enabled)
            blackscore++;
        else if(cirWhite[i][j].enabled)
            whitescore++;
        else if(cirTran[i][j].enW)
            blackscore++;
        else if(cirTran[i][j].enB)
            whitescore++;
        if(rects[i][j].enB&&rects[i][j].enW){
            rects[i][j].enB=0;
            rects[i][j].enW=0;
        }else if(rects[i][j].enB){
            blackscore++;
        }else if(rects[i][j].enW){
            whitescore++;
        };
    };
};
blackscore=blackscore+kills[0];
whitescore=whitescore+kills[1]+6;
};

void Game::tempDel(const bool black, const int strucNum)  //удаляет пленные камни
{
if(black){
  for(int i=0;i<numOfM;i++){
    for(int j=0;j<numOfM;j++)
    {
        if(cirBlack[i][j].struc==strucNum){
            cirBlack[i][j].enabled=0;
            cirTran[i][j].enB=1;
        };
    };
    };
}else{
    for(int i=0;i<numOfM;i++){
    for(int j=0;j<numOfM;j++)
    {
        if(cirWhite[i][j].struc==strucNum){
            cirWhite[i][j].enabled=0;
            cirTran[i][j].enW=1;
        };
    };
    };
};
};

void Game::recovery(const bool black,const int strucNum)  //восстанавливает пленные камни
{
if(black){
  for(int i=0;i<numOfM;i++){
    for(int j=0;j<numOfM;j++)
    {
        if(cirTran[i][j].enB&&cirBlack[i][j].struc==strucNum){
            cirBlack[i][j].enabled=1;
            cirTran[i][j].enB=0;
        };
    };
    };
}else{
    for(int i=0;i<numOfM;i++){
    for(int j=0;j<numOfM;j++)
    {
        if(cirTran[i][j].enW&&cirWhite[i][j].struc==strucNum){
            cirWhite[i][j].enabled=1;
            cirTran[i][j].enW=0;
        };
    };
    };
};
}

void Game::delRecs()                  //удаляет все квадраты и обнуляет счет для переподсчёта
{
    for(int i=0;i<numOfM;i++){
    for(int j=0;j<numOfM;j++)
    {
        rects[i][j].enB=0;
        rects[i][j].enW=0;
    };
    };
    whitescore=0;
    blackscore=0;
};

void Game::twoPasses(const int i, const int j){


if(cirBlack[i][j].enabled||cirWhite[i][j].enabled){
    if(cirBlack[i][j].enabled){
        tempDel(1,cirBlack[i][j].struc);
        delRecs();
        score();
        updateScoreText(1);
    }else{
        tempDel(0,cirWhite[i][j].struc);
        delRecs();
        score();
        updateScoreText(1);
        };
}else if(cirTran[i][j].enB||cirTran[i][j].enW){
    if(cirBlack[i][j].struc){
        recovery(1,cirBlack[i][j].struc);
        delRecs();
        score();
        updateScoreText(1);
    }else{
        recovery(0,cirWhite[i][j].struc);
        delRecs();
        score();
        updateScoreText(1);
    };
};
};

void Game::passButClick(int &passed){    //Если кнопка пасс была нажата
if(passed==1){
        if(turn){
        turn=0;
        }else{
        turn=1;
        };
        save();
       // whitescore=whitescore-6;
        for(int i=0;i<numOfM;i++){          //Объединение клеток в структуры
            for(int j=0;j<numOfM;j++)
            {
                if(cirBlack[i][j].enabled&&cirBlack[i][j].struc==0){
                    cirBlack[i][j].strucCountB++;
                    checkForStruc(i,j,1);
                }else if(cirWhite[i][j].enabled&&cirWhite[i][j].struc==0){
                    cirWhite[i][j].strucCountW++;
                    checkForStruc(i,j,0);
                };
            };
        };
        score();
        passed=2;
        updateScoreText(1);
        graphics.moveText(-50.f,0.f,"turnText");
        graphics.editText("Select prisoners","turnText");
        graphics.editText("End","passText");
    }else if(passed==0){
    passed=1;
    if(turn){
    graphics.editText("White","turnText");
    turn=0;
    }else{
    graphics.editText("Black","turnText");
    turn=1;
    };
    if(ruleKo[3]==1)ruleKo[3]=2;
        else ruleKo[3]=3;
    };
};

void Game::turn_(int& passed, const int i, const int j){    //Обычный ход
if(!cirWhite[i][j].enabled && !cirBlack[i][j].enabled){   //Если камень уже стоит на этом местe то пропуск
if(turn){
    cirBlack[i][j].enabled=1;
        if(checkAll(i,j,turn)){             //Если самоубийство
            cirBlack[i][j].enabled=0;
        }else{
    graphics.editText("White","turnText");
    turn=0;
    passed=0;
    };
    }else{
    cirWhite[i][j].enabled=1;
    if(checkAll(i,j,turn)){
            cirWhite[i][j].enabled=0;
        }else{
    graphics.editText("Black","turnText");
    turn=1;
    passed=0;
        };
    };
    updateScoreText(0);
}
    };

void Game::updateScoreText(const bool passed)   //Обновляет текст очков
{
    if(passed)
    {
bTs="Black:"+std::to_string(blackscore);
wTs="White:"+std::to_string(whitescore)+".5";
graphics.editText(bTs,"blackscoreText");
graphics.editText(wTs,"whitescoreText");
    }else{
bTs="Black:"+std::to_string(kills[0]);
wTs="White:"+std::to_string(kills[1]+6)+".5";
graphics.editText(bTs,"blackscoreText");
graphics.editText(wTs,"whitescoreText");
    };
};

void Game::save()
{
    std::ofstream fout;
    fout.open("Save.txt");
    if(!fout.is_open())
    {
        std::cout<<"Error opening save file"<<std::endl;
    }else{
            fout<<' ';
        for(int i=0;i<numOfM;i++)
        {
            for(int j=0;j<numOfM;j++)
            {
                if(cirBlack[i][j].enabled)
            fout<< '1' << ' ';
                else if(cirWhite[i][j].enabled)
            fout<< '2' << ' ';
                else
            fout<< '0' << ' ';
            }
            fout<<'\n';
            fout<<' ';
        }
        fout<<'\n';
        fout<<"turn:"<<turn<<'\n';
        fout<<"blackscore:"<<kills[0]<<'\n';
        fout<<"whitescore:"<<kills[1];

    };

    fout.close();
}

void Game::load()
{
    std::ifstream fin;
    fin.open("Save.txt");
    if(!fin.is_open())
    {
     std::cout<<"Failed to load data (FNF)"<<std::endl;
    }else{
        char ch=' ';
    for(int i=0, j=0;i<numOfM;i++){
        while(ch!='\n'){
        fin.get(ch);
        if(ch=='1'){
        cirBlack[i][j].enabled = 1;          //Код символа - код символа '0' = число от 0 до 9
        j++;
        }else if(ch=='2'){
        cirWhite[i][j].enabled = 1;
        j++;
        }else if(ch=='0'){
        j++;
        }
        }
    j=0;
    fin.get(ch);
    }
    while(ch!=':')      //ищем первое : (где turn:)
        fin.get(ch);
    fin.get(ch);
    turn=ch-'0';
    if(turn)
    graphics.editText("Black","turnText");
    else
    graphics.editText("White","turnText");
    while(ch!=':')
        fin.get(ch);
    fin.get(ch);
    kills[0]=ch-'0';
    fin.get(ch);
    if(ch>='0'&&ch<='9'){       //если счёт из 2 чаров
        kills[0]=kills[0]*10 + ch-'0';
    }
    while(ch!=':')
        fin.get(ch);
    fin.get(ch);
    kills[1]=ch-'0';
    fin.get(ch);

    if(ch>='0'&&ch<='9'&&!fin.eof()){
        kills[1]=kills[1]*10 + ch-'0';
    }
    updateScoreText(0);
    fin.close();
}
}

void Game::newGame(int& passed, bool& gameOver)
{
    if(passed==2){
    graphics.editText("Pass","passText");
    graphics.moveText(50.f,0.f,"turnText");
    }
    if(gameOver){
        gameOver=0;
        graphics.moveText(30.f,0.f,"turnText");
    }
    passed=0;
    for(int i=0;i<numOfM;i++)
        {
            for(int j=0;j<numOfM;j++)
            {
            cirBlack[i][j].enabled=0;
            cirBlack[i][j].struc=0;
            cirWhite[i][j].enabled=0;
            cirWhite[i][j].struc=0;
            cirTran[i][j].enB=0;
            cirTran[i][j].enW=0;
            rects[i][j].enB=0;
            rects[i][j].enW=0;
            }
        }
        cirBlack[0][0].strucCountB=0;
        cirBlack[0][0].strucCountW=0;
    blackscore=0, whitescore=0, kills[0]=0, kills[1]=0, turn=1;
    for(int i=0;i<4;i++)
        ruleKo[i]=-1;

    updateScoreText(0);
    graphics.editText("Black","turnText");
}

void Game::continueButClick(int& passed, bool& gameOver)
{
    newGame(passed,gameOver);
    load();
}

void Game::endButClick(bool& gameOver)
{
    gameOver=1;
    graphics.editText("Close","passText");
    graphics.moveText(-30.f,0.f,"turnText");
    float sc=(float)whitescore+0.5f-(float)blackscore;
    if(sc>0){
        std::string scText="White won by "+std::to_string((int)sc)+'.'+std::to_string(((int)(sc*10))%10)+" points";
        graphics.editText(scText,"turnText");
    }else{
        std::string scText="Black won by "+std::to_string((int)sc*(-1))+'.'+std::to_string((int)(sc*(-10))%10)+" points";
        graphics.editText(scText,"turnText");
    };
}

std::map<std::string,int[numOfM][numOfM]> Game::getObjects(){   //Возвращает массив, в котором сказано, какие объекты должны отрисоватся
    for(int i=0;i<numOfM;i++)
    {
        for(int j=0;j<numOfM;j++)
        {
        objects["cirB"][i][j]=cirBlack[i][j].enabled;
        objects["cirW"][i][j]=cirWhite[i][j].enabled;
        objects["recW"][i][j]=rects[i][j].enW;
        objects["recB"][i][j]=rects[i][j].enB;
        objects["cirTB"][i][j]=cirTran[i][j].enB;
        objects["cirTW"][i][j]=cirTran[i][j].enW;
    };
	};
return objects;
};

int Game::whitescore=6, Game::blackscore=0, Game::kills[2]={0,0}, Game::ruleKo[4]={-1,-1,-1,-1};


