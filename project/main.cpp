#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace sf;
//98,98,98,98,98
//0,0,0,0,0
//global variable
int playerHand[5] = {0,0,0,0,0};
int BotHand[5] = {0,0,0,0,0};
int playerHP = 80, pselectcard, playerATK = 0, playerDEF = 0, playerTempDEF = 0, PlayerLevel = 0, playerRune = 0, PundyATK = 0; //player status
int botHP = 80, bselectcard, botDEF = 0, botTempDEF = 0, botAtk = 0, BotRune, BotLevel = 0, BundyATK = 0;                       // bot status
int PlayerMaxRune;
int BotMaxRune;
int keytime;
int card;
bool botwin = false, playerwin = false, withdraw = false;
bool PlayerStun, PlayerPoison, PlayerBurn, PlayerIllu, PlayerCA, selected = false, PlayerUndying, botshow = false, PrawStun, PTempDEF,pfc,pberserk,pdestiny,pls=0;
bool BotStun, BotPoison, BotBurn, BotIllu, BotCA, BotUndying, End, BrawStun, BTempDEF,bfc,bberserk,bdestiny,bls=0;
int Ppoisoncount, Pburncount, Pillucount, Pundycount, PCAcount, PTempDEFcount;
int Bpoisoncount, Bburncount, Billucount, Bundycount, BCAcount, BTempDEFcount;
Text CurrentPlayerHP, CurrentBotHP, Pdef, Patk, Bdef, Batk, Prune, Brune;
float Positionxpcard[5] = {}, Positionypcard[5] = {};
float Positionxbcard[5] = {}, Positionybcard[5] = {};
Sprite berserkSoul,destiny;
Texture CurrentPlayerHand[5], Pcrystal[6],berserkImage,Prunecryst[5];
Texture CurrentBotHand[5], Bcrystal[6],destinyImage,Brunecryst[5];
RenderWindow window(VideoMode(1200, 800), "Project!");

