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



#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include "Robot.h"
#include "Grille.h"
#include <iostream>

using Position = sf::Vector2f;

class Animation
{
public:
    Animation(Grille * grille, Robot *robot, Position origine);

    void avancer(sf::RenderWindow & window);
    void sauter()   ;
    void allumer();
    void top();

    virtual bool contient(const Position & position) const;
    virtual ~Animation() = default;

    bool m_animation;
private:
    Robot * m_robot;
    Grille * m_grille;
    Position m_origine;
    int m_delai_animation;
    int m_nb_top;


    sf::Texture m_textureGauche1,m_textureGauche2,m_textureGauche3,m_textureGauche4;
};

#endif // ANIMATION_H
