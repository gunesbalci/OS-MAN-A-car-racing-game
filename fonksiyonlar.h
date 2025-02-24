#define PI 3.14159265359

/* --- Baslangic Degerleri --- */
void menuDegerler(struct Menu *menu)
{
    menu->x_klavye=200;
    menu->y_klavye=120;
    menu->y_sonucEkrani=330;
    menu->baslaTus=false;
    menu->zorlukTus=false;
    menu->cikisTus=false;
    menu->anaMenuTus=false;
    menu->yerDegistirme=0;
    menu->win=true;
    menu->zor=false;
}

void baslamaEkrani(struct Menu *menu)
{
    menu->x_klavye=200;
    menu->anaMenuTus=false;
    menu->yerDegistirme=0;
}

void bitisEkrani(struct Araba *Player,struct Dusman *Player2,struct Menu *menu)
{
    menu->x_klavye=400;
    menu->baslaTus=false;
    menu->cikisTus=false;
    menu->yerDegistirme=0;

    Player->mX=130;
    Player->mY=480;
    Player->derece=90;

    Player2->mX=60;
    Player2->mY=480;
    Player2->derece=90;
}

void ArabaDegerler(struct Araba *Player)
{
    Player->mX=130;
    Player->mY=480;
    Player->hiz=0;
    Player->vites=0;
    Player->ivme=0.1;
    Player->derece=90;
    Player->TurSayi=0;
    Player->cpoint=false;
    Player->kazaSayi=0;
    Player->kazaSimdi=false;
    Player->kazaOnce=false;
    Player->kazaSimdiDusman=false;
    Player->kazaOnceDusman=false;
    Player->vites1=true;
    Player->vites2=false;
    Player->vites3=false;
}

void ArabaSinirleri(struct Araba *Player)
{
    Player->ustY= Player->mY-(Player->gens/20)*(sin(Player->derece*PI/180));
    Player->ustX= Player->mX-(Player->gens/20)*(cos(Player->derece*PI/180));
    Player->altY= Player->mY+(Player->gens/20)*(sin(Player->derece*PI/180));
    Player->altX= Player->mX+(Player->gens/20)*(cos(Player->derece*PI/180));
    Player->sagX= Player->mX+(Player->yuks/20)*(sin(Player->derece*PI/180));
    Player->sagY= Player->mY-(Player->yuks/20)*(cos(Player->derece*PI/180));
    Player->solX= Player->mX-(Player->yuks/20)*(sin(Player->derece*PI/180));
    Player->solY= Player->mY+(Player->yuks/20)*(cos(Player->derece*PI/180));
}

void Dusmandegerler(struct Dusman *Player2)
{
    Player2->mX=60;
    Player2->mY=480;
    Player2->hiz=5;
    Player2->derece=90;
    Player2->TurSayi=0;
}

void DusmanSinirleri(struct Dusman *Player2)
{
    Player2->ustY= Player2->mY-(Player2->gens/20)*(sin(Player2->derece*PI/180));
    Player2->ustX= Player2->mX-(Player2->gens/20)*(cos(Player2->derece*PI/180));
    Player2->altY= Player2->mY+(Player2->gens/20)*(sin(Player2->derece*PI/180));
    Player2->altX= Player2->mX+(Player2->gens/20)*(cos(Player2->derece*PI/180));
    Player2->sagX= Player2->mX+(Player2->yuks/20)*(sin(Player2->derece*PI/180));
    Player2->sagY= Player2->mY-(Player2->yuks/20)*(cos(Player2->derece*PI/180));
    Player2->solX= Player2->mX-(Player2->yuks/20)*(sin(Player2->derece*PI/180));
    Player2->solY= Player2->mY+(Player2->yuks/20)*(cos(Player2->derece*PI/180));
}
/* --- --------------------------------- --- */

