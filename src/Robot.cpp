#include "Robot.h"

const sf::Vector2f TAILLECASE = {65*1.4,70*1.4};
const int TAILLEDIAGONALEHEXAGONE = 40;
const float SCALECASE = 1.4;
const double PI = atan(1)*4;
const std::string DOSSIER = "D:/Fac/Algo_System/Algo-Prog/LightBot/Sprites/";
const sf::Vector2f POSITIONCASEPAIRE = {20,20};
const sf::Vector2f POSITIONCASEIMPAIRE = {POSITIONCASEPAIRE.x+TAILLECASE.x*cos(PI/3.),POSITIONCASEPAIRE.y+TAILLECASE.y*sin(PI/3.)};

Robot::Robot(Cases *ncase)
    :m_coord_x {ncase->getCenter().x},
     m_coord_y {ncase->getCenter().y},
     m_idCase{ncase->getID()},
     m_etage{ncase->getEtage()},
     m_case{ncase},
     m_numCase{ncase->getnum()}
{
    if (!m_textureBasD.loadFromFile(DOSSIER + "Bas_D.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }

    m_Robot.setTexture(m_textureBasD);
    m_Robot.setOrigin(m_Robot.getPosition().x+TAILLECASE.x/2-10,m_Robot.getPosition().y+TAILLECASE.y/2+25);
    m_Robot.setPosition(sf::Vector2f(m_coord_x,m_coord_y));
    m_Robot.scale(0.9,0.9);
    m_direction = 4;


    if (!m_texturehautG.loadFromFile(DOSSIER + "Haut_G.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }

    if (!m_texturehautD.loadFromFile(DOSSIER + "Haut_D.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }

    if (!m_textureDroite.loadFromFile(DOSSIER + "Droite.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }

    if (!m_textureBasD.loadFromFile(DOSSIER + "Bas_D.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }

    if (!m_textureBasG.loadFromFile(DOSSIER + "Bas_G.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }

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
    if (!m_textureLight.loadFromFile(DOSSIER + "Light.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }
}

void Robot::afficher(sf::RenderWindow & window)
{
    window.draw(m_Robot);
}

//--------------------------Getteurs -------------------------

int Robot::getX()
{
    return m_coord_x;
}

int Robot::getY()
{
    return m_coord_y;
}

void Robot::setX(int nombre)
{
    m_coord_x = nombre;
}

void Robot::setY(int nombre)
{
    m_coord_y = nombre;
}

void Robot::ReplaceRobot(Cases *ncase)
{
    m_coord_x = ncase->getCenter().x;
    m_coord_y = ncase->getCenter().y;
    m_idCase = ncase->getID();
    m_etage = ncase->getEtage();
    m_case = ncase;
    m_numCase = ncase->getnum();
}

sf::Sprite Robot::getSprite()
{
    return m_Robot;
}

int Robot::ChangerDirection(int p)
{
    m_direction+=p;

    if(m_direction > 6)
        m_direction = 1;
    if(m_direction < 1)
        m_direction=6;

    return m_direction;
}


//-------------------Methode Instructions--------------------------

void Robot::MoveFoward(Grille * grille)
{
    Cases *nextCase;
    int numCase = m_case->getnum();
    bool move = false;
    switch (m_direction)
    {
    case 1: //HAUTGAUCHE--------------------------------------------------------------------------------------------

        if (!m_case->estPaire())
        {
            if(numCase > 6 )
            {
                nextCase = grille->getCase(numCase-6);
                move = true;
            }

        }

        else
        {

            if (numCase > 6 && numCase != 13 && numCase != 25 && numCase != 37 && numCase != 49)
            {
                nextCase = grille->getCase(m_numCase -7);
                move = true;
            }
        }


        if (move && nextCase->estaccessible(m_etage))
        {
            m_Robot.setPosition(nextCase->getCenter().x,nextCase->getCenter().y);
            m_case = nextCase;
            m_idCase = nextCase->getID();
            m_numCase = nextCase->getnum();
            m_etage = nextCase->getEtage();

        }

        else
            m_Robot.setPosition(m_Robot.getPosition());


        break;
    case 2: //HAUTDROITE -------------------------------------------------------------------------------------------

        if (!m_case->estPaire())
        {
            if(numCase > 6 && numCase != 12 && numCase != 24 && numCase != 36 && numCase != 48)
            {
                nextCase = grille->getCase(numCase -5);
                move = true;
            }

        }

        else
        {

            if (numCase > 6 )
            {
                nextCase = grille->getCase(m_numCase -6);
                move = true;
            }
        }


        if (move && nextCase->estaccessible(m_etage))
        {
            m_Robot.setPosition(nextCase->getCenter().x,nextCase->getCenter().y);
            m_case = nextCase;
            m_idCase = nextCase->getID();
            m_numCase = nextCase->getnum();
            m_etage = nextCase->getEtage();

        }

        else
            m_Robot.setPosition(m_Robot.getPosition());

        break;

    case 3: //DROITE ---------------------------------------------------------------------------------------

        if (numCase %6 != 0)
        {
            nextCase = grille->getCase(m_numCase + 1);
            move = true;
        }

        if (move && nextCase->estaccessible(m_etage))
        {
            m_Robot.setPosition(nextCase->getCenter().x,nextCase->getCenter().y);
            m_case = nextCase;
            m_idCase = nextCase->getID();
            m_numCase = nextCase->getnum();
            m_etage = nextCase->getEtage();

        }

        else
            m_Robot.setPosition(m_Robot.getPosition());
        break;

    case 4: //BASDROITE ---------------------------------------------------------------------------------------

        if (!m_case->estPaire())
        {
            if(numCase < 43 && numCase != 12 && numCase != 24 && numCase != 36 && numCase != 48)
            {
                nextCase = grille->getCase(numCase +7);
                move = true;
            }

        }

        else
        {

            if (numCase < 43 )
            {
                nextCase = grille->getCase(m_numCase +6);
                move = true;
            }
        }


        if (move && nextCase->estaccessible(m_etage))
        {
            m_Robot.setPosition(nextCase->getCenter().x,nextCase->getCenter().y);
            m_case = nextCase;
            m_idCase = nextCase->getID();
            m_numCase = nextCase->getnum();
            m_etage = nextCase->getEtage();

        }
        else
            m_Robot.setPosition(m_Robot.getPosition());

        break;

    case 5: //BASGAUCHE ---------------------------------------------------------------------------------------

        if (!m_case->estPaire())
        {
            if(numCase < 43 )
            {
                nextCase = grille->getCase(numCase +6);
                move = true;
            }

        }

        else
        {

            if (numCase < 43 && numCase != 1 && numCase != 13 && numCase != 25 && numCase != 37 && numCase!=49)
            {
                nextCase = grille->getCase(m_numCase +5);
                move = true;
            }
        }


        if (move && nextCase->estaccessible(m_etage))
        {
            m_Robot.setPosition(nextCase->getCenter().x,nextCase->getCenter().y);
            m_case = nextCase;
            m_idCase = nextCase->getID();
            m_numCase = nextCase->getnum();
            m_etage = nextCase->getEtage();

        }
        else
            m_Robot.setPosition(m_Robot.getPosition());

        break;

    case 6: // GAUCHE ---------------------------------------------------------------------------------------

        if (numCase %6 != 1)
        {
            nextCase = grille->getCase(m_numCase - 1);
            move = true;
        }

        if (move && nextCase->estaccessible(m_etage))
        {
            m_Robot.setPosition(nextCase->getCenter().x,nextCase->getCenter().y);
            m_case = nextCase;
            m_idCase = nextCase->getID();
            m_numCase = nextCase->getnum();
            m_etage = nextCase->getEtage();

        }

        else
            m_Robot.setPosition(m_Robot.getPosition());

        break;
    }

}

void Robot::ChargeTexture()
{



    switch (m_direction)
    {
    case 1:
        m_Robot.setTexture(m_texturehautG);
        break;
    case 2:
        m_Robot.setTexture(m_texturehautD);
        break;
    case 3:
        m_Robot.setTexture(m_textureDroite);
        break;
    case 4:
        m_Robot.setTexture(m_textureBasD);
        break;
    case 5:
        m_Robot.setTexture(m_textureBasG);
        break;
    case 6:
        m_Robot.setTexture(m_textureGauche1);
        break;
    }
}

void Robot::RotateG()
{
    ChangerDirection(-1);
    ChargeTexture();
}

void Robot::RotateD()
{
    ChangerDirection(1);
    ChargeTexture();
}

void Robot::Light_up(Grille * grille)
{
    if (grille->getCase(m_numCase)->getID() == 50 ||grille->getCase(m_numCase)->getID() == 53 || grille->getCase(m_numCase)->getID() == 56)
        grille->getCase(m_numCase)->ChangerCouleur();
}

//Fonction de Saut -----------------------------------------------------------------------------------------------------------------

void Robot::Jump(Grille * grille)
{
    Cases *nextCase;
    int numCase = m_case->getnum();
    bool move = false;
    // if (m_numeroCase >= 0 && m_numeroCase < 55)
    // {
    switch (m_direction)
    {
    case 1: //HAUTGAUCHE--------------------------------------------------------------------------------------------

        if (!m_case->estPaire())
        {
            if(numCase > 6 )
            {
                nextCase = grille->getCase(numCase -6);
                move = true;
            }

        }

        else
        {

            if (numCase > 6 && numCase != 13 && numCase != 25 && numCase != 37 && numCase != 49)
            {
                nextCase = grille->getCase(m_numCase -7);
                move = true;
            }
        }


        if (move && nextCase->getID() != 48 && (nextCase->getEtage() == m_etage+1 || nextCase->getEtage() == m_etage-1) )
        {
            m_Robot.setPosition(nextCase->getCenter().x,nextCase->getCenter().y);
            m_case = nextCase;
            m_idCase = nextCase->getID();
            m_numCase = nextCase->getnum();
            m_etage = nextCase->getEtage();

        }

        else
            m_Robot.setPosition(m_Robot.getPosition());


        break;
    case 2: //HAUTDROITE -------------------------------------------------------------------------------------------

        if (!m_case->estPaire())
        {
            if(numCase > 6 && numCase != 12 && numCase != 24 && numCase != 36 && numCase != 48)
            {
                nextCase = grille->getCase(numCase -5);
                move = true;
            }

        }

        else
        {

            if (numCase > 6 )
            {
                nextCase = grille->getCase(m_numCase -6);
                move = true;
            }
        }


        if (move && nextCase->getID() != 48 && (nextCase->getEtage() == m_etage+1 || nextCase->getEtage() == m_etage-1))
        {
            m_Robot.setPosition(nextCase->getCenter().x,nextCase->getCenter().y);
            m_case = nextCase;
            m_idCase = nextCase->getID();
            m_numCase = nextCase->getnum();
            m_etage = nextCase->getEtage();

        }

        else
            m_Robot.setPosition(m_Robot.getPosition());

        break;

    case 3: //DROITE ---------------------------------------------------------------------------------------

        if (numCase %6 != 0)
        {
            nextCase = grille->getCase(m_numCase + 1);
            move = true;
        }

        if (move && nextCase->getID() != 48 && (nextCase->getEtage() == m_etage+1 || nextCase->getEtage() == m_etage-1))
        {
            m_Robot.setPosition(nextCase->getCenter().x,nextCase->getCenter().y);
            m_case = nextCase;
            m_idCase = nextCase->getID();
            m_numCase = nextCase->getnum();
            m_etage = nextCase->getEtage();

        }

        else
            m_Robot.setPosition(m_Robot.getPosition());
        break;

    case 4: //BASDROITE ---------------------------------------------------------------------------------------

        if (!m_case->estPaire())
        {
            if(numCase < 43 && numCase != 12 && numCase != 24 && numCase != 36 && numCase != 48)
            {
                nextCase = grille->getCase(numCase +7);
                move = true;
            }

        }

        else
        {

            if (numCase < 43 )
            {
                nextCase = grille->getCase(m_numCase +6);
                move = true;
            }
        }


        if (move && nextCase->getID() != 48 && (nextCase->getEtage() == m_etage+1 || nextCase->getEtage() == m_etage-1))
        {
            m_Robot.setPosition(nextCase->getCenter().x,nextCase->getCenter().y);
            m_case = nextCase;
            m_idCase = nextCase->getID();
            m_numCase = nextCase->getnum();
            m_etage = nextCase->getEtage();

        }
        else
            m_Robot.setPosition(m_Robot.getPosition());

        break;

    case 5: //BASGAUCHE ---------------------------------------------------------------------------------------

        if (!m_case->estPaire())
        {
            if(numCase < 43 )
            {
                nextCase = grille->getCase(numCase +6);
                move = true;
            }

        }

        else
        {

            if (numCase < 43 && numCase != 1 && numCase != 13 && numCase != 25 && numCase != 37 && numCase!=49)
            {
                nextCase = grille->getCase(m_numCase +5);
                move = true;
            }
        }


        if (move && nextCase->getID() != 48 && (nextCase->getEtage() == m_etage+1 || nextCase->getEtage() == m_etage-1))
        {
            m_Robot.setPosition(nextCase->getCenter().x,nextCase->getCenter().y);
            m_case = nextCase;
            m_idCase = nextCase->getID();
            m_numCase = nextCase->getnum();
            m_etage = nextCase->getEtage();

        }
        else
            m_Robot.setPosition(m_Robot.getPosition());

        break;

    case 6: // GAUCHE ---------------------------------------------------------------------------------------

        if (numCase %6 != 1)
        {
            nextCase = grille->getCase(m_numCase - 1);
            move = true;
        }

        if (move && nextCase->getID() != 48 && (nextCase->getEtage() == m_etage+1 || nextCase->getEtage() == m_etage-1))
        {
            m_Robot.setPosition(nextCase->getCenter().x,nextCase->getCenter().y);
            m_case = nextCase;
            m_idCase = nextCase->getID();
            m_numCase = nextCase->getnum();
            m_etage = nextCase->getEtage();

        }

        else
            m_Robot.setPosition(m_Robot.getPosition());

        break;
    }

}