void drawCard();
std::string loadCard(int);
void pcardselect(float[], float[]);
void bcardselect(float[], float[]);
void loadText(Font &font);
std::string IntToString(int);
void cardUse(bool isplayer);
void effectphase(bool playerturn);
void damageCalculate(int, bool);
void LevelUp();
void endphase();
void debuffUse();
void turnCount();
void wincondition();
void restart();
void destinyselect(bool);
void gameEnd(Font &font);
void loadcrystal();
void loadrune();
bool havecard(int , int);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Font font;
    bool PlayerStart = true;
    //background
    Texture backgroundImage;
    Sprite bg;
    backgroundImage.loadFromFile("cardImage/bg.jpg");
    bg.setTexture(backgroundImage);
    bg.setScale(1.7f, 1.85f);

    //crystal
    Sprite Pcryst[6];
    Sprite Bcryst[6];
    Sprite Plevelcryst[5],Blevelcryst[5];

    //card Sprites
    Sprite playerCard[5];
    Sprite BotCard[5];
    int randCard =0;
    srand(time(NULL));
    window.setFramerateLimit(60);
    for (int i = 0; i < 5; i++)
    {
        Positionxpcard[i] = 180 * i;
        Positionypcard[i] = window.getSize().y - 250.f;
        Positionxbcard[i] = window.getSize().x - 180 - (180 * i);
        Positionybcard[i] = 0;
    }

    while (window.isOpen())
    {
        PlayerMaxRune = 40 + (PlayerLevel * 20);
        BotMaxRune = 40 + (BotLevel * 20);
        if (keytime < 3)
            keytime++;
        //screen unwider
        Vector2u screen = Vector2u(1200, 800);
        if (window.getSize().x > 1200 || window.getSize().x < 1200)
            window.setSize(screen);
        if (window.getSize().y > 800 || window.getSize().y < 800)
            window.setSize(screen);

        //event detecting
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (botwin == false && playerwin == false && withdraw == false)
            {

                //turn end simulation
                pcardselect(Positionxpcard, Positionypcard);

                //////////show berserker card///////////////
                if(pberserk == true || bberserk == true){  
                        if(randCard==0)randCard= rand()%100+1;
                        berserkImage.loadFromFile(loadCard(randCard));
                        berserkSoul.setScale(0.5f,0.5f);
                        berserkSoul.setTexture(berserkImage);
                        berserkSoul.setPosition(450,300);
                }
                if (Keyboard::isKeyPressed(Keyboard::A) && keytime >= 3 && selected == true)
                {
                    bdestiny = false;
                    keytime = 0;
                    if (botshow == true)
                    {
                        for (int i = 0; i < 5; i++)
                        {   
                            Positionxpcard[i] = 180 * i;
                            Positionypcard[i] = window.getSize().y - 250.f;
                            Positionxbcard[i] = window.getSize().x - 180 - (180 * i);
                            Positionybcard[i] = 0;
                            botshow = false;
                            effectphase(PlayerStart);
                            if(pdestiny!=true)
                            playerHand[pselectcard] = 0;
                            BotHand[bselectcard] = 0;
                            End=true;       
                        }
                    }
                    else
                    {
                        if(playerHand[pselectcard]>=70 && playerHand[pselectcard]<=72 && PlayerStun==1){
                            Positionxpcard[pselectcard]=140;
                            Positionypcard[pselectcard]=300;
                            selected=0;
                            pls=1;
                        }
                        else if(BotHand[bselectcard]>=70 && BotHand[bselectcard]<=72 && BotStun==1){
                            std :: cout << "ok";
                            Positionxbcard[bselectcard]=760;
                            Positionybcard[bselectcard]=300;
                            bls=1;
                            bcardselect(Positionxbcard,Positionybcard);
                            botshow = true;
                        }
                        else{
                        botshow = true;
                        }
                    }

                    //endphase condition
                    if (End)
                        endphase();

                 /*   if (End == true)
                        End = false;
                    else if (End == false)
                        End = true;*/
                }

                //////////////////berserker soul press A
                else if(Keyboard::isKeyPressed(Keyboard::A) && keytime >= 3 && pdestiny!=true){
                    keytime=0;
                    std::cout<<pberserk<<" "<<bberserk<<std::endl;
                    if((randCard >= 1 && randCard <= 12) || (randCard >= 25 && randCard <= 48) || (randCard >= 82 && randCard <= 87) || (randCard >= 95 && randCard <= 96) || (randCard >= 99 && randCard <= 100))
                    {
                        if(pberserk==true){
                            botHP-=15;
                        }
                        else if(bberserk==true){
                            playerHP-=15;
                        }
                        randCard = 0;
                    }
                    else if(bberserk == true || pberserk == true){
                        if(pberserk){
                            pberserk = false;
                            randCard = 0;
                            //break;
                        }
                        else if(bberserk){
                            bberserk = false;
                            randCard = 0;
                            //break;
                        }
                    }
                }
            }
            else if (botwin == true || playerwin == true || withdraw == true)
            {
                if (Keyboard::isKeyPressed(Keyboard::R) && keytime >= 3)
                {
                    restart();
                } 
            }
        }

        if(bdestiny == true)
        {
            BotHand[bselectcard] = rand()%10+91;
            do{
                BotHand[bselectcard] = rand()%10+91;
            }while(BotHand[bselectcard] == 97 || BotHand[bselectcard] == 98);
            std::cout<<BotHand[bselectcard]<<std::endl;
            bdestiny = false;
        }
        
        if(pberserk!=true && bberserk!= true)
            wincondition();
        //colossal titan detect
        if (BTempDEF)
            botTempDEF = 5; //used with collosal titan - Art
        if (PTempDEF)
            playerTempDEF = 5; //used with collosal titan - Art

        //undying detect
        if (PlayerUndying)
            PundyATK = 10;
        if (BotUndying)
            BundyATK = 10;

        //Current Hand//
        if(bdestiny!=true||pdestiny!=true)
            drawCard();
        for (int i = 0; i < 5; i++)
        {
            CurrentPlayerHand[i].loadFromFile(loadCard(playerHand[i]));
            playerCard[i].setScale(0.5f, 0.5f);
            playerCard[i].setTexture(CurrentPlayerHand[i]);
            playerCard[i].setPosition(Positionxpcard[i], Positionypcard[i]);
            if(pdestiny==true)
            playerCard[pselectcard].setColor(Color::Transparent);
            else
            playerCard[pselectcard].setColor(Color::White);
        }
        
        

        for (int i = 0; i < 5; i++)
        {
            if (Positionybcard[i] >= 200.f && botshow == true)
            {
                CurrentBotHand[i].loadFromFile(loadCard(BotHand[i]));
            }
            else
            {
                CurrentBotHand[i].loadFromFile("cardImage/back.png");
               //CurrentBotHand[i].loadFromFile(loadCard(BotHand[i]));
            }
            BotCard[i].setScale(0.5f, 0.5f);
            BotCard[i].setTexture(CurrentBotHand[i]);
            BotCard[i].setPosition(Positionxbcard[i], Positionybcard[i]);
        }

        //call text
        loadText(font);

        //crystal
        loadcrystal();
        for (int i = 0; i < 6; i++)
        {
            Pcryst[i].setTexture(Pcrystal[i]);
            Pcryst[i].setScale(0.05f, 0.05f);
            Pcryst[i].setPosition(950 + (40 * i), 560);

            Bcryst[i].setTexture(Bcrystal[i]);
            Bcryst[i].setScale(0.05f, 0.05f);
            Bcryst[i].setPosition(10 + (40 * i), 10);
        }

        //Rune Check
        LevelUp();
        //Rune show
        loadrune();
        for(int i=0;i<5;i++){
            Plevelcryst[i].setTexture(Prunecryst[i]);
            Plevelcryst[i].setScale(0.1f,0.1f);
            Plevelcryst[i].setPosition(1150,(280+(50*i)));

            Blevelcryst[i].setTexture(Brunecryst[i]);
            Blevelcryst[i].setScale(0.1f,0.1f);
            Blevelcryst[i].setPosition(0,(250+(50*i)));
        }

        //draw background
        window.clear(Color::White);
        window.draw(bg);

        //show card on screen
        for (int i = 0; i < 5; i++)
        {
            window.draw(playerCard[i]);
            window.draw(BotCard[i]);
        }

        //show player status
        window.draw(CurrentPlayerHP); //write current Hp.
        window.draw(Patk);            //write current atk
        window.draw(Pdef);            //write current def
        window.draw(Prune);           //write current rune

        //show bot status
        window.draw(CurrentBotHP); //write current Hp.
        window.draw(Batk);         //write current atk
        window.draw(Bdef);         //write current def
        window.draw(Brune);        //write current rune

        //show crystal
        for (int i = 0; i < 6; i++)
        {
            window.draw(Pcryst[i]);
            window.draw(Bcryst[i]);
        }

        RectangleShape side,lefts;
        side.setSize(Vector2f(50.f,250.f));
        side.setFillColor(Color::White);
        side.setPosition(1150,280);

        lefts.setSize(Vector2f(50.f,250.f));
        lefts.setFillColor(Color::White);
        lefts.setPosition(0,250);
        window.draw(side);
        window.draw(lefts);
        //show rune
        for(int i=0;i<5;i++){
            window.draw(Plevelcryst[i]);
            window.draw(Blevelcryst[i]);
        }


        if(pdestiny)
            window.draw(destiny);

        if((pberserk||bberserk) && pdestiny!=true){
            window.draw(berserkSoul);
        }
        if(playerwin||botwin||withdraw)
            gameEnd(font);

        window.display();
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////



