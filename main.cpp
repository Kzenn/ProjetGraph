#include <iostream>
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cmath>

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
    bool chargement = 0;
    bool click=0;
    int mem=0;
    int k=0;
    int stockage=0;


    ///DECLARATION BITMAP
    BITMAP* wallpaper = load_bitmap("wallpaper.bmp",NULL);
    BITMAP* title = load_bitmap("title.bmp",NULL);
    BITMAP* cursor = load_bitmap("cursor.bmp", NULL);
    BITMAP* play = load_bitmap("play.bmp",NULL);
    BITMAP* menu = load_bitmap("wallpaper2.bmp",NULL);
    BITMAP* choix_menu = load_bitmap("choix.bmp",NULL);
    BITMAP* feuille = load_bitmap("feuille.bmp", NULL);
    BITMAP* toolbar = load_bitmap("toolbar.bmp", NULL);
    BITMAP* exit = load_bitmap("exit.bmp",NULL);
    BITMAP* blanc = load_bitmap("blanc.bmp", NULL);
    BITMAP* sante =  load_bitmap("sante.bmp",NULL);
    BITMAP* rouge = load_bitmap("rouge.bmp",NULL);
    BITMAP* save = load_bitmap("save.bmp",NULL);
    BITMAP* fleches = load_bitmap("fleches.bmp",NULL);
    BITMAP* valider = load_bitmap("check.bmp",NULL);
    BITMAP* choix_menu_save = load_bitmap("choix_menu_save.bmp",NULL);

    BITMAP* buffer = create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* buffermenu = create_bitmap(SCREEN_W,SCREEN_H);

    SAMPLE *song;
    SAMPLE* mer;
    SAMPLE* success;
    SAMPLE* next;

    song = load_sample("son.wav");
    mer = load_sample("mer.wav");
    success = load_sample("success.wav");
    next = load_sample("next.wav");

    play_sample(song,255, 128, 1000, true);

    std::string choice = "Food2.txt";
    Graph g;


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
        chargement = false;
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
            rest(200);
            g.ReadFileDocument();
            ///MENU CHARGEMENT GRAPHE
            while(chargement == false)
            {

                clear_bitmap(buffermenu);
                blit(menu, buffermenu,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(buffermenu,choix_menu_save,0,(SCREEN_W/2)+90);
                draw_sprite(buffermenu, fleches,350,(SCREEN_W/2)+90);
                textprintf_ex(buffermenu,font,750,(SCREEN_W/2)+115,makecol(255,255,255), -1,  "%s",g.getGraphFile()[k].c_str());
                draw_sprite(buffermenu,cursor,mouse_x,mouse_y);
                blit(buffermenu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                std::cout << g.getGraphFile()[k] << std::endl;

                std::cout << " ICI " << g.getGraphFile().size() << std::endl;

                if(key[KEY_ESC])
                {
                    chargement = true;
                    choix=1;
                }
                else if(key[KEY_LEFT])
                {
                    if(k-1<0)
                    {
                        k=g.getGraphFile().size()-1;
                        rest(200);
                        play_sample(next,255, 128, 2000, false);
                    }
                    else if(k-1>=0)
                    {
                        k-=1;
                        rest(200);
                        play_sample(next,255, 128, 2000, false);
                    }

                }
                else if(key[KEY_RIGHT])
                {
                    if(k+1>g.getGraphFile().size()-1)
                    {
                        k=0;
                        rest(200);
                        play_sample(next,255, 128, 2000, false);
                    }
                    else if(k+1<=g.getGraphFile().size()-1)
                    {
                        k+=1;
                        rest(200);
                        play_sample(next,255, 128, 2000, false);
                    }


                }
                else if(mouse_x>7 && mouse_x<295 && mouse_y>(SCREEN_W/2)+90 && mouse_y<(SCREEN_W/2)+150 && mouse_b)
                {
                    chargement = true;
                    choice = g.getGraphFile()[k];
                    choix=2;
                    g.ClearVecFileName();
                }


            }

            stop_sample(mer);

            g.ClearVecEdge();
            g.ClearVecSommet();
            g.ReadFile(choice);
            while(choix==2)
            {
                blit(feuille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);

                ///AFFICHAGE ARETES
                for(auto& elem : g.getEdgeTab())
                {
                    //std::cout << elem.geta().getchemin() << "   " << elem.geta().getpos_x() << "   " << elem.geta().getpos_y() << "   " << elem.getb().getchemin()<< "   " << elem.getb().getpos_x() << "   " << elem.getb().getpos_y() <<std::endl;
                    if(elem.getWeight()>0 && elem.geta().getpop()>0 && elem.getb().getpop()>0)
                        thick_line(buffer, elem.geta().getpos_x()+TAILLEX/2, elem.geta().getpos_y()+TAILLEY/2, elem.getb().getpos_x()+TAILLEX/2, elem.getb().getpos_y()+TAILLEY/2, 5.0, makecol(255, 255, 255));
                    ///line(buffer,elem.geta().getpos_x()+(TAILLEX/2), elem.geta().getpos_y()+(TAILLEY/2), elem.getb().getpos_x()+(TAILLEX/2), elem.getb().getpos_y()+(TAILLEY/2),makecol(255,255,255));
                    blit(rouge,buffer,0,0,(abs(elem.geta().getpos_x()+elem.getb().getpos_x())/2)+15,(abs(elem.geta().getpos_y()+elem.getb().getpos_y())/2)+10,SCREEN_W,SCREEN_H);
                    textprintf_ex(buffer,font,(abs(elem.geta().getpos_x()+elem.getb().getpos_x())/2)+20,(abs(elem.geta().getpos_y()+elem.getb().getpos_y())/2)+15,makecol(0,0,0), -1,  "%d", elem.getWeight());
                }
                //std::cout << std::endl;

                ///AFFICHAGE SOMMETS
                for(unsigned int i=0; i<g.getSommetTab().size(); i++)
                {
                    //std::cout << "TABLEAU :  " << g.getSommetTab()[i]->getchemin() << "   " << g.getSommetTab()[i]->getpos_x() << "   " << g.getSommetTab()[i]->getpos_y() << std::endl;
                    blit(g.getSommetTab()[i]->getpic(),buffer,0,0,g.getSommetTab()[i]->getpos_x(),g.getSommetTab()[i]->getpos_y(),SCREEN_W,SCREEN_H);
                    blit(blanc,buffer,0,0,g.getSommetTab()[i]->getpos_x()+70,g.getSommetTab()[i]->getpos_y()+80,SCREEN_W,SCREEN_H);
                    blit(sante,buffer,0,0,g.getSommetTab()[i]->getpos_x()-30,g.getSommetTab()[i]->getpos_y()+25,SCREEN_W,SCREEN_H);
                    textprintf_ex(buffer,font,g.getSommetTab()[i]->getpos_x()+80,g.getSommetTab()[i]->getpos_y()+90,makecol(0,0,0), -1,  "%d", g.getSommetTab()[i]->getidx());
                    textprintf_ex(buffer,font,g.getSommetTab()[i]->getpos_x()-25,g.getSommetTab()[i]->getpos_y()+60,makecol(0,0,0), -1,  "%d", g.getSommetTab()[i]->getpop());
                }


                blit(toolbar,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(buffer,save,15,SCREEN_H/1.25);
                draw_sprite(buffer,exit,15,SCREEN_H/1.1);

                draw_sprite(buffer,cursor,mouse_x,mouse_y);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

                for(int i=0; i<g.getSommetTab().size(); i++)
                {
                    if(mouse_b&2 && mouse_x>g.getSommetTab()[i]->getpos_x()-30 && mouse_x<g.getSommetTab()[i]->getpos_x() && mouse_y>g.getSommetTab()[i]->getpos_y()+25 && mouse_y<g.getSommetTab()[i]->getpos_y()+80)
                    {

                        if(g.getSommetTab()[i]->getpop()-5==0)
                        {
                            g.getSommetTab()[i]->setpop(0);
                            for(auto& elem : g.getEdgeTab())
                            {
                                if(g.getSommetTab()[i]->getchemin() == elem.geta().getchemin())
                                    elem.geta().setpop(g.getSommetTab()[i]->getpop());
                                else if(g.getSommetTab()[i]->getchemin() == elem.getb().getchemin())
                                    elem.getb().setpop(g.getSommetTab()[i]->getpop());

                            }
                            rest(100);
                        }
                        else if(g.getSommetTab()[i]->getpop()-5<=0)
                        {
                            g.getSommetTab()[i]->setpop(0);
                            for(auto& elem : g.getEdgeTab())
                            {
                                if(g.getSommetTab()[i]->getchemin() == elem.geta().getchemin())
                                    elem.geta().setpop(g.getSommetTab()[i]->getpop());
                                else if(g.getSommetTab()[i]->getchemin() == elem.getb().getchemin())
                                    elem.getb().setpop(g.getSommetTab()[i]->getpop());

                            }
                            rest(100);
                        }
                        else if(g.getSommetTab()[i]->getpop()-5>0)
                        {
                            g.getSommetTab()[i]->setpop(g.getSommetTab()[i]->getpop()-5);
                            for(auto& elem : g.getEdgeTab())
                            {
                                if(g.getSommetTab()[i]->getchemin() == elem.geta().getchemin())
                                    elem.geta().setpop(g.getSommetTab()[i]->getpop());
                                else if(g.getSommetTab()[i]->getchemin() == elem.getb().getchemin())
                                    elem.getb().setpop(g.getSommetTab()[i]->getpop());

                            }
                            rest(100);
                        }
                    }

                    else if(mouse_b && mouse_x>g.getSommetTab()[i]->getpos_x()-30 && mouse_x<g.getSommetTab()[i]->getpos_x() && mouse_y>g.getSommetTab()[i]->getpos_y()+25 && mouse_y<g.getSommetTab()[i]->getpos_y()+80)
                    {
                        g.getSommetTab()[i]->setpop(g.getSommetTab()[i]->getpop()+5);
                        for(auto& elem : g.getEdgeTab())
                        {
                            if(g.getSommetTab()[i]->getchemin() == elem.geta().getchemin())
                                elem.geta().setpop(g.getSommetTab()[i]->getpop());
                            else if(g.getSommetTab()[i]->getchemin() == elem.getb().getchemin())
                                elem.getb().setpop(g.getSommetTab()[i]->getpop());

                        }
                        rest(100);
                    }
                    else if(mouse_b && mouse_x>g.getSommetTab()[i]->getpos_x() && mouse_x<g.getSommetTab()[i]->getpos_x()+TAILLEX && mouse_y>g.getSommetTab()[i]->getpos_y() && mouse_y<g.getSommetTab()[i]->getpos_y()+TAILLEY)
                    {
                        click = 1;
                        mem = i;
                    }
                }
                for(auto& elem : g.getEdgeTab())
                {
                    if(mouse_b&2 && click==0 && mouse_x>(abs(elem.geta().getpos_x()+elem.getb().getpos_x())/2)+15 && mouse_x<(abs(elem.geta().getpos_x()+elem.getb().getpos_x())/2)+45 && mouse_y>(abs(elem.geta().getpos_y()+elem.getb().getpos_y())/2)+10 && mouse_y<(abs(elem.geta().getpos_y()+elem.getb().getpos_y())/2)+30)
                    {

                        if(elem.getWeight()-5<=0)
                        {
                            elem.setWeight(0);
                            rest(100);
                        }
                        else if(elem.getWeight()-5>0)
                        {
                            elem.setWeight(elem.getWeight()-5);
                            rest(100);
                        }

                    }
                    else if(mouse_b && click==0 && mouse_x>(abs(elem.geta().getpos_x()+elem.getb().getpos_x())/2)+15 && mouse_x<(abs(elem.geta().getpos_x()+elem.getb().getpos_x())/2)+45 && mouse_y>(abs(elem.geta().getpos_y()+elem.getb().getpos_y())/2)+10 && mouse_y<(abs(elem.geta().getpos_y()+elem.getb().getpos_y())/2)+30)
                    {
                        if(elem.getWeight()+5>0)
                        {
                            elem.setWeight(elem.getWeight()+5);
                            rest(100);
                        }

                    }
                }

                if(click==1)
                {
                    clear_bitmap(buffer);
                    ///MISE A JOUR SOMMET
                    if(g.getSommetTab()[mem]->getpos_x()<88)
                        g.getSommetTab()[mem]->setpos_x(88);
                    else if(g.getSommetTab()[mem]->getpos_x()+TAILLEX>SCREEN_W)
                        g.getSommetTab()[mem]->setpos_x(SCREEN_W-TAILLEX);
                    else if(g.getSommetTab()[mem]->getpos_y()+TAILLEY>SCREEN_H)
                        g.getSommetTab()[mem]->setpos_y(SCREEN_H-TAILLEY);
                    else if(g.getSommetTab()[mem]->getpos_y()<0)
                        g.getSommetTab()[mem]->setpos_y(0);
                    else
                    {
                        g.getSommetTab()[mem]->setpos_x(mouse_x - TAILLEX/2);
                        g.getSommetTab()[mem]->setpos_y(mouse_y - TAILLEX/2);
                    }
                    ///MISE A JOUR ARETE
                    for(const auto& elem : g.getEdgeTab())
                    {
                        if(elem.geta().getidx() == g.getSommetTab()[mem]->getidx())
                        {
                            elem.geta().setpos_x(g.getSommetTab()[mem]->getpos_x());
                            elem.geta().setpos_y(g.getSommetTab()[mem]->getpos_y());
                        }
                        if(elem.getb().getidx() == g.getSommetTab()[mem]->getidx())
                        {
                            elem.getb().setpos_x(g.getSommetTab()[mem]->getpos_x());
                            elem.getb().setpos_y(g.getSommetTab()[mem]->getpos_y());
                        }
                    }

                }
                if(click==1 && mouse_b)
                {
                    click = 0;
                }





                ///ON CLIQUE SUR AJOUT D'UN SOMMET/NOEUD
                if(choix==2 && mouse_x>30 && mouse_x<60 && mouse_y>100 && mouse_y<149 && mouse_b)
                {
                    rest(200);
                    g.AddVertex();

                }

                ///ON CLIQUE SUR SUPRESSION D'UN SOMMET/NOEUD
                if(choix==2 && mouse_x>30 && mouse_x<60 && mouse_y>149 && mouse_y<194 && mouse_b)
                {
                    ///FONCTION CORRESPONDANTE
                }

                ///ON CLIQUE SUR AJOUT D'UN EDGE/ARETE
                if(choix==2 && mouse_x>30 && mouse_x<60 && mouse_y>272 && mouse_y<320 && mouse_b)
                {
                    rest(200);
                    g.AddEdge();
                }

                ///ON CLIQUE SUR SUPPRESSION D'UN EDGE/ARETE
                if(choix==2 && mouse_x>30 && mouse_x<60 && mouse_y>320 && mouse_y<366 && mouse_b)
                {
                    ///FONCTION CORRESPONDANTE
                }

                ///ON CLIQUE SUR SAUVEGARDE
                if(choix==2 && mouse_x>15 && mouse_x<75 && mouse_y>(SCREEN_H/1.25) && mouse_y<(SCREEN_H/1.25)+60 && mouse_b)
                {

                    g.SaveFile(choice);
                    play_sample(success,255, 128, 1000, false);
                    rest(100);

                }


                ///ON CLIQUE SUR EXIT
                if(choix==2 && mouse_x>15 && mouse_x<75 && mouse_y>(SCREEN_H/1.1) && mouse_y<(SCREEN_H/1.1)+60 && mouse_b)
                {
                    choix=1;
                    rest(200);
                }



            }

        }
        if(choix==1 && mouse_x>7 && mouse_x<295 && mouse_y>(SCREEN_W/2)+178 && mouse_y<(SCREEN_W/2)+220 && mouse_b)
        {
            stop_sample(mer);
            choix=2;
            return 0;
        }


    }

    return 0;
}
END_OF_MAIN();
