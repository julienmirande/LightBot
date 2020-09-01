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




#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cases.h"
#include "Grille.h"
#include <unistd.h>
#include <time.h>
#include <ctime>
#include <math.h>

class Robot
{
public:
    Robot(Cases *ncase);
    void ChargeTexture();
    int getX();
    int getY();
    void setX(int nombre);
    void setY(int nombre);
    Cases *getCase();
    sf::Sprite getSprite();
    void afficher(sf::RenderWindow &m_window);
    void ReplaceRobot(Cases *ncase);
    int ChangerDirection(int p);

    void MoveFoward(Grille *grille);
    void RotateG();
    void RotateD();
    void Light_up(Grille *grille);
    void Jump(Grille * grille);
private:
    Cases* m_case;
    float m_coord_x;
    float m_coord_y;

    int m_etage;
    int m_direction;
    int m_idCase;
    int m_numCase;
    int m_numeroCase;

    //sf::Texture m_textureFace;

    sf::Texture m_texturehautG;
    sf::Texture m_texturehautD;
    sf::Texture m_textureDroite;
    sf::Texture m_textureBasD;
    sf::Texture m_textureBasG;


    sf::Texture m_textureGauche1;
    sf::Texture m_textureGauche2;
    sf::Texture m_textureGauche3;
    sf::Texture m_textureGauche4;

    sf::Texture m_textureLight;


    sf::Sprite m_Robot;
};

#endif // ROBOT_H