void drawCard()
{
    for (int i = 0; i < 5; i++)
        if (playerHand[i] == 0)
            playerHand[i] = rand() % 100 + 1;
    for (int i = 0; i < 5; i++)
        if (BotHand[i] == 0)
            BotHand[i] = rand() % 100 + 1;
}

std::string loadCard(int card)
{
    if (card >= 1 && card <= 6)
        return "cardImage/1.png";
    else if (card >= 7 && card <= 12)
        return "cardImage/2.png";
    else if (card >= 13 && card <= 18)
        return "cardImage/3.png";
    else if (card >= 19 && card <= 24)
        return "cardImage/4.png";
    else if (card >= 25 && card <= 30)
        return "cardImage/5.png";
    else if (card >= 31 && card <= 36)
        return "cardImage/6.png";
    else if (card >= 37 && card <= 42)
        return "cardImage/7.png";
    else if (card >= 43 && card <= 48)
        return "cardImage/8.png";
    else if (card >= 49 && card <= 51)
        return "cardImage/9.png";
    else if (card >= 52 && card <= 57)
        return "cardImage/10.png";
    else if (card >= 58 && card <= 60)
        return "cardImage/11.png";
    else if (card >= 61 && card <= 63)
        return "cardImage/12.png";
    else if (card >= 64 && card <= 66)
        return "cardImage/13.png";
    else if (card >= 67 && card <= 69)
        return "cardImage/14.png";
    else if (card >= 70 && card <= 72)
        return "cardImage/15.png";
    else if (card >= 73 && card <= 75)
        return "cardImage/16.png";
    else if (card >= 76 && card <= 78)
        return "cardImage/17.png";
    else if (card >= 79 && card <= 81)
        return "cardImage/18.png";
    else if (card >= 82 && card <= 87)
        return "cardImage/19.png";
    else if (card >= 88 && card <= 90)
        return "cardImage/20.png";
    else if (card == 91 || card == 92)
        return "cardImage/21.png";
    else if (card == 93 || card == 94)
        return "cardImage/22.png";
    else if (card == 95 || card == 96)
        return "cardImage/23.png";
    else if (card == 97 || card == 98)
        return "cardImage/24.png";
    else if (card == 99 || card == 100)
        return "cardImage/25.png";
}

void pcardselect(float Positionxpcard[], float Positionypcard[])
{
    if (Mouse::isButtonPressed(Mouse::Left) && keytime >= 3)
    {
        keytime = 0;
        for (int i = 0; i < 5; i++)
        {
            if (Mouse::getPosition(window).x >= 180 * i && Mouse::getPosition(window).x <= 180 * (i + 1) && Mouse::getPosition(window).y >= 550.f)
            {
                if (selected == false && (pberserk == false &&bberserk == false) && pdestiny==false)
                {
                    selected = true;
                    Positionxpcard[i] = 300;
                    Positionypcard[i] = 300;
                    pselectcard = i;
                    if(pls==0)
                    bcardselect(Positionxbcard, Positionybcard);
                      card = playerHand[pselectcard];
                    if(card >= 64 && card <= 66){
                        card = BotHand[bselectcard];
                        if((card >= 1 && card <= 12) || (card >= 25 && card <= 48) || (card >= 82 && card <= 87) || (card >= 95 && card <= 96) || (card >= 99 && card <= 100))
                        {
                            bfc=1;
                        }  
                    } 
                }
                else if (selected == true && botshow == false && (pberserk == false &&bberserk == false) && pdestiny==false)
                {
                    if(card >= 64 && card <= 66)
                    bfc=0;
                    Positionxpcard[i] = 300;
                    Positionypcard[i] = 300;
                    Positionxpcard[pselectcard] = 180 * pselectcard;
                    Positionypcard[pselectcard] = 550.f;
                    pselectcard = i;
                    card = playerHand[pselectcard];
                    if(card >= 64 && card <= 66){
                        card = BotHand[bselectcard];
                        if((card >= 1 && card <= 12) || (card >= 25 && card <= 48) || (card >= 82 && card <= 87) || (card >= 95 && card <= 96) || (card >= 99 && card <= 100))
                        {
                            bfc=1;
                        }  
                    }            
                }
            }
        }
        for(int i=0;i<4;i++)
        {
            if(Mouse::getPosition(window).x>250+(204*i) && Mouse::getPosition(window).x<250+(204*(i+1)) && Mouse::getPosition(window).y>250.f){
                if(pdestiny == true){
                    if(i==0)playerHand[pselectcard]=91;
                    else if(i==1)playerHand[pselectcard]=93;
                    else if(i==2)playerHand[pselectcard]=96;
                    else if(i==3)playerHand[pselectcard]=99;
                    pdestiny = false;
                    std::cout<<"Yes";
                    
                }
            }
        }
    }
}

