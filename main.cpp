#include "GameClass.h"
//numOfM - size of mesh
#define numOfM 9


int main()
{
    Game game;

    int mouX, mouY, passed=0, openMenu=1; // openMenu: 1-menu, 2-howToPlay, 3-autors, 0-game
    bool gameOver=0;

	RenderWindow window(VideoMode(400, 450), "Go");
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);

    Event event;

	while (window.isOpen())
	{
	window.clear(Color::White);
    game.graphics.drawObjects(window, openMenu, gameOver, game.getObjects());

    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed){
            if(passed!=2)
                game.save();
            window.close();
        }else if(event.type == Event::MouseButtonReleased)
            {
                    mouX= event.mouseButton.x;
                    mouY= event.mouseButton.y;
                    if(openMenu==1)
                    {
                        if(mouX>=168&&mouX<=232&&mouY>=398&&mouY<=432)      //Кнопка выход
                        {
                            window.close();
                        }else if(mouX>=108&&mouX<=192&&mouY>=248&&mouY<=282)    //Кнопка новая игра
                        {
                            game.newGame(passed,gameOver);
                            openMenu=0;
                        }else if(mouX>=208&&mouX<=292&&mouY>=248&&mouY<=282){    //Кнопка продолжить
                            game.continueButClick(passed, gameOver);
                            openMenu=0;
                        }else if(mouX>=168&&mouX<=232&&mouY>=348&&mouY<=382){    //Кнопка autors
                            openMenu=3;
                        }else if(mouX>=148&&mouX<=252&&mouY>=298&&mouY<=332){    //Кнопка how to play
                            openMenu=2;
                        }
                    }else if(mouX>=18&&mouX<=82&&mouY>=398&&mouY<=442){         //Кнопка в меню
                        if(passed!=2&&openMenu==0)
                        game.save();
                        openMenu=1;
                    }else if(!gameOver){
                   if(passed==2)                                //Если 2 паса(конец игры)
                   {
                       int i=(int)((mouY+15)/40)-1 , j=(int)((mouX+15)/40)-1;
                       if(i<numOfM && j<numOfM && i>=0 && j>=0){
                       game.twoPasses(i,j);

                       }else if(mouX>=168&&mouX<=232&&mouY>=398&&mouY<=432){
                        game.endButClick(gameOver);
                       };
                   }else{
                   if(mouX>=168&&mouX<=232&&mouY>=398&&mouY<=432){      //Если кнопка Пас нажата
                    game.passButClick(passed);
                   }else{                                               //Если попытка поставить камень
                   int i=(int)((mouY+15)/40)-1 , j=(int)((mouX+15)/40)-1;
                   if(i<numOfM && j<numOfM && i>=0 && j>=0){
                   game.turn_(passed,i,j);
                   };
               };
               };

            }else if(mouX>=168&&mouX<=232&&mouY>=398&&mouY<=432){ //Если close нажата
                game.newGame(passed,gameOver);
                game.save();
                window.close();};
            };

    };
    window.display();
	};
	return 0;
}

