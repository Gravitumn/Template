#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
using namespace sf;

//global variable
int playerHand[5]={0,0,0,0,0};
int BotHand[5]={0,0,0,0,0};
int playerHP=80,pselectcard,playerATK=0,playerDEF=0,PlayerLevel=0,playerRune=0; //player status
int botHP=80,bselectcard,botDEF=0,botAtk=0,BotRune,BotLevel=0; // bot status
int PlayerMaxRune;
int BotMaxRune;
int keytime = 10;
bool PlayerStun,PlayerPoison,PlayerBurn,PlayerIllu,PlayerCA,selected=false,PlayerUndying,botshow=false,PlayerCounter;
bool BotStun,BotPoison,BotBurn,BotIllu,BotCA,BotUndying,BotCounter;
int Ppoisoncount,Pburncount,Pillucount,Pundycount;
int Bpoisoncount,Bburncount,Billucount,Bundycount;
Text CurrentPlayerHP,CurrentBotHP,Pdef,Patk,Bdef,Batk,Prune,Brune;
float Positionxpcard[5]={},Positionypcard[5]={};
float Positionxbcard[5]={},Positionybcard[5]={};
Texture CurrentPlayerHand[5];
Texture CurrentBotHand[5];
RenderWindow window(VideoMode(1200, 800), "Project!");

void drawCard();
std::string loadCard(int);
void pcardselect(float [],float[]);
void bcardselect(float [],float[]);
void loadText(Font &font);
std::string IntToString(int);
void cardUse(bool isplayer);
void effectphase(bool playerturn);
void damageCalculate(int,bool);
void LevelUp();
void endphase();
void debuffUse();
void turnCount();

