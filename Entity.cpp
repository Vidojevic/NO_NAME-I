#include "Entity.h"

/*Entity::Entity()
{
    //ctor
}
*/
Entity::~Entity()
{
    ///OSLOBADJANJE POINTERA JE PREBACENO U ENTITY MANAGER KOSTRUKTOR ZBOG PROBLEMA SA LOSIM PODACDIMA U KOMPONENTAMA JER SE VRSI KOPIRANJE
    /// PRILIKOM UBACIVANJA ENTITIJA U VEKTOR I POINTERI GUBE VREDNOST AKO SE OVDE BRISU..

}


//createEntity
void Entity::createEntity(const sf::Vector2f position, const sf::Vector2f rectSize, const sf::Vector2f velocity, sf::Texture& texture)
{
    if (tag == "Player")
    {
        ptrCTransform      = new CTransform(position,velocity);
        ptrCBoundingBox    = new CBoundingBox(rectSize);
        ptrCPlayerAssets   = new CPlayerAssets(texture);

        ptrActive1 = true;   //Pointer na CTransform aktivan
        ptrActive2 = true;   //Pointer na CBoundingBox aktivan
        ptrActive3 = true;   //Pointer na CPlayerAssets aktivan

        addShape();       //Shape je vec kreiran kroz konstruktor Entity, ovom funkcijom se dodaju ostale informacije o shape-u

    }

    else if (tag == "Enemy")
    {
        ptrCTransform   = new CTransform(position,velocity);
        ptrCBoundingBox = new CBoundingBox(rectSize);
        ptrCEnemyAssets = new CEnemyAssets();

        ptrActive1 = true;
        ptrActive2 = true;
        ptrActive3 = true;

        addShape();

    }

    if (tag == "Boss")
    {
        ptrCTransform   = new CTransform(position,velocity);
        ptrCBoundingBox = new CBoundingBox(rectSize);
        ptrCEnemyAssets = new CEnemyAssets();

        ptrActive1 = true;
        ptrActive2 = true;
        ptrActive3 = true;

        addShape();
    }

    else if (tag == "tile0")             //Pocetak zelene povrsine
    {
        ptrCTransform   = new CTransform(position,velocity);
        ptrCBoundingBox = new CBoundingBox(rectSize);
        ptrCTileAssets  = new CTileAssets();

        ptrActive1 = true;
        ptrActive2 = true;
        ptrActive3 = true;

        addShape();
    }

    if (tag == "tile1")       //Sredina zelene povrsine
    {

        ptrCTransform   = new CTransform(position,velocity);
        ptrCBoundingBox = new CBoundingBox(rectSize);
        ptrCTileAssets  = new CTileAssets();

        ptrActive1 = true;
        ptrActive2 = true;
        ptrActive3 = true;

        addShape();

    }

    else if (tag == "tile2")           //Kraj zelene povrsine
    {
        ptrCTransform   = new CTransform(position,velocity);
        ptrCBoundingBox = new CBoundingBox(rectSize);
        ptrCTileAssets  = new CTileAssets();

        ptrActive1 = true;
        ptrActive2 = true;
        ptrActive3 = true;

        addShape();
    }

    if (tag == "tile3")      //Neunistivi tile
    {

        ptrCTransform   = new CTransform(position,velocity);
        ptrCBoundingBox = new CBoundingBox(rectSize);
        ptrCTileAssets  = new CTileAssets();

        ptrActive1 = true;
        ptrActive2 = true;
        ptrActive3 = true;

        addShape();
    }

    else if (tag == "tile4")          //Special tile
    {
        ptrCTransform   = new CTransform(position,velocity);
        ptrCBoundingBox = new CBoundingBox(rectSize);
        ptrCTileAssets  = new CTileAssets();

        ptrActive1 = true;
        ptrActive2 = true;
        ptrActive3 = true;

        addShape();
    }

    if (tag == "tile5")     //Water tile
    {

        ptrCTransform   = new CTransform(position,velocity);
        ptrCBoundingBox = new CBoundingBox(rectSize);
        ptrCTileAssets  = new CTileAssets();

        ptrActive1 = true;
        ptrActive2 = true;
        ptrActive3 = true;

        //addShape();              Tile5 je voda. Ne treba bounding box pa zato i nema eRectangle, inace bi plejer hodao po vodi
    }

    else if (tag == "tile8")      //Pocetak neunistivog tile (platforma)
    {

        ptrCTransform   = new CTransform(position,velocity);
        ptrCBoundingBox = new CBoundingBox(rectSize);
        ptrCTileAssets  = new CTileAssets();

        ptrActive1 = true;
        ptrActive2 = true;
        ptrActive3 = true;

        addShape();
    }

    if (tag == "tile9")      //Sredina neunistivog tile (platforma)
    {

        ptrCTransform   = new CTransform(position,velocity);
        ptrCBoundingBox = new CBoundingBox(rectSize);
        ptrCTileAssets  = new CTileAssets();

        ptrActive1 = true;
        ptrActive2 = true;
        ptrActive3 = true;

        addShape();
    }

    else if (tag == "tile10")      //Kraj neunistivog tile (platforma)
    {

        ptrCTransform   = new CTransform(position,velocity);
        ptrCBoundingBox = new CBoundingBox(rectSize);
        ptrCTileAssets  = new CTileAssets();

        ptrActive1 = true;
        ptrActive2 = true;
        ptrActive3 = true;

        addShape();
    }

    if (tag == "tile14")             //Poluga za kraj levela
    {
        ptrCTransform   = new CTransform(position,velocity);
        ptrCBoundingBox = new CBoundingBox(rectSize);
        ptrCTileAssets  = new CTileAssets();

        ptrActive1 = true;
        ptrActive2 = true;
        ptrActive3 = true;

        addShape();
    }

    if (tag == "tile15")     //Healt tile (SRCA)
    {

        ptrCTransform   = new CTransform(position,velocity);
        ptrCBoundingBox = new CBoundingBox(rectSize);
        ptrCTileAssets  = new CTileAssets();

        ptrActive1 = true;
        ptrActive2 = true;
        ptrActive3 = true;

        //addShape();              Tile15 je health. Ne treba bounding box pa zato i nema eRectangle
    }
}


