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




#ifndef JEU_H
#define JEU_H

#include "Application.h"
#include "Niveau.h"
#include "Programme.h"
#include "Animation.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <time.h>



#include <SFML/Graphics.hpp>

class Jeu: public Application
{
public:
    Jeu();
    std::vector<Niveau *> getNiveaux();
    void setNumLvl(int num);
    ~Jeu();

private:
    sf::RectangleShape  m_barreVerticale,m_barreHorizontale , m_executer, m_clear;
    sf::Texture m_lave;
    sf::Sprite m_rectangle_grille;
    sf::Text m_exe,m_cl;
    sf::Font m_police;
    std::vector<Niveau *> m_niveaux;
    unsigned int m_num_lvl;
    Niveau * m_lvl_courant;
    std::vector<std::string> m_nom_niveaux;

    bool Next_Lvl();

    void dessiner_barre();
    void dessiner_boutons();

    void AfficherNextLvl();
    void AfficherEnd();
    void AfficherLoose();


    bool contient(sf::RectangleShape rectangle);

    void loop()                                        override;
    void mouse_button_pressed()                        override;
    void mouse_button_released()                       override;
    void mouse_moved()                                 override;
    void key_pressed(const sf::Event::KeyEvent &event) override;
    //void text_box(const sf::Event &event)    override;

    sf::Texture m_texture,m_texture2,m_texture3;
    sf::Sprite m_fond;
};

#endif // JEU_H
