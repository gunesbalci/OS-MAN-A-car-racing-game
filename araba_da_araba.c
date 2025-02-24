#include <allegro5/allegro5.h>
#include <stdio.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include "struct.h"
#include "fonksiyonlar.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#define PI 3.14159265359


int main()
{
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* ekran = al_create_display(910, 720);
    ALLEGRO_BITMAP* background=NULL;
    ALLEGRO_BITMAP* araba=NULL;
    ALLEGRO_BITMAP* dusman=NULL;
    ALLEGRO_BITMAP* odunSol=NULL;
    ALLEGRO_BITMAP* odunUst=NULL;
    ALLEGRO_BITMAP* menuArkaplan=NULL;
    ALLEGRO_FONT* oyunIsmi = al_create_builtin_font();
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_FONT* tuslar = al_create_builtin_font();
    ALLEGRO_FONT* secilituslar = al_create_builtin_font();
    ALLEGRO_FONT* OyuniciFont = al_create_builtin_font();
    ALLEGRO_KEYBOARD_STATE klavyeDurum;
    ALLEGRO_EVENT event;

/* --- Degerler ve Atamalar --- */
    bool work=true;
    bool tersYon=false;
    bool yarismabaslasin=false;
    bool redraw = true;

// durum[0]=menu, durum[1]=oyun, durum[2]=sonuc ekrani
    bool durum[3]={true,false,false};

    struct Araba Player;
    struct Dusman Player2;
    struct Menu menu;

    int genislik=910;
    int yukseklik=720;
    int odunGenis=0;

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(ekran));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    //bitmapler
    background= al_load_bitmap("arabayarisi_bg.png");
    araba= al_load_bitmap("arabam.png");
    dusman= al_load_bitmap("arabam2.png");
    odunSol= al_load_bitmap("odunSol.png");
    odunUst= al_load_bitmap("odunUst.png");
    menuArkaplan= al_load_bitmap("osman.png");

    //fontlar
    oyunIsmi= al_load_ttf_font("font.TTF",80,0);
    tuslar= al_load_ttf_font("font.TTF",50,0);
    secilituslar= al_load_ttf_font("font.TTF",40,0);
    OyuniciFont= al_load_ttf_font("oyuniciFont.TTF",30,0);

    //boyutlar
    Player.yuks= al_get_bitmap_height(araba);
    Player.gens= al_get_bitmap_width(araba);
    Player2.yuks= al_get_bitmap_height(dusman);
    Player2.gens= al_get_bitmap_width(dusman);
    odunGenis= al_get_bitmap_width(odunSol);

    //degiskenlere deger atama fonksiyonlari
    ArabaDegerler(&Player);
    Dusmandegerler(&Player2);
    menuDegerler(&menu);
/* --- ----------------------------------- --- */

