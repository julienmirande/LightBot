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




#ifndef EDITEUR_H
#define EDITEUR_H

#include "Application.h"
#include "Niveau.h"
#include "Programme.h"
#include "Jeu.h"
#include "Niveau.h"

#include <SFML/Graphics.hpp>

class Editeur:public Application
{
public:
    //-------------------------------------------//
    //     CONSTRUCTEUR ET DESTRUCTEUR           //
    //-------------------------------------------//
    Editeur();
    ~Editeur();
private:
    //-------------------------------------------//
    //          Rctangles et sprites             //
    //-------------------------------------------//
    sf::RectangleShape  m_rectangle_grille, m_rectangle_text_box;
    sf::Texture m_texture,m_texture1,m_texture2,m_texture3,m_texture4,m_texture5,m_texture6,m_texture7,m_texture8,m_texture9;
    sf::Sprite m_sprite_save,m_sprite_recommencer,m_sprite_menu,m_sprite_couleur,m_sprite_etage;
    Grille * m_grille;

    //-------------------------------------------//
    //               Strings et font             //
    //-------------------------------------------//
    std::string m_string_box;
    sf::Text m_text,nom;
    sf::Font m_police;

    //-------------------------------------------//
    //               Booléens                    //
    //-------------------------------------------//
    bool m_choisirCouleur;
    bool m_choisirEtage;
    bool m_choisir_nomFichier;

    enum class Etat { CONCEPTION, ANIMATION} m_etat;

    //-------------------------------------------//
    //           Fonctions de la classe          //
    //-------------------------------------------//
    void dessiner_reste();
    void dessiner_boutons();
    bool contient(const Position & position, sf::Sprite m_sprite, sf::Texture m_texture);
    bool contient(sf::RectangleShape rectangle);
    void switchBouttonCouleur();
    void switchBouttonEtage();
    void text_box();

    //-------------------------------------------//
    //             Fonctions héritées            //
    //-------------------------------------------//
    void loop()                                        override;
    void mouse_button_pressed()                        override;
    void mouse_button_released()                       override;
    void mouse_moved()                                 override;
    void key_pressed(const sf::Event::KeyEvent &event) override;
};

#endif // EDITEUR_H