bool criticalcondition(int i){
    if(playerDEF < 6 && (BotHand[i]>=61 && BotHand[i]<=63)) return true;            //demonic curse

    else if(botHP <= 25+playerATK && BotHand[i]>=49 && BotHand[i]<=51) return true;         //abyssal power

    else if(botHP <= 5+playerATK && playerHP+playerDEF > botAtk+25 && BotHand[i]>=31 && BotHand[i]<=36) return true;    //smash

    else if(playerATK<=1 && BotHand[i]>=7 && BotHand[i]<=12)return true;        //jankenpon
    
    else if(PlayerStun == true && BotHand[i]>=88 && BotHand[i]<=90) return true;        //trace on

    else if(botHP <= 15+playerATK && BotHand[i]>=97 && BotHand[i]<=98) return true;     //destiny draw

    else if(BotHand[i]>=73 && BotHand[i]<=75){
        if(!(havecard(1,6) || havecard(99,100) || havecard(31,36) || havecard(95,96) ||havecard(82,87) || havecard(43,48) || havecard(25,30) || havecard(37,42) || havecard(7,12)))
            return true;                // colossal assault when not have any dmg card.
    }
}

int indexcard(int start , int end){
    for(int i=0;i<5;i++){
        if(BotHand[i]>=start && BotHand[i]<=end)return i;
    }
}


void bcardselect(float Positionxbcard[], float Positionybcard[])
{
    int i=-1;

    if(BotStun && !(BotHand[bselectcard]>=70 && BotHand[bselectcard]<=72)){         // Stun cleansing
        if(havecard(70,72)){
            i = indexcard(70,72);
        }
        std::cout<<"bot in condition of cleansing"<<std::endl;
    }

    if(PlayerCA == true && PlayerStun == false){            /// countering Colossal assault
        if(havecard(64,66)) i = indexcard(64,66);
        else if(havecard(76,78)) i = indexcard(76,78);
        else if(havecard(43,48)) i = indexcard(43,48);      // for when the former cards aren't on the bot's hand - Art
        else if(havecard(49,51)) i = indexcard(49,51);

        std::cout<<"bot countering colossal assault"<<std::endl;
    }

    else if(BotCA == true && BotStun == false){             //using colossal assualt
        if(havecard(99,100)) i = indexcard(99,100);
        else if(havecard(31,36)) i = indexcard(31,36);
        else if(havecard(95,96)) i = indexcard(95,96);
        else if(havecard(1,6)) i = indexcard(1,6);
        else if(havecard(82,87)) i = indexcard(82,87);
        else if(havecard(43,48)) i = indexcard(43,48);
        else if(havecard(25,30)) i = indexcard(25,30);
        else if(havecard(37,42)) i = indexcard(37,42);
        else if(havecard(7,12)) i = indexcard(7,12);

        std::cout<<"bot try to use dmg card for colossal assualt"<<std::endl;
    }

    else if(havecard(93,94)){
        i = indexcard(93,94);
        std::cout<<"bot try to use berserker soul"<<std::endl;
    }          ///////////// Using Berserker soul no matter what!!!



    else if (BotPoison == true && BotBurn == true && botHP <= 40+playerATK){  //debuff cleanse. - Art
        if (havecard(70,72)){
            i = indexcard(70,72);
        }
        std::cout<<"bot try to cleanse poison and burn"<<std::endl;
    }
    
    else if(playerDEF>=6){
        if(havecard(61,63)) i = indexcard(61,63);          ////// demonic curse
    }

    else if((botHP < playerHP)){  
        std::cout<<"bot know that hp less than player"<<std::endl;
        if(botHP <= playerATK+20){                         ///////////// Less Hp condition for undying rage
            if(havecard(91,92)) i =indexcard(91,92);
            else if(havecard(64,66)) i = indexcard(64,66);
            else if(havecard(76,78)) i = indexcard(76,78);

            else{
                if(havecard(82,87)) i = indexcard(82,87);
                else if(havecard(19,24) && Billucount<=1) i = indexcard(19,24);    //changed to BotIlluCount <= 1 - more in commit desc.
                else if(havecard(79,81) && BTempDEFcount<=1) i = indexcard(79,81);     // added armor titan for as a priority between illu and holy light as an alternative hp reservation. - Art
                else if(havecard(13,18)) i = indexcard(13,18);

                else if(havecard(99,100)) i = indexcard(99,100);
                else if(havecard(43,48)) i = indexcard(43,48);
                else if(havecard(49,51)) i = indexcard(49,51);

                else if(playerATK>=5){
                if(havecard(67,69)) i = indexcard(67,69);
                else if(havecard(79,81) && BTempDEFcount <=1) i = indexcard(79,81);
                else if(havecard(76,78)) i = indexcard(76,78);
                else if(havecard(64,66)) i = indexcard(64,66);
                }

            }

            std::cout<<"bot try to use undying rage"<<std::endl;
        }

        else if(havecard(82,87)) i = indexcard(82,87);
        else if(havecard(19,24) && Billucount<=1) i = indexcard(19,24);    //changed to BotIlluCount <= 1 - more in commit desc.
        else if(havecard(79,81) && BTempDEFcount<=1) i = indexcard(79,81);     // added armor titan for as a priority between illu and holy light as an alternative hp reservation. - Art
        else if(havecard(13,18)) i = indexcard(13,18);

        else if(havecard(99,100)) i = indexcard(99,100);
        else if(havecard(43,48)) i = indexcard(43,48);
        else if(havecard(49,51)) i = indexcard(49,51);

        else if(playerATK>=5){
            if(havecard(67,69)) i = indexcard(67,69);
            else if(havecard(79,81) && BTempDEFcount <=1) i = indexcard(79,81);
            else if(havecard(76,78)) i = indexcard(76,78);
            else if(havecard(64,66)) i = indexcard(64,66);
        }

        
    }

    else if(botHP > playerHP){
        std::cout<<"bot know that hp more than player"<<std::endl; 
        if(havecard(95,96)) i = indexcard(95,96);                                       //rune power
        else if(havecard(58,60) && botHP > 25+playerATK) i = indexcard(58,60);
        else if(havecard(52,57)) i = indexcard(52,57);

        else if(havecard(31,36)) i = indexcard(31,36);                                   //dmg card
        else if(havecard(82,87)) i = indexcard(82,87);
        else if(havecard(7,12) && playerATK>0) i = indexcard(7,12);
        else if(havecard(25,30) && Pburncount<=1) i = indexcard(25,30);
        else if(havecard(37,42) && Ppoisoncount<=1) i = indexcard(37,42);
        else if(havecard(1,6)) i = indexcard(1,6);
        else if(havecard(7,12)) i = indexcard(7,12);

        else if(havecard(82,87)) i = indexcard(82,87);                                  //healing
        else if(havecard(19,24) && Billucount<=1) i = indexcard(19,24);        
        else if(havecard(13,18)) i = indexcard(13,18);

         
    }

    
 

    if(i==-1){
        try{
            while(criticalcondition(i)){
                i = rand() % 5;
                if(i = std::numeric_limits<double>::infinity())
                    throw std::domain_error("infinity");
            }
        }
        catch(std::exception& e){
            i = rand()%5;
            std::cout<<"Bot use card randomly"<<std::endl;
        }
    }


    Positionxbcard[i] = 600;
    Positionybcard[i] = 300;
    bselectcard = i;
    card = BotHand[bselectcard];
        if(card >= 64 && card <= 66){
            card = playerHand[pselectcard];
            if((card >= 1 && card <= 12) || (card >= 25 && card <= 48) || (card >= 82 && card <= 87) || (card >= 95 && card <= 96) || (card >= 99 && card <= 100))
            {
                pfc=1;
            }  
        } 
}

