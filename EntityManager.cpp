#include "EntityManager.h"

EntityManager::EntityManager()
{
    //ctor
}

//DESTRUKTOR
EntityManager::~EntityManager()
{
/// OCLOBADJANJE PIOINTERA NA KOMPONENTE
    for (Entity& i: entityPlayerStorage)   //Oslobodi plejera
    {
        if (i.ptrActive1)                  //Oslobadjanje pointera ka komponentama
        {
            delete i.ptrCTransform;
            i.ptrCTransform = nullptr;
            //std::cout << "Obrisan ptrCTransform!" << "\n";
        }
        else if (i.ptrActive2)
        {
            delete i.ptrCBoundingBox;
            i.ptrCBoundingBox = nullptr;
            //std::cout << "Obrisan ptrBoundingBox!" << "\n";
        }
        if (i.ptrActive3)
        {
            delete i.ptrCPlayerAssets;
            i.ptrCPlayerAssets = nullptr;
            //std::cout << "Obrisan ptrCAssets!" << "\n";
        }
    }

    for (Entity& i: entityEnemyStorage)   //Oslobodi Enemy
    {
        if (i.ptrActive1)                  //Oslobadjanje pointera ka komponentama
        {
            delete i.ptrCTransform;
            i.ptrCTransform = nullptr;
            //std::cout << "Obrisan ptrCTransform!" << "\n";
        }
        else if (i.ptrActive2)
        {
            delete i.ptrCBoundingBox;
            i.ptrCBoundingBox = nullptr;
            //std::cout << "Obrisan ptrBoundingBox!" << "\n";
        }
        if (i.ptrActive3)
        {
            delete i.ptrCEnemyAssets;
            i.ptrCEnemyAssets = nullptr;
            //std::cout << "Obrisan ptrCAssets!" << "\n";
        }

    }

    for (Entity& i: entityBossStorage)   //Oslobodi Boss
    {
        if (i.ptrActive1)                  //Oslobadjanje pointera ka komponentama
        {
            delete i.ptrCTransform;
            i.ptrCTransform = nullptr;
            //std::cout << "Obrisan ptrCTransform!" << "\n";
        }
        else if (i.ptrActive2)
        {
            delete i.ptrCBoundingBox;
            i.ptrCBoundingBox = nullptr;
            //std::cout << "Obrisan ptrBoundingBox!" << "\n";
        }
        if (i.ptrActive3)
        {
            delete i.ptrCEnemyAssets;
            i.ptrCEnemyAssets = nullptr;
            //std::cout << "Obrisan ptrCAssets!" << "\n";
        }

    }

    for (Entity& i: entityTreeStorage)    //Oslobodi Tiles
    {
        if (i.ptrActive1)                  //Oslobadjanje pointera ka komponentama
        {
            delete i.ptrCTransform;
            i.ptrCTransform = nullptr;
            //std::cout << "Obrisan ptrCTransform!" << "\n";
        }
        else if (i.ptrActive2)
        {
            delete i.ptrCBoundingBox;
            i.ptrCBoundingBox = nullptr;
            //std::cout << "Obrisan ptrBoundingBox!" << "\n";
        }
        if (i.ptrActive3)
        {
            delete i.ptrCTileAssets;
            i.ptrCTileAssets = nullptr;
            //std::cout << "Obrisan ptrCAssets!" << "\n";
        }
    }

    for (Entity& i: entitySpecialTilesStorage)    //Oslobodi Special tiles
    {
        if (i.ptrActive1)                  //Oslobadjanje pointera ka komponentama
        {
            delete i.ptrCTransform;
            i.ptrCTransform = nullptr;
            //std::cout << "Obrisan ptrCTransform!" << "\n";
        }
        else if (i.ptrActive2)
        {
            delete i.ptrCBoundingBox;
            i.ptrCBoundingBox = nullptr;
            //std::cout << "Obrisan ptrBoundingBox!" << "\n";
        }
        if (i.ptrActive3)
        {
            delete i.ptrCTileAssets;
            i.ptrCTileAssets = nullptr;
            //std::cout << "Obrisan ptrCAssets!" << "\n";
        }
    }

    for (Entity& i: entityWaterStorage)    //Oslobodi Water tiles
    {
        if (i.ptrActive1)                  //Oslobadjanje pointera ka komponentama
        {
            delete i.ptrCTransform;
            i.ptrCTransform = nullptr;
            //std::cout << "Obrisan ptrCTransform!" << "\n";
        }
        else if (i.ptrActive2)
        {
            delete i.ptrCBoundingBox;
            i.ptrCBoundingBox = nullptr;
            //std::cout << "Obrisan ptrBoundingBox!" << "\n";
        }
        if (i.ptrActive3)
        {
            delete i.ptrCTileAssets;
            i.ptrCTileAssets = nullptr;
            //std::cout << "Obrisan ptrCAssets!" << "\n";
        }
    }

    for (sf::Texture*& i: textureTileVec)
    {
        delete i;
        i = nullptr;
    }

    for (sf::SoundBuffer*& i: soundBufferVec)
    {
        delete i;
        i = nullptr;
    }

    for (sf::Music*& i: musicVec)
    {
        delete i;
        i= nullptr;
    }
}



