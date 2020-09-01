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




#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "Application.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Instruction
{
public:
    Instruction(const std::string &nom, int x , int y, const std::string &nomFichier);
    Instruction(const Instruction &source, sf::Vector2f souris);

    void afficher(sf::RenderWindow &window);
    bool contient(const Position &position);
    void glisser(sf::Vector2f souris,sf::Vector2f centre);
    void placerDansProgramme(int cpt, int x, int y);
    void decalageGaucheDansProgramme(int placeInstruction, int x, int y);
    sf::Vector2f getCenter();
    std::string getNom();
    ~Instruction();
private:
    enum class Action { AVANCER, ROTATIONGAUCHE,ROTATIONDROITE, SAUTER , ALLUMER } m_action;
    std::string m_nom;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};

#endif // INSTRUCTION_H
