#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
using namespace sf;

//global variable
int playerHand[5]={0,0,0,0,0};
int BotHand[5]={0,0,0,0,0};
int playerHP=80,botHP=80,pselectcard;
RenderWindow window(VideoMode(1200, 800), "Project!");


void drawCard();
std::string loadCard(int);
void cardselect(float [],float[]);

int main()
{
    Texture backgroundImage;
    Sprite bg;
    backgroundImage.loadFromFile("cardImage/bg.jpg");
    bg.setTexture(backgroundImage);
    bg.setScale(1.7f,1.85f);

    Texture CurrentPlayerHand[5];
    Sprite playerCard[5];
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
        //screen unwider
        Vector2u screen = Vector2u(1200,800);
        if(window.getSize().x>1200||window.getSize().x<1200)window.setSize(screen);
        if(window.getSize().y>800||window.getSize().y<800)window.setSize(screen);
        Event event;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
            cardselect(Positionxpcard,Positionypcard);
            if(Keyboard::isKeyPressed(Keyboard::A)){
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
        }
        
        //show Current Hand//
        drawCard();
        for(int i=0;i<5;i++){
            CurrentPlayerHand[i].loadFromFile(loadCard(playerHand[i]));
            playerCard[i].setScale(0.5f,0.5f);
            playerCard[i].setTexture(CurrentPlayerHand[i]);
            playerCard[i].setPosition(Positionxpcard[i],Positionypcard[i]);
        }
        Texture CurrentBotHand[5];
        Sprite BotCard[5];
        for(int i=0;i<5;i++){
            CurrentBotHand[i].loadFromFile("cardImage/back.png");
            BotCard[i].setScale(0.5f,0.5f);
            BotCard[i].setTexture(CurrentBotHand[i]);
            BotCard[i].setPosition(Vector2f(window.getSize().x-180-(180*i),0));
        }
        if(event.type == Event::KeyPressed){
            if(Keyboard::isKeyPressed(Keyboard::A)){
                playerHand[0] = 0;
            }
        }

        //draw//
        window.clear(Color::White);
        window.draw(bg);
        for(int i=0;i<5;i++){
            window.draw(playerCard[i]);
            window.draw(BotCard[i]);
        }
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