//createEntity
void EntityManager::addEntity(const std::string entityType, const sf::Vector2f position, const sf::Vector2f rectSize, const sf::Vector2f velocity)  // DODAJ SIZE, VELOCITY...
{
    tag = entityType;

    if (tag == "Player")    ///Player
    {
        if (!playerTexture.loadFromFile("assets/Player.png"))
        {
            std::cout << "Failure to load texture!" << "\n";
        }

        entityPlayerStorage.push_back(Entity(tag));      //Kreira Entity i odmah ga dodaje u vektor.Inicijalizuje se  tag i eRectangle (shape) data memberi
        totalEntityCreated += 1;                                   //Povecaj totalPlayerCreated za 1
        entityPlayerStorage.back().id = totalEntityCreated;        //i dodeli tu vrednost Entitju kao id

        entityPlayerStorage.back().createEntity(position, rectSize, velocity, playerTexture);         //Povezi komponente sa entity (pozicija, BBSize, brzina, srpite texture)

        entityPlayerStorage.back().ptrCPlayerAssets->sprite.setOrigin(entityPlayerStorage.back().ptrCBoundingBox->halfSizeBB); //SetOrigin na sredinu sprajta (Ubaci ova dva reda u zasebnu funkciju
                                                                                                                               //ako je moguce. setOrigin na sredinu sprajta se postavlja isto u Movement+Gravity left-right
                                                                                                                               //Bolji nacin je tamo jer su sprajtovi razlicite velicine i tamo je formula za
                                                                                                                               // racunanje sredine srpajta a ne eRectangla kao ovde.++++++++++++++++
        entityPlayerStorage.back().ptrCPlayerAssets->sprite.setPosition(entityPlayerStorage.back().ptrCTransform->position);   //Postavljanje sprajta na poziciju eRectangla


    }

    else if (tag == "Enemy")   ///Kretanje enemy se nalazi u klasi Movement.
    {
        entityEnemyStorage.push_back(Entity(tag));
        totalEntityCreated += 1;
        entityEnemyStorage.back().id = totalEntityCreated;

        entityEnemyStorage.back().createEntity(position, rectSize, velocity, playerTexture);
        entityEnemyStorage.back().ptrCEnemyAssets->health = 1;  //health za obicni enemy
        //spriteWalk
        entityEnemyStorage.back().ptrCEnemyAssets->spriteWalk.setTexture(*textureTileVec[11]);
        entityEnemyStorage.back().ptrCEnemyAssets->spriteWalk.setOrigin(entityEnemyStorage.back().ptrCBoundingBox->halfSizeBB.x +8, entityEnemyStorage.back().ptrCBoundingBox->halfSizeBB.y -2);
        entityEnemyStorage.back().ptrCEnemyAssets->spriteWalk.setPosition(entityEnemyStorage.back().ptrCTransform->position);
        //spriteDeath
        entityEnemyStorage.back().ptrCEnemyAssets->spriteDeath.setTexture(*textureTileVec[12]);
        entityEnemyStorage.back().ptrCEnemyAssets->spriteDeath.setOrigin(entityEnemyStorage.back().ptrCBoundingBox->halfSizeBB.x +8, entityEnemyStorage.back().ptrCBoundingBox->halfSizeBB.y -2);
        entityEnemyStorage.back().ptrCEnemyAssets->spriteDeath.setPosition(entityEnemyStorage.back().ptrCTransform->position);
    }

    if (tag == "Boss")        ///Kreiranja Boss enemy
    {
        entityBossStorage.push_back(Entity(tag));
        totalEntityCreated += 1;
        entityBossStorage.back().id = totalEntityCreated;

        entityBossStorage.back().createEntity(position, rectSize, velocity, playerTexture);
        entityBossStorage.back().ptrCEnemyAssets->health = 3;  //health za obicni enemy
        //spriteWalk and spriteDeath sheet. Walk i Death animacija se nalazi na istom sheet-u
        entityBossStorage.back().ptrCEnemyAssets->spriteWalk.setTexture(*textureTileVec[13]);
        entityBossStorage.back().ptrCEnemyAssets->spriteWalk.setOrigin(entityBossStorage.back().ptrCBoundingBox->halfSizeBB.x + 40, entityBossStorage.back().ptrCBoundingBox->halfSizeBB.y +10);
        entityBossStorage.back().ptrCEnemyAssets->spriteWalk.setPosition(entityBossStorage.back().ptrCTransform->position);
    }

    else if (tag == "tile0")             /// Pocetak zelenog tile. Svi tiles na dole nemaju sprajtove koji ih prate kao plejera vec su sprajtovi zalepljeni direktno na eRectangle (shape).
    {
        entityTreeStorage.push_back(Entity(tag));
        totalEntityCreated += 1;
        entityTreeStorage.back().id = totalEntityCreated;

        entityTreeStorage.back().createEntity(position, rectSize, velocity, playerTexture);  //(4. argument ne sluzi nicemu posto se u sledecoj liniji setuje texture. Dizajn je lose uradjen)
        entityTreeStorage.back().eRectangle.setTexture(textureTileVec[0]);       //Zalepi default sprite na eRectangle

        entityTreeStorage.back().ptrCTileAssets->spriteTileAnimation.setTexture(*textureTileVec[6]);   //postavlja texture za animaciju unistavanja tile (tileDestruction).
                                                                                                      //Member je componente CTileAssets.
        entityTreeStorage.back().ptrCTileAssets->spriteTileAnimation.setOrigin(entityTreeStorage.back().ptrCBoundingBox->halfSizeBB);  //set origin of animation
        entityTreeStorage.back().ptrCTileAssets->spriteTileAnimation.setPosition(entityTreeStorage.back().ptrCTransform->position);    //set position of animation
    }

    if (tag == "tile1")        ///Sredina zelenog tile.
    {
        entityTreeStorage.push_back(Entity(tag));
        totalEntityCreated += 1;
        entityTreeStorage.back().id = totalEntityCreated;

        entityTreeStorage.back().createEntity(position, rectSize, velocity, playerTexture);   //(4. argument ne sluzi nicemu posto se u sledecoj liniji setuje texture. Dizajn je lose uradjen).
        entityTreeStorage.back().eRectangle.setTexture(textureTileVec[1]);                    //Zalepi default sprite na eRectangle.

        entityTreeStorage.back().ptrCTileAssets->spriteTileAnimation.setTexture(*textureTileVec[6]);   //postavlja texture za animaciju unistavanja tile (tileDestruction).
                                                                                                      //Member je componente CTileAssets.
        entityTreeStorage.back().ptrCTileAssets->spriteTileAnimation.setOrigin(entityTreeStorage.back().ptrCBoundingBox->halfSizeBB);  //set origin of animation
        entityTreeStorage.back().ptrCTileAssets->spriteTileAnimation.setPosition(entityTreeStorage.back().ptrCTransform->position);    //set position of animation
    }

    else if (tag == "tile2")            ///Kraj zelenog tile.
    {
        entityTreeStorage.push_back(Entity(tag));
        totalEntityCreated += 1;
        entityTreeStorage.back().id = totalEntityCreated;

        entityTreeStorage.back().createEntity(position, rectSize, velocity, playerTexture);   //(4. argument ne sluzi nicemu posto se u sledecoj liniji setuje texture. Dizajn je lose uradjen).
        entityTreeStorage.back().eRectangle.setTexture(textureTileVec[2]);         //Zalepi default sprite na eRectangle

        entityTreeStorage.back().ptrCTileAssets->spriteTileAnimation.setTexture(*textureTileVec[6]);   //postavlja texture za animaciju unistavanja tile (tileDestruction).
                                                                                                      //Member je componente CTileAssets.
        entityTreeStorage.back().ptrCTileAssets->spriteTileAnimation.setOrigin(entityTreeStorage.back().ptrCBoundingBox->halfSizeBB);  //set origin of animation
        entityTreeStorage.back().ptrCTileAssets->spriteTileAnimation.setPosition(entityTreeStorage.back().ptrCTransform->position);    //set position of animation
    }

    if (tag == "tile3")      ///Neunistivi tile
    {
        entityTreeStorage.push_back(Entity(tag));
        totalEntityCreated += 1;
        entityTreeStorage.back().id = totalEntityCreated;

        entityTreeStorage.back().createEntity(position, rectSize, velocity, playerTexture);   //(4. argument ne sluzi nicemu posto se u sledecoj liniji setuje texture. Dizajn je lose uradjen).
        entityTreeStorage.back().eRectangle.setTexture(textureTileVec[3]);           //Zalepi default sprite na eRectangle.
    }

    else if (tag == "tile4")   ///Special tile
    {
        entitySpecialTilesStorage.push_back(Entity(tag));
        totalEntityCreated += 1;
        entitySpecialTilesStorage.back().id = totalEntityCreated;

        entitySpecialTilesStorage.back().createEntity(position, rectSize, velocity, playerTexture);   //(4. argument ne sluzi nicemu posto se u sledecoj liniji setuje texture. Dizajn je lose uradjen)
        entitySpecialTilesStorage.back().eRectangle.setTexture(textureTileVec[4]);           //Zalepi default sprite na eRectangle

        entitySpecialTilesStorage.back().ptrCTileAssets->spriteTileAnimation.setTexture(*textureTileVec[7]);   //postavlja texture za animaciju bonusa specijalnog tile-a.
                                                                                                               //Member je componente CTileAssets.
        entitySpecialTilesStorage.back().ptrCTileAssets->spriteTileAnimation.setOrigin(entitySpecialTilesStorage.back().ptrCBoundingBox->halfSizeBB);  //set origin of animation
        entitySpecialTilesStorage.back().ptrCTileAssets->spriteTileAnimation.setPosition(entitySpecialTilesStorage.back().ptrCTransform->position.x,
                                                                                         entitySpecialTilesStorage.back().ptrCTransform->position.y - 50);    //set position of animation
                                                                                                                                                              // -50 po y osi da bi se pojavilo iznad
                                                                                                                                                              //tile-a
    }

    if (tag == "tile5")   ///Water tile
    {                                                     //tile 5 je VODA i ona nema rectangle shape zato sto za vodu ne treba bounding box, igrac treba da propadne kroz nju. tile5 koristi samo sprite.
        entityWaterStorage.push_back(Entity(tag));        //Igrac treba da propadne kroz nju. tile5 koristi samo sprite.
        totalEntityCreated += 1;
        entityWaterStorage.back().id = totalEntityCreated;

        entityWaterStorage.back().createEntity(position, rectSize, velocity, playerTexture);
        entityWaterStorage.back().ptrCTileAssets->spriteTileDefault.setTexture(*textureTileVec[5]);
        entityWaterStorage.back().ptrCTileAssets->spriteTileDefault.setOrigin(entityWaterStorage.back().ptrCBoundingBox->halfSizeBB);
        entityWaterStorage.back().ptrCTileAssets->spriteTileDefault.setPosition(entityWaterStorage.back().ptrCTransform->position.x,
                                                                               entityWaterStorage.back().ptrCTransform->position.y + 15);   //Magic number 15 je da bi voda bila malo spustena po Y osi
                                                                                                                                           //ispod linije zemljista.
    }

    else if (tag == "tile8")      ///Neunistivi tile pocetak
    {
        entityTreeStorage.push_back(Entity(tag));
        totalEntityCreated += 1;
        entityTreeStorage.back().id = totalEntityCreated;

        entityTreeStorage.back().createEntity(position, rectSize, velocity, playerTexture);   //(4. argument ne sluzi nicemu posto se u sledecoj liniji setuje texture. Dizajn je lose uradjen).
        entityTreeStorage.back().eRectangle.setTexture(textureTileVec[8]);           //Zalepi default sprite na eRectangle.
    }

    if (tag == "tile9")      ///Neunistivi tile sredina
    {
        entityTreeStorage.push_back(Entity(tag));
        totalEntityCreated += 1;
        entityTreeStorage.back().id = totalEntityCreated;

        entityTreeStorage.back().createEntity(position, rectSize, velocity, playerTexture);   //(4. argument ne sluzi nicemu posto se u sledecoj liniji setuje texture. Dizajn je lose uradjen).
        entityTreeStorage.back().eRectangle.setTexture(textureTileVec[9]);           //Zalepi default sprite na eRectangle.
    }

    else if (tag == "tile10")      ///Neunistivi tile kraj
    {
        entityTreeStorage.push_back(Entity(tag));
        totalEntityCreated += 1;
        entityTreeStorage.back().id = totalEntityCreated;

        entityTreeStorage.back().createEntity(position, rectSize, velocity, playerTexture);   //(4. argument ne sluzi nicemu posto se u sledecoj liniji setuje texture. Dizajn je lose uradjen).
        entityTreeStorage.back().eRectangle.setTexture(textureTileVec[10]);           //Zalepi default sprite na eRectangle.
    }

    if (tag == "tile14")        ///Poluga za kraj levela
    {
        entityTreeStorage.push_back(Entity(tag));
        totalEntityCreated += 1;
        entityTreeStorage.back().id = totalEntityCreated;

        entityTreeStorage.back().createEntity(position, rectSize, velocity, playerTexture);   //(4. argument ne sluzi nicemu posto se u sledecoj liniji setuje texture. Dizajn je lose uradjen).

        entityTreeStorage.back().eRectangle.setTexture(textureTileVec[14]);
        entityTreeStorage.back().eRectangle.setTextureRect(sf::IntRect(0,0, 50,50));  //postavi na prvu s;ilu.
    }

    else if (tag == "tile15")   ///Health tile (SRCA). Skladisti se u entityWaterStorage vektor zato sto isto nema eRectangle (shape-bounding box) kao i water (a i manje su velicine objekti)
    {                                                     //tile 15 je health i nema rectangle shape zato sto za health ne treba bounding box
        entityWaterStorage.push_back(Entity(tag));
        totalEntityCreated   += 1;
        totalyHearthsCreated += 1;
        entityWaterStorage.back().id = totalEntityCreated;

        entityWaterStorage.back().createEntity(position, rectSize, velocity, playerTexture);
        entityWaterStorage.back().ptrCTileAssets->numberOfHearths = totalyHearthsCreated;

        entityWaterStorage.back().ptrCTileAssets->spriteTileDefault.setTexture(*textureTileVec[15]);
        entityWaterStorage.back().ptrCTileAssets->spriteTileDefault.setOrigin(entityWaterStorage.back().ptrCBoundingBox->halfSizeBB);
    }
}


