/* -isCollision : Konstruktor prima 4 argumenta:  sf::RectangleShape entityA,       -Prvi objekat koji se poredi
                                                  sf::RectangleShape& entityB,      -Drugi objekat koji se poredi
                                                  sf::Vector2f& prevPosEntityA      -Prethodna pozicija prvog objekta
                                                  sf::Vector2f& rectSize            -Velicina objekta za sada samo za kvadrate. --URADI I ZA PRAVOUGAONIKE RAZLICITIH STRANICA!!!--
                                                                                     ZA SVE VELICINE ->>> (halfSize iz entity->CTransform.halfSize) <<<-

   -Sve ostale funkcije uzimaju ista 2 argumenta: sf::RectangleShape,  -Prvi objekat koji seporedi
                                                  sf::RectangleShape   -Drugi objekat koji se poredi
*/
#include <SFML/Graphics.hpp>
#include <vector>
#include "EntityManager.h"

#ifndef COLLISION_H
#define COLLISION_H


class Collision
{
//Funkcije
public:
    bool isCollision(const Entity& entityA, const Entity& entityB);
    bool isRightCollision(const Entity& entityA, const Entity& entityB);
    bool isLeftCollision(const Entity& entityA, const Entity& entityB);
    bool isTopCollision(const Entity& entityA, const Entity& entityB);
    bool isBottomCollision(const Entity& entityA, const Entity& entityB);


    void collisionDetection (std::vector<Entity>& entityPlayerStorage, std::vector<Entity>& entityEnemyStorage, std::vector<Entity>& entityTreeStorage);

//Varijable
private:
    sf::Vector2f         prevOverlap;             //Previous frame before overlap of 2 objects. Potrebna je za 4 funkcije (isRight, isLeft, isTop,isBottom), pa da je ne bi prosledjivao kao parametar
public:                                           // ili racunao u svaku funkciju posebno, racuna se samo jednom u funkciju isCollision i vrednost se skladisti u ovu varijablu.
    sf::Vector2f         overlap;                 //Racuna koliko je objekat A uso u objekat B. Koristi se za korekciju da prilikom kolizije, ta vrednost se oduzme ili doda od pozicije

//Konstruktor-Destruktor
public:
    Collision();
    virtual ~Collision();

};

#endif // COLLISION_H