bool havecard(int start,int end){
    for(int i=0;i<5;i++){
        if(BotHand[i]>=start && BotHand[i]<=end)return true;
    }
    return false;
}

void loadText(Font &font)
{
    std::string hp, atk, def, rune;
    font.loadFromFile("font/Bold.otf");

    //player hp//
    CurrentPlayerHP.setCharacterSize(25);
    CurrentPlayerHP.setFillColor(Color::Black);
    CurrentPlayerHP.setFont(font);
    CurrentPlayerHP.setPosition(1000, 600);
    hp = "HP : " + IntToString(playerHP);
    CurrentPlayerHP.setString(hp);

    //player atk//
    Patk.setCharacterSize(25);
    Patk.setFillColor(Color::Black);
    Patk.setFont(font);
    Patk.setPosition(1000, 650);
    atk = "ATK : " + IntToString(playerATK + PundyATK);
    Patk.setString(atk);

    //player def//
    Pdef.setCharacterSize(25);
    Pdef.setFillColor(Color::Black);
    Pdef.setFont(font);
    Pdef.setPosition(1000, 700);
    def = "DEF : " + IntToString(playerDEF + playerTempDEF);
    Pdef.setString(def);

    //player rune//
    Prune.setCharacterSize(25);
    Prune.setFillColor(Color::Black);
    Prune.setFont(font);
    Prune.setPosition(1000, 750);
    rune = "Rune : " + IntToString(playerRune) + " / " + IntToString(PlayerMaxRune);
    Prune.setString(rune);

    //Bot hp//
    CurrentBotHP.setCharacterSize(25);
    CurrentBotHP.setFillColor(Color::Black);
    CurrentBotHP.setFont(font);
    CurrentBotHP.setPosition(80, 50);
    hp = "HP : " + IntToString(botHP);
    CurrentBotHP.setString(hp);

    //bot atk//
    Batk.setCharacterSize(25);
    Batk.setFillColor(Color::Black);
    Batk.setFont(font);
    Batk.setPosition(80, 100);
    atk = "ATK : " + IntToString(botAtk + BundyATK);
    Batk.setString(atk);

    //bot def//
    Bdef.setCharacterSize(25);
    Bdef.setFillColor(Color::Black);
    Bdef.setFont(font);
    Bdef.setPosition(80, 150);
    def = "DEF : " + IntToString(botDEF + botTempDEF);
    Bdef.setString(def);

    //bot rune//
    Brune.setCharacterSize(25);
    Brune.setFillColor(Color::Black);
    Brune.setFont(font);
    Brune.setPosition(80, 200);
    rune = "Rune : " + IntToString(BotRune) + " / " + IntToString(BotMaxRune);
    Brune.setString(rune);
}

std::string IntToString(int x)
{
    std::string str;
    std::ostringstream temp;
    temp << x;
    str = temp.str();
    return str;
}

void Healing(int heal, bool Isplayer)
{
    if (Isplayer)
        playerHP += heal;
    else
        botHP += heal;
}

void effectphase(bool PlayerStart)
{   
    //lamb
    if(pls==1 || playerHand[pselectcard] >= 70 && playerHand[pselectcard] <= 72){
        PlayerStun = false;
        Ppoisoncount = 0;
        Pburncount = 0;
        pls=0;
    }
    if(bls==1 || BotHand[bselectcard] >= 70 && BotHand[bselectcard] <= 72){
        BotStun = false;
        Bpoisoncount = 0;
        Bburncount = 0;
        bls=0;
    }
    //explosive trap
    if((!(playerHand[pselectcard] >= 76 && playerHand[pselectcard] <= 78) || PlayerStun) && (!(BotHand[bselectcard] >= 76 && BotHand[bselectcard] <= 78) || BotStun)){
    if(!PlayerStun && !pfc)cardUse(true);
    if(!BotStun && !bfc)cardUse(false);
    }
    selected = false;
}

