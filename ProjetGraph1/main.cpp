#include <iostream>
#include <allegro.h>

#define MODE_GRAPHIQUE GFX_AUTODETECT_FULLSCREEN

#define LARGEURECRAN 1024
#define HAUTEURECRAN 768
#include "Graph.hpp"

int main()
{
    Graph g;
    std::string choix;

    std::cout << "Entrer le nom du fichier : " << std::endl;
    std::cin >> choix;
    g.FileReading(choix);


///INITIALISATION DE ALLEGRO
    allegro_init();

    install_keyboard();
    install_mouse();
    show_mouse(screen);

    ///UTILISATION DU SON
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

    ///BIBLIOTHEQUES GRAPHIQUES ALLEGRO
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(MODE_GRAPHIQUE,LARGEURECRAN,HAUTEURECRAN,0,0)!=0)
    {
        if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,SCREEN_W,SCREEN_H,0,0)!=0)
        {
            allegro_message("prb gfx mode");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
    set_display_switch_mode(SWITCH_BACKGROUND);


    int choix=0;
    ///DECLARATION BITMAP
    BITMAP* wallpaper = load_bitmap("wallpaper.bmp",NULL);
    BITMAP* title = load_bitmap("title.bmp",NULL);
    BITMAP* cursor = load_bitmap("cursor.bmp", NULL);
    BITMAP* play = load_bitmap("play.bmp",NULL);
    BITMAP* menu = load_bitmap("wallpaper2.bmp",NULL);
    BITMAP* choix_menu = load_bitmap("choix.bmp",NULL);
    BITMAP* toolbar = load_bitmap("toolbar.bmp",NULL);

    BITMAP* buffermenu = create_bitmap(SCREEN_W,SCREEN_H);

    SAMPLE *song;

    song = load_sample("son.wav");

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

    while(choix==1)
    {
        blit(menu, buffermenu,0,0,0,0,SCREEN_W,SCREEN_H);
        draw_sprite(buffermenu,choix_menu,0,(SCREEN_W/2));
        draw_sprite(buffermenu,cursor,mouse_x,mouse_y);
        blit(buffermenu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if(choix==1 && mouse_x>7 && mouse_x<295 && mouse_y>(SCREEN_W/2) && mouse_y<(SCREEN_W/2)+60 && mouse_b)
        {
            ///MENU CREATION GRAPHE
            choix=2;
        }

        if(choix==1 && mouse_x>7 && mouse_x<295 && mouse_y>(SCREEN_W/2)+90 && mouse_y<(SCREEN_W/2)+150 && mouse_b)
        {
            ///MENU CHARGEMENT GRAPHE
            choix=2;
        }

         if(choix==1 && mouse_x>7 && mouse_x<295 && mouse_y>(SCREEN_W/2)+178 && mouse_y<(SCREEN_W/2)+220 && mouse_b)
        {
            choix=2;
            return 0;
        }

    }

    stop_sample(song);


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {

    }

    return 0;
}
END_OF_MAIN();