#include "grman/grman.h"
#include <iostream>
#include <allegro.h>


#include "graph.h"

int main()
{



    ///INITIALISATION DE ALLEGRO
    allegro_init();

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

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
    BITMAP* toolbar = load_bitmap("toolbar.bmp",NULL);

    BITMAP* buffermenu = create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* buffer = create_bitmap(SCREEN_W,SCREEN_H);

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



    /// Un exemple de graphe
    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");
    Graph g;
    std::string choice;
    std::cout << "Entrer le nom du fichier : " << std::endl;
    std::cin >> choice;
    g.ReadFile(choice);
    //g.make_example();

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
       /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