void cardUse(bool Isplayer)
{

    if (Isplayer)
        card = playerHand[pselectcard];
    else
        card = BotHand[bselectcard];

    if (card >= 1 && card <= 6) //Gomu Gomu no! #1
    {
        damageCalculate(10, Isplayer);
    }

    else if (card >= 7 && card <= 12) //Jankenpon!! #2
    {
        int rps = rand() % 3 + 1;
        if (rps == 1) //rock
            damageCalculate(15, Isplayer);
        else if (rps == 2) //paper
        {
            damageCalculate(2, Isplayer);
            if (Isplayer == true)
                botAtk -= 1;
            else
                playerATK -= 1;
        }
        else
        {
            damageCalculate(2, Isplayer); //scissors
            if (Isplayer == true)
                playerATK += 1;
            else
                botAtk += 1;
        }
    }
    else if (card >= 13 && card <= 18) //holy light #3
        Healing(12, Isplayer);
    else if (card >= 19 && card <= 24) //Illuminate #4
    {
        if (Isplayer)
        {
            PlayerIllu = true;
            Pillucount = 3;
        }
        else
        {
            BotIllu = true;
            Billucount = 3;
        }
    }
    else if (card >= 25 && card <= 30) //flamethrower #5
    {
        damageCalculate(3, Isplayer);
        if (Isplayer)
        {
            BotBurn = true;
            Bburncount = 3;
        }
        else
        {
            PlayerBurn = true;
            Pburncount = 3;
        }
    }
    else if (card >= 31 && card <= 36) //smash!!! #6
    {
        damageCalculate(15, Isplayer);
        damageCalculate(5, !Isplayer);
    }
    else if (card >= 37 && card <= 42) //trickster #7
    {
        damageCalculate(3, Isplayer);
        if (Isplayer)
        {
            BotPoison = true;
            Bpoisoncount = 5;
        }
        else
        {
            PlayerPoison = true;
            Ppoisoncount = 5;
        }
    }
    else if (card >= 43 && card <= 48) //Arc #8
    {
        damageCalculate(3, Isplayer);
        if (Isplayer)
        {
            BrawStun = true;
        }
        else
        {
            PrawStun = true;
        }
    }
    else if (card >= 49 && card <= 51) //gracial prison #9*
    {
        if (Isplayer == true)
        {
            botDEF = botDEF - 5;
            BrawStun = true;
        }
        else
        {
            playerDEF = playerDEF - 5;
            PrawStun = true;
        }
    }
    else if (card >= 52 && card <= 57) //rune power #10
    {
        if (Isplayer)
        {
            playerRune += 20;
        }
        else
        {
            BotRune += 20;
        }
    }
    else if (card >= 58 && card <= 60) //abyssal power #11
    {
        if (Isplayer)
        {
            playerRune += 60;
            playerHP -= 15;
        }
        else
        {
            BotRune += 60;
            botHP -= 15;
        }
    }
    else if (card >= 61 && card <= 63) //demonic course #12*
    {
        if (Isplayer == true)
        {
            if (botDEF - 10 >= 0)
            {
                botDEF = botDEF - 10;
                playerDEF = playerDEF + 10;
            }
            else
            {
                playerDEF += botDEF;
                botDEF = 0;
            }
        }
        else
        {
            if (playerDEF - 10 >= 0)
            {
                playerDEF = playerDEF - 10;
                botDEF = botDEF + 10;
            }
            else
            {
                botDEF += playerDEF;
                playerDEF = 0;
            }
        }
    }
    else if (card >= 64 && card <= 66) //full counter #13
    {
        if (Isplayer && bfc)
        {
           playerHand[pselectcard]=BotHand[bselectcard];
           cardUse(Isplayer);
        }
        else if(!Isplayer && pfc)
        {
            BotHand[bselectcard]=playerHand[pselectcard];
            cardUse(Isplayer);
        }
        
    }
    else if (card >= 67 && card <= 69) //rho aias #14*
    {
        if (Isplayer == true)
        {
            playerDEF = playerDEF + 15;
        }
        else
        {
            botDEF = botDEF + 15;
        }
    }
    else if (card >= 70 && card <= 72) //lamb's respite #15    //not done
    {
        //nope
    }
    else if (card >= 73 && card <= 75) //Colossal Assault #16
    {
        if (Isplayer == true)
        {
            PlayerCA = true;
            PCAcount = 2;
        }
        else
        {
            BotCA = true;
            BCAcount = 2;
        }
    }
    else if (card >= 76 && card <= 78) //explosive trap #17 
    {
        //use in effect phase
    }
    else if (card >= 79 && card <= 81) //armor tiran #18  *WIP. If there is anything to add, please call me. - Art
    {
        if (Isplayer)
        {
            PTempDEF = true;
            PTempDEFcount = 3;
        }
        else
        {
            BTempDEF = true;
            BTempDEFcount = 3;
        }
    }
    else if (card >= 82 && card <= 87) //blood thirster #19
    {
        if (Isplayer)
        {
            int firstbothp = botHP;
            damageCalculate(6, Isplayer);
            int dif = firstbothp - botHP;
            Healing(dif, Isplayer);
        }
        else
        {
            int playerfirsthp = playerHP;
            damageCalculate(6, Isplayer);
            int dif2 = playerfirsthp - playerHP;
            Healing(dif2, Isplayer);
        }
    }
    else if (card >= 88 && card <= 90) //trace on! #20
    {
        if(Isplayer){
            if(BotHand[bselectcard]<88 || BotHand[bselectcard]>90){ //not trace on
                playerHand[pselectcard] = BotHand[bselectcard];
                cardUse(true);
            }
        }
        else{
            if(playerHand[pselectcard]<88 || playerHand[pselectcard]>90){ //not trace on
                BotHand[bselectcard] = playerHand[pselectcard];
                cardUse(false);
            }
        }
    }
    else if (card >= 91 && card <= 92) //undying rage #21
    {
        if (Isplayer)
        {
            PlayerUndying = true;
            Pundycount = 3;
        }
        else
        {
            BotUndying = true;
            Bundycount = 3;
        }
    }
    else if (card >= 93 && card <= 94) //berserker soul #22
    {
        if(Isplayer) pberserk =true;
        else bberserk = true;
    }
    else if (card >= 95 && card <= 96) //sigil of power #23*
    {
        if (Isplayer)
        {
            damageCalculate(10, Isplayer);
            playerRune += PlayerMaxRune;
        }
        else
        {
            damageCalculate(10, Isplayer);
            BotRune += BotMaxRune;
        }
    }
    else if (card >= 97 && card <= 98) //destiny draw #24
    {
        destinyselect(Isplayer);
    }
    else if (card >= 99 && card <= 100) //chibaku tensei #25*
    {
        if (Isplayer)
        {
            damageCalculate(20, Isplayer);
            BrawStun = true;
        }
        else
        {
            damageCalculate(20, Isplayer);
            PrawStun = true;
        }
    }

    
}

