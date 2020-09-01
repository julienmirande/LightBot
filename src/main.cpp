#include <iostream>

#include "Grille.h"
#include "Jeu.h"
#include "Menu.h"
#include "Editeur.h"
#include "MenuSelect.h"
using namespace std;

int main()
{
    bool quit = false;
    while (!quit)
    {
        Menu menu;
        menu.run();
        if (!menu.m_menuActif)
            quit = true;
        if (menu.m_menu_select_actif)
        {
            MenuSelect menuSelection;
            menuSelection.run();
            int num_lvl_depart = menuSelection.numLevel();

            if(menuSelection.m_play)
            {
                Jeu lightBot;
                lightBot.setNumLvl(num_lvl_depart);
                lightBot.run();
            }
        }

        if (menu.m_editeur)
        {
            Editeur editeur;
            editeur.run();
        }
    }

    return 0;
}