//textureInitialization
void EntityManager::texturesInitialization()          //Inicijalizuje vektor pointera na skoro sve Texture koje se koriste u igrici
{
    for (unsigned i=0; i < 16; ++i)   //Magican broj 16. Ovde voditi racuna jer broj mora da bude ekvivalentan broju tile-ova koji postoje u folder za ucitavanje, inace nece da ucita sve ili
                                      //ce da se javi greska.
    {
        std::string fileName = ("assets/tile" + std::to_string(i) + ".png");    // Konvertovanje broja u string. Svi sprajtovi u folder "assets" nose isto ime,
                                                                                // pocinju sa "tile" i samo se dodaje broj na kraj zbog lakseg ucitavanje iz fajla.
        sf::Texture* texturePtr = new sf::Texture;
        textureTileVec.push_back(texturePtr);

        textureTileVec[i]->loadFromFile(fileName);
    }

}


//soundInit
void EntityManager::soundInit()
{
    for (unsigned i=0; i < 5; ++i)
    {
        std::string fileName = ("assets/sound" + std::to_string(i) + ".wav");    // Konvertovanje broja u string. Svi sprajtovi u folder "assets" nose isto ime,
                                                                              // pocinju sa "tile" i samo se dodaje broj na kraj zbog lakseg ucitavanje iz fajla.
        sf::SoundBuffer* soundBufferPtr = new sf::SoundBuffer;
        soundBufferVec.push_back(soundBufferPtr);

        if (!soundBufferVec[i]->loadFromFile(fileName))
        {
            std::cout << "SOUND NOT LOADED!!!" << "\n";
        }

        sf::Sound sound;                   //Inicijalizaija sounda sa bufferom (kao Sprite kada ucita Texture)
        soundVec.push_back(sound);
        soundVec.back().setBuffer(*soundBufferVec[i]);


    }
}