int main()
{
    Font font;
    bool playerturn = true;
    //background 
    Texture backgroundImage;
    Sprite bg;
    backgroundImage.loadFromFile("cardImage/bg.jpg");
    bg.setTexture(backgroundImage);
    bg.setScale(1.7f,1.85f);

    //card Sprites
    Sprite playerCard[5];
    Sprite BotCard[5];
    int winner =0;
    srand(time(NULL));
    window.setFramerateLimit(60);
    for (int i = 0; i < 5; i++)
    {
        Positionxpcard[i]=180*i;
        Positionypcard[i]=window.getSize().y-250.f;
        Positionxbcard[i]=window.getSize().x-180-(180*i);
        Positionybcard[i]=0;
    }
    
    while (window.isOpen()&&winner==0)
    {   
        PlayerMaxRune = 80+(PlayerLevel*20);
        BotMaxRune = 80+(BotLevel*20);
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
        

            //turn end simulation
            pcardselect(Positionxpcard,Positionypcard);
            if(Keyboard::isKeyPressed(Keyboard::A) && keytime>=10 && selected==true){
                keytime = 0;
                if(botshow==true){
                    for (int i = 0; i < 5; i++)
                        {
                            Positionxpcard[i]=180*i;
                            Positionypcard[i]=window.getSize().y-250.f;
                            Positionxbcard[i]=window.getSize().x-180-(180*i);
                            Positionybcard[i]=0;
                            botshow=false;
                            effectphase(playerturn);
                            endphase();
                            playerHand[pselectcard]=0;
                            BotHand[bselectcard]=0;
                        }
                }
                else{
                    botshow=true;
                }
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
            if(Keyboard::isKeyPressed(Keyboard::Q) && keytime>=10){
                keytime = 0;
                PlayerStun = true;
            }
            if(Keyboard::isKeyPressed(Keyboard::W) && keytime>=10){
                keytime = 0;
                playerRune+=10;
            }
            if(Keyboard::isKeyPressed(Keyboard::E) && keytime>=10){
                keytime = 0;
                playerDEF+=5;
            }
            if(Keyboard::isKeyPressed(Keyboard::R) && keytime>=10){
                keytime = 0;
                BotUndying = true;
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
            if(Positionybcard[i]>=200.f && botshow == true){
                CurrentBotHand[i].loadFromFile(loadCard(BotHand[i]));
            }
            else{
                CurrentBotHand[i].loadFromFile("cardImage/back.png");
            }
            BotCard[i].setScale(0.5f,0.5f);
            BotCard[i].setTexture(CurrentBotHand[i]);
            BotCard[i].setPosition(Positionxbcard[i],Positionybcard[i]);
        }
        
        //call text
        loadText(font);

        //Rune Check
        LevelUp();    
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
        window.draw(Prune);//write current rune

        //show bot status
        window.draw(CurrentBotHP);//write current Hp.
        window.draw(Batk);//write current atk
        window.draw(Bdef);//write current def
        window.draw(Brune);//write current rune

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
void pcardselect(float Positionxpcard[],float Positionypcard[]){
    if(Mouse::isButtonPressed(Mouse::Left) && keytime >=10 ){
        keytime = 0;
        for (int i = 0; i < 5; i++){
            if(Mouse::getPosition(window).x>=180*i &&Mouse::getPosition(window).x<=180*(i+1) &&Mouse::getPosition(window).y>=550.f){
                if(selected == false){
                    selected =true;
                    Positionxpcard[i]=300;  
                    Positionypcard[i]=300;
                    pselectcard=i;
                    bcardselect(Positionxbcard,Positionybcard);                    
                }
                else{
                    Positionxpcard[i]=300;
                    Positionypcard[i]=300;
                    Positionxpcard[pselectcard]=180*pselectcard;
                    Positionypcard[pselectcard]=550.f;
                    pselectcard=i;
                } 
            }
        }
    }
}

void bcardselect(float Positionxbcard[],float Positionybcard[]){
    int i;
    i=rand()%5;
                Positionxbcard[i]=600;  
                Positionybcard[i]=300;
                bselectcard=i;
}       


void loadText(Font &font){
    std::string hp,atk,def,rune;
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

        //player rune//
    Prune.setCharacterSize(25);
    Prune.setFillColor(Color::Black);
    Prune.setFont(font);
    Prune.setPosition(1000,750);
    rune = "Rune : " + IntToString(playerRune) + " / " + IntToString(PlayerMaxRune);
    Prune.setString(rune);

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

        //bot rune//
    Brune.setCharacterSize(25);
    Brune.setFillColor(Color::Black);
    Brune.setFont(font);
    Brune.setPosition(80,200);
    rune = "Rune : " + IntToString(BotRune) + " / " + IntToString(BotMaxRune);
    Brune.setString(rune);

}

std::string IntToString(int x){
    std::string str;
    std::ostringstream temp;  
	temp << x;
	str = temp.str();
    return str;
}

void Healing(int heal,bool Isplayer){
    if(Isplayer) playerHP += heal;
    else botHP += heal;
}

void effectphase(bool playerturn){
    if(playerturn == true){
        if(!PlayerStun)cardUse(true);
        if(!BotStun)cardUse(false);
    }
    else{
        if(!BotStun)cardUse(false);
        if(!PlayerStun)cardUse(true);
    }
}

void cardUse(bool Isplayer){
    int card = playerHand[pselectcard];
    if(Isplayer) card = playerHand[pselectcard];
    else card = BotHand[bselectcard];

    if(card >=1 && card <= 6){ //Gomu Gomu no!
        damageCalculate(10,Isplayer);
    }

    else if(card >= 7 && card <= 12){ //Jankenpon!!
        int rps = rand()%3+1;
        if(rps == 1) damageCalculate(15,Isplayer); //rock
        else if(rps == 2){                          //paper
            damageCalculate(3,Isplayer);
            if(Isplayer == true) botAtk -=3;
            else playerATK -=3;
        }
        else{                                       //scissors
            damageCalculate(5,Isplayer);
            if(Isplayer == true) playerATK += 2;
            else botAtk += 2;
        }
    }

    else if(card >=13 && card <= 18) Healing(15,Isplayer); //holy light

    else if(card >=19 && card <= 24){ //illuminate
        if (Isplayer) PlayerIllu==true;
        else BotIllu=true;
    }

    else if(card >=25 && card <=30){ //flamethrower
        damageCalculate(3,Isplayer);
        if(Isplayer) BotBurn==true;
        else PlayerBurn==true;
    }

    else if(card >=31 && card <=36){ //smash!!! 
	    damageCalculate(20,Isplayer);
	    damageCalculate(5,!Isplayer);
    }

    else if(card >=37 && card <=42){ //sword! wait, it's trickster.
        damageCalculate(5,Isplayer);
        if (Isplayer) BotPoison == true;
        else PlayerPoison == true;
    }

    else if(card >=43 && card <=48){  //arc!!!
	    damageCalculate(3,Isplayer);
	    if(Isplayer) BotStun=true;
	    else PlayerStun =true;
    }

    else if(card >=49 && card <=51){  //glacial prison
        if(Isplayer){ 
            BotStun=true;
            botDEF-=5;
        }
	    else{ 
            PlayerStun =true;
            playerDEF -=5;
        }
    } 

    else if(card >=52 && card <=57){  //rune of powar!!!!

        
    } 

    else if(card >= 58 && card <=60){  //abyssal powar!!!!
        if (Isplayer) playerRune+=1;
        else BotRune+=1;
        damageCalculate(15,!Isplayer);
    } 

    else if(card >= 61 && card <= 63){  //demonic powar


    } 

    else if(card >= 64 && card <= 66){  //full counter
        if (Isplayer) PlayerCounter = true;
        else BotCounter = true;
    } 

    else if(card >= 67 && card <= 69){   //rho aias

    }

    else if(card >= 70 && card <= 72){  //lamb's respite

    } 

    else if(card >= 73 && card <= 75){  //colossal assault
        if(Isplayer) PlayerCA == true;
        else BotCA == true;
    }  

    else if(card >= 76 && card <= 78)  //explosive trap

    else if(card >= 79 && card <= 81)  //armor titan

    else if(card >= 82 && card <= 87)  //blood thirster 

    else if(card >= 88 && card <= 90) //Not UBW. *The problem is how we can effectively check it's the bot's card that is used on the field.

    else if(card == 91 || card == 92){  //undying rage
        if (Isplayer) PlayerUndying = true;
        else BotUndying = true;
    }

    else if(card == 93 || card == 94){  //berserker soul
        
    }

    else if(card == 95 || card == 96)  //sigil of power

    else if(card == 97 || card == 98)  //destiny draw

    else if(card == 99 || card == 100)  //chicabu tensei


    selected = false;
}

void damageCalculate(int damage,bool Isplayer){
    int totaldamage;
    if(Isplayer){
        totaldamage = damage+playerATK-botDEF;
        if(PlayerCA)totaldamage*=2;
        if(BotCounter){  //when a counter card is used.
            if(playerDEF >= damage+botAtk) playerDEF -= damage+botAtk;
            else{
                if(PlayerUndying == true && playerHP - totaldamage <= 0) playerHP=1;
                else playerHP = playerHP - totaldamage;
            }
        }
        else if(botDEF >= damage+playerATK) botDEF -= damage+playerATK;
        else{
            if(BotUndying==true && botHP - totaldamage <= 0 ){
                botHP = 1;
            }
            else botHP = botHP - totaldamage;
        } 
    }
    else{
        totaldamage = damage+botAtk-playerDEF;
        if(BotCA)totaldamage*=2;
        if (PlayerCounter){
            if(botDEF >= damage+playerATK) botDEF -= damage+playerATK;
            else{
                if(BotUndying==true && botHP - totaldamage <= 0 ){
                    botHP = 1;
                }
                else botHP = botHP - totaldamage;
            } 
        }
        else if(playerDEF >= damage+botAtk) playerDEF -= damage+botAtk;
        else {
            if(PlayerUndying == true && playerHP - totaldamage <= 0) playerHP=1;
            else playerHP = playerHP - totaldamage;
        }   
    }
}

void LevelUp(){
    if(playerRune == PlayerMaxRune){
        PlayerLevel++;
        playerRune = 0;
    }
    if(BotMaxRune == BotRune){
        BotLevel++;
        BotRune = 0;
    }
}

void endphase(){
    PlayerStun =false;
    BotStun = false;
    PlayerCA =false;
    BotCA = false;
    PlayerCounter = false;
    BotCounter = false;

    debuffUse();
    turnCount();
    
}

void debuffUse(){
    if(PlayerIllu)playerHP+=7;
    if(BotIllu)botHP+=7;

    if(PlayerBurn)playerHP-=3;
    if(BotBurn)botHP-=3;

    if(PlayerPoison)playerHP-=2;
    if(BotPoison)botHP-=2;
    
    
}

void turnCount(){
    if(Ppoisoncount!=0)Ppoisoncount-=1;
    if(Bpoisoncount!=0)Bpoisoncount-=1;
    
    if(Pburncount!=0)Pburncount-=1;
    if(Bburncount!=0)Bburncount-=1;

    if(Pillucount!=0)Pillucount-=1;
    if(Billucount!=0)Billucount-=1;

    if(Pundycount!=0)Pundycount-=1;
    if(Bundycount!=0)Bundycount-=1;

    //checking
    if(Ppoisoncount==0)PlayerPoison=false;
    if(Bpoisoncount==0)BotPoison=false;

    if(Pburncount==0)PlayerBurn=false;
    if(Bburncount==0)BotBurn=false;

    if(Pillucount==0)PlayerIllu=false;
    if(Billucount==0)BotIllu=false;

    if(Pundycount==0)PlayerUndying = false;
    if(Bundycount==0)BotUndying = false;
}
