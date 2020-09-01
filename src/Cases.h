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




#ifndef CASES_H
#define CASES_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <string>
#include <iostream>


class Cases
{
public:
    Cases(int x, int y, int id, const std::string &type, int num_case);
    void afficher(sf::RenderWindow &window);
    int getX();
    int getY();
    sf::Vector2f getCenter();
    int getID();
    int getEtage();
    void setID(int nombre);
    bool estPaire();
    void ChangerCouleur();
    bool contient(const sf::Vector2f &position);
    void SurlignerHexagone(int id);
    void initialiserSprite();
    void incrementerID();
    void incrementerEtage();
    void afficherEtage(sf::RenderWindow &m_window);
    void setEtage(int nombre);

    bool estaccessible(int etage);
    int getnum();
private:
    int m_x;
    int m_y;
    int m_id;

    int m_num_etage;
    int m_num_case;
    std::string m_type;
    sf::Texture m_textureBl,m_textureG,m_textureB,m_textureJ;
    sf::Texture m_textureGrise,m_textureBleue,m_textureJaune,m_textureBlanche;
    sf::Sprite m_sprite;

};

#endif // CASES_H