/* --- Menu --- */
void menuSeciliTus(struct Menu *menu,bool durum[3])
{
    if(menu->x_klavye<330&&menu->x_klavye>80&&menu->y_klavye>170&&menu->y_klavye<230&&durum[0])
    {
        menu->baslaTus=true;
        menu->zorlukTus=false;
        menu->cikisTus=false;
    }
    if(menu->x_klavye<330&&menu->x_klavye>80&&menu->y_klavye>250&&menu->y_klavye<310&&durum[0])
    {
        menu->baslaTus=false;
        menu->zorlukTus=true;
        menu->cikisTus=false;
    }
    if(menu->x_klavye<330&&menu->x_klavye>80&&menu->y_klavye>330&&menu->y_klavye<390&&durum[0])
    {
        menu->baslaTus=false;
        menu->zorlukTus=false;
        menu->cikisTus=true;
    }

    if(menu->x_klavye<760&&menu->x_klavye>150&&menu->y_sonucEkrani>300&&menu->y_sonucEkrani<360&&durum[2])
    {
        menu->baslaTus=true;
        menu->anaMenuTus=false;
        menu->cikisTus=false;
    }
    if(menu->x_klavye<760&&menu->x_klavye>150&&menu->y_sonucEkrani>380&&menu->y_sonucEkrani<440&&durum[2])
    {
        menu->baslaTus=false;
        menu->anaMenuTus=true;
        menu->cikisTus=false;
    }
    if(menu->x_klavye<760&&menu->x_klavye>150&&menu->y_sonucEkrani>460&&menu->y_sonucEkrani<520&&durum[2])
    {
        menu->baslaTus=false;
        menu->anaMenuTus=false;
        menu->cikisTus=true;
    }
}

void menuTusDegistirme(struct Menu *menu,bool durum[3])
{
    if(durum[0])
    {
        menu->yerDegistirme=80;
        if(menu->y_klavye>=360)
        {
            menu->yerDegistirme=-160;
        }
    }
    if(durum[2])
    {
        menu->yerDegistirme=80;
        if(menu->y_sonucEkrani>=490)
        {
            menu->yerDegistirme=-160;
        }
    }

}

void zorlukBelirleme(struct Menu *menu)
{
    if(menu->zor)
    {
        menu->zor=false;
    }
    else
    {
        menu->zor=true;
    }
}
/* --- ------------------------------------------- --- */

/* --- Oyuncu ve AI Arabalarin Hareketleri --- */
float sagadon(struct Araba player)
{
    player.derece+=5;
    if(player.derece>360)
        player.derece=0;
    return player.derece;
}

float soladon(struct Araba Player)
{
    Player.derece-=5;
    if(Player.derece<0)
        Player.derece=360;
    return Player.derece;
}

void ilerigit(struct Araba *Player)
{
    Player->mY-=sin(Player->derece*PI/180)*(Player->hiz);
    Player->mX-=cos(Player->derece*PI/180)*(Player->hiz);
    Player->hiz+=Player->ivme;
}

void gerigit(struct Araba *Player)
{
    Player->mY-=sin(Player->derece*PI/180)*(Player->hiz);
    Player->mX-=cos(Player->derece*PI/180)*(Player->hiz);
    Player->hiz-=Player->ivme;
    if(Player->hiz<=-4)
        Player->hiz=-4;
}

void ivmelidur(struct Araba *Player)
{
    if(Player->hiz>0)
    {
        Player->mY-=sin(Player->derece*PI/180)*(Player->hiz);
        Player->mX-=cos(Player->derece*PI/180)*(Player->hiz);
        Player->hiz-=0.6;
        if(Player->hiz<0.6)
            Player->hiz=0;
    }
    if(Player->hiz<0)
    {
        Player->mY-=sin(Player->derece*PI/180)*(Player->hiz);
        Player->mX-=cos(Player->derece*PI/180)*(Player->hiz);
        Player->hiz+=0.6;
        if(Player->hiz>-0.6)
            Player->hiz=0;
    }
}