//addShape
void Entity::addShape()        //Kreira shape    SREDI OVO POSTO SE PONAVLJA ISTA RADNJA (OSTAVI SAMO JEDNU< PROVERI DA LI JE TAKO)
{

    if (tag == "Player")
    {
        eRectangle.setSize(ptrCBoundingBox->sizeBB);
        eRectangle.setOrigin(ptrCBoundingBox->halfSizeBB);
        eRectangle.setPosition(ptrCTransform->position);
        eRectangle.setFillColor(sf::Color::Transparent);
    }

    else if (tag == "Enemy")
    {
        eRectangle.setSize(ptrCBoundingBox->sizeBB);
        eRectangle.setOrigin(ptrCBoundingBox->halfSizeBB);
        eRectangle.setPosition(ptrCTransform->position);
        eRectangle.setFillColor(sf::Color::Transparent);
    }

    if (tag == "Boss")
    {
        eRectangle.setSize(ptrCBoundingBox->sizeBB);
        eRectangle.setOrigin(ptrCBoundingBox->halfSizeBB);
        eRectangle.setPosition(ptrCTransform->position);
        eRectangle.setFillColor(sf::Color::Transparent);
    }

    else if (tag== "tile0")          //Pocetak zelene povrsine
    {
        eRectangle.setSize(ptrCBoundingBox->sizeBB);
        eRectangle.setOrigin(ptrCBoundingBox->halfSizeBB);
        eRectangle.setPosition(ptrCTransform->position);
        eRectangle.setFillColor(sf::Color::White);
    }

    if (tag == "tile1")    //Sredina zelene povrsine
    {
        eRectangle.setSize(ptrCBoundingBox->sizeBB);
        eRectangle.setOrigin(ptrCBoundingBox->halfSizeBB);
        eRectangle.setPosition(ptrCTransform->position);
        eRectangle.setFillColor(sf::Color::White);
    }

    else if (tag== "tile2")         //Kraj zelene povrsine
    {
        eRectangle.setSize(ptrCBoundingBox->sizeBB);
        eRectangle.setOrigin(ptrCBoundingBox->halfSizeBB);
        eRectangle.setPosition(ptrCTransform->position);
        eRectangle.setFillColor(sf::Color::White);
    }

    if (tag == "tile3")   //Neunistivi tile
    {
        eRectangle.setSize(ptrCBoundingBox->sizeBB);
        eRectangle.setOrigin(ptrCBoundingBox->halfSizeBB);
        eRectangle.setPosition(ptrCTransform->position);
        eRectangle.setFillColor(sf::Color::White);
    }

    else if (tag == "tile4")        //Special tile
    {
        eRectangle.setSize(ptrCBoundingBox->sizeBB);
        eRectangle.setOrigin(ptrCBoundingBox->halfSizeBB);
        eRectangle.setPosition(ptrCTransform->position);
        eRectangle.setFillColor(sf::Color::White);
    }

    if (tag == "tile5")            // Tile5 je voda. Ne treba bounding box pa zato i nema eRectangle, inace bi plejer hodao po vodi
    {
        eRectangle.setSize(ptrCBoundingBox->sizeBB);
        eRectangle.setOrigin(ptrCBoundingBox->halfSizeBB);
        eRectangle.setPosition(ptrCTransform->position);
        eRectangle.setFillColor(sf::Color::White);
    }

   else if (tag == "tile8")                 //Pocetak neunistivog dela platforme
    {
        eRectangle.setSize(ptrCBoundingBox->sizeBB);
        eRectangle.setOrigin(ptrCBoundingBox->halfSizeBB);
        eRectangle.setPosition(ptrCTransform->position);
        eRectangle.setFillColor(sf::Color::White);
    }

    if (tag == "tile9")          // Sredina neunistivog dela platforme
    {
        eRectangle.setSize(ptrCBoundingBox->sizeBB);
        eRectangle.setOrigin(ptrCBoundingBox->halfSizeBB);
        eRectangle.setPosition(ptrCTransform->position);
        eRectangle.setFillColor(sf::Color::White);
    }

    else if (tag == "tile10")              //Kraj neunistivog dela platforme
    {
        eRectangle.setSize(ptrCBoundingBox->sizeBB);
        eRectangle.setOrigin(ptrCBoundingBox->halfSizeBB);
        eRectangle.setPosition(ptrCTransform->position);
        eRectangle.setFillColor(sf::Color::White);
    }

    if (tag== "tile14")          //Poluga za kraj levela
    {
        eRectangle.setSize(ptrCBoundingBox->sizeBB);
        eRectangle.setOrigin(ptrCBoundingBox->halfSizeBB);
        eRectangle.setPosition(ptrCTransform->position);
        eRectangle.setFillColor(sf::Color::White);
    }
}



//destroy
void Entity::destroy()          //Entity postaje inaktivan, to jest unisten. Ne koristi se vise. Kolizija preskace inactive entitije.
{
    this->isActive = false;
}

//revive
void Entity::revive()          //Entity postaje opet aktivan. Koristi se kod plejera kad izgubi jedan health da mu se skloni bounding box na kratko vreme, pa da se vrati (EntityManager.draw funkcija)
{
    this->isActive = true;
}


//getTag
const std::string& Entity::getTag() const
{
    return tag;
}


//getIsActive
bool Entity::getIsActive() const
{
    return isActive;
}


//getID
const int Entity::getID() const
{
  return id;
}











