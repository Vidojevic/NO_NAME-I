#include <SFML/Graphics.hpp>
#include "EntityManager.h"

#ifndef SCREENS_H
#define SCREENS_H


class Screens
{
//Varijable
private:
    bool     isGameStart = false;  //Flag za loop pocetnog ekran(Blue screen) dok se ne pritisne odredjeno dugme (space u ovom slucaju). Kad se postavi na true, prelazi se na main game loop.
    bool     restartGame = false;  //Setuje se na true kada korisnik izabere da pocne ponovo. Setuje se u finishScreen i endScreen a koristi se u Game->run za pokretanje funkcije restart.
    unsigned scoreToShow = 0;      //Varijabla koja se puni (ima efekat punjenja) i prikazuje ukupan score plejera.

    sf::Font font1;  //Inicijalizuje se u konstruktor.
    sf::Font font2;  //Inicijalizuje se u konstruktor.
    sf::Font font3;  //Inicijalizuje se u konstruktor.

    unsigned frameCount = 0;  //Brojac za prikazivanje "Press SPACE to start the game" svakih 10 frejma (odradice se sa modulo).

//Funkcije
public:
    void startScreen(sf::RenderWindow& window, sf::View& view);                    //Pocetni ekran.

    void finishScreen(sf::RenderWindow& window, sf::View& view, unsigned score, EntityManager& manager);   //Uspesno zavrsen level.

    void endScreen(sf::RenderWindow& window, sf::View& view, unsigned score, EntityManager& manager);      //Izgubljena oba zivota.

    bool getIsGameStart();                                        //Geter za isGameStart varijablu.
    void setIsGameStart();                                        //Seter za isGameStart varijablu, postavi na true.
    void setIsGameStartFalse();                                   //Postavi na false.

    bool getRestartGame();                                      //Geter za restartGame.
    void setRestartGameTrue();                                  //Vraca restartGame na true. Koristi se u Game->restart funkciji.
    void setRestartGameFalse();                                 //Vraca restartGame na false. Koristi se u Game->restart funkciji.

//Konsturktor-Destruktor
public:
    Screens();
virtual ~Screens();

};

#endif // SCREENS_H