//musicInit
void EntityManager::musicInit()
{
    for (unsigned i=0; i < 2; ++i)
    {
        std::string fileName = ("assets/music" + std::to_string(i) + ".wav");    // Konvertovanje broja u string. Svi sprajtovi u folder "assets" nose isto ime,
                                                                              // pocinju sa "tile" i samo se dodaje broj na kraj zbog lakseg ucitavanje iz fajla.
        sf::Music* music = new sf::Music;
        musicVec.push_back(music);
        musicVec[i]->openFromFile(fileName);
    }
}


//setPrevPos
void EntityManager::setPrevPos()
{

    for (unsigned i=0; i < entityPlayerStorage.size(); ++i)
    {
        entityPlayerStorage[i].ptrCTransform->prevPos = entityPlayerStorage[i].ptrCTransform->position;

    }
    for (unsigned i=0; i < entityEnemyStorage.size(); ++i)
    {
        entityEnemyStorage[i].ptrCTransform->prevPos = entityEnemyStorage[i].ptrCTransform->position;

    }
    for (unsigned i=0; i < entityTreeStorage.size(); ++i)
    {
        entityTreeStorage[i].ptrCTransform->prevPos = entityTreeStorage[i].ptrCTransform->position;
    }
}


//distance
bool EntityManager::distance(const sf::Vector2f& playerPos, const sf::Vector2f& otherPos)  //Racuna razdaljinu izmedju dva entitija. Sluzi za proximity koliziju.
{
    sf::Vector2f distance;
    distance.x = abs (playerPos.x - otherPos.x);
    distance.y = abs (playerPos.y - otherPos.y);

    if (distance.x < 100)
    {
        return true;
    }
    else if (distance.y < 100)
    {
        return true;
    }
    return false;
}


