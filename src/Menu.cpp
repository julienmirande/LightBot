#include "Menu.h"

constexpr int W = 1000, H = 800;
const std::string POLICE = "D:/Fac/Algo_System/Algo-Prog/LightBot/FreeMonoBold.ttf";
const std::string DOSSIER = "D:/Fac/Algo_System/Algo-Prog/LightBot/Sprites/";
const Position DIMS_Rect {150,100};

Menu::Menu()
    :Application {W, H, L"Menu"}
{

    m_play = false;
    m_editeur = false;
    m_menuActif = true;
    m_menu_select_actif = false;

    if (!m_jeu.loadFromFile(DOSSIER + "Play.png"))
    {

    }
    if (!m_jeu2.loadFromFile(DOSSIER + "Play2.png"))
    {

    }

    if (!m_edit.loadFromFile(DOSSIER + "Edit.png"))
    {

    }
    if (!m_edit2.loadFromFile(DOSSIER + "Edit2.png"))
    {

    }
    if (!m_quit.loadFromFile(DOSSIER + "Quit.png"))
    {

    }
    if (!m_quit2.loadFromFile(DOSSIER + "Quit2.png"))
    {

    }

    if (!m_fond.loadFromFile(DOSSIER + "Menu.png"))
    {

    }

    m_jeu.isSmooth();
    m_jeu2.isSmooth();
    m_edit.isSmooth();
    m_edit2.isSmooth();
    m_quit.isSmooth();
    m_quit2.isSmooth();

    m_Fond.setTexture(m_fond);
    m_Fond.setPosition(0,0);

    m_Jeu.setTexture(m_jeu);
    m_Jeu.setPosition(100,250);

    m_Edit.setTexture(m_edit);
    m_Edit.setPosition(690,350);

    m_Quit.setTexture(m_quit);
    m_Quit.setPosition(100,600);



}

void Menu::loop()
{
    m_window.clear(sf::Color::White);

    dessiner();
    surbrillance();

    /* On afficher a l'ecran */
    m_window.display();
}

void Menu::dessiner()
{
    m_window.draw(m_Fond);
    m_window.draw(m_Jeu);
    m_window.draw(m_Edit);
    m_window.draw(m_Quit);
}

void Menu::mouse_button_pressed()
{
    if (contient(m_Quit,m_quit))
    {
        m_menuActif = false;
        m_window.close();
    }

    if (contient(m_Jeu,m_jeu))
    {
        m_menu_select_actif = true;
        m_window.close();
    }

    if (contient(m_Edit,m_edit))
    {
        m_editeur = true;
        m_window.close();
    }
}

void Menu::mouse_button_released()
{


}

void Menu::mouse_moved()
{


}

void Menu::key_pressed(const sf::Event::KeyEvent &event)
{
    switch (event.code)
    {
    case sf::Keyboard::Escape:
        m_menuActif = false;
        m_window.close();
        break;
    default:
        break;
    }

}

bool Menu::contient(sf::Sprite sprite ,sf::Texture texture)
{
    if ( m_mouse.x >= sprite.getPosition().x &&  m_mouse.x <= sprite.getPosition().x + (texture.getSize().x * sprite.getScale().x)
            && m_mouse.y >= sprite.getPosition().y && m_mouse.y <= sprite.getPosition().y + texture.getSize().y * sprite.getScale().y )
    {
        return true;
    }
    else
        return false;

}

bool Menu::surbrillance()
{
    if (contient(m_Jeu,m_jeu))
        m_Jeu.setTexture(m_jeu2);

    else if (contient(m_Quit,m_quit))
        m_Quit.setTexture(m_quit2);

    else if (contient(m_Edit,m_edit))
        m_Edit.setTexture(m_edit2);
    else
    {
        m_Jeu.setTexture(m_jeu);
        m_Quit.setTexture(m_quit);
        m_Edit.setTexture(m_edit);
    }

}
