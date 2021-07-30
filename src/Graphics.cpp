#include "Graphics.h"
Graphics::Graphics()
:
    mesh(Vector2f(320.f,320.f)),
    passBut(Vector2f(60.f,30.f)),
    continueBut(Vector2f(80.f,30.f)),
    NGBut(Vector2f(80.f,30.f)),
    toMenuBut(Vector2f(60.f,30.f)),
    exitBut(Vector2f(60.f,30.f)),
    howToPlayBut(Vector2f(100.f,30.f)),
    autorsBut(Vector2f(60.f,30.f))
{

    mesh.move(40.f,40.f);
	mesh.setFillColor(Color(224,207,177));

    if (!font.loadFromFile("arial.ttf")){   //Добавление текстовых полей
       std::cout<<"Font error"<<std::endl;
    }else{
        std::string names[] = {"turnText","blackscoreText","whitescoreText","passText","continueText","NGText","toMenuText","exitText","howToPlayText","autorsText","autorsText1",
        "howToPlayText1","howToPlayText2","howToPlayText3","howToPlayTextHead","autorsTextHead"}
        ,texts[] = {"Black","0","5.5","Pass","Continue","New game","Menu","Exit","How to play","Autor","The autor is Vladislav Ivelov.\nStudies at the Kherson National Technical University."};
        for(int i=0;i<11;i++)
            text[names[i]]= Text(texts[i],font,15);

        text["howToPlayText1"]=     Text("The goal of the game is to earn more points than the opponent.\nPoints are awarded for living stones, kills, and the enclosed territory.\n",font,10);
        text["howToPlayText2"]=     Text("To place a stone, press the left mouse button on the place where you\n want to place it.",font,10);
        text["howToPlayText3"]=     Text("The game ends when both players fold.\n After that, you can select the captive stones with the left mouse button.",font,10);
        text["howToPlayTextHead"]=  Text("How to play",font,20);
        text["autorsTextHead"]=     Text("Autor",font,20);

        short int moveCords[][16]={{190,50,300,182,222,115,30,187,162,182,20,20,20,20,155,175},{0,0,0,405,255,255,405,405,305,355,100,100,124,148,50,50}};
        for(int i=0;i<16;i++)
            text[names[i]].move(moveCords[0][i],moveCords[1][i]);

        for(std::map<std::string,Text>::iterator i=text.begin(); i!=text.end(); i++)
            i->second.setFillColor(Color::Black);
        }

    cirB = new CircleShape*[numOfM];
    cirW = new CircleShape*[numOfM];
    cirTB = new CircleShape*[numOfM];
    cirTW = new CircleShape*[numOfM];
    recW = new RectangleShape*[numOfM];
    recB = new RectangleShape*[numOfM];

    for(int i=0;i<numOfM;i++){
    cirB[i] = new CircleShape[numOfM];
    cirW[i] = new CircleShape[numOfM];
    cirTB[i] = new CircleShape[numOfM];
    cirTW[i] = new CircleShape[numOfM];
    recW[i] = new RectangleShape[numOfM];
    recB[i] = new RectangleShape[numOfM];
    }
     for(int i=0;i<numOfM;i++)  //Инициализация камней
    {
        for(int j=0;j<numOfM;j++)
        {
            cirW[i][j]= CircleShape(16.f);
            cirW[i][j].setFillColor(Color::White);
            cirW[i][j].setOutlineThickness(1.f);
            cirW[i][j].setOutlineColor(Color::Black);
            cirB[i][j]=CircleShape(17.f);
            cirB[i][j].setFillColor(Color::Black);
            cirTW[i][j]=CircleShape(16.f);
            cirTW[i][j].setFillColor(Color(250,250,250,100));
            cirTW[i][j].setOutlineThickness(1.f);
            cirTW[i][j].setOutlineColor(Color::Black);
            cirTB[i][j]=CircleShape(17.f);
            cirTB[i][j].setFillColor(Color(0,0,0,100));
            recW[i][j]=RectangleShape(Vector2f(9.f,9.f));
            recW[i][j].setFillColor(Color::White);
            recW[i][j].setOutlineThickness(1.f);
            recW[i][j].setOutlineColor(Color::Black);
            recB[i][j]=RectangleShape(Vector2f(9.f,9.f));
            recB[i][j].setOutlineThickness(1.f);
            recB[i][j].setOutlineColor(Color::White);
            recB[i][j].setFillColor(Color::Black);
        }
    }


    lines= new RectangleShape[numOfM];
	rows= new RectangleShape[numOfM];
    for(int i=0;i<numOfM;i++) //создание сетки
    {
        lines[i]= RectangleShape(Vector2f(1.f,(numOfM-1)*40));
        lines[i].move(40*i+40,40);
        lines[i].setFillColor(Color::Black);
        rows[i]= RectangleShape(Vector2f((numOfM-1)*40,1.f));
        rows[i].move(40,40*i+40);
        rows[i].setFillColor(Color::Black);
    };

    for(int i=0;i<numOfM;i++)  //Добавление невидимых камней and клеток подсчёта на поле
    {
        for(int j=0;j<numOfM;j++)
        {
        cirB[i][j].move(25+j*40,25+i*40);
        cirW[i][j].move(25+j*40,25+i*40);
        cirTB[i][j].move(25+j*40,25+i*40);
        cirTW[i][j].move(25+j*40,25+i*40);
        recW[i][j].move(36+j*40,36+i*40);
        recB[i][j].move(36+j*40,36+i*40);
        }
    }

    sf::RectangleShape** buttons = new sf::RectangleShape*[7]{&passBut,&continueBut,&NGBut,&toMenuBut,&exitBut,&howToPlayBut,&autorsBut};
    short int moveCords[][7] = {{170,210,110,20,170,150,170},{400,250,250,400,400,300,350}};
    for(int i=0;i<7;i++)
    {
        buttons[i]->move(moveCords[0][i],moveCords[1][i]);
        buttons[i]->setOutlineThickness(2.f);
        buttons[i]->setOutlineColor(Color::Black);
    }

    texture.loadFromFile("Go.jpg");
    sprite.setTexture(texture);
    sprite.move(115,50);

}

