#include "MenuSelect.h"

constexpr int W = 1000, H = 800;
const std::string POLICE = "D:/Fac/Algo_System/Algo-Prog/LightBot/FreeMonoBold.ttf";
const std::string DOSSIER = "D:/Fac/Algo_System/Algo-Prog/LightBot/Sprites/";

MenuSelect::MenuSelect()
            :Application(W,H, L"Menu sélection")
{
    int x =300;
    int y =200;
    m_play = false;
    /* Initialisation des niveaux */
    struct dirent *lecture;
    DIR *rep;
    rep = opendir("D:/Fac/Algo_System/Algo-Prog/LightBot/Niveaux");
    std::string maChaine;
    std::vector<std::string> m_nom_niveaux;
    while ((lecture = readdir(rep)))
    {
        maChaine= lecture->d_name;
        std::size_t found = maChaine.find(".txt");
        if (found!=std::string::npos && maChaine != "Niveau_editeur.txt")
        {
          m_nom_niveaux.push_back(maChaine.replace(maChaine.end()-4,maChaine.end(),""));
        }
    }
    closedir(rep);

    std::sort (m_nom_niveaux.begin(),m_nom_niveaux.end());

    if (! m_police.loadFromFile(POLICE)) {
        throw "Police "+POLICE+" manquante";
    }

    for (auto n : m_nom_niveaux)
    {
        m_rect.setOutlineColor(sf::Color::Black);
        m_rect.setOutlineThickness(2);
        m_rect.setSize(sf::Vector2f(340,50));
        m_rect.setPosition(x,y);

        m_txt.setFont(m_police);
        m_txt.setCharacterSize(25);

        m_txt.setString(n);
        m_txt.setColor(sf::Color::Black);
        m_txt.setPosition(m_rect.getPosition().x+5,m_rect.getPosition().y+5);

        m_boutons.push_back(m_rect);
        m_text.push_back(m_txt);
        y+=100;
    }

    if(!m_texture.loadFromFile(DOSSIER + "Select_Lvl.png"))
    {

    }

    m_fond.setTexture(m_texture);
}

void MenuSelect::loop()
{
    m_window.clear(sf::Color::White);

    dessiner();


    for (auto b:m_boutons)
    {
        if (contient(b))
        {
            b.setOutlineColor(sf::Color::Red);
        }
        else
        {
            b.setOutlineColor(sf::Color::Black);
        }
    }

    /* On afficher a l'ecran */
    m_window.display();
}

void MenuSelect::dessiner()
{
    m_window.draw(m_fond);

    for (auto b : m_boutons)
    {
        m_window.draw(b);
    }

    for (auto t : m_text)
    {
        m_window.draw(t);
    }
}

bool MenuSelect::contient(sf::RectangleShape rectangle)
{
    if ( m_mouse.x >= rectangle.getPosition().x &&  m_mouse.x <= rectangle.getPosition().x + rectangle.getSize().x
         && m_mouse.y >= rectangle.getPosition().y && m_mouse.y <= rectangle.getPosition().y + rectangle.getSize().y)
    {
        return true;
    }
    else
        return false;
}

void MenuSelect::mouse_button_pressed()
{
    int numlvl =0;
    for (auto b: m_boutons)
    {
        if (contient(b))
        {
            m_lvl = numlvl;
            m_play = true;
            m_window.close();
        }
        numlvl++;
    }
}

void MenuSelect::mouse_button_released()
{


}

void MenuSelect::mouse_moved()
{


}

void MenuSelect::key_pressed(const sf::Event::KeyEvent &event)
{
    switch (event.code)
    {
    case sf::Keyboard::Escape:
        m_window.close();
        break;
    default:
        break;
    }

}

int MenuSelect::numLevel()
{
    return m_lvl;
}

