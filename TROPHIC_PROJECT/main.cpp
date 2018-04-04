#include <iostream>
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SCREEN_H 768
#define SCREEN_W 1024

#define TAILLEX 100
#define TAILLEY 100

#include "Graph.hpp"
#include "Edge.hpp"

void thick_line(BITMAP *bmp, int x, int y, int x_, int y_,int thickness, int color)
{
    int dx = x - x_;
    int dy = y - y_;
    int d = sqrtf(dx * dx + dy * dy);
    if (!d)
        return;
    int v[8];
    v[0] = x - thickness * dy / d;
    v[1] = y + thickness * dx / d;
    v[2] = x + thickness * dy / d;
    v[3] = y - thickness * dx / d;
    v[4] = x_ + thickness * dy / d;
    v[5] = y_ - thickness * dx / d;
    v[6] = x_ - thickness * dy / d;
    v[7] = y_ + thickness * dx / d;
    polygon(bmp, 4, v, color);
}
int main()
{
    ///INITIALISATION DE ALLEGRO
    allegro_init();

    install_keyboard();
    install_mouse();
    show_mouse(screen);

    ///UTILISATION DU SON
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);


    ///BIBLIOTHEQUES GRAPHIQUES ALLEGRO
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,SCREEN_W, SCREEN_H,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);

    }

    int choix=0;

    ///DECLARATION BITMAP
    BITMAP* wallpaper = load_bitmap("wallpaper.bmp",NULL);
    BITMAP* title = load_bitmap("title.bmp",NULL);
    BITMAP* cursor = load_bitmap("cursor.bmp", NULL);
    BITMAP* play = load_bitmap("play.bmp",NULL);
    BITMAP* menu = load_bitmap("wallpaper2.bmp",NULL);
    BITMAP* choix_menu = load_bitmap("choix.bmp",NULL);
    BITMAP* feuille = load_bitmap("feuille.bmp", NULL);
    BITMAP* toolbar = load_bitmap("toolbar.bmp", NULL);

    BITMAP* buffer = create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* buffermenu = create_bitmap(SCREEN_W,SCREEN_H);

    BITMAP* im1 = load_bitmap("pics/wolf.bmp", NULL);
    BITMAP* im2 = load_bitmap("pics/python.bmp", NULL);

    SAMPLE *song;
    SAMPLE* mer;

    song = load_sample("son.wav");
    mer = load_sample("mer.wav");

    play_sample(song,255, 128, 1000, true);

    while(choix==0)
    {
        clear_bitmap(buffermenu);

        blit(wallpaper, buffermenu,0,0,0,0,SCREEN_W,SCREEN_H);
        draw_sprite(buffermenu,title,(SCREEN_W/3),30);
        draw_sprite(buffermenu,play,(SCREEN_W/1.3),(SCREEN_H/1.3));
        draw_sprite(buffermenu,cursor,mouse_x,mouse_y);
        blit(buffermenu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if(choix==0 && mouse_x>(SCREEN_W/1.3) && mouse_x<(SCREEN_W/1.3)+131 && mouse_y>(SCREEN_H/1.3)+87 && mouse_y<(SCREEN_H/1.3)+131 && mouse_b)
        {
            stop_sample(song);
            return 0;

        }
        if(choix==0 && mouse_x>(SCREEN_W/1.3) && mouse_x<(SCREEN_W/1.3)+131 && mouse_y>(SCREEN_H/1.3) && mouse_y<(SCREEN_H/1.3)+45 && mouse_b)
        {
            stop_sample(song);
            choix=1;
        }
    }

    play_sample(mer,255, 128, 1000, true);

    while(choix==1)
    {
        blit(menu, buffermenu,0,0,0,0,SCREEN_W,SCREEN_H);
        draw_sprite(buffermenu,choix_menu,0,(SCREEN_W/2));
        draw_sprite(buffermenu,cursor,mouse_x,mouse_y);
        blit(buffermenu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if(choix==1 && mouse_x>7 && mouse_x<295 && mouse_y>(SCREEN_W/2) && mouse_y<(SCREEN_W/2)+60 && mouse_b)
        {
            ///MENU CREATION GRAPHE
            stop_sample(mer);
            choix=2;
        }

        if(choix==1 && mouse_x>7 && mouse_x<295 && mouse_y>(SCREEN_W/2)+90 && mouse_y<(SCREEN_W/2)+150 && mouse_b)
        {
            ///MENU CHARGEMENT GRAPHE
            stop_sample(mer);
            clear_bitmap(buffermenu);
            choix=2;

            int x1=0+(TAILLEX/2);
            int y1=0+(TAILLEY/2);
            int x2=200+(TAILLEX/2);
            int y2=200+(TAILLEY/2);
            bool click=0;
            while(choix==2)
            {

                blit(feuille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                blit(toolbar,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                thick_line(buffer, x1+TAILLEX/2, y1+TAILLEY/2, x2+TAILLEX/2, y2+TAILLEY/2, 5.0, makecol(255, 255, 255));
                //triangle(buffer, x2-20, y2, x2-5, y2-20, x2, y2, makecol(0, 255, 255));
                blit(im1, buffer,0,0,x1,y1,SCREEN_W,SCREEN_H);
                blit(im2, buffer,0,0,x2,y2,SCREEN_W,SCREEN_H);
                draw_sprite(buffer,cursor,mouse_x,mouse_y);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

                if(click == 0 && mouse_b && mouse_x>x1 && mouse_x<x1+TAILLEX && mouse_y>y1 && mouse_y<y1+TAILLEY)
                {
                    click=1;
                }
                if(click==1)
                {
                    clear_bitmap(buffer);
                    x1 = mouse_x - TAILLEX/2;
                    y1 = mouse_y - TAILLEX/2;
                }
                if(click==1 && mouse_b)
                {
                    click = 0;
                }

            }

        }

        if(choix==1 && mouse_x>7 && mouse_x<295 && mouse_y>(SCREEN_W/2)+178 && mouse_y<(SCREEN_W/2)+220 && mouse_b)
        {
            stop_sample(mer);
            choix=2;
            return 0;
        }

        /// Un exemple de graphe
        /// Le nom du répertoire où se trouvent les images à charger

        while(choix==2)
        {

            /// Vous gardez la main sur la "boucle de jeu"
            /// ( contrairement à des frameworks plus avancés )
            while (choix==2)
            {

                ///ON CLIQUE SUR AJOUT D'UN SOMMET/NOEUD
                if(choix==2 && mouse_x>50 && mouse_x<80 && mouse_y>100 && mouse_y<149 && mouse_b)
                {
                    ///FONCTION CORRESPONDANTE
                }

                ///ON CLIQUE SUR SUPRESSION D'UN SOMMET/NOEUD
                if(choix==2 && mouse_x>50 && mouse_x<80 && mouse_y>149 && mouse_y<194 && mouse_b)
                {
                    ///FONCTION CORRESPONDANTE
                }

                ///ON CLIQUE SUR AJOUT D'UN EDGE/ARETE
                if(choix==2 && mouse_x>50 && mouse_x<80 && mouse_y>272 && mouse_y<320 && mouse_b)
                {
                    ///FONCTION CORRESPONDANTE
                }

                ///ON CLIQUE SUR SUPPRESSION D'UN EDGE/ARETE
                if(choix==2 && mouse_x>50 && mouse_x<80 && mouse_y>320 && mouse_y<366 && mouse_b)
                {
                    ///FONCTION CORRESPONDANTE
                }


                ///ON CLIQUE SUR EXIT
                if(choix==2 && mouse_x>35 && mouse_x<95 && mouse_y>(SCREEN_H/1.15) && mouse_y<(SCREEN_H/1.15)+60 && mouse_b)
                {
                    choix=1;
                }

            }

        }
    }

    return 0;
}
END_OF_MAIN();