Graphics::~Graphics()
{
    for(int i=0;i<numOfM;i++){
        delete[] cirB[i];
        delete[] cirW[i];
        delete[] cirTB[i];
        delete[] cirTW[i];
        delete[] recW[i];
        delete[] recB[i];
    }
    delete[] cirB;
    delete[] cirW;
    delete[] cirTB;
    delete[] cirTW;
    delete[] recW;
    delete[] recB;
    delete[] lines;
    delete[] rows;
}

void Graphics::drawObjects(RenderWindow& window, const int openMenu, const bool gameOver, std::map<std::string,int[numOfM][numOfM]> mp)    //Рисует все нужные объекты
{
    if(openMenu==1){
    window.draw(sprite);

    window.draw(continueBut);
    window.draw(NGBut);
    window.draw(exitBut);
    window.draw(howToPlayBut);
    window.draw(autorsBut);

    window.draw(text["continueText"]);
    window.draw(text["NGText"]);
    window.draw(text["exitText"]);
    window.draw(text["howToPlayText"]);
    window.draw(text["autorsText"]);

	}else if(openMenu==2){
    window.draw(text["howToPlayText1"]);
    window.draw(text["howToPlayText2"]);
    window.draw(text["howToPlayText3"]);
    window.draw(text["howToPlayTextHead"]);
    window.draw(toMenuBut);
	window.draw(text["toMenuText"]);

	}else if(openMenu==3){
    window.draw(text["autorsTextHead"]);
    window.draw(text["autorsText1"]);
    window.draw(toMenuBut);
	window.draw(text["toMenuText"]);

	}else{
	window.draw(mesh);
    if(!gameOver){
    window.draw(text["blackscoreText"]);
    window.draw(text["whitescoreText"]);
    };
    window.draw(text["turnText"]);
    window.draw(toMenuBut);
    window.draw(text["toMenuText"]);
    for(int i=0;i<numOfM;i++)   //Отображение сетки
    {
    window.draw(lines[i]);
    window.draw(rows[i]);
    };
    window.draw(passBut);
    window.draw(text["passText"]);
	for(int i=0;i<numOfM;i++)   //Отображение видимых камней на поле
    {
        for(int j=0;j<numOfM;j++)
        {
        if(mp["cirTB"][i][j])window.draw(cirTB[i][j]);
        else if(mp["cirTW"][i][j])window.draw(cirTW[i][j]);
        if(mp["cirB"][i][j])window.draw(cirB[i][j]);
        else if(mp["cirW"][i][j])window.draw(cirW[i][j]);
        else if(mp["recW"][i][j])window.draw(recW[i][j]);
        else if(mp["recB"][i][j])window.draw(recB[i][j]);

        };
    };
	};
}

void Graphics::editText(const std::string _text, const std::string textName)
{
    text[textName].setString(_text);
    return;
}

void Graphics::moveText(const float x, const float y, const std::string textName){
    text[textName].move(x,y);
    return;
}

/*
"The goal of the game is to earn more points than the opponent. Points are awarded for living stones, kills, and the enclosed territory."
"To place a stone, press the left mouse button on the place where you want to place it."
"The game ends when both players fold. After that, you can select the captive stones with the left mouse button. "
*/
