#include "Cases.h"

const sf::Vector2f TAILLECASE = {65*1.4,70*1.4};
const std::string DOSSIER = "D:/Fac/Algo_System/Algo-Prog/LightBot/Sprites/";
const std::string POLICE = "D:/Fac/Algo_System/Algo-Prog/LightBot/FreeMonoBold.ttf";

Cases::Cases(int x, int y, int id , const std::string & type, int num_case)
    :m_x {x},
     m_y {y},
     m_id {id},
     m_type {type},
     m_num_case {num_case}
{
    if (!m_textureBl.loadFromFile(DOSSIER + "Case_blanche.png"))
        std::cout << "Erreur chargement Image" << std::endl;

    if (!m_textureG.loadFromFile(DOSSIER + "Case_Grise.png"))
        std::cout << "Erreur chargement Image" << std::endl;

    if (!m_textureB.loadFromFile(DOSSIER + "Case_Bleu.png"))
        std::cout << "Erreur chargement Image" << std::endl;

    if (!m_textureJ.loadFromFile(DOSSIER + "Case_Jaune.png"))
        std::cout << "Erreur chargement Image" << std::endl;
    switch (m_id)
    {
    case 48:
        m_num_etage = 0;
        break;
    case 49:
        m_num_etage = 1;
        break;
    case 50:
        m_num_etage = 1;
        break;
    case 51:
        m_num_etage = 1;
        break;
    case 52:
        m_num_etage = 2;
        m_y-=20;
        break;
    case 53:
        m_num_etage = 2;
        m_y-=20;
        break;
    case 54:
        m_num_etage = 2;
        m_y-=20;
        break;
    case 55:
        m_num_etage = 3;
        m_y-=40;
        break;
    case 56:
        m_num_etage = 3;
        m_y-=40;
        break;
    case 57:
        m_num_etage = 3;
        m_y-=40;
    }
    initialiserSprite();

    m_sprite.setScale(1.4,1.4);
    m_sprite.setPosition(sf::Vector2f(m_x,m_y));
}

void Cases::initialiserSprite()
{

    switch (m_id)
    {
    case 48:
        m_sprite.setTexture(m_textureBl);
        break;
    case 49:
        m_sprite.setTexture(m_textureG);
        break;
    case 50:
        m_sprite.setTexture(m_textureB);
        break;
    case 51:
        m_sprite.setTexture(m_textureJ);
        break;
    case 52:
        m_sprite.setTexture(m_textureG);
        break;
    case 53:
        m_sprite.setTexture(m_textureB);
        break;
    case 54:
        m_sprite.setTexture(m_textureJ);
    case 55:
        m_sprite.setTexture(m_textureG);
        break;
    case 56:
        m_sprite.setTexture(m_textureB);
        break;
    case 57:
        m_sprite.setTexture(m_textureJ);
    }

    m_textureG.isSmooth();
    m_textureB.isSmooth();
    m_textureJ.isSmooth();

    // sf::Texture m_textureGrise,m_textureBleue,m_textureJaune,m_textureBlanche;
     if (!m_textureGrise.loadFromFile(DOSSIER + "Case_Grise_editeur.png"))
         std::cout << "Erreur chargement Image" << std::endl;

     if (!m_textureBleue.loadFromFile(DOSSIER + "Case_Bleu_editeur.png"))
         std::cout << "Erreur chargement Image" << std::endl;

     if (!m_textureJaune.loadFromFile(DOSSIER + "Case_Jaune_editeur.png"))
         std::cout << "Erreur chargement Image" << std::endl;

     if (!m_textureBlanche.loadFromFile(DOSSIER + "Case_blanche_editeur.png"))
         std::cout << "Erreur chargement Image" << std::endl;

}

void Cases::afficher(sf::RenderWindow & window)
{
    window.draw(m_sprite);
}

int Cases::getX()
{
    return m_x;
}

int Cases::getY()
{
    return m_y;
}

sf::Vector2f Cases::getCenter()
{
    return {m_sprite.getPosition().x+TAILLECASE.x/2,m_sprite.getPosition().y+TAILLECASE.y/2};
}

int Cases::getID()
{
    return m_id;
}

int Cases::getEtage()
{
    return m_num_etage;
}

int Cases::getnum()
{
    return m_num_case;
}

void Cases::setID(int nombre)
{
    m_id = nombre;
}

void Cases::setEtage(int nombre)
{
    m_num_etage = nombre;
}

void Cases::ChangerCouleur()
{
    m_sprite.setTexture(m_textureJ);
    m_id=3;
}

bool Cases::estPaire()
{

    return (m_type == "PAIRE" );
}


bool Cases::contient(const sf::Vector2f &position)
{
    if ( position.x >= m_sprite.getPosition().x &&  position.x <= m_x + 65
            && position.y >= m_sprite.getPosition().y && position.y <= m_y + 52 )
    {
        return true;
    }
    else
        return false;

}

void Cases::SurlignerHexagone(int id)
{

    switch (m_id)
    {
    case 48:
        m_sprite.setTexture(m_textureBlanche);
        break;
    case 49:
        m_sprite.setTexture(m_textureGrise);
        break;
    case 50:
        m_sprite.setTexture(m_textureBleue);
        break;
    case 51:
        m_sprite.setTexture(m_textureJaune);
        break;
    }
}

void Cases::incrementerID()
{
    m_id++;
    if (m_id > 51)
        m_id = 48;
}

void Cases::incrementerEtage()
{
    m_num_etage++;
    if (m_num_etage> 3)
        m_num_etage = 0;
}

void Cases::afficherEtage(sf::RenderWindow & m_window)
{
    sf::Font m_police;
    sf::Text m_text;
    if (! m_police.loadFromFile(POLICE)) {
        throw "Police "+DOSSIER + " FreeMonoBold.ttf manquante";
    }

    m_text.setFont(m_police);
    m_text.setCharacterSize(25);
    m_text.setString(std::to_string(m_num_etage));
    m_text.setColor(sf::Color::Black);
    m_text.setPosition(this->getCenter().x-5,this->getCenter().y-30);
    m_window.draw(m_text);
}

bool Cases::estaccessible(int etage)
{
    return (m_id != 48 && m_num_etage == etage);
}


