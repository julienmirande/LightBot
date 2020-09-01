#include "Programme.h"

namespace {
const std::string POLICE = "D:/Fac/Algo_System/Algo-Prog/LightBot/FreeMonoBold.ttf";
const Position DIMS_BOUTON {330,160};
const Position DIMS_INSTRUCTION {150,150};

}

Programme::Programme(unsigned int nb_instructions, int x,int y,const std::string & nom)
    :m_nb_instructions {nb_instructions}
{


    m_emplacement.setPosition(sf::Vector2f(x,y));
    m_emplacement.setFillColor(sf::Color::White);
    m_emplacement.setOutlineColor(sf::Color::Black);
    m_emplacement.setOutlineThickness(1);

    switch(m_nb_instructions)
    {
        case 5:
            m_emplacement.setSize({DIMS_BOUTON.x,10 + DIMS_BOUTON.y/2});
            break;
        case 10:
            m_emplacement.setSize(DIMS_BOUTON);
            break;
    }

    /* Initialisation du texte des boutons */
    if (! m_police.loadFromFile(POLICE)) {
        throw "Police "+POLICE+" manquante";
    }

    m_name.setFont(m_police);
    m_name.setCharacterSize(15);
    m_name.setString(nom);
    m_name.setColor(sf::Color::Black);
    m_name.setPosition(x+5,y+5);


}

void Programme::afficher(sf::RenderWindow &m_window)
{
    m_window.draw(m_emplacement);
    for (auto p : m_instructions)
        p->afficher(m_window);

    m_window.draw(m_name);
}

void Programme::AddInstruction(Instruction* instruction)
{
    if(  m_instructions.size() < m_nb_instructions)
    {
        m_instructions.push_back(instruction);
        instruction->placerDansProgramme(m_instructions.size(),m_emplacement.getPosition().x,m_emplacement.getPosition().y);
    }
}

void Programme::ReinitialiserProgramme()
{
    m_instructions.clear();
}

bool Programme::contient(const Position &position)
{
    bool temp = false;
    if ( position.x >= m_emplacement.getPosition().x &&  position.x <= m_emplacement.getPosition().x + DIMS_BOUTON.x
         && position.y >= m_emplacement.getPosition().y && position.y <= m_emplacement.getPosition().y + DIMS_BOUTON.y && m_nb_instructions ==10)
    {
        temp = true;
    }

    else if (position.x >= m_emplacement.getPosition().x &&  position.x <= m_emplacement.getPosition().x + DIMS_BOUTON.x
             && position.y >= m_emplacement.getPosition().y && position.y <= m_emplacement.getPosition().y + (10+DIMS_BOUTON.y/2) && m_nb_instructions ==5)
    {
        temp = true;
    }
    return temp;

}

void Programme::ExecuterProgramme(Robot * robot, Grille * grille, Programme * p1,Programme * p2,sf::RenderWindow & m_window, int &tour)
{
    std::string nomInstruction;
    for (auto i: m_instructions)
    {
        if ( tour < 15)
        {
            nomInstruction = i->getNom();
            if (nomInstruction == "AVANCER" )
            {
                robot->MoveFoward(grille);
                tour++;
            }
            if (nomInstruction == "ROTATIOND" )
            {
                robot->RotateD();
                tour++;
            }

            if (nomInstruction == "ROTATIONG" )
            {
                robot->RotateG();
                tour ++;
            }

            if (nomInstruction == "ALLUMER" )
            {
                robot->Light_up(grille);
                //a->allumer();
                tour ++;
            }
            if (nomInstruction == "P1" )
                p1->ExecuterProgramme(robot,grille,p1,p2,m_window,tour);
            if (nomInstruction == "P2" )
                p2->ExecuterProgramme(robot,grille,p1,p2,m_window,tour);
            if (nomInstruction == "SAUTER")
            {
                robot->Jump(grille);
                //a->sauter();
                tour++;
            }
        }

        m_window.clear(sf::Color::White);
        grille->afficher(m_window);
        robot->afficher(m_window);
        m_window.display();
        sleep(1);
    }
}


void Programme::SupprimerInstructionDansProgramme(Instruction * instruction)
{
    std::vector<Instruction *>::iterator it = find (m_instructions.begin(), m_instructions.end(), instruction);
    if (!m_instructions.empty())
    {
        m_instructions.erase(it);
    }

    int cpt = 0;
    for (it; it != m_instructions.begin() ; it--)
    {
        cpt ++;
    }
    for ( int i = cpt ; i<m_instructions.size(); i++)
    {
        m_instructions[i]->decalageGaucheDansProgramme(i,m_emplacement.getPosition().x,m_emplacement.getPosition().y);
    }

}

Instruction* Programme::SourisDansInstruction(Position m_mouse)
{
    for ( auto i : m_instructions)
    {
        if (i->contient(m_mouse))
        {
            return i;
        }
    }
}

std::vector<Instruction *> Programme::getInstructions()
{
    return m_instructions;
}

