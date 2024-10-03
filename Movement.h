#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Entity.h"
#include <vector>
#ifndef MOVEMENT_H
#define MOVEMENT_H


class Movement
{
//Varijable
public:
    bool          isJump          = true; //Da li je plejer skocio
    bool          leftPressed     = false; //Da li je pritisnuto kretanje na levo. Sluzi da bi se pravilno postavila default pozicija(stajanje) plejera u levo.
    bool          rightPressed    = false; //Da li je pritisnuto kretanje na desno. Sluzi da bi se pravilno postavila default pozicija(stajanje) plejera u desno.
    bool          jumpPressed     = false; //Da li je pritisnuto skakanje.Sluzi da bi se pravilno postavila skok pozicija(stajanje) plejera u levo ili desno. Resetuje se na false u Game klasu
                                           // kad se desi bittom collision (plejer pao na zemlju).
    unsigned      sprtCntr        = 0;     // Sprite frame counter- sluzi za brojanje frejmova animacije
    float         jumpVelocity    = 0;     //Brizna kojom plejer skace prilikom jump
    const float   gravity         = 9;     //Utice na entitije, povecava im y osu svaki frejm (Za sada utice samo na plejera)

//Funkcije
public:
    void playerMovementNormal (std::vector<Entity>& entityPlayerStorage);        //Bez gravitacije
    void playerMovementGravity (std::vector<Entity>& entityPlayerStorage);       //Sa gravitacijom

    void enemyMovement (std::vector<Entity>& entityEnemyStorage, std::vector<Entity>& entityBossStorage);      //Enemy i Boss movement


//Konstruktor-Destruktor
public:
    Movement();
    virtual ~Movement();

};

#endif // MOVEMENT_H
