#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
using namespace sf;

//global variable
int playerHand[5]={0,0,0,0,0};
int BotHand[5]={0,0,0,0,0};
int playerHP=80,botHP=80,pselectcard,botDEF=0,botAtk=0,playerATK=0,playerDEF=0;
Text CurrentPlayerHP,CurrentBotHP,Pdef,Patk,Bdef,Batk;
RenderWindow window(VideoMode(1200, 800), "Project!");


void drawCard();
std::string loadCard(int);
void cardselect(float [],float[]);
void loadText(Font &font);
std::string IntToString(int);

int main()
{
    int keytime = 10;
    Font font;

    //background 
    Texture backgroundImage;
    Sprite bg;
    backgroundImage.loadFromFile("cardImage/bg.jpg");
    bg.setTexture(backgroundImage);
    bg.setScale(1.7f,1.85f);

    //card Sprites
    Texture CurrentPlayerHand[5];
    Sprite playerCard[5];
    Texture CurrentBotHand[5];
    Sprite BotCard[5];
    int winner =0;
    srand(time(NULL));
    window.setFramerateLimit(60);
    float Positionxpcard[5]={},Positionypcard[5]={};
    for (int i = 0; i < 5; i++)
    {
        Positionxpcard[i]=180*i;
    }
    for (int i = 0; i < 5; i++)
    {
        Positionypcard[i]=window.getSize().y-250.f;
    }
    
    while (window.isOpen()&&winner==0)
    {   
        if(keytime<10)keytime++;
        //screen unwider
        Vector2u screen = Vector2u(1200,800);
        if(window.getSize().x>1200||window.getSize().x<1200)window.setSize(screen);
        if(window.getSize().y>800||window.getSize().y<800)window.setSize(screen);

        //event detecting
        Event event;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();

            //turn end simalation
            cardselect(Positionxpcard,Positionypcard);
            if(Keyboard::isKeyPressed(Keyboard::A) && keytime>=10){
                keytime = 0;
                for (int i = 0; i < 5; i++)
                    {
                        Positionxpcard[i]=180*i;
                    }
                for (int i = 0; i < 5; i++)
                    {
                        Positionypcard[i]=window.getSize().y-250.f;
                    }
                playerHand[pselectcard]=0;
                drawCard();
            }

            //status simulation
            if(Keyboard::isKeyPressed(Keyboard::S) && keytime>=10){
                keytime = 0;
                playerHP -=1;
            }
            if(Keyboard::isKeyPressed(Keyboard::D) && keytime>=10){
                keytime = 0;
                botHP -=1;
            }
            if(Keyboard::isKeyPressed(Keyboard::F) && keytime>=10){
                keytime = 0;
                playerATK +=1;
            }
            if(Keyboard::isKeyPressed(Keyboard::G) && keytime>=10){
                keytime = 0;
                botAtk +=1;
            }
        }
        
        
        //Current Hand//
        drawCard();
        for(int i=0;i<5;i++){
            CurrentPlayerHand[i].loadFromFile(loadCard(playerHand[i]));
            playerCard[i].setScale(0.5f,0.5f);
            playerCard[i].setTexture(CurrentPlayerHand[i]);
            playerCard[i].setPosition(Positionxpcard[i],Positionypcard[i]);
        }

        for(int i=0;i<5;i++){
            CurrentBotHand[i].loadFromFile("cardImage/back.png");
            BotCard[i].setScale(0.5f,0.5f);
            BotCard[i].setTexture(CurrentBotHand[i]);
            BotCard[i].setPosition(Vector2f(window.getSize().x-180-(180*i),0));
        }

        //call text
        loadText(font);

              
        //draw background
        window.clear(Color::White);  
        window.draw(bg);

        //show card on screen
        for(int i=0;i<5;i++){
            window.draw(playerCard[i]);
            window.draw(BotCard[i]);
        }

        //show player status
        window.draw(CurrentPlayerHP);//write current Hp.
        window.draw(Patk);//write current atk
        window.draw(Pdef);//write current def

        //show bot status
        window.draw(CurrentBotHP);//write current Hp.
        window.draw(Batk);//write current atk
        window.draw(Bdef);//write current def

        window.display();

    }
    return 0;
}