/* --- Programin calistirilmasi --- */
    al_start_timer(timer);
    while(work)
    {
        al_wait_for_event(queue, &event);
        al_get_keyboard_state(&klavyeDurum);

        ArabaSinirleri(&Player);
        DusmanSinirleri(&Player2);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;

                //menu degerleri
                if(durum[2])
                {
                    bitisEkrani(&Player,&Player2,&menu);
                }
                if(durum[0])
                {
                    baslamaEkrani(&menu);
                }

                //Arabalarin hareketleri
                vitesKontrolu(&Player);
                if(al_key_down(&klavyeDurum,ALLEGRO_KEY_W)&&durum[1])
                {
                    ilerigit(&Player);
                    yarismabaslasin=true;
                }
                if(al_key_down(&klavyeDurum,ALLEGRO_KEY_D))
                {
                    Player.derece=sagadon(Player);
                }
                if(al_key_down(&klavyeDurum,ALLEGRO_KEY_A))
                {
                    Player.derece=soladon(Player);
                }
                if(al_key_down(&klavyeDurum,ALLEGRO_KEY_S))
                {
                    gerigit(&Player);
                }
                if(al_key_down(&klavyeDurum,ALLEGRO_KEY_E))
                {
                    vitesDegistir(&Player);
                }
                if(!al_key_down(&klavyeDurum,ALLEGRO_KEY_W)&&!al_key_down(&klavyeDurum,ALLEGRO_KEY_S))
                {
                   ivmelidur(&Player);
                }
                if(!al_key_down(&klavyeDurum,ALLEGRO_KEY_W))
                {
                    Player.vites1=true;
                    Player.vites2=false;
                    Player.vites3=false;
                }
                if((Player.ustY>181&&Player.ustY<546&&Player.ustX>152&&Player.ustX<760)||
                   (Player.altY>181&&Player.altY<546&&Player.altX>152&&Player.altX<760))
                {
                    if(al_key_down(&klavyeDurum,ALLEGRO_KEY_W))
                    {
                        yavaslama_pztf(&Player);
                    }
                    if(al_key_down(&klavyeDurum,ALLEGRO_KEY_S))
                    {
                        yavaslama_ngtf(&Player);
                    }
                }
                if(yarismabaslasin)
                {
                    DusmanRota(&Player2,odunGenis,yukseklik,durum);
                }
                kazaWobje(&Player,genislik,yukseklik,odunGenis);
                kazaWdusman(&Player,&Player2);
                tersYon=tersYonKontrol(Player,genislik,yukseklik,odunGenis,tersYon);
                checkPoint(&Player,yukseklik,genislik,odunGenis);
                turKontrol(&Player,tersYon,odunGenis);
                turKontrolDusman(&Player2);
                KazaSayma(&Player);
                W_or_L(&menu,&Player,&Player2,durum);

                //menu
                menuSeciliTus(&menu,durum);

            case ALLEGRO_EVENT_KEY_DOWN:

                //menu tuslari arasinda ilerleme
                if(event.keyboard.keycode==ALLEGRO_KEY_DOWN&&(durum[0]||durum[2]))
                {
                    menuTusDegistirme(&menu,durum);
                    menu.y_klavye+=menu.yerDegistirme;
                    menu.y_sonucEkrani+=menu.yerDegistirme;
                }

                //menu tuslarini secme
                if(event.keyboard.keycode==ALLEGRO_KEY_ENTER&&(durum[0]||durum[2]))
                {
                    if(menu.baslaTus)
                    {
                        Player.kazaSayi=0;
                        Player.TurSayi=0;
                        durum[0]=false;
                        durum[2]=false;
                        durum[1]=true;
                    }
                    if(menu.zorlukTus)
                    {
                        zorlukBelirleme(&menu);
                    }
                    if(menu.anaMenuTus)
                    {
                        durum[2]=false;
                        durum[0]=true;
                        durum[1]=false;

                        menu.y_klavye=120;
                    }
                    if(menu.cikisTus)
                    {
                        work=false;
                    }
                }

                //oyun devam ederken tusa basarak oyunu bitirme
                if(event.keyboard.keycode==ALLEGRO_KEY_ESCAPE&&durum[1])
                {
                    Player.kazaSayi=6;
                }
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                break;
        }

        //ekran ciktilari
        if(redraw&&al_is_event_queue_empty(queue))
        {
            //ana menu
            if(durum[0])
            {
                al_draw_bitmap(menuArkaplan,0,0,0);
                al_draw_text(oyunIsmi, al_map_rgb(220, 220, 220), 30, 30, 0, "OS-MAN");
                al_draw_text(OyuniciFont, al_map_rgb(0, 0, 0), 10, 630, 0, "down - tuslari gezmek");
                al_draw_text(OyuniciFont, al_map_rgb(0, 0, 0), 10, 660, 0, "enter - tus secme");
                al_draw_text(OyuniciFont, al_map_rgb(0, 0, 0), 10, 690, 0, "escape - oyunu bitirme");
                al_draw_text(OyuniciFont, al_map_rgb(0, 0, 0), 630, 630, 0, "w/s - ileri/geri");
                al_draw_text(OyuniciFont, al_map_rgb(0, 0, 0), 630, 660, 0, "a/d - direksiyon");
                al_draw_text(OyuniciFont, al_map_rgb(0, 0, 0), 630, 690, 0, "e - vites");
                al_draw_filled_rounded_rectangle(80,170,330,230,10,10,al_map_rgb(240, 240, 240));
                al_draw_filled_rounded_rectangle(80,250,330,310,10,10,al_map_rgb(240, 240, 240));
                al_draw_filled_rounded_rectangle(80,330,330,390,10,10,al_map_rgb(240, 240, 240));
                if(menu.baslaTus)
                {
                    al_draw_text(secilituslar, al_map_rgb(20, 255, 50), 115, 180, 0, "BASLA");
                }
                else
                {
                    al_draw_text(tuslar, al_map_rgb(81, 118, 255), 90, 175, 0, "BASLA");
                }
                if(menu.zorlukTus)
                {
                    if(menu.zor)
                    {
                        al_draw_text(secilituslar, al_map_rgb(20, 255, 50), 150, 260, 0, "ZOR");
                    }
                    if(!menu.zor)
                    {
                        al_draw_text(secilituslar, al_map_rgb(20, 255, 50), 115, 260, 0, "KOLAY");
                    }
                }
                else
                {
                    if(menu.zor)
                    {
                        al_draw_text(tuslar, al_map_rgb(81, 118, 255), 140, 255, 0, "ZOR");
                    }
                    if(!menu.zor)
                    {
                        al_draw_text(tuslar, al_map_rgb(81, 118, 255), 95, 255, 0, "KOLAY");
                    }
                }
                if(menu.cikisTus)
                {
                    al_draw_text(secilituslar, al_map_rgb(20, 255, 50), 130, 340, 0, "CIKIS");
                }
                else
                {
                    al_draw_text(tuslar, al_map_rgb(81, 118, 255), 110, 335, 0, "CIKIS");
                }
            }

            //oyun
            if(durum[1])
            {
                al_draw_bitmap(background,0,0,0);
                al_draw_bitmap(odunSol,0,0,0);
                al_draw_bitmap(odunSol,genislik-odunGenis+1,0,0);
                al_draw_bitmap(odunUst,0,0,0);
                al_draw_bitmap(odunUst,0,yukseklik-odunGenis+2,0);
                al_draw_scaled_rotated_bitmap(araba,811/2,368/2,Player.mX,Player.mY,0.1,0.1,Player.derece*PI/180,0);
                al_draw_scaled_rotated_bitmap(dusman,811/2,368/2,Player2.mX,Player2.mY,0.1,0.1,Player2.derece*PI/180,0);

                if(tersYon)
                {
                    al_draw_text(font, al_map_rgb(255, 255, 255), Player.mX, Player.mY, 0, "Ters Yondesin!");
                }

                al_draw_textf(OyuniciFont, al_map_rgb(0, 255, 0),15, 5, 0, "Tur: %d/3",Player.TurSayi);
                al_draw_textf(OyuniciFont, al_map_rgb(0, 255, 0),400, 5, 0, "vites: %d",Player.vites);
                if(!menu.zor)
                {
                    al_draw_textf(OyuniciFont, al_map_rgb(0, 255, 0),740, 5, 0, "Kaza: %d/5",Player.kazaSayi);
                }
            }

            //sonuc ekrani
            if(durum[2])
            {
                Player.kazaSayi=0;
                Player.TurSayi=0;
                Player2.TurSayi=0;
                Player.vites1=true;
                Player.vites2=false;
                Player.vites3=false;
                yarismabaslasin=false;
                al_draw_bitmap(background,0,0,0);
                al_draw_bitmap(odunSol,0,0,0);
                al_draw_bitmap(odunSol,genislik-odunGenis+1,0,0);
                al_draw_bitmap(odunUst,0,0,0);
                al_draw_bitmap(odunUst,0,yukseklik-odunGenis+2,0);
                al_draw_scaled_rotated_bitmap(araba,811/2,368/2,Player.mX,Player.mY,0.1,0.1,Player.derece*PI/180,0);
                al_draw_scaled_rotated_bitmap(dusman,811/2,368/2,Player2.mX,Player2.mY,0.1,0.1,Player2.derece*PI/180,0);
                al_draw_text(OyuniciFont, al_map_rgb(255, 255, 255), 10, 630, 0, "down - tuslari gezmek");
                al_draw_text(OyuniciFont, al_map_rgb(255, 255, 255), 10, 660, 0, "enter - tus secme");
                al_draw_text(OyuniciFont, al_map_rgb(255, 255, 255), 10, 690, 0, "escape - oyunu bitirme");
                al_draw_text(OyuniciFont, al_map_rgb(255, 255, 255), 630, 630, 0, "w/s - ileri/geri");
                al_draw_text(OyuniciFont, al_map_rgb(255, 255, 255), 630, 660, 0, "a/d - direksiyon");
                al_draw_text(OyuniciFont, al_map_rgb(255, 255, 255), 630, 690, 0, "e - vites");

                if(menu.win)
                {
                    al_draw_text(oyunIsmi, al_map_rgb(0, 255, 255), 200, 100, 0, "Kazandin!");
                }
                if(!menu.win)
                {
                    al_draw_text(oyunIsmi, al_map_rgb(255, 30, 30), 160, 100, 0, "Kaybettin!");
                }
                al_draw_filled_rounded_rectangle(150,300,760,360,10,10,al_map_rgb(240, 240, 240));
                al_draw_filled_rounded_rectangle(150,380,760,440,10,10,al_map_rgb(240, 240, 240));
                al_draw_filled_rounded_rectangle(150,460,760,520,10,10,al_map_rgb(240, 240, 240));
                if(menu.baslaTus)
                {
                    al_draw_text(secilituslar, al_map_rgb(20, 255, 50), 220, 310, 0, "YENIDEN BASLA");
                }
                else
                {
                    al_draw_text(tuslar, al_map_rgb(81, 118, 255), 170, 305, 0, "YENIDEN BASLA");
                }
                if(menu.anaMenuTus)
                {
                    al_draw_text(secilituslar, al_map_rgb(20, 255, 50), 310, 390, 0, "ANA MENU");
                }
                else
                {
                    al_draw_text(tuslar, al_map_rgb(81, 118, 255), 280, 385, 0, "ANA MENU");
                }
                if(menu.cikisTus)
                {
                    al_draw_text(secilituslar, al_map_rgb(20, 255, 50), 380, 470, 0, "CIKIS");
                }
                else
                {
                    al_draw_text(tuslar, al_map_rgb(81, 118, 255), 360, 465, 0, "CIKIS");
                }

            }

            al_flip_display();
            redraw = false;
        }

    }
/* --- --------------------------------------- --- */

//olusturulan degerleri yok etme
    al_destroy_font(font);
    al_destroy_font(oyunIsmi);
    al_destroy_font(OyuniciFont);
    al_destroy_font(secilituslar);
    al_destroy_font(tuslar);

    al_destroy_display(ekran);

    al_destroy_bitmap(background);
    al_destroy_bitmap(menuArkaplan);
    al_destroy_bitmap(araba);
    al_destroy_bitmap(dusman);
    al_destroy_bitmap(odunSol);
    al_destroy_bitmap(odunUst);

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_uninstall_keyboard();

    return 0;
}
