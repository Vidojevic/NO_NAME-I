/* -addEntity-   Ova funkcija kreira entity i odgovarajuci shape i smesta ih u odgovarajuce vektore.
                 Linija 1: Kreira se objekat klase Entity (argument je string sa imenom tipa entitija koji zelimo da stvorimo, Player, Tree, Enemy..)i smesta seodmah  u odgovarajuci vektor)
                 Linija 4: Poziva se funkcija createEntity preko upravo napravljenog objekta klase Entity (createEntity je clan Entity klase). povezuje Entity sa komponentama i kreira shape.
   -setPrevPos-  Setuje prevPos varijablu u Entity.CTransform->prevPos. Ova funkcija mora da se postavi u sami vrh main loop-a u main() da bi se dobila tacna vrednost prethodne pozicije.
                 ------ DA LI JE OVOJ FUNKCIJI OVDE MESTO, NISAM SIGURAN. PORADI NA OVOM ------
   -draw-        Iscrtava shape-ove iz vektora shapeStorage na ekran. Prima argument referencu na RenderWindow gde zelimo da se iscrtaju shape-ovi.
   Entity Types: 1- Player
                 2. Enemy
                 3. Tree
*/
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <cstring>     //za to_string naredbu (konverzija brojeva u string)
#include "Entity.h"
#include "Component.h"
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H


class EntityManager
{
public:

//Varijable
private:
    unsigned                        totalEntityCreated   = 0;  //Koliko je ukupno entitja stvoreno. Sluzi da se dodeli id entitijima.
    unsigned                        totalyHearthsCreated = 0;  //Koliko je srca napravljeno (health). Sluzi za algoritam da srca budu odvojena i da se ne crtaju na isto mesto, jedno preko drugog.
                                                               //Koristi se u EntityManager->draw funkciji, u water tiles + health sekciji.

public:
    std::string                     tag = "default";     //Za skladistenje entity type-a.

    sf::Texture                     playerTexture;       //Texture for Player sprite (moving, jumping, default, hit, death).
    std::vector<sf::Texture*>       textureTileVec;      //Vektor za ucitavanje Texture za tiles iz foldera "assets" (tile, tile destruction, finish).
    std::vector<sf::SoundBuffer*>   soundBufferVec;      //Vektor za ucitavanje soundbuffer-a, sto je ekvivalent kao Texture. Pravi se varijabla tipa Sound (kao Sprite) gde se ucita zvuk.
    std::vector<sf::Sound>          soundVec;            //Vektor za skladistenje Sound(sprite) varijable u koju se ucitava SoundBuffer.
    std::vector<sf::Music*>         musicVec;            //Vektor za skladistenje pointera na Music

    std::vector<Entity>             entityPlayerStorage;        //Vektor za skladistenje kreiranih Player entityja (Entity->Components + Shape).
    std::vector<Entity>             entityEnemyStorage;         //Vektor za skladistenje kreiranih Enemy entityja (Entity->Components + Shape).
    std::vector<Entity>             entityTreeStorage;          //Vektor za skladistenje normal tiles, neunistivi tiles i poluge za kraj levela.(Entity->Components + Shape).
    std::vector<Entity>             entitySpecialTilesStorage;  //Vektor za special tiles.
    std::vector<Entity>             entityWaterStorage;         //Vektor za water tiles i Health jer ne sadrzi eRectangle(Shape) i samim tim nije iste velicine kao i obicni tile objekti.
                                                                //Zbog razlicite velicine objekata, moraju u posebne vektore. U vektor mogu samo objekti iste velicine ili nastaju problemi.
    std::vector<Entity>             entityBossStorage;          //Vektor za Boss enemy


//Funkcije
public:
    void addEntity(const std::string entityType, const sf::Vector2f position, const sf::Vector2f rectSize, const sf::Vector2f velocity);          //Kreiranje entityja

    void texturesInitialization();                   //Load textures from file (assets folder) and store them for later use. Za sada samo tile texture i skladisti u textureTile vektor.

    void soundInit();                                //Load sounds from file (assets folder) and store them in Sound variables (SoundBuffer-Texture, Sound-Sprite).

    void musicInit();                                //Load larger sound file for music (Larger sound files are stored in sf::Music and doesnt need soundbuffer(Texture). it loads directly from file.

    void setPrevPos();                               //Azurira prevPos varijablu u Entity.CTransform->prevPos. Ova funkcija mora da se postavi u sami vrh main loop-a u main() da bi se
                                                     //dobila tacna vrednost prethodne pozicije
    void updateSprite();                             //Update poziciju sprite-a sa pozicijom eRectangla (sluzi kao bounding box). Sprite samo prati eRectangle nikakvu mehaniku nema.
                                                     //----------Napravi da ova funkcija update-uje sve entitiy->sprite-ove, za sada update-uje samo Player sprite----------------

public:
    bool distance (const sf::Vector2f& playerPos, const sf::Vector2f& otherPos);          //Racuna da li je distance izmedju plejera i drugih entiteta manja od 100,
                                                                                          //ako jeste vraca tacno i propusta ih kroz koliziju.  -------------ZA PROXIMITY SYTEM-----------------
public:
    void draw     (sf::RenderWindow& argWindow, sf::View& view);


//Konstruktor-Destruktor
public:
    EntityManager();
    virtual ~EntityManager();

};

#endif // ENTITYMANAGER_H
