#include "Jeu.h"


namespace {
constexpr int W = 1000, H = 800;
const std::string POLICE = "D:/Fac/Algo_System/Algo-Prog/LightBot/FreeMonoBold.ttf";
const std::string DOSSIER = "D:/Fac/Algo_System/Algo-Prog/LightBot/Sprites/";
const Position DIMS_BOUTON {150,100};
Position BOUTON_EXECUTER {670,650};
bool glisser = false;

}


Jeu::Jeu()
    :Application {W, H, L"LightBot"}
{



    /* Initialisation des niveaux */
    struct dirent *lecture;
    DIR *rep;
    rep = opendir("D:/Fac/Algo_System/Algo-Prog/LightBot/Niveaux");
    std::string maChaine;
    while ((lecture = readdir(rep)))
    {
        maChaine= lecture->d_name;
        std::size_t found = maChaine.find(".txt");
        if (found!=std::string::npos && maChaine != "Niveau_editeur.txt")
        {
            m_nom_niveaux.push_back(maChaine);
        }

    }
    closedir(rep);

    std::sort (m_nom_niveaux.begin(),m_nom_niveaux.end());
    for (std::vector<std::string>::iterator it = m_nom_niveaux.begin() ; it != m_nom_niveaux.end(); ++it)
    {
        m_niveaux.push_back(new Niveau(*it));
    }


    /* Initialisation des barres horizontales et verticales */

    m_barreVerticale.setPosition({650,0});
    m_barreVerticale.setSize({2,H});
    m_barreVerticale.setFillColor(sf::Color::Black);

    m_barreHorizontale.setPosition({0,600});
    m_barreHorizontale.setSize({W,2});
    m_barreHorizontale.setFillColor(sf::Color::Black);


    m_rectangle_grille.setTexture(m_lave);
    m_rectangle_grille.setPosition({0,0});

    /* Initialisation des boutons */
    m_executer.setPosition(BOUTON_EXECUTER);
    m_executer.setSize(DIMS_BOUTON);
    m_executer.setFillColor(sf::Color::White);
    m_executer.setOutlineColor(sf::Color::Black);
    m_executer.setOutlineThickness(1);

    m_clear.setPosition({BOUTON_EXECUTER.x+DIMS_BOUTON.x+10,BOUTON_EXECUTER.y});
    m_clear.setSize(DIMS_BOUTON);
    m_clear.setFillColor(sf::Color::White);
    m_clear.setOutlineColor(sf::Color::Black);
    m_clear.setOutlineThickness(1);

    /* Initialisation du texte des boutons */
    if (! m_police.loadFromFile(POLICE)) {
        throw "Police "+POLICE+" manquante";
    }

    m_exe.setFont(m_police);
    m_exe.setCharacterSize(25);
    m_exe.setString("Executer");
    m_exe.setColor(sf::Color::Black);
    m_exe.setPosition(BOUTON_EXECUTER.x+5,BOUTON_EXECUTER.y-25+DIMS_BOUTON.y/2);

    m_cl.setFont(m_police);
    m_cl.setCharacterSize(25);
    m_cl.setString("Nettoyer");
    m_cl.setColor(sf::Color::Black);
    m_cl.setPosition(BOUTON_EXECUTER.x+DIMS_BOUTON.x+15,BOUTON_EXECUTER.y-25+DIMS_BOUTON.y/2);

    if (!m_texture.loadFromFile(DOSSIER + "Next_Lvl.png"))
    {

    }

    if (!m_texture2.loadFromFile(DOSSIER + "End.png"))
    {

    }

    if (!m_texture3.loadFromFile(DOSSIER + "Loose.png"))
    {

    }
}


void Jeu::loop()
{
    m_window.clear(sf::Color::White);

    m_lvl_courant = m_niveaux[m_num_lvl];

    /* Dessine l'ATH */
    dessiner_barre();
    dessiner_boutons();

    if (contient(m_executer))
    {
        m_executer.setOutlineColor(sf::Color::Red);
        m_exe.setColor(sf::Color::Red);
    }
    else
    {
        m_executer.setOutlineColor(sf::Color::Black);
        m_exe.setColor(sf::Color::Black);
    }
    if (contient(m_clear))
    {
        m_clear.setOutlineColor(sf::Color::Red);
        m_cl.setColor(sf::Color::Red);
    }
    else
    {
        m_clear.setOutlineColor(sf::Color::Black);
        m_cl.setColor(sf::Color::Black);
    }


    /* Affiche le niveau */
    m_lvl_courant->afficher(m_window);

    if(Next_Lvl())
    {
        if (m_num_lvl + 1 < m_niveaux.size())
        {
            AfficherNextLvl();;
            sleep(2);
            m_num_lvl++;
        }
        else
        {
            AfficherEnd();
            m_window.close();
        }
    }


    /* On afficher a l'ecran */
    m_window.display();
}


void Jeu::dessiner_barre()
{
    m_window.draw(m_barreVerticale);
    m_window.draw(m_rectangle_grille);
    m_window.draw(m_barreHorizontale);
}

void Jeu::dessiner_boutons()
{
    m_window.draw(m_executer);
    m_window.draw(m_exe);
    m_window.draw(m_clear);
    m_window.draw(m_cl);
}