void damageCalculate(int damage, bool Isplayer)
{
    int totaldamage;
    if (Isplayer)
    {
        if (PlayerCA)
            damage *= 2;
        totaldamage = damage + playerATK;

        if (totaldamage < 0)
            totaldamage = 0;
        if (botTempDEF >= totaldamage) //used with collosal titan - Art
        {
            botTempDEF -= totaldamage;
            totaldamage = 0;
        }
        else
        {
            totaldamage -= playerTempDEF;
            botTempDEF = 0;
        }
        if (botDEF >= totaldamage)
            botDEF -= totaldamage;
        else
        {
            if (BotUndying == true && botHP - totaldamage <= 0)
            {
                botHP = 1;
            }
            else
                botHP = botHP - totaldamage;
        }
    }

    else
    {
        if (BotCA)
            damage *= 2;
        totaldamage = damage + botAtk;

        if (totaldamage < 0)
            totaldamage = 0;
        if (PTempDEF > totaldamage)
        { //used with collosal titan - Art
            PTempDEF -= totaldamage;
            totaldamage = 0;
        }
        else
        {
            totaldamage -= playerTempDEF;
            playerTempDEF = 0;
        }
        if (playerDEF >= totaldamage)
        {
            playerDEF -= totaldamage;
        }
        else
        {
            if (PlayerUndying == true && playerHP - totaldamage <= 0)
            {
                playerHP = 1;
            }
            else
                playerHP = playerHP - totaldamage;
        }
    }
}
void LevelUp()
{
    if (playerRune >= PlayerMaxRune)
    {
        playerRune = playerRune - PlayerMaxRune;
        PlayerLevel++;
        playerATK += 5;
    }
    if (BotRune >= BotMaxRune)
    {
        BotRune = BotRune - BotMaxRune;
        BotLevel++;
        botAtk += 5;
    }
}

void endphase()
{
    debuffUse();
    wincondition();
    turnCount();
    End=false;
}

void debuffUse()
{
    if (PlayerIllu)
        playerHP += 5;
    if (BotIllu)
        botHP += 5;

    if (PlayerBurn)
        playerHP -= 3;
    if (BotBurn)
        botHP -= 3;

    if (PlayerPoison)
        playerHP -= 2;
    if (BotPoison)
        botHP -= 2;

    if (botDEF < 0)
        botDEF = 0;
    if (playerDEF < 0)
        playerDEF = 0;
}

void turnCount()
{
    if (pfc > 0)
        pfc -= 1;
    if (bfc > 0)
        bfc -= 1;

    if (Ppoisoncount > 0)
        Ppoisoncount -= 1;
    if (Bpoisoncount > 0)
        Bpoisoncount -= 1;

    if (Pburncount > 0)
        Pburncount -= 1;
    if (Bburncount > 0)
        Bburncount -= 1;

    if (Pillucount > 0)
        Pillucount -= 1;
    if (Billucount > 0)
        Billucount -= 1;

    if (Pundycount > 0)
        Pundycount -= 1;
    if (Bundycount > 0)
        Bundycount -= 1;

    if (PCAcount > 0)
        PCAcount -= 1;
    if (BCAcount > 0)
        BCAcount -= 1;

    if (PTempDEFcount > 0)
        PTempDEFcount -= 1;
    if (BTempDEFcount > 0)
        BTempDEFcount -= 1;

    //checking
    if (Ppoisoncount == 0)
        PlayerPoison = false;
    if (Bpoisoncount == 0)
        BotPoison = false;

    if (Pburncount == 0)
        PlayerBurn = false;
    if (Bburncount == 0)
        BotBurn = false;

    if (Pillucount == 0)
        PlayerIllu = false;
    if (Billucount == 0)
        BotIllu = false;

    if (Pundycount == 0)
    {
        PlayerUndying = false;
        PundyATK = 0;
    }
    if (Bundycount == 0)
    {
        BotUndying = false;
        BundyATK = 0;
    }

    if (BCAcount == 0)
        BotCA = false;
    if (PCAcount == 0)
        PlayerCA = false;

    PlayerStun = false;
    BotStun = false;

    if (PrawStun == true)
    {
        PrawStun = false;
        PlayerStun = true;
    }
    if (BrawStun == true)
    {
        BrawStun = false;
        BotStun = true;
    }

    if (PTempDEFcount == 0)
    {
        PTempDEF = false;
        playerTempDEF = 0;
    }
    if (BTempDEFcount == 0)
    {
        BTempDEF = false;
        botTempDEF = 0;
    }
}

