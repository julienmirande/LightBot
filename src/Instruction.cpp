#include "Instruction.h"

const std::string DOSSIER = "D:/Fac/Algo_System/Algo-Prog/LightBot/Sprites/";
const Position DIMS_INSTRUCTION {150,150};
const Position COORD_PROGRAMME {660,20};
const Position DIMS_PROGRAMME {330,160};

Instruction::Instruction(const std::string & nom, int x, int y , const std::string & nomFichier)
            :m_nom{nom}
{

    if (!m_texture.loadFromFile(DOSSIER + nomFichier))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setPosition({x,y});

}



void Instruction::afficher(sf::RenderWindow & window)
{
    window.draw(m_sprite);
}

bool Instruction::contient(const Position &position)
{
    if ( position.x >= m_sprite.getPosition().x &&  position.x <= m_sprite.getPosition().x + (this->m_texture.getSize().x * m_sprite.getScale().x)
            && position.y >= m_sprite.getPosition().y && position.y <= m_sprite.getPosition().y + this->m_texture.getSize().y * m_sprite.getScale().y )
    {
        return true;
    }
    else
        return false;

}

std::string Instruction::getNom()
{
    return m_nom;
}

void Instruction::glisser(sf::Vector2f souris, sf::Vector2f centre)
{
    m_sprite.setPosition({souris.x-centre.x,souris.y-centre.y});
}

sf::Vector2f Instruction::getCenter()
{
    return  {(m_sprite.getPosition().x + this->m_texture.getSize().x * m_sprite.getScale().x)/2,
             (m_sprite.getPosition().y + this->m_texture.getSize().y * m_sprite.getScale().y)/2};
}

void Instruction::placerDansProgramme(int cpt , int x, int y)
{
    if (cpt <= 5)
    {
        this->m_sprite.setPosition({x+10+(cpt-1)*this->m_texture.getSize().x * m_sprite.getScale().x,y+25});
    }
    else
    {
        cpt -= 5;
        this->m_sprite.setPosition({x+10+(cpt-1)*this->m_texture.getSize().x * m_sprite.getScale().x,
                             y+30+this->m_texture.getSize().y * m_sprite.getScale().y});
    }
}

void Instruction::decalageGaucheDansProgramme(int placeInstruction, int x, int y)
{
    if (placeInstruction == 4)
    {
        this->m_sprite.setPosition({COORD_PROGRAMME.x+10+4*this->m_texture.getSize().x * m_sprite.getScale().x,
                                    y+25});
    }
    else
    {
        this->m_sprite.setPosition({m_sprite.getPosition().x - (this->m_texture.getSize().x * m_sprite.getScale().x),
                                   m_sprite.getPosition().y});
    }
}

Instruction::~Instruction()
{
}


