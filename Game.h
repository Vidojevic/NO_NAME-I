#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Screens.h"
#include "EntityManager.h"
#include "Collision.h"
#include "Movement.h"
#include "GridSystem.h"
//#include "EntityManager.h"
#include "FPS.h"
#ifndef GAME_H
#define GAME_H


class Game
{
private:
    unsigned jumpVelocity = 25;       //Potrebna mi je da bi implementirao odbijanje plejera od protivnika kada mu skoci na glavu. Morao sam ovako jer je igrica vec pri kraju a dizajn nije dobar.
                                      //Funkcija koja radi odbijanje se nalazi u funkciji 'run' u ovoj klasi, pri dnu.
    unsigned scoreInt     = 0;        //Brojac poena. Sve ostalo je u glavni game loop, pri pocetku. Koristi se i u restart funkciji da se resetuje vrednost na nula.

public:
    void run();

    void initialization(EntityManager& manager);

    void restart(EntityManager& manager, Screens& screens, Movement& movement);


//Konstruktor-Destruktor
public:
         Game();
virtual ~Game();


};

#endif // GAME_H