void drawCard(){
    for(int i=0;i<5;i++)if(playerHand[i]==0)playerHand[i]=rand()%100+1;
    for(int i=0;i<5;i++)if(BotHand[i]==0)BotHand[i]=rand()%100+1;
}

std::string loadCard(int card){
    if(card>=1&&card<=6)return "cardImage/1.png";
	else if(card>=7&&card<=12)return "cardImage/2.png";
	else if(card>=13&&card<=18)return "cardImage/3.png";
	else if(card>=19&&card<=24)return "cardImage/4.png";
	else if(card>=25&&card<=30)return "cardImage/5.png";
	else if(card>=31&&card<=36)return "cardImage/6.png";
	else if(card>=37&&card<=42)return "cardImage/7.png";
	else if(card>=43&&card<=48)return "cardImage/8.png";
	else if(card>=49&&card<=51)return "cardImage/9.png";
	else if(card>=52&&card<=57)return "cardImage/10.png";
	else if(card>=58&&card<=60)return "cardImage/11.png";
	else if(card>=61&&card<=63)return "cardImage/12.png";
	else if(card>=64&&card<=66)return "cardImage/13.png";
	else if(card>=67&&card<=69)return "cardImage/14.png";
	else if(card>=70&&card<=72)return "cardImage/15.png";
	else if(card>=73&&card<=75)return "cardImage/16.png";
	else if(card>=76&&card<=78)return "cardImage/17.png";
	else if(card>=79&&card<=81)return "cardImage/18.png";
	else if(card>=82&&card<=87)return "cardImage/19.png";
	else if(card>=88&&card<=90)return "cardImage/20.png";
	else if(card==91||card==92)return "cardImage/21.png";
	else if(card==93||card==94)return "cardImage/22.png";
	else if(card==95||card==96)return "cardImage/23.png";
	else if(card==97||card==98)return "cardImage/24.png";
	else if(card==99||card==100)return "cardImage/25.png";
    else return(NULL);
}
void cardselect(float Positionxpcard[],float Positionypcard[]){
    if(Mouse::isButtonPressed(Mouse::Left)){
        for (int i = 0; i < 5; i++){
            if(Mouse::getPosition(window).x>=180*i &&Mouse::getPosition(window).x<=180*(i+1) &&Mouse::getPosition(window).y>=550.f){
                Positionxpcard[i]=300;  
                Positionypcard[i]=300;
                pselectcard=i;        
            }
        }
    }
}

void loadText(Font &font){
    std::string hp,atk,def;
    font.loadFromFile("font/Bold.otf");

        //player hp//
    CurrentPlayerHP.setCharacterSize(25);
    CurrentPlayerHP.setFillColor(Color::Black);
    CurrentPlayerHP.setFont(font);
    CurrentPlayerHP.setPosition(1000,600);
    hp = "HP : " + IntToString(playerHP);
    CurrentPlayerHP.setString(hp);

        //player atk//
    Patk.setCharacterSize(25);
    Patk.setFillColor(Color::Black);
    Patk.setFont(font);
    Patk.setPosition(1000,650);
    atk = "ATK : " + IntToString(playerATK);
    Patk.setString(atk);
        
        //player def//
    Pdef.setCharacterSize(25);
    Pdef.setFillColor(Color::Black);
    Pdef.setFont(font);
    Pdef.setPosition(1000,700);
    def = "DEF : " + IntToString(playerDEF);
    Pdef.setString(def);

        //Bot hp//
    CurrentBotHP.setCharacterSize(25);
    CurrentBotHP.setFillColor(Color::Black);
    CurrentBotHP.setFont(font);
    CurrentBotHP.setPosition(80,50);
    hp = "HP : " + IntToString(botHP);
    CurrentBotHP.setString(hp);

        //bot atk//
    Batk.setCharacterSize(25);
    Batk.setFillColor(Color::Black);
    Batk.setFont(font);
    Batk.setPosition(80,100);
    atk = "ATK : " + IntToString(botAtk);
    Batk.setString(atk);

        //bot def//
    Bdef.setCharacterSize(25);
    Bdef.setFillColor(Color::Black);
    Bdef.setFont(font);
    Bdef.setPosition(80,150);
    def = "DEF : " + IntToString(botDEF);
    Bdef.setString(def);

}

std::string IntToString(int x){
    std::string str;
    std::ostringstream temp;  
	temp << x;
	str = temp.str();
    return str;
}
