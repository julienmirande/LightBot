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




#ifndef NIVEAU_H
#define NIVEAU_H

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "Grille.h"
#include "Robot.h"
#include "Programme.h"

class Niveau
{
public:
    Niveau(const std::string & nomFichier);
    void afficher(sf::RenderWindow & window);
    void RotateG();
    void RotateD();
    void Avancer();
    void Allumer();
    void Jump();
    Robot* getRobot();
    Grille *getGrille();
    std::vector<Programme *> getProgramme();
    std::vector<Instruction *> getInstruction();
    Instruction *SourisDansInstruction(Position m_mouse);
    void ajouterInstruction(Instruction * instruction, sf::Vector2f souris);
    void SupprimerDerniereInstruction();
    bool isEnd();
    int getCaseRobot();
    int afficherScore(int nb_instructions_use);
    int getScoreMax();
    ~Niveau();
private:
    std::string m_fichier;
    Grille * m_grille;
    Robot * m_robot;
    int m_caseRobot;
    int m_scoreMax;

    enum class Etat { CONCEPTION, ANIMATION} m_etat;

    std::vector<Programme *> m_programme;
    std::vector<Instruction *> m_instruction;
};

#endif // NIVEAU_H
