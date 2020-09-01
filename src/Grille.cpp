#include "Grille.h"

const double PI = atan(1)*4;
const std::string DOSSIER = "D:/Fac/Algo_System/Algo-Prog/LightBot/Niveaux/";
const sf::Vector2f TAILLECASE = {65*1.4,70*1.4};
const sf::Vector2f POSITIONCASEPAIRE = {20,20};
const sf::Vector2f POSITIONCASEIMPAIRE = {POSITIONCASEPAIRE.x+TAILLECASE.x*cos(PI/3.),POSITIONCASEPAIRE.y+TAILLECASE.y*sin(PI/3.)};


Grille::Grille(const int &nb_ligne,const int &nb_colonne, const std::string & nomFichier)
    :m_nb_ligne {nb_ligne},
      m_nb_colonne {nb_colonne}
{
    /* Récupération des valeurs du fichier */
    std::string ligne,chemin;
    int temp=0;

    chemin = DOSSIER + nomFichier;
    std::ifstream fichier(chemin, std::ios::in);  // on ouvre en lecture

    int i ;
    int j = 0;

    // Nicolas code
    int cpt= 1;


    if(fichier)  // si l'ouverture a fonctionné
    {
        while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
        {

            i=0;
//            std::string r = "\r";
//            int pos = ligne.find(r);
//            ligne.replace(pos,2,"");
            for(auto l :ligne)
            {

                temp = l;
                if (j%2 == 0)
                {
                    m_grille.push_back(new Cases(POSITIONCASEPAIRE.x+TAILLECASE.x*i,POSITIONCASEPAIRE.y+(0.54*j*POSITIONCASEIMPAIRE.y),temp, "PAIRE",cpt));
                }
                else
                {
                    m_grille.push_back(new Cases(POSITIONCASEIMPAIRE.x+TAILLECASE.x*i,POSITIONCASEPAIRE.y+(0.54*j*POSITIONCASEIMPAIRE.y),temp, "IMPAIRE",cpt));
                }
                i++;
                cpt++;

            }
            j++;

        }
        fichier.close();
    }

    else
    {
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
    }

    int toz = 0;
    for (auto c : m_grille)
    {

        toz ++;
    }
}

void Grille::afficher(sf::RenderWindow & window)
{
    for(auto c: m_grille)
    {
        c->afficher(window);
    }
}

Cases* Grille::getCase(int num_case)
{
    return m_grille[num_case-1];
}

Grille::~Grille()
{
    for(auto c : m_grille)
    {
        delete c;
    }
}

std::vector<Cases*> Grille::getGrille()
{
    return m_grille;
}

void Grille::resetGrille()
{
    for (auto cases:m_grille)
    {
        cases->setID(48);
        cases->setEtage(0);
    }
}

int Grille::calculEtage(int temp)
{
    int nombre;
    if (temp == 48)
        nombre = 0;
    else if(temp == 49 || temp == 50 || temp == 51 )
        nombre = 1;
    else if (temp == 52 || temp == 53 || temp == 54)
        nombre = 2;
    else if (temp == 55 || temp == 56 || temp == 57)
        nombre = 3;
    return nombre;

}

std::string Grille::getOutput(int id, int etage)
{
    int temp;
    if (id == 48 && etage==0)
        temp = 0;
    if (id == 49 && etage==1)
        temp = 1;
    if (id == 50 && etage==1)
        temp = 2;
    if (id == 51 && etage==1)
        temp = 3;
    if (id == 49 && etage==2)
        temp = 4;
    if (id == 50 && etage==2)
        temp = 5;
    if (id == 51 && etage==2)
        temp = 6;
    if (id == 49 && etage==3)
        temp = 7;
    if (id == 50 && etage==3)
        temp = 8;
    if (id == 51 && etage==3)
        temp = 9;
    return std::to_string(temp);
}

void Grille::sauvegarderGrille(std::string nomFichier)
{

    std::string caractere;

    int cpt = 0;

    std::ofstream fichier(DOSSIER + nomFichier +".txt", std::ios::out);

            if(fichier)
            {
                for ( auto cases:m_grille)
                {
                   cpt++;
                   caractere = getOutput(cases->getID(),cases->getEtage());
                   fichier << caractere;
                   if (cpt > 5)
                   {
                       fichier << std::endl;
                       cpt = 0;
                   }

                }

                fichier.close();

            }
            else
                    std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;

}
