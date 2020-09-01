#include "Animation.h"

const std::string DOSSIER = "/mnt/roon/users/jmirande/LightBot/Sprites/";

Animation::Animation(Grille *grille, Robot * robot, Position origine)
    :m_grille {grille},
      m_robot {robot},
      m_origine {origine}
{
    m_nb_top =0;
    m_delai_animation = 40;
    m_animation = false;

    if (!m_textureGauche1.loadFromFile(DOSSIER + "Gauche1.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }
    if (!m_textureGauche2.loadFromFile(DOSSIER + "Gauche2.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }

    if (!m_textureGauche3.loadFromFile(DOSSIER + "Gauche3.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }

    if (!m_textureGauche4.loadFromFile(DOSSIER + "Gauche4.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }
}


bool Animation::contient(const Position & position) const
{

}


void Animation::top()
{
    m_nb_top ++ ;
}

void Animation::avancer(sf::RenderWindow &window)
{
    std::cout << " TEST " << std ::endl;
    if (m_nb_top < m_delai_animation)
    {
        switch(m_nb_top)
        {
        case 10:
            m_robot->getSprite().setTexture(m_textureGauche1);
            break;

        case 20:
            m_robot->getSprite().setTexture(m_textureGauche2);
            break;

        case 30:
            m_robot->getSprite().setTexture(m_textureGauche3);
            break;

        case 40:
            m_robot->getSprite().setTexture(m_textureGauche4);
            break;
        std::cout << " TEST " << std ::endl;
        }
        sleep(2);
        m_robot->afficher(window);
        window.display();
    }
    else
    {
       m_animation = false;
    }



}

void Animation::sauter()
{

    if (m_nb_top > m_delai_animation)
        m_animation = false;
}

void Animation::allumer()
{
    if (m_nb_top > m_delai_animation)
        m_animation = false;
}