void yavaslama_pztf(struct Araba *Player)
{
    Player->vites1=true;
    Player->vites2=false;
    Player->vites3=false;
    if(Player->hiz>0.3)
        Player->hiz-=Player->ivme*2;
    if(Player->hiz>4)
        Player->hiz-=Player->hiz*0.5;
}

void yavaslama_ngtf(struct Araba *Player)
{
    Player->vites1=true;
    Player->vites2=false;
    Player->vites3=false;
    if(Player->hiz<-0.3)
        Player->hiz+=Player->ivme*2;
    if(Player->hiz<-0.6)
        Player->hiz+=Player->ivme;
}

void DusmanRota(struct Dusman *Player2,int objeGenisligi, int yukseklik,bool durum[3])
{
    if(durum[1])
    {
        Player2->mY-=sin(Player2->derece*PI/180)*(Player2->hiz);
        Player2->mX-=cos(Player2->derece*PI/180)*(Player2->hiz);
        if(Player2->derece>=360)
        {
        Player2->derece=0;
        }
        if(Player2->mY>120&&Player2->mX>objeGenisligi&&Player2->mX<152&&Player2->mX<=118)
        {
            if(Player2->derece<90)
            {
                Player2->derece+=5;
            }
        }
        else if(Player2->mY<=120&&Player2->mX<800)
        {
            if(Player2->derece<180)
            {
                Player2->derece+=5;
            }
        }
        else if(Player2->mY<596&&Player2->mX>=800)
        {
            if(Player2->derece<270)
            {
                Player2->derece+=5;
            }
        }
        else if(Player2->mY>596&&Player2->mY<yukseklik-objeGenisligi+2&&Player2->mX>60)
        {
            if(Player2->derece<360&&Player2->derece>=270)
            {
                Player2->derece+=5;
            }
        }
    }
}
/* --- ------------------------------------------------------------------- --- */

/* --- Kazalar --- */
void kazaWobje(struct Araba *Player,int genislik,int yukseklik,int objeGenisligi)
{
    if(Player->ustX<objeGenisligi||Player->altX<objeGenisligi||
        Player->ustX>genislik-objeGenisligi||Player->altX>genislik-objeGenisligi||
        Player->ustY<objeGenisligi+8||Player->altY<objeGenisligi+8||
        Player->ustY>yukseklik-objeGenisligi||Player->altY>yukseklik-objeGenisligi)
    {
        Player->hiz=0;
        Player->kazaSimdi=true;
        Player->vites1=true;
        Player->vites2=false;
        Player->vites3=false;
    }
    else
        Player->kazaSimdi=false;
}