std::vector<Niveau *> Jeu::getNiveaux()
{
    return m_niveaux;
}

void Jeu::mouse_button_pressed()
{

    /* Si dans instruction alors commencer glisser avec clone */
    if (m_lvl_courant->SourisDansInstruction(m_mouse)->contient(m_mouse) && !glisser)
    {
        glisser = true;
        Instruction * m_instruction = m_lvl_courant->SourisDansInstruction(m_mouse);
        m_lvl_courant->ajouterInstruction(m_instruction,m_mouse);
    }

    /* Lance les programmes */
    if (contient(m_executer))
    {
        int tour = 0;
        m_lvl_courant->getProgramme()[0]->ExecuterProgramme(m_lvl_courant->getRobot(),m_lvl_courant->getGrille(),
                                                            m_lvl_courant->getProgramme()[1],m_lvl_courant->getProgramme()[2],m_window, tour);
        if (!Next_Lvl())
        {
            AfficherLoose();
            m_niveaux.erase(m_niveaux.begin()+m_num_lvl);
            m_niveaux.emplace(m_niveaux.begin()+ m_num_lvl, new Niveau(m_nom_niveaux[m_num_lvl]) );
        }
    }

    for (auto p : m_lvl_courant->getProgramme())
    {
        if (!p->getInstructions().empty() && p->contient(m_mouse) && p->SourisDansInstruction(m_mouse)->contient(m_mouse))
        {
            Instruction *instruction = p->SourisDansInstruction(m_mouse);
            p->SupprimerInstructionDansProgramme(instruction);
        }

    }

    /* Clear les programmes */
    if (contient(m_clear))
    {
        for (auto p : m_lvl_courant->getProgramme())
        {
            p->ReinitialiserProgramme();
        }
    }

}


void Jeu::mouse_button_released()
{
    glisser = false;
    for (auto p : m_lvl_courant->getProgramme())
    {
        if (p->contient(m_mouse) && m_lvl_courant->getInstruction().size() > 7)
        {
            p->AddInstruction(m_lvl_courant->getInstruction().back());
        }

    }
    m_lvl_courant->SupprimerDerniereInstruction();

}

void Jeu::mouse_moved()
{
    if (glisser)
    {
        m_lvl_courant->getInstruction().back()->glisser(m_mouse,{25,25});
    }

}

void Jeu::key_pressed(const sf::Event::KeyEvent &event)
{

    switch (event.code)
    {
    case sf::Keyboard::Escape:
        m_window.close();
        break;

// ATTENTION CHEAT CODE //

    case sf::Keyboard::Q:
        m_lvl_courant->RotateG();
        break;


    case sf::Keyboard::D:
        m_lvl_courant->RotateD();
        break;


    case sf::Keyboard::Z:
        m_lvl_courant->Avancer();
        break;

    case sf::Keyboard::Right:
        m_num_lvl+=1;
        break;

    case sf::Keyboard::Left:
        m_num_lvl-=1;
        break;

    case sf::Keyboard::L:
        m_lvl_courant->Allumer();
        break;

    case sf::Keyboard::Space:
        m_lvl_courant->Jump();
        break;

    default:
        break;
    }

}

bool Jeu::contient(sf::RectangleShape rectangle)
{
    if ( m_mouse.x >= rectangle.getPosition().x &&  m_mouse.x <= rectangle.getPosition().x + rectangle.getSize().x
         && m_mouse.y >= rectangle.getPosition().y && m_mouse.y <= rectangle.getPosition().y + rectangle.getSize().y)
    {
        return true;
    }
    else
        return false;

}

bool Jeu::Next_Lvl()
{
    return m_lvl_courant->isEnd();
}

void Jeu::AfficherNextLvl()
{
    m_fond.setTexture(m_texture);
    int score = m_lvl_courant->afficherScore(m_lvl_courant->getProgramme()[0]->getInstructions().size());
    sf::Text m_text;
    m_text.setFont(m_police);
    m_text.setCharacterSize(60);
    m_text.setString(std::to_string(score) + "/" + std::to_string(m_lvl_courant->getScoreMax()) + " deplacements utilises !");
    m_text.setColor(sf::Color::Black);
    m_text.setPosition({0,650});
    m_window.draw(m_fond);
    m_window.draw(m_text);
    m_window.display();
}

void Jeu::AfficherEnd()
{
    int score = m_lvl_courant->afficherScore(m_lvl_courant->getProgramme()[0]->getInstructions().size());
    sf::Text m_text;
    m_text.setFont(m_police);
    m_text.setCharacterSize(60);
    m_text.setString(std::to_string(score) + "/" + std::to_string(m_lvl_courant->getScoreMax()) + " deplacements utilises !");
    m_text.setColor(sf::Color::Black);
    m_text.setPosition({0,650});
    m_fond.setTexture(m_texture2);
    m_window.draw(m_fond);
    m_window.draw(m_text);
    m_window.display();
    sleep(1);
}

void Jeu::AfficherLoose()
{
    m_fond.setTexture(m_texture3);
    m_window.draw(m_fond);
    m_window.display();
    sleep(1);
}

void Jeu::setNumLvl(int num)
{
    m_num_lvl = num;
}

Jeu::~Jeu()
{
    for (auto n: m_niveaux)
    {
        delete n;
    }
}
