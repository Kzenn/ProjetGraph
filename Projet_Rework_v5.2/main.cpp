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
    polygon(bmp, 4.9, v, color);
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
    bool d_edge=0;
    bool d_vertex=0;

    bool a_edge=0;

    bool sel1=0;
    bool sel2=0;
    bool add1=0;
    bool add2=0;
    Sommet* s_1;
    Sommet* s_2;

    std::vector<std::vector<int>> TabAdj;
    std::vector<std::vector<int>> CompConnexe;



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
    BITMAP* delete_cursor = load_bitmap("delete_cursor.bmp",NULL);
    BITMAP* delete_cursor_edge = load_bitmap("delete_cursor_edge.bmp",NULL);
    BITMAP* add_cursor_edge = load_bitmap("add_cursor_edge.bmp",NULL);
    BITMAP* conn_ic = load_bitmap("conn_ic.bmp",NULL);

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

    std::string choice;
    Graph g;

    while(choix==0)
    {
        clear_bitmap(buffermenu);

        blit(wallpaper, buffermenu,0,0,0,0,SCREEN_W,SCREEN_H);
        draw_sprite(buffermenu,title,(SCREEN_W/3),30);
        draw_sprite(buffermenu,play,(SCREEN_W/1.3),(SCREEN_H/1.3));
        draw_sprite(buffermenu,cursor,mouse_x,mouse_y);
        blit(buffermenu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if(choix==0 && mouse_x>(SCREEN_W/1.3) && mouse_x<(SCREEN_W/1.3)+131 && mouse_y>(SCREEN_H/1.3)+87 && mouse_y<(SCREEN_H/1.3)+131 && mouse_b&1)
        {
            stop_sample(song);
            return 0;

        }
        if(choix==0 && mouse_x>(SCREEN_W/1.3) && mouse_x<(SCREEN_W/1.3)+131 && mouse_y>(SCREEN_H/1.3) && mouse_y<(SCREEN_H/1.3)+45 && mouse_b&1)
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






        ///MENU CREATION GRAPHE
        if(choix==1 && mouse_x>7 && mouse_x<295 && mouse_y>(SCREEN_W/2) && mouse_y<(SCREEN_W/2)+60 && mouse_b&1)
        {

            stop_sample(mer);
            g.ClearVecEdge();
            g.ClearVecSommet();
            choice = g.CreateFile();
            choix=3;
        }

        ///MENU CHARGEMENT GRAPHE
        if(choix==1 && mouse_x>7 && mouse_x<295 && mouse_y>(SCREEN_W/2)+90 && mouse_y<(SCREEN_W/2)+150 && mouse_b&1)
        {
            rest(200);
            g.ReadFileDocument();
            choix=2;
        }

        ///SI ON CLIQUE SUR EXIT
        if(choix==1 && mouse_x>7 && mouse_x<295 && mouse_y>(SCREEN_W/2)+178 && mouse_y<(SCREEN_W/2)+220 && mouse_b&1)
        {
            stop_sample(mer);
            return 0;
        }

        if(choix==2)
        {
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
                else if(mouse_x>7 && mouse_x<295 && mouse_y>(SCREEN_W/2)+90 && mouse_y<(SCREEN_W/2)+150 && mouse_b&1)
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
            choix=3;
        }
        if(choix==3)
        {
            while(choix==3)
            {
                if(key[KEY_ESC])
                {
                    d_vertex = 0;
                    d_edge = 0;
                    a_edge = 0;
                }
                blit(feuille,buffer,0,0,0,0,SCREEN_W,SCREEN_H);

                ///AFFICHAGE ARETES
                for(auto& elem : g.getEdgeTab())
                {
                    if(elem.getWeight()>0 && elem.geta().getpop()>0 && elem.getb().getpop()>0)
                    {
                        if(elem.getWeight()<51)
                            line(buffer,elem.geta().getpos_x()+(TAILLEX/2), elem.geta().getpos_y()+(TAILLEY/2), elem.getb().getpos_x()+(TAILLEX/2), elem.getb().getpos_y()+(TAILLEY/2),makecol(255,255,255));
                        else if (elem.getWeight()>50 && elem.getWeight()<251)
                            thick_line(buffer, elem.geta().getpos_x()+TAILLEX/2, elem.geta().getpos_y()+TAILLEY/2, elem.getb().getpos_x()+TAILLEX/2, elem.getb().getpos_y()+TAILLEY/2, 5.0, makecol(255, 255, 255));
                        else if (elem.getWeight()>200 && elem.getWeight()<501)
                            thick_line(buffer, elem.geta().getpos_x()+TAILLEX/2, elem.geta().getpos_y()+TAILLEY/2, elem.getb().getpos_x()+TAILLEX/2, elem.getb().getpos_y()+TAILLEY/2, 11.0, makecol(255, 255, 255));
                        else
                            thick_line(buffer, elem.geta().getpos_x()+TAILLEX/2, elem.geta().getpos_y()+TAILLEY/2, elem.getb().getpos_x()+TAILLEX/2, elem.getb().getpos_y()+TAILLEY/2, 19.0, makecol(255, 255, 255));

                    }
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
                draw_sprite(buffer,conn_ic,15,SCREEN_H/1.40);
                draw_sprite(buffer,save,15,SCREEN_H/1.25);
                draw_sprite(buffer,exit,15,SCREEN_H/1.1);

                if(d_vertex==1)
                    draw_sprite(buffer,delete_cursor,mouse_x,mouse_y);
                else if(d_edge==1)
                    draw_sprite(buffer,delete_cursor_edge,mouse_x,mouse_y);
                else if(a_edge==1)
                    draw_sprite(buffer,add_cursor_edge,mouse_x,mouse_y);
                else
                    draw_sprite(buffer,cursor,mouse_x,mouse_y);

                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

                for(int i=0; i<g.getSommetTab().size(); i++)
                {
                    if(d_vertex==0 && d_edge==0 && a_edge==0 && mouse_b&2 && mouse_x>g.getSommetTab()[i]->getpos_x()-30 && mouse_x<g.getSommetTab()[i]->getpos_x() && mouse_y>g.getSommetTab()[i]->getpos_y()+25 && mouse_y<g.getSommetTab()[i]->getpos_y()+80)
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

                    else if(d_vertex==0 && d_edge==0 && a_edge==0 && mouse_b&1 && mouse_x>g.getSommetTab()[i]->getpos_x()-30 && mouse_x<g.getSommetTab()[i]->getpos_x() && mouse_y>g.getSommetTab()[i]->getpos_y()+25 && mouse_y<g.getSommetTab()[i]->getpos_y()+80)
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
                    else if(d_vertex==0 && d_edge==0 && a_edge==0 && mouse_b&1 && mouse_x>g.getSommetTab()[i]->getpos_x() && mouse_x<g.getSommetTab()[i]->getpos_x()+TAILLEX && mouse_y>g.getSommetTab()[i]->getpos_y() && mouse_y<g.getSommetTab()[i]->getpos_y()+TAILLEY)
                    {
                        click = 1;
                        mem = i;
                    }
                }
                for(auto& elem : g.getEdgeTab())
                {
                    if(d_vertex==0 && d_edge==0 && a_edge==0 && mouse_b&2 && click==0 && mouse_x>(abs(elem.geta().getpos_x()+elem.getb().getpos_x())/2)+15 && mouse_x<(abs(elem.geta().getpos_x()+elem.getb().getpos_x())/2)+45 && mouse_y>(abs(elem.geta().getpos_y()+elem.getb().getpos_y())/2)+10 && mouse_y<(abs(elem.geta().getpos_y()+elem.getb().getpos_y())/2)+30)
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
                    else if(d_vertex==0 && d_edge==0 && a_edge==0 && mouse_b&1 && click==0 && mouse_x>(abs(elem.geta().getpos_x()+elem.getb().getpos_x())/2)+15 && mouse_x<(abs(elem.geta().getpos_x()+elem.getb().getpos_x())/2)+45 && mouse_y>(abs(elem.geta().getpos_y()+elem.getb().getpos_y())/2)+10 && mouse_y<(abs(elem.geta().getpos_y()+elem.getb().getpos_y())/2)+30)
                    {
                        if(elem.getWeight()+5>0)
                        {
                            elem.setWeight(elem.getWeight()+5);
                            rest(100);
                        }

                    }
                }

                if(d_vertex==0 && d_edge==0 && a_edge==0 && click==1)
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
                if(click==1 && mouse_b&1)
                {
                    click = 0;
                }





                ///ON CLIQUE SUR AJOUT D'UN SOMMET/NOEUD
                if(d_vertex==0 && d_edge==0 && a_edge==0 && mouse_x>30 && mouse_x<60 && mouse_y>100 && mouse_y<149 && mouse_b&1)
                {
                    rest(200);
                    g.AddVertex();

                }

                ///ON CLIQUE SUR SUPRESSION D'UN SOMMET/NOEUD
                if(d_vertex==0 && d_edge==0 && a_edge==0 && mouse_x>30 && mouse_x<60 && mouse_y>149 && mouse_y<194 && mouse_b&1)
                {
                    rest(200);
                    d_vertex=1;
                }
                if(d_vertex == 1)
                {
                    for(int i=0; i<g.getSommetTab().size(); i++)
                    {
                        if(mouse_b&1 && mouse_x>g.getSommetTab()[i]->getpos_x() && mouse_x<g.getSommetTab()[i]->getpos_x()+TAILLEX && mouse_y>g.getSommetTab()[i]->getpos_y() && mouse_y<g.getSommetTab()[i]->getpos_y()+TAILLEY)
                        {
                            g.DeleteVertex(g.getSommetTab()[i]);
                            d_vertex=0;
                        }
                    }
                }

                ///ON CLIQUE SUR AJOUT D'UN EDGE/ARETE
                if(d_vertex==0 && d_edge==0 && a_edge==0 && mouse_x>30 && mouse_x<60 && mouse_y>272 && mouse_y<320 && mouse_b&1)
                {
                    rest(200);
                    a_edge=1;

                }
                if(a_edge==1)
                {
                    if(add1==0)
                    {
                        for(int i=0; i<g.getSommetTab().size(); i++)
                        {
                            if(mouse_b&1 && mouse_x>g.getSommetTab()[i]->getpos_x() && mouse_x<g.getSommetTab()[i]->getpos_x()+TAILLEX && mouse_y>g.getSommetTab()[i]->getpos_y() && mouse_y<g.getSommetTab()[i]->getpos_y()+TAILLEY)
                            {
                                s_1 = g.getSommetTab()[i];
                                add1=1;
                                rest(300);
                            }
                        }
                    }
                    else if(add1==1 && add2==0)
                    {
                        for(int i=0; i<g.getSommetTab().size(); i++)
                        {
                            if(mouse_b&1 && mouse_x>g.getSommetTab()[i]->getpos_x() && mouse_x<g.getSommetTab()[i]->getpos_x()+TAILLEX && mouse_y>g.getSommetTab()[i]->getpos_y() && mouse_y<g.getSommetTab()[i]->getpos_y()+TAILLEY)
                            {
                                s_2 = g.getSommetTab()[i];
                                add2=1;
                                rest(300);
                            }
                        }
                    }
                    if(add1==true && add2==true)
                    {
                        if(s_1->getidx()!=s_2->getidx())
                        {
                            g.AddEdge(s_1,s_2);

                        }
                        add1=false;
                        add2=false;
                        a_edge=0;

                    }
                }


                ///ON CLIQUE SUR SUPPRESSION D'UN EDGE/ARETE
                if(d_edge==0 && d_vertex==0 && a_edge==0 && mouse_x>30 && mouse_x<60 && mouse_y>320 && mouse_y<366 && mouse_b&1)
                {
                    rest(200);
                    d_edge=1;
                }
                if(d_edge==1)
                {
                    if(sel1==0)
                    {
                        for(int i=0; i<g.getSommetTab().size(); i++)
                        {
                            if(mouse_b&1 && mouse_x>g.getSommetTab()[i]->getpos_x() && mouse_x<g.getSommetTab()[i]->getpos_x()+TAILLEX && mouse_y>g.getSommetTab()[i]->getpos_y() && mouse_y<g.getSommetTab()[i]->getpos_y()+TAILLEY)
                            {
                                s_1 = g.getSommetTab()[i];
                                sel1=1;
                                rest(300);
                            }
                        }
                    }
                    else if(sel1==1 && sel2==0)
                    {
                        for(int i=0; i<g.getSommetTab().size(); i++)
                        {
                            if(mouse_b&1 && mouse_x>g.getSommetTab()[i]->getpos_x() && mouse_x<g.getSommetTab()[i]->getpos_x()+TAILLEX && mouse_y>g.getSommetTab()[i]->getpos_y() && mouse_y<g.getSommetTab()[i]->getpos_y()+TAILLEY)
                            {
                                s_2 = g.getSommetTab()[i];
                                sel2=1;
                                rest(300);
                            }
                        }
                    }
                    if(sel1==true && sel2==true)
                    {
                        if(s_1->getidx()!=s_2->getidx())
                        {
                            g.DeleteEdge(s_1,s_2);

                        }
                        sel1=false;
                        sel2=false;
                        d_edge=0;

                    }
                }
                ///CONNEXE
                if(d_vertex==0 && d_edge==0 && a_edge==0 && mouse_x>15 && mouse_x<75 && mouse_y>(SCREEN_H/1.40) && mouse_y<(SCREEN_H/1.40)+60 && mouse_b&1)
                {
                    TabAdj=g.getAdjMatrix();
                    CompConnexe = g.toutesLesComposantesFortementConnexes(TabAdj,g.getSommetTab().size());
                    for(int i=0;i<CompConnexe.size();i++)
                    {
                        for(int j=0;j<CompConnexe[i].size();j++)
                        {
                            std::cout << CompConnexe[i][j] << " ";
                        }
                        std::cout << std::endl;
                    }

                    allegro_message("lol");
                }

                ///ON CLIQUE SUR SAUVEGARDE
                if(d_vertex==0 && d_edge==0 && a_edge==0 && mouse_x>15 && mouse_x<75 && mouse_y>(SCREEN_H/1.25) && mouse_y<(SCREEN_H/1.25)+60 && mouse_b&1)
                {

                    g.SaveFile(choice);
                    play_sample(success,255, 128, 1000, false);
                    rest(100);

                }

                ///ON CLIQUE SUR EXIT
                if(g.getEdgeTab().size()!=0 && g.getSommetTab().size()!=0 && d_vertex==0 && d_edge==0 && a_edge==0 && mouse_x>15 && mouse_x<75 && mouse_y>(SCREEN_H/1.1) && mouse_y<(SCREEN_H/1.1)+60 && mouse_b&1)
                {
                    choix=1;
                    rest(200);
                }
            }
        }

    }
    return 0;
}
END_OF_MAIN();
