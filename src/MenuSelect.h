//------------------------------------------------------------------//
//                                                                  //
//                                                                  //
//                            © COPYRIGHTED                         //
//                                                                  //
//                                                                  //
//                                Creators                          //
//                                                                  //
//                            Julien MIRANDE                        //
//                            Nicolas DESCLAUX                      //
//                                                                  //
//                                                                  //
//                                                                  //
//                                                                  //
//------------------------------------------------------------------//



#ifndef MENUSELECT_H
#define MENUSELECT_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#include "Application.h"
#include "Niveau.h"

class MenuSelect : public Application
{
public:
    MenuSelect();

    void loop()                                        override;
    void mouse_button_pressed()                        override;
    void mouse_button_released()                       override;
    void mouse_moved()                                 override;
    void key_pressed(const sf::Event::KeyEvent &event) override;
    void dessiner();
    bool contient(sf::RectangleShape rectangle);
    int numLevel();

    void DessinerBouton(int x, int y, const std::string &num);
    bool m_play;


private:
    sf::Sprite m_fond;
    sf::Texture m_texture;

    sf::RectangleShape m_rect;
    sf::Text m_txt;

    std::vector<sf::RectangleShape> m_boutons;
    std::vector<sf::Text> m_text;


    sf::Font m_police;

     int m_lvl;
};

#endif // MENUSELECT_H
