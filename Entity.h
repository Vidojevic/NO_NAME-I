/* -Konstruktor prima string sa tipom entitija (Player, Enemy, Tree..., i velicinu shape-a)
*/
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Component.h"
#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>


class Entity
{
public:
    friend class EntityManager;                    //Friend class zato sto je konstruktor private i moze da mu pristupi samo EntityManager klasa

//Varijable
public:
    CTransform*              ptrCTransform     = nullptr;        //Pointer na komponentu koja sadrzi position, prevPosistion i velocity
    CBoundingBox*            ptrCBoundingBox   = nullptr;        //Pointer na komponentu koja sadrzi rectSize i halfSize
    CPlayerAssets*           ptrCPlayerAssets  = nullptr;        //Pointer na komponentu koja sadrzi player sprite, animation, sound..
    CEnemyAssets*            ptrCEnemyAssets   = nullptr;        //Pointer na komponentu za obicnog enemy.
    CTileAssets*             ptrCTileAssets    = nullptr;        //Poinetr na komponentu za tiles (sprite, animation)

    sf::RectangleShape       eRectangle;                       //Pravougaonik

private:
    bool                     isActive   = true;    //Da li je entity aktivan (ziv). Postavljen je na true zato sto prilikom kreiranja objekta on je automatski ziv. Od ovoga zavisi da li ce
                                                   //biti iscrtan na ekran i ida li ce biti propusten kroz koliziju. Ako je false onda je mrtav i ne iscrtava se sledeci frejm i ne vrsi se kolizija.
    bool                     ptrActive1 = false;   //Flag da oznaci da je neki pointer na komponente aktivan. Pomaze pri brisanju aktivnih pointera prilikom unistavanja objekta
    bool                     ptrActive2 = false;   //------ zadatak: Stavi pointere u array ili vector -------
    bool                     ptrActive3 = false;   //Pointer na komponentu Assets aktivan

    int                      id  = 0;               //ID broj entity-ja.
    std::string              tag = "Default";      //Tip entitija prosledjen kroz konstruktor (Player, Enemy, Tree...).


//Funkcije
public:
    bool                     getIsActive()const;   //Getter za private varijablu isActive
    const std::string&       getTag() const;       //Getter za private varijablu tag
    const  int               getID() const;        //Getter za private varijablu id
private:
    void                     createEntity(const sf::Vector2f position, const sf::Vector2f rectSize, const sf::Vector2f velocity, sf::Texture& texture);       //Dodaj komponente
    void                     addShape();           //Shape je vec inicijalizovan velicinom u konstruktor. Ova funkcija dodaje ostale informacije o shape (position, velocity..)
public:
    void                     destroy();            //Postavi bool isActive = FALSE, da ga ne bi brisao iz vektora. Entity Inactive, preskace se pri iteracijama collision, movement
    void                     revive();             //Vraca Entity u stanje Active, isActive = TRUE. Koristi se kod plejera (EntityManager.draw funkcija).

//Konstruktor-Destruktor
public:
//    Entity();
private:
    Entity (const std::string& entityType)                //Konstruktor je private i moze da ga koristi samo EntityManager klasa
            : tag(entityType){}
public:
    virtual ~Entity();
};

#endif // ENTITY_H
