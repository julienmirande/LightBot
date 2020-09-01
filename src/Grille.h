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




#ifndef GRILLE_H
#define GRILLE_H


#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <math.h>

#include "Cases.h"

class Grille
{
public:
    Grille(const int & nb_ligne, const int &nb_colonne, const std::string &nomFichier);
    void afficher(sf::RenderWindow &window);
    Cases* getCase(int num_case);
    std::vector<Cases *> getGrille();
    void resetGrille();
    int calculEtage(int temp);
    void sauvegarderGrille(std::string nomFichier);
    std::string getOutput(int id, int etage);
    ~Grille();
private:
    int m_nb_ligne;
    int m_nb_colonne;
    std::vector<Cases *> m_grille;



};

#endif // GRILLE_H
