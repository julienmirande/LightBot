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




#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Application.h"

class Menu : public Application
{
public:
    Menu();


    void loop()                                        override;
    void mouse_button_pressed()                        override;
    void mouse_button_released()                       override;
    void mouse_moved()                                 override;
    void key_pressed(const sf::Event::KeyEvent &event) override;
    void dessiner();
    bool contient(sf::Sprite sprite ,sf::Texture texture);
    bool surbrillance();

    bool m_play;
    bool m_editeur;
    bool m_menuActif;
    bool m_menu_select_actif;

private:

    sf::Sprite m_Fond;
    sf::Texture m_fond;

    sf::Sprite m_Jeu;
    sf::Texture m_jeu;
    sf::Texture m_jeu2;

    sf::Sprite m_Edit;
    sf::Texture m_edit;
    sf::Texture m_edit2;

    sf::Sprite m_Quit;
    sf::Texture m_quit;
    sf::Texture m_quit2;


};

#endif // MENU_H
