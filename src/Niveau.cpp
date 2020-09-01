#include "Niveau.h"

namespace {
const std::string POLICE = "D:/Fac/Algo_System/Algo-Prog/LightBot/FreeMonoBold.ttf";
const int LIGNE = 6, COLONNE = 6;
const Position DIMS_PROGRAMME {330,160};
const Position COORD_PROGRAMME {660,20};
const Position DIMS_INSTRUCTION {150,150};
const Position COORD_INSTRUCTION {60,630};
const sf::Vector2f TAILLECASE = {60,70};

}

Niveau::Niveau(const std::string &nomFichier)
    : m_fichier { nomFichier }
{

    m_scoreMax = 20;

    /* Initialisation grille */

    m_grille = new Grille(LIGNE,COLONNE,nomFichier);

    /* Initialisation du robot */
    m_caseRobot = 8;
    m_robot = new Robot(m_grille->getCase(m_caseRobot));

    /* Initialisation des programmes */

    Programme * main = new Programme(10,COORD_PROGRAMME.x,COORD_PROGRAMME.y,"MAIN");
    m_programme.push_back(main);
    Programme * p1 = new Programme(5,COORD_PROGRAMME.x,COORD_PROGRAMME.y+DIMS_PROGRAMME.y+15,"P1");
    m_programme.push_back(p1);
    Programme * p2 = new Programme(5,COORD_PROGRAMME.x,COORD_PROGRAMME.y+(1.6*DIMS_PROGRAMME.y)+25,"P2");
    m_programme.push_back(p2);

    /* Initialisation des instructions */

    Instruction * avancer = new Instruction("AVANCER",COORD_INSTRUCTION.x,COORD_INSTRUCTION.y,"Avancer.png");
    m_instruction.push_back(avancer);
    Instruction * rotationgauche = new Instruction("ROTATIONG",COORD_INSTRUCTION.x+(DIMS_INSTRUCTION.x),COORD_INSTRUCTION.y,"RotateG.png");
    m_instruction.push_back(rotationgauche);
    Instruction * rotationdroite = new Instruction("ROTATIOND",COORD_INSTRUCTION.x+(2*DIMS_INSTRUCTION.x),COORD_INSTRUCTION.y,"RotateD.png");
    m_instruction.push_back(rotationdroite);
    Instruction * sauter = new Instruction("SAUTER",COORD_INSTRUCTION.x+(3*DIMS_INSTRUCTION.x),COORD_INSTRUCTION.y,"Jump.png");
    m_instruction.push_back(sauter);
    Instruction * allumer = new Instruction("ALLUMER",COORD_INSTRUCTION.x+(0.5*DIMS_INSTRUCTION.x),COORD_INSTRUCTION.y+(DIMS_INSTRUCTION.y/2),"Allumer.png");
    m_instruction.push_back(allumer);
    Instruction * programme1 = new Instruction("P1",COORD_INSTRUCTION.x+(1.5*DIMS_INSTRUCTION.x),COORD_INSTRUCTION.y+(DIMS_INSTRUCTION.y/2),"P1.png");
    m_instruction.push_back(programme1);
    Instruction * programme2 = new Instruction("P2",COORD_INSTRUCTION.x+(2.5*DIMS_INSTRUCTION.x),COORD_INSTRUCTION.y+(DIMS_INSTRUCTION.y/2),"P2.png");
    m_instruction.push_back(programme2);

}

void Niveau::afficher(sf::RenderWindow & window)
{
    /* Affichage de la grille */
    m_grille->afficher(window);

    /* Affichage du robot */
    m_robot->afficher(window);

    /* Affichage des programmes */
    for ( auto programmes: m_programme)
    {
        programmes->afficher(window);
    }

    /* Affichage des instructions*/
    for ( auto instructions: m_instruction)
    {
        instructions->afficher(window);
    }
}

Niveau::~Niveau()
{
    /* Suppression de la grille */
    delete m_grille;

    /* Suppression du robot */
    delete m_robot;

    /* Suppression des programmes */
    for ( auto programmes: m_programme)
    {
        delete programmes;
    }

    /* Suppression des instructions*/
    for ( auto instructions: m_instruction)
    {
        delete instructions;
    }

}

Robot *Niveau::getRobot()
{
    return m_robot;
}

Grille *Niveau::getGrille()
{
    return m_grille;
}

std::vector<Programme *> Niveau::getProgramme()
{
    return m_programme;
}


std::vector<Instruction *> Niveau::getInstruction()
{
    return m_instruction;
}


Instruction* Niveau::SourisDansInstruction(Position m_mouse)
{

    for ( auto i : m_instruction)
    {
        if (i->contient(m_mouse))
        {
            return i;
        }
    }
}

void Niveau::RotateD()
{
    m_robot->RotateD();
}

void Niveau::RotateG()
{
    m_robot->RotateG();
}

void Niveau::Avancer()
{
    m_robot->MoveFoward(m_grille);
}

void Niveau::Jump()
{
    m_robot->Jump(m_grille);
}

void Niveau::Allumer()
{
    m_robot->Light_up(m_grille);
}

void Niveau::ajouterInstruction(Instruction * instruction,sf::Vector2f souris)
{
    Instruction * m_instructionTemporaire;
    std::string nomInstruction = instruction->getNom();
    if (nomInstruction == "AVANCER" )
    {
        m_instructionTemporaire = new Instruction("AVANCER",souris.x+instruction->getCenter().x,souris.y+instruction->getCenter().y,"Avancer.png");
    }
    if (nomInstruction == "ROTATIOND" )
    {
        m_instructionTemporaire = new Instruction("ROTATIOND",souris.x+instruction->getCenter().x,souris.y+instruction->getCenter().y,"RotateD.png");
    }
    if (nomInstruction == "ROTATIONG" )
    {
        m_instructionTemporaire = new Instruction("ROTATIONG",souris.x+instruction->getCenter().x,souris.y+instruction->getCenter().y,"RotateG.png");
    }
    if (nomInstruction == "ALLUMER" )
    {
        m_instructionTemporaire = new Instruction("ALLUMER",souris.x+instruction->getCenter().x,souris.y+instruction->getCenter().y,"Allumer.png");
    }
    if (nomInstruction == "P1" )
    {
        m_instructionTemporaire = new Instruction("P1",souris.x+instruction->getCenter().x,souris.y+instruction->getCenter().y,"P1.png");
    }
    if (nomInstruction == "P2" )
    {
        m_instructionTemporaire = new Instruction("P2",souris.x+instruction->getCenter().x,souris.y+instruction->getCenter().y,"P2.png");
    }
    if (nomInstruction == "SAUTER" )
    {
        m_instructionTemporaire = new Instruction("SAUTER",souris.x+instruction->getCenter().x,souris.y+instruction->getCenter().y,"Jump.png");
    }
    m_instruction.push_back(m_instructionTemporaire);
}

void Niveau::SupprimerDerniereInstruction()
{
    if (m_instruction.size() > 7)
        m_instruction.pop_back();
}

bool Niveau::isEnd()
{
    for (auto n : m_grille->getGrille())
    {
        if(n->getID() == 50 || n->getID() == 53 || n->getID()==56)
            return false;
    }
    return true;

}

int Niveau::getCaseRobot()
{
    return m_caseRobot;
}

int Niveau::afficherScore(int nb_instructions_use)
{
   int score = m_scoreMax - nb_instructions_use;
   return score;
}

int Niveau::getScoreMax()
{
    return m_scoreMax;
}
