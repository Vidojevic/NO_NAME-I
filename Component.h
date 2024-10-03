#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef COMPONENT_H
#define COMPONENT_H

//Base Class              ------OVO SE NE KORISTI---------
class Component
{
    public:
        Component();
        virtual ~Component();


        bool has = false;    //Da li entity poseduje komponentu


    protected:
    private:
};



//CTransform
class CTransform
{

public:
    sf::Vector2f position;     //Position of the entity
    sf::Vector2f prevPos;      //Previous position of the entity. Ova varijabla se inicijalizuje preko EntityManagera.setPrevPos funkcije koja se poziva u sam vrh main loop-a u main()
    sf::Vector2f velocity;     //Velocity of the entity

    sf::Vector2f positionRestart;  //Pamti pocetnu poziciju entitija i ne menja se. Koristi se za Game->restart kako bi se pokretni entitji vratili na pocetne pozicije.

public:
//    CTransform ();
    CTransform (const sf::Vector2f pos, const sf::Vector2f vel)
                : position(pos), velocity(vel), positionRestart(pos) { }

};



//CBoundingBox
class CBoundingBox
{
public:
    CBoundingBox ();
    CBoundingBox (const sf::Vector2f sizeBB)
                  : sizeBB(sizeBB), halfSizeBB(sizeBB.x / 2, sizeBB.y / 2) {}

public:
    sf::Vector2f sizeBB;           //Size of the Bounding Box
    sf::Vector2f halfSizeBB;       //Half size of the Bounding Box

};


//CPlayerAssets
class CPlayerAssets
{
public:
    bool       isEnemyHit        = false;   //Sluzi da omoguci odbijanje plejera po Y osi ako skoci neprijatelju na glavu. Ako skoci neprijatelju na glavu stavlja se na TRUE.
                                            //To se radi u Game klasu pod enemy-bottom kolizija.
    bool       isPlayerHit       = false;   //Ako se Playeru oduzme health, postavlja se na true (u kolizija). Sluzi kao flag za oduzimanje srca(healtha), entityManager->draw, water+health sekcija
    bool       isLeverActivated  = false;   //Fleg da li je poluga na kraj levela aktivirana (to je kraj levela). Sluzi da plejer izgubi mogucnost kretanja ako jeste (Inactive).
                                            //Isto tako sluzi da prikaze finishScreen ako je poluga aktivirana.
    unsigned   health            = 2;
    unsigned   frameCount        = 0;

    sf::Sprite sprite;

//Konstruktor
public:
    CPlayerAssets (sf::Texture& playerTexture)
    {
        sprite.setTexture(playerTexture);
        sprite.setTextureRect(sf::IntRect(0,0, 51,94));
    }

};


//CEnemyAssets  ---- Enemy i Boss
class CEnemyAssets
{
public:
    int      health              = 0;    //Jacina enemija, Postavlja se u EntityManager klasi u funkciji addEntity.
    unsigned frameCount          = 0;    //Sluzi kao brojac za menjanje frejmova u animacijama.
    unsigned frameCountDeath     = 0;    //Frame count za boss death. Morao sam da ubacim ovaj brojac samo za boss

    float    xPatrolBegin        = 0;    //Prvi granicnik od koga enemy ili boss patrolira. Uzima se pozicija prvog tile-a platforme (samo X osa) po kojoj treba da patrolira.
                                         //Inicijalizuje se u Game klasi odmah ispod AddEntity funcije.
    float    xPatrolEnd          = 0;    //Drugi granicnik do koga enemy ili boss patrolira. Uzima se pozicija zadnjeg tile-a platforme (samo X osa) po kojoj treba da patrolira.
                                         //Inicijalizuje se u Game klasi odmah ispod AddEntity funcije.

    sf::Sprite spriteWalk;
    sf::Sprite spriteDeath;
};


//CTileAssets
class CTileAssets
{
//Varijable
public:
    bool      animation           = false;    //Da li je animacija ukljucena trenutno, ako jeste eRectangle se ne iscrtava vise, krece animacija i objekat bude unisten (kod normal tiles)
                                              //Kod special tiles, izvrsava se animacija ali eRectangle ostaje da se vidi i zivi, tile nije unisten.
                                              //Koristi se u EntityManager.draw funkciju
    unsigned  frameCount             = 0;     //Sluzi za funkciju draw da animacija za tile traje 100 frejma (tile destruction, special tile award animation)
    unsigned  numberOfHearths        = 0;     //Sluzi da ne crta srca(health) na istoj poziciji vec da pravi odredjeni razmak izmedju njih.
                                              //Inicijalizuje se u EntityManager->addEntity funkciji i postavlja se od 0 i povecava se za jedan za svako srce.
                                              //Koristi se u EntityManager->draw funkciji (water tiles + hearth section)

    sf::Sprite spriteTileDefault;
    sf::Sprite spriteTileAnimation;

//Konstruktor
public:
    CTileAssets () {};

};


#endif // COMPONENT_H