void wincondition()
{
    if (playerHP <= 0 && botHP <= 0)
        withdraw = true;
    else if (playerHP <= 0)
        botwin = true;
    else if (botHP <= 0)
        playerwin = true;
}

void restart()
{
    for (int i = 0; i < 5; i++)
        playerHand[i] = 0;
    for (int i = 0; i < 5; i++)
        BotHand[i] = 0;
    playerHP = 80;botHP = 80;
    playerATK = 0;botAtk = 0;
    playerDEF = 0;botDEF = 0;
    playerRune = 0;BotRune = 0;
    BotLevel = 0;PlayerLevel = 0;
    PlayerStun = false;BotStun = false;
    PlayerPoison = false;BotPoison = false;
    PlayerBurn = false;BotBurn = false;
    PlayerIllu = false;BotIllu = false;
    PlayerUndying = false;BotUndying = false;
    PrawStun = false;BrawStun = false;
    Ppoisoncount = 0;Bpoisoncount = 0;
    Pburncount = 0;Bburncount = 0;
    PCAcount = 0;BCAcount = 0;
    Pillucount = 0;Billucount = 0;
    playerwin = false;botwin = false;
    withdraw = false;PTempDEF = false;BTempDEF = false;
    PTempDEFcount = 0;BTempDEFcount = 0;
    PundyATK = 0;BundyATK = 0;
}

void loadcrystal()
{
    //stun
    if (PlayerStun)
        Pcrystal[0].loadFromFile("ui/stun.png");
    else
        Pcrystal[0].loadFromFile("ui/none.png");
    if (BotStun)
        Bcrystal[0].loadFromFile("ui/stun.png");
    else
        Bcrystal[0].loadFromFile("ui/none.png");

    //burn
    if (PlayerBurn)
        Pcrystal[1].loadFromFile("ui/burn.png");
    else
        Pcrystal[1].loadFromFile("ui/none.png");
    if (BotBurn)
        Bcrystal[1].loadFromFile("ui/burn.png");
    else
        Bcrystal[1].loadFromFile("ui/none.png");

    //poison
    if (PlayerPoison)
        Pcrystal[2].loadFromFile("ui/poison.png");
    else
        Pcrystal[2].loadFromFile("ui/none.png");
    if (BotPoison)
        Bcrystal[2].loadFromFile("ui/poison.png");
    else
        Bcrystal[2].loadFromFile("ui/none.png");

    //illuminate
    if (PlayerIllu)
        Pcrystal[3].loadFromFile("ui/Illuminate.png");
    else
        Pcrystal[3].loadFromFile("ui/none.png");
    if (BotIllu)
        Bcrystal[3].loadFromFile("ui/Illuminate.png");
    else
        Bcrystal[3].loadFromFile("ui/none.png");

    //undying
    if (PlayerUndying)
        Pcrystal[4].loadFromFile("ui/undying.png");
    else
        Pcrystal[4].loadFromFile("ui/none.png");
    if (BotUndying)
        Bcrystal[4].loadFromFile("ui/undying.png");
    else
        Bcrystal[4].loadFromFile("ui/none.png");

    //CA
    if (PlayerCA)
        Pcrystal[5].loadFromFile("ui/CA.png");
    else
        Pcrystal[5].loadFromFile("ui/none.png");
    if (BotCA)
        Bcrystal[5].loadFromFile("ui/CA.png");
    else
        Bcrystal[5].loadFromFile("ui/none.png");
}


void gameEnd(Font &font){
    Text ending;
    ending.setFont(font);
    ending.setPosition(500,400);
    ending.setCharacterSize(40);
    ending.setFillColor(Color::Black);
    if(playerwin)
        ending.setString("You win!");
    else if(botwin)
        ending.setString("You lost!");
    else if(withdraw)
        ending.setString("Draw!!!");

    RectangleShape rect;
    rect.setSize(Vector2f(300.f,150.f));
    rect.setFillColor(Color::White);
    rect.setPosition(440,350);
    window.draw(rect);
    window.draw(ending);
}

void destinyselect(bool isplayer){
    if(isplayer){
        destinyImage.loadFromFile("cardImage/destinyselect.png");
        destiny.setTexture(destinyImage);
        destiny.setScale(0.6f,0.6f);
        destiny.setPosition(250,250);
        pdestiny = true;
    }
    else{
        bdestiny = true;
    }
}

void loadrune(){
    for(int i=0;i<5;i++){
        if(PlayerLevel<=5){
            if(i<PlayerLevel)Prunecryst[i].loadFromFile("ui/bluerunestone.png");
            else Prunecryst[i].loadFromFile("ui/greyrunestone.png");
        }
        else{
            int lev = PlayerLevel%5;
            if(i<lev)Prunecryst[i].loadFromFile("ui/bluerunestone.png");
            else Prunecryst[i].loadFromFile("ui/redrunestone.png");
        }
    }

    for(int i=0;i<5;i++){
        if(BotLevel<=5){
            if(i<BotLevel)Brunecryst[i].loadFromFile("ui/bluerunestone.png");
            else Brunecryst[i].loadFromFile("ui/greyrunestone.png");
        }
        else{
            int lev = BotLevel%5;
            if(i<lev)Brunecryst[i].loadFromFile("ui/bluerunestone.png");
            else Brunecryst[i].loadFromFile("ui/redrunestone.png");
        }
    }

    
}