void kazaWdusman(struct Araba *Player,struct Dusman *Player2)
{
    bool arkadanKaza=false;
    if(((Player->altY>=Player2->ustY && Player->altX>=Player2->solX && Player->altX<=Player2->sagX && Player->altY<=Player2->altY) ||
       (Player->altY>=Player2->solY && Player->altX>=Player2->altX && Player->altX<=Player2->ustX && Player->altY<=Player2->sagY))||
       ((Player->altY<=Player2->ustY && Player->altX<=Player2->solX && Player->altX>=Player2->sagX && Player->altY>=Player2->altY) ||
       (Player->altY<=Player2->solY && Player->altX<=Player2->altX && Player->altX>=Player2->ustX && Player->altY>=Player2->sagY)))
    {
        arkadanKaza=true;
    }
    if(((Player->ustY>=Player2->ustY && Player->ustX>=Player2->solX && Player->ustX<=Player2->sagX && Player->ustY<=Player2->altY) ||
       (Player->ustY>=Player2->solY && Player->ustX>=Player2->altX && Player->ustX<=Player2->ustX && Player->ustY<=Player2->sagY) ||

       (Player->solY>=Player2->ustY && Player->solX>=Player2->solX && Player->solX<=Player2->sagX && Player->solY<=Player2->altY) ||
       (Player->solY>=Player2->solY && Player->solX>=Player2->altX && Player->solX<=Player2->ustX && Player->solY<=Player2->sagY) ||

       (Player->sagY>=Player2->ustY && Player->sagX>=Player2->solX && Player->sagX<=Player2->sagX && Player->sagY<=Player2->altY) ||
       (Player->sagY>=Player2->solY && Player->sagX>=Player2->altX && Player->sagX<=Player2->ustX && Player->sagY<=Player2->sagY) ||

       (Player->altY>=Player2->ustY && Player->altX>=Player2->solX && Player->altX<=Player2->sagX && Player->altY<=Player2->altY) ||
       (Player->altY>=Player2->solY && Player->altX>=Player2->altX && Player->altX<=Player2->ustX && Player->altY<=Player2->sagY)) ||

      ((Player->ustY<=Player2->ustY && Player->ustX<=Player2->solX && Player->ustX>=Player2->sagX && Player->ustY>=Player2->altY) ||
       (Player->ustY<=Player2->solY && Player->ustX<=Player2->altX && Player->ustX>=Player2->ustX && Player->ustY>=Player2->sagY) ||

       (Player->solY<=Player2->ustY && Player->solX<=Player2->solX && Player->solX>=Player2->sagX && Player->solY>=Player2->altY) ||
       (Player->solY<=Player2->solY && Player->solX<=Player2->altX && Player->solX>=Player2->ustX && Player->solY>=Player2->sagY) ||

       (Player->sagY<=Player2->ustY && Player->sagX<=Player2->solX && Player->sagX>=Player2->sagX && Player->sagY>=Player2->altY) ||
       (Player->sagY<=Player2->solY && Player->sagX<=Player2->altX && Player->sagX>=Player2->ustX && Player->sagY>=Player2->sagY) ||

       (Player->altY<=Player2->ustY && Player->altX<=Player2->solX && Player->altX>=Player2->sagX && Player->altY>=Player2->altY) ||
       (Player->altY<=Player2->solY && Player->altX<=Player2->altX && Player->altX>=Player2->ustX && Player->altY>=Player2->sagY)))
    {
        Player->hiz=0;
        Player2->hiz=0;
        Player->kazaSimdiDusman=true;
        Player->vites1=true;
        Player->vites2=false;
        Player->vites3=false;
        if(arkadanKaza)
        {
            Player2->hiz=5;
        }
    }
    else
    {
        Player2->hiz=5;
        Player->kazaSimdiDusman=false;
    }
}

int KazaSayma(struct Araba *Player)
{
    if(Player->kazaSimdi!=Player->kazaOnce&&Player->kazaSimdi)
    {
        Player->kazaSayi+=1;
    }
    if(Player->kazaSimdi!=Player->kazaOnce)
    {
        Player->kazaOnce=Player->kazaSimdi;
    }
    if(Player->kazaSimdiDusman!=Player->kazaOnceDusman&&Player->kazaSimdiDusman)
    {
        Player->kazaSayi+=1;
    }
    if(Player->kazaSimdiDusman!=Player->kazaOnceDusman)
    {
        Player->kazaOnceDusman=Player->kazaSimdiDusman;
    }
}
/* --- ------------------------------------------------ --- */

/* --- Kontroller --- */
bool tersYonKontrol(struct Araba Player,int genislik,int yukseklik,int objeGenisligi,bool tersYon)
{
        if((((Player.mX>objeGenisligi&&Player.mX<152)||(Player.mY>objeGenisligi&&Player.mY<181)||
            (Player.mX>760&&Player.mX<genislik-objeGenisligi+1)||(Player.mY>546&&Player.mY<yukseklik-objeGenisligi+2))&&Player.hiz<0)||
            (Player.mX>objeGenisligi&&Player.mX<152&&Player.ustY>Player.altY)||(Player.mY>objeGenisligi&&Player.mY<181&&Player.ustX<Player.altX)||
            (Player.mX>760&&Player.mX<genislik-objeGenisligi+1&&Player.ustY<Player.altY)||
            (Player.mY>546&&Player.mY<yukseklik-objeGenisligi+2&&Player.ustX>Player.altX))
        {
            tersYon=true;
        }
        else
            tersYon=false;
        return tersYon;
}