//updateSprite PLAYER
void EntityManager::updateSprite()
{
    entityPlayerStorage[0].ptrCPlayerAssets->sprite.setPosition(entityPlayerStorage[0].ptrCTransform->position.x,
                                                                entityPlayerStorage[0].ptrCTransform->position.y + 2);   //Pomeri sprite na poziciju eRectangla i
                                                                                                                         //prilagodi je eRectanglu (+2 za ovaj trenutni sprajt)
}


//draw
void EntityManager::draw(sf::RenderWindow& argWindow, sf::View& view)
{
//Player
    for (unsigned i=0; i < entityPlayerStorage.size(); ++i)
    {
        if (entityPlayerStorage[i].ptrCPlayerAssets->health != 0 && entityPlayerStorage[i].getIsActive())
        {
            argWindow.draw(entityPlayerStorage[i].eRectangle);
            argWindow.draw(entityPlayerStorage[i].ptrCPlayerAssets->sprite);
        }
    //Prelazak nivoa. Kad plejer povuce polugu za kraj animacija za default position.
        else if (entityPlayerStorage[i].ptrCPlayerAssets->health != 0 && entityPlayerStorage[i].ptrCPlayerAssets->isLeverActivated)
        {
            entityPlayerStorage[i].destroy();

            entityPlayerStorage[i].ptrCPlayerAssets->sprite.setOrigin(entityPlayerStorage[i].ptrCPlayerAssets->sprite.getLocalBounds().width/2 - 10,
                                                                      entityPlayerStorage[i].ptrCPlayerAssets->sprite.getLocalBounds().height/2);
            entityPlayerStorage[i].ptrCPlayerAssets->sprite.setTextureRect(sf::IntRect(entityPlayerStorage[i].ptrCPlayerAssets->frameCount/15%5 *67,0, 67,93));  //Postavi plejera na default position.
            ++entityPlayerStorage[i].ptrCPlayerAssets->frameCount;

            argWindow.draw(entityPlayerStorage[i].eRectangle);
            argWindow.draw(entityPlayerStorage[i].ptrCPlayerAssets->sprite);
        }
    //Animacija oduzimanja healtha
        if (entityPlayerStorage[i].ptrCPlayerAssets->health != 0 && (!entityPlayerStorage[i].getIsActive())
            && entityPlayerStorage[i].ptrCPlayerAssets->frameCount < 100 && (!entityPlayerStorage[0].ptrCPlayerAssets->isLeverActivated)) //Zadnji uslov "isLeverActivated" je tu da se ova animacija ne bi aktivirala kada se zavrsi level
        {                                                                                                                                            //Imao sam bug da mi se ova animacija aktivirala prilikom zavrsavanja levela, ovim uslovom sam je odstranio.
            entityPlayerStorage[i].ptrCPlayerAssets->sprite.setTextureRect(sf::IntRect(entityPlayerStorage[i].ptrCPlayerAssets->frameCount/10%3 *65,412, 65,90));  //Usporava animaciju kretanja
            entityPlayerStorage[i].ptrCPlayerAssets->sprite.setPosition(entityPlayerStorage[i].ptrCTransform->position.x, entityPlayerStorage[i].ptrCTransform->position.y + 4);  //Korekcija sprite po y osi
            ++entityPlayerStorage[i].ptrCPlayerAssets->frameCount;

            argWindow.draw(entityPlayerStorage[i].eRectangle);                 //crta rectangle
            argWindow.draw(entityPlayerStorage[i].ptrCPlayerAssets->sprite);   //crta sprite
        }
    //Vracanje plejera u Active posle animacije oduzimanja healtha
        else if (entityPlayerStorage[i].ptrCPlayerAssets->health != 0 && (!entityPlayerStorage[i].getIsActive()) && entityPlayerStorage[i].ptrCPlayerAssets->frameCount == 100)
        {
            entityPlayerStorage[i].revive();
            entityPlayerStorage[i].ptrCPlayerAssets->frameCount = 0;   //resetuj frame count za sledece oduzimanje healtha
        }
    //Animacija gubitka oba srca
        if (entityPlayerStorage[i].ptrCPlayerAssets->health == 0 && entityPlayerStorage[i].ptrCPlayerAssets->frameCount < 75)
        {
            //UBACI ANIMACIJU KRAJA PLEJERA
            entityPlayerStorage[i].ptrCPlayerAssets->sprite.setTextureRect(sf::IntRect(entityPlayerStorage[i].ptrCPlayerAssets->frameCount/15%5 *96,309, 96,95));  //Usporava animaciju
            entityPlayerStorage[i].ptrCPlayerAssets->sprite.setPosition(entityPlayerStorage[i].ptrCTransform->position.x, entityPlayerStorage[i].ptrCTransform->position.y +4);  //Korekcija sprite po y osi
            ++entityPlayerStorage[i].ptrCPlayerAssets->frameCount;
            //POSTAVI PLEJERA NA INACTIVE
            entityPlayerStorage[i].destroy();

            argWindow.draw(entityPlayerStorage[i].eRectangle);                 //crta rectangle
            argWindow.draw(entityPlayerStorage[i].ptrCPlayerAssets->sprite);   //crta sprite
        }
    //Gubitak oba srca, postavi plejer sprite samo da lezi
        else if (entityPlayerStorage[i].ptrCPlayerAssets->health == 0 && entityPlayerStorage[i].ptrCPlayerAssets->frameCount == 75)
        {
            //Za kraj samo prite plejera kako lezi
            entityPlayerStorage[i].ptrCPlayerAssets->sprite.setTextureRect(sf::IntRect(386,353, 95,46));
            entityPlayerStorage[i].ptrCPlayerAssets->sprite.setPosition(entityPlayerStorage[i].ptrCTransform->position.x, entityPlayerStorage[i].ptrCTransform->position.y +48);  //Korekcija sprite po y osi
            argWindow.draw(entityPlayerStorage[i].ptrCPlayerAssets->sprite);   //crta sprite
        }
    }
//Enemy
    for (unsigned i=0; i < entityEnemyStorage.size(); ++i)
    {
        //Walk
        if (entityEnemyStorage[i].ptrCEnemyAssets->health != 0)
        {
            //Animacija walk
            entityEnemyStorage[i].ptrCEnemyAssets->spriteWalk.setTextureRect(sf::IntRect(entityEnemyStorage[i].ptrCEnemyAssets->frameCount/5%13 *55,0, 55,87));  //Usporava animaciju kretanja
            entityEnemyStorage[i].ptrCEnemyAssets->spriteWalk.setPosition(entityEnemyStorage[i].ptrCTransform->position);

            argWindow.draw(entityEnemyStorage[i].eRectangle);                    //crta rectangle
            argWindow.draw(entityEnemyStorage[i].ptrCEnemyAssets->spriteWalk);   //crta sprite

            ++entityEnemyStorage[i].ptrCEnemyAssets->frameCount;
        }
        //Death
        else if (entityEnemyStorage[i].ptrCEnemyAssets->health == 0)
        {
            entityEnemyStorage[i].destroy();
            //Animacija death
            entityEnemyStorage[i].ptrCEnemyAssets->spriteDeath.setPosition(entityEnemyStorage[i].ptrCTransform->position.x, entityEnemyStorage[i].ptrCTransform->position.y + 60);
            argWindow.draw((entityEnemyStorage[i].ptrCEnemyAssets->spriteDeath));   //crta samo sprite bey rectangla

        }
    }

//Boss
    for (unsigned i=0; i < entityBossStorage.size(); ++i)
    {
        //Walk
        if (entityBossStorage[i].ptrCEnemyAssets->health != 0)
        {
            //Animacija walk
            entityBossStorage[i].ptrCEnemyAssets->spriteWalk.setTextureRect(sf::IntRect(entityBossStorage[i].ptrCEnemyAssets->frameCount/7%11 *135,0, 135,125));  //Usporava animaciju kretanja
            entityBossStorage[i].ptrCEnemyAssets->spriteWalk.setPosition(entityBossStorage[i].ptrCTransform->position);

            argWindow.draw(entityBossStorage[i].eRectangle);                    //crta rectangle
            argWindow.draw(entityBossStorage[i].ptrCEnemyAssets->spriteWalk);   //crta sprite

            ++entityBossStorage[i].ptrCEnemyAssets->frameCount;
        }
        //Death
        else if (entityBossStorage[i].ptrCEnemyAssets->health == 0 && entityBossStorage[i].ptrCEnemyAssets->frameCountDeath < 85)   //frameCountDeath je ubacen samo za ovu animaciju (Boss death)
        {
            entityBossStorage[i].destroy();
            //Animacija death
            entityBossStorage[i].ptrCEnemyAssets->spriteWalk.setTextureRect(sf::IntRect(entityBossStorage[i].ptrCEnemyAssets->frameCountDeath/17%5 *130,152, 130,112));  //Usporava animaciju
            entityBossStorage.back().ptrCEnemyAssets->spriteWalk.setOrigin(entityBossStorage.back().ptrCBoundingBox->halfSizeBB.x +30, entityBossStorage.back().ptrCBoundingBox->halfSizeBB.y);
            entityBossStorage[i].ptrCEnemyAssets->spriteWalk.setPosition(entityBossStorage[i].ptrCTransform->position);

            argWindow.draw(entityBossStorage[i].eRectangle);
            argWindow.draw((entityBossStorage[i].ptrCEnemyAssets->spriteWalk));   //crta samo sprite bey rectangla
            ++entityBossStorage[i].ptrCEnemyAssets->frameCountDeath;
        }
        //Death, ostaje da lezi sprite
        if (entityBossStorage[i].ptrCEnemyAssets->health == 0 && entityBossStorage[i].ptrCEnemyAssets->frameCountDeath == 85)
        {
            entityBossStorage[i].ptrCEnemyAssets->spriteWalk.setTextureRect(sf::IntRect(520,152, 130,112));  //samo jedan frejm, kako bos lezi
            entityBossStorage.back().ptrCEnemyAssets->spriteWalk.setOrigin(entityBossStorage.back().ptrCBoundingBox->halfSizeBB.x +30, entityBossStorage.back().ptrCBoundingBox->halfSizeBB.y);
            entityBossStorage[i].ptrCEnemyAssets->spriteWalk.setPosition(entityBossStorage[i].ptrCTransform->position);

            argWindow.draw((entityBossStorage[i].ptrCEnemyAssets->spriteWalk));   //crta samo sprite bey rectangla
        }
    }

//Normal tiles (entityTreeStorage)
    for (unsigned i=0; i < entityTreeStorage.size(); ++i)
    {
        if (entityTreeStorage[i].ptrCTileAssets->animation == false)   //Ako nije pokrenuta animacija iscrtavaj eRectangle, cim krene animacija (sto znaci da je tile udaren odozdo, prestani
                                                                       //prestani da crtas eRectangle i prikazi animaciju kja traje 30 frejma i onda se objekat unistava (sledece dve if naredbe ispod)
        {
            argWindow.draw(entityTreeStorage[i].eRectangle);
        }

        //Poluga za kraj igrice (tile14)
        else if (entityTreeStorage[i].getTag() == "tile14" && entityTreeStorage[i].ptrCTileAssets->animation)  //Poluga za kraj igirce, animation se postavlja na true u Game->Kolizija(entityTreeStorage)
        {                                                                                                      //Screens funckije za kraj i prekid igrice se pozivaju u Game.draw
            entityPlayerStorage[0].ptrCPlayerAssets->isLeverActivated = true;  //Postavi fleg da je poluga povecana, uslov da se prikaze finishScreen.
            entityPlayerStorage[0].destroy();                                  //Postavi plejera na inactive kako ne bi vise mogao da se krece.
            //prikazi drugi polozaj poluge koji signalizira kraj levela (nema animacija, samo drugi sprajt)
            entityTreeStorage[i].eRectangle.setTextureRect(sf::IntRect(100-2, 0,  50, 50)); //prikazi trecu sliku
            argWindow.draw(entityTreeStorage[i].eRectangle);
        }
        //Unistavanje zelenih tiles
        if (entityTreeStorage[i].ptrCTileAssets->animation == true && entityTreeStorage[i].ptrCTileAssets->frameCount < 30)   //Ako je pokrenuta animacija i frameCount ispod 30
        {
            entityTreeStorage[i].destroy();       //Postavlja entity isActive = FALSE. Entitiji koji su inactive se ne koriste vise za koliziju i ostale stvari. Ne postoje vise. Iscrtava se samo animacija
                                                  // ili ostavljamo da se isrctava sprite bez bounding box, to zavisi od koda ispod..
            //prikazuj animaciju
            entityTreeStorage[i].ptrCTileAssets->spriteTileAnimation.setTextureRect(sf::IntRect(entityTreeStorage[i].ptrCTileAssets->frameCount/6%6 *50, 0,  50, 36));  //Uspori animaciju.
            argWindow.draw(entityTreeStorage[i].ptrCTileAssets->spriteTileAnimation);
            ++entityTreeStorage[i].ptrCTileAssets->frameCount;   //Dodaj 1 frameCount. Ovaj frameCount je deklarisan u komponentu Assets gde se nalazi animacija, postavljen je na 0.
        }
    }

//Special tiles
    for (unsigned i=0; i < entitySpecialTilesStorage.size(); ++i)
    {
        if (entitySpecialTilesStorage[i].ptrCTileAssets->animation == false)
        {
            argWindow.draw(entitySpecialTilesStorage[i].eRectangle);
        }
        else if (entitySpecialTilesStorage[i].ptrCTileAssets->animation == true && entitySpecialTilesStorage[i].ptrCTileAssets->frameCount < 63)
        {
            entitySpecialTilesStorage[i].eRectangle.setTexture(textureTileVec[3]);  //Dodeli mu texture gvozdenog tile, nema vise tile sa znakom upitnika
            argWindow.draw(entitySpecialTilesStorage[i].eRectangle);

            entitySpecialTilesStorage[i].ptrCTileAssets->spriteTileAnimation.setTextureRect(sf::IntRect(entitySpecialTilesStorage[i].ptrCTileAssets->frameCount/9%9 *50, 0,  50, 50));  //Uspori animaciju.
            argWindow.draw(entitySpecialTilesStorage[i].ptrCTileAssets->spriteTileAnimation);
            ++entitySpecialTilesStorage[i].ptrCTileAssets->frameCount;   //Oduzimaj frameCount. Ovaj frameCount je deklarisan u komponentu Assets gde se nalazi animacija, postavljen je na 0.
        }
        if (entitySpecialTilesStorage[i].ptrCTileAssets->animation == true && entitySpecialTilesStorage[i].ptrCTileAssets->frameCount >= 63)  //Ako je upaljena animacija i frameCount 0, unisti objekat
        {
            argWindow.draw(entitySpecialTilesStorage[i].eRectangle);
        }
    }

//Water tiles + Health
    for (unsigned i=0; i < entityWaterStorage.size(); ++i)
    {
        //Postavljanje srca na svoja mesta u odnosu na View (prate plejera), a ne u odnosu na glavni ekran
        if (entityWaterStorage[i].getTag() == "tile15" && entityWaterStorage[i].getIsActive())
        {
            sf::Vector2f viewCenter = view.getCenter();  //Koordinate centra View ekrana a ne glavnog ekrana.
            viewCenter.x = viewCenter.x - (650 + (entityWaterStorage[i].ptrCTileAssets->numberOfHearths * 50));  //Korekcija
            viewCenter.y = viewCenter.y - 320;

            entityWaterStorage[i].ptrCTransform->position.x = viewCenter.x;
            entityWaterStorage[i].ptrCTransform->position.y = viewCenter.y;
            entityWaterStorage[i].ptrCTileAssets->spriteTileDefault.setPosition(entityWaterStorage[i].ptrCTransform->position);
        }

        //Algoritam za oduzimanje health-a (srca)
        if (entityWaterStorage[i].getTag() == "tile15" && entityWaterStorage[i].getIsActive() && entityPlayerStorage[0].ptrCPlayerAssets->isPlayerHit)
        {
            entityWaterStorage[i].destroy();    //stavi na inaktivan da se ne bi vise iscrtavao.
            entityPlayerStorage[0].ptrCPlayerAssets->isPlayerHit = false;   //Vrati flag na false
        }

        //Iscrtavaj samo aktivne water tiles (ovo je samo zbog srca uradjeno)
        else if (entityWaterStorage[i].getIsActive())  //Iscrtavaj samo aktivne (ovo je samo zbog srca uradjeno) jer se samo srca stavljaju na inactive.
        {
            argWindow.draw(entityWaterStorage[i].ptrCTileAssets->spriteTileDefault);   //iscrtaj vodu, ima samo sprite nema eRectangle. Nalazi se u poseban vektor zbog velicine objekta)
        }
    }

}






