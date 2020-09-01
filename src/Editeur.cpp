#include "Editeur.h"

namespace {
constexpr int W = 1000, H = 800;
const std::string POLICE = "D:/Fac/Algo_System/Algo-Prog/LightBot/FreeMonoBold.ttf";
const std::string DOSSIER = "D:/Fac/Algo_System/Algo-Prog/LightBot/Sprites/";
const Position DIMS_BOUTON = {150,100};
const Position BOUTON_SAVE = {50,700};
const Position INPUTBOX = {640,100 };
const Position POSITIONCASE = {20,20};
const int LIGNE = 6, COLONNE = 6;

}

Editeur::Editeur()
    :Application {W, H, L"LightBot"}
{
    /*Initialisation des booléeens */
    m_choisirCouleur = true;
    m_choisirEtage = false;
    m_choisir_nomFichier = false;

    /* Initialisation de la grille */
    m_grille = new Grille(LIGNE,COLONNE,"Niveau_editeur.txt");

    /* Initialisation du rectangle autour de la grille */
    m_rectangle_grille.setPosition(POSITIONCASE);
    m_rectangle_grille.setSize({590,495});
    m_rectangle_grille.setFillColor(sf::Color::White);
    m_rectangle_grille.setOutlineThickness(2);
    m_rectangle_grille.setOutlineColor(sf::Color::Black);


    /* Initialisation du rectangle pour l'inputBox */
    m_rectangle_text_box.setPosition(INPUTBOX);
    m_rectangle_text_box.setSize({340,50});
    m_rectangle_text_box.setFillColor(sf::Color::White);
    m_rectangle_text_box.setOutlineThickness(2);
    m_rectangle_text_box.setOutlineColor(sf::Color::Black);

    //-------------------------------------------//
    // Initialisation des sprite pour boutons    //
    //-------------------------------------------//

    /* Sprite bouton sauvegarder */
    if (!m_texture1.loadFromFile(DOSSIER + "bouton_save.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }
    if (!m_texture8.loadFromFile(DOSSIER + "bouton_save2.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }
    m_sprite_save.setTexture(m_texture1);
    m_sprite_save.setPosition(BOUTON_SAVE);
    m_sprite_save.scale(2,2);

    /* Sprite bouton recommencer */
    if (!m_texture2.loadFromFile(DOSSIER + "bouton_recommencer.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }
    if (!m_texture9.loadFromFile(DOSSIER + "bouton_recommencer2.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }
    m_sprite_recommencer.setTexture(m_texture2);
    m_sprite_recommencer.setPosition(BOUTON_SAVE.x + 2*DIMS_BOUTON.x,BOUTON_SAVE.y);
    m_sprite_recommencer.scale(2,2);

    /* Sprite Menu */
    if (!m_texture3.loadFromFile(DOSSIER + "bouton_menu.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }
    if (!m_texture.loadFromFile(DOSSIER + "bouton_menu2.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }
    m_sprite_menu.setTexture(m_texture3);
    m_sprite_menu.setPosition(BOUTON_SAVE.x + 4.5*DIMS_BOUTON.x,BOUTON_SAVE.y);
    m_sprite_menu.scale(2,2);

    /* Sprite Couleur */
    if (!m_texture4.loadFromFile(DOSSIER + "Changer_couleur_ok.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }
    m_sprite_couleur.setTexture(m_texture4);
    m_sprite_couleur.setPosition(BOUTON_SAVE.x,BOUTON_SAVE.y-150);
    m_sprite_couleur.scale(2,2);

    /* Sprite Etage */
    if (!m_texture6.loadFromFile(DOSSIER + "Changer_etage.png"))
    {
        std::cout << "Erreur chargement Image !" << std::endl;
    }
    m_sprite_etage.setTexture(m_texture6);
    m_sprite_etage.setPosition(BOUTON_SAVE.x + 2*DIMS_BOUTON.x,BOUTON_SAVE.y-150);
    m_sprite_etage.scale(2,2);

    //-------------------------------------------//
    // Initialisation des textes et polices      //
    //-------------------------------------------//

    if (! m_police.loadFromFile(POLICE)) {
        throw "Police "+POLICE+" manquante";
    }

    nom.setFont(m_police);
    nom.setCharacterSize(25);
    nom.setString("Nom du fichier: ");
    nom.setColor(sf::Color::Black);
    nom.setPosition(INPUTBOX.x,INPUTBOX.y-INPUTBOX.y/2);

    m_string_box = "Niveau_?";
    m_text.setFont(m_police);
    m_text.setCharacterSize(25);
    m_text.setColor(sf::Color::Black);
    m_text.setPosition(INPUTBOX.x+5,INPUTBOX.y+5);
}


void Editeur::loop()
{
    //-------------------------------------------//
    //               Dessine à l'écran           //
    //-------------------------------------------//

    /* Nettoie la fenêtre */
    m_window.clear(sf::Color::White);

    /* Dessine l'ATH */
    dessiner_reste();
    dessiner_boutons();

    /* Affiche le niveau */
    m_grille->afficher(m_window);

    //-------------------------------------------//
    //               Evenements                  //
    //-------------------------------------------//

    /*Affichage en surbrillance */
    for (auto cases:m_grille->getGrille())
    {
        if (cases->contient(m_mouse))
            cases->SurlignerHexagone(cases->getID());
        else
            cases->initialiserSprite();
    }

    /* Affichage des cases */
    for (auto cases:m_grille->getGrille())
    {
        cases->afficherEtage(m_window);
    }

    /* Bouton menu clignotant */
    if (contient(m_mouse,m_sprite_menu,m_texture3))
    {
        m_sprite_menu.setTexture(m_texture);
    }
    else
        m_sprite_menu.setTexture(m_texture3);

    /* Bouton menu clignotant */
    if (contient(m_mouse,m_sprite_save,m_texture1))
        m_sprite_save.setTexture(m_texture8);
    else
        m_sprite_save.setTexture(m_texture1);

    /* Bouton menu clignotant */
    if (contient(m_mouse,m_sprite_recommencer,m_texture2))
        m_sprite_recommencer.setTexture(m_texture9);
    else
        m_sprite_recommencer.setTexture(m_texture2);

    /* Modifie en direct dans l'inputBox */
    m_string_box = s;
    m_text.setString(m_string_box);

    /* On afficher a l'ecran */
    m_window.display();

}


void Editeur::dessiner_reste()
{
    m_window.draw(m_rectangle_grille);
    m_window.draw(m_rectangle_text_box);
    m_window.draw(m_text);
    m_window.draw(nom);
}
void Editeur::dessiner_boutons()
{
    m_window.draw(m_sprite_save);
    m_window.draw(m_sprite_recommencer);
    m_window.draw(m_sprite_menu);
    m_window.draw(m_sprite_couleur);
    m_window.draw(m_sprite_etage);
}

void Editeur::mouse_button_pressed()
{
    if (contient(m_mouse,m_sprite_menu,m_texture3))
    {
        m_window.close();
    }

    if (contient(m_mouse,m_sprite_recommencer,m_texture2))
    {
        m_grille->resetGrille();
    }

    if (contient(m_mouse,m_sprite_couleur,m_texture4) )
    {
        switchBouttonCouleur();
    }

    if (contient(m_mouse,m_sprite_etage,m_texture6))
    {
        switchBouttonEtage();
    }

    if (m_choisirCouleur)
    {
        for (auto cases: m_grille->getGrille())
        {
            if (cases->contient(m_mouse))
            {
                cases->incrementerID();
                if (cases->getEtage() == 0)
                {
                    cases->setEtage(1);
                }
                if(cases->getID() == 48)
                {
                    cases->setEtage(0);
                }
            }
        }
    }

    if (m_choisirEtage)
    {
        for (auto cases: m_grille->getGrille())
        {
            if (cases->contient(m_mouse))
            {
                cases->incrementerEtage();
                if (cases->getEtage() == 0)
                {
                    cases->setID(48);
                }
                else
                    cases->setID(cases->getID());
            }
        }
    }

    if (contient(m_mouse,m_sprite_save,m_texture1))
    {

        if (m_string_box.size() !=0)
        {
           m_grille->sauvegarderGrille(m_string_box);
           m_window.close();
        }
        else
            std::cerr << "NOM DE FICHIER VIDE" << std::endl;
    }

    if (contient(m_rectangle_text_box))
    {
        m_rectangle_text_box.setOutlineColor(sf::Color::Red);
        m_entrer_nomFichier = true;
    }

}

void Editeur::mouse_button_released()
{

}

void Editeur::mouse_moved()
{


}

void Editeur::key_pressed(const sf::Event::KeyEvent &event)
{

    switch (event.code)
    {
    case sf::Keyboard::Escape:
        m_window.close();
        break;

    case sf::Keyboard::BackSpace:
        if(m_entrer_nomFichier &&  s.size()!=0){
                m_effacer = true;
        }
        break;

    case sf::Keyboard::Return:
        m_entrer_nomFichier = false;
        m_rectangle_text_box.setOutlineColor(sf::Color::Black);
    default:
        break;
    }

}

bool Editeur::contient(const Position &position, sf::Sprite m_sprite, sf::Texture m_texture)
{
    if ( position.x >= m_sprite.getPosition().x &&  position.x <= m_sprite.getPosition().x + (m_texture.getSize().x * m_sprite.getScale().x)
         && position.y >= m_sprite.getPosition().y && position.y <= m_sprite.getPosition().y + m_texture.getSize().y * m_sprite.getScale().y )
    {
        return true;
    }
    else
        return false;

}

bool Editeur::contient(sf::RectangleShape rectangle)
{
    if ( m_mouse.x >= rectangle.getPosition().x &&  m_mouse.x <= rectangle.getPosition().x + rectangle.getSize().x
         && m_mouse.y >= rectangle.getPosition().y && m_mouse.y <= rectangle.getPosition().y + rectangle.getSize().y)
    {
        return true;
    }
    else
        return false;

}

void Editeur::switchBouttonCouleur()
{
    if (!m_choisirCouleur && m_choisirEtage)
    {
        if (!m_texture5.loadFromFile(DOSSIER + "Changer_couleur_ok.png"))
        {
            std::cout << "Erreur chargement Image !" << std::endl;
        }
        m_sprite_couleur.setTexture(m_texture5);
        m_choisirCouleur = true;

        if (!m_texture7.loadFromFile(DOSSIER + "Changer_etage.png"))
        {
            std::cout << "Erreur chargement Image !" << std::endl;
        }
        m_sprite_etage.setTexture(m_texture7);
        m_choisirEtage = false;
    }



}

void Editeur::switchBouttonEtage()
{
    if (!m_choisirEtage && m_choisirCouleur)
    {
        if (!m_texture6.loadFromFile(DOSSIER + "Changer_etage_ok.png"))
        {
            std::cout << "Erreur chargement Image !" << std::endl;
        }
        m_sprite_etage.setTexture(m_texture6);
        m_choisirEtage = true;

        if (!m_texture4.loadFromFile(DOSSIER + "Changer_couleur.png"))
        {
            std::cout << "Erreur chargement Image !" << std::endl;
        }
        m_sprite_couleur.setTexture(m_texture4);
        m_choisirCouleur = false;
    }
}

Editeur::~Editeur()
{
    delete m_grille;
}




