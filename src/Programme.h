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




#ifndef PROGRAMME_H
#define PROGRAMME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Instruction.h"
#include "Animation.h"

#include <Robot.h>

class Programme
{
public:
    Programme(unsigned int nb_instructions, int x, int y, const std::string & nom);
    void afficher(sf::RenderWindow & m_window);
    void AddInstruction(Instruction* instruction);
    void ReinitialiserProgramme();
    bool contient(const Position &position);
    void ExecuterProgramme(Robot *robot, Grille * grille,  Programme * p1,Programme * p2,sf::RenderWindow & m_window, int &tour);
    void SupprimerInstructionDansProgramme(Instruction * instruction);
    std::vector<Instruction *> getInstructions();
    Instruction* SourisDansInstruction(Position m_mouse);

private:
    std::vector<Instruction*> m_instructions;
    sf::Text m_name;
    sf::Font m_police;
    sf::RectangleShape m_emplacement;
    unsigned int m_nb_instructions;

};

#endif // PROGRAMME_H