void turKontrol(struct Araba *Player,bool tersyon,int objeGenisligi)
{
    if(Player->mY<500&&Player->mY>=493&&Player->mX>objeGenisligi&&Player->mX<152&&!tersyon&&Player->cpoint)
    {
        Player->TurSayi+=1;
        if(Player->mY<500&&Player->mY>497&&Player->mX>objeGenisligi&&Player->mX<152&&!tersyon&&Player->cpoint&&Player->vites2)
        {
            Player->TurSayi-=1;
        }
        if(Player->mY<500&&Player->mY>497&&Player->mX>objeGenisligi&&Player->mX<152&&!tersyon&&Player->cpoint&&Player->vites1)
        {
            Player->TurSayi-=2;
        }
    }
}

void turKontrolDusman(struct Dusman *Player2)
{
    if(Player2->mY<500&&Player2->mY>=495&&Player2->mX<152)
    {
        Player2->TurSayi+=1;
    }
}

void checkPoint(struct Araba *Player,int yukseklik,int genislik,int objeGenisligi)
{
    if(Player->mY>544&&Player->mY<yukseklik-objeGenisligi&&Player->mX<genislik-objeGenisligi&&Player->mX>755)
    {
        Player->cpoint=true;
    }
    if(Player->mY>440&&Player->mY<490&&Player->mX>objeGenisligi&&Player->mX<152)
    {
        Player->cpoint=false;
    }
}

void vitesDegistir(struct Araba *Player)
{
    if(Player->vites1&&Player->hiz==3)
    {
        Player->vites1=false;
        Player->vites2=true;
        Player->vites3=false;
    }

    if(Player->vites2&&Player->hiz==5)
    {
        Player->vites1=false;
        Player->vites2=false;
        Player->vites3=true;
    }

    if(Player->vites3&&Player->hiz==9)
    {
        Player->vites1=true;
        Player->vites2=false;
        Player->vites3=false;
    }
}

void vitesKontrolu(struct Araba *Player)
{
    if(Player->vites1)
    {
        Player->ivme=0.1;
        if(Player->hiz>=2.9)
        {
            Player->hiz=2.9;
        }
        Player->vites=1;
    }

    if(Player->vites2)
    {
        Player->ivme=0.1;
        if(Player->hiz>=4.9)
        {
            Player->hiz=4.9;
        }
        Player->vites=2;
    }

    if(Player->vites3)
    {
        Player->ivme=0.5;
        if(Player->hiz>=8.5)
        {
            Player->hiz=8.5;
        }
        Player->vites=3;
    }
}

void W_or_L(struct Menu *menu,struct Araba *Player,struct Dusman *Player2,bool durum[3])
{
    if(menu->zor)
    {
        if(Player->TurSayi>Player2->TurSayi&&Player->TurSayi==3&&Player->kazaSayi<1)
        {
            durum[1]=false;
            durum[2]=true;
            menu->win=true;
        }
        if((Player->TurSayi<Player2->TurSayi&&Player2->TurSayi==3)||Player->kazaSayi>=1)
        {
            durum[1]=false;
            durum[2]=true;
            menu->win=false;
        }
    }
    else
    {
        if(Player->TurSayi>Player2->TurSayi&&Player->TurSayi==3&&Player->kazaSayi<=5)
        {
            durum[1]=false;
            durum[2]=true;
            menu->win=true;
        }
        if((Player->TurSayi<Player2->TurSayi&&Player2->TurSayi==3)||Player->kazaSayi>5)
        {
            durum[1]=false;
            durum[2]=true;
            menu->win=false;
        }
    }
}
/* --- ------------------------------------------------- --- */



















