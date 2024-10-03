#include "Movement.h"

Movement::Movement()
{
    //ctor
}

Movement::~Movement()
{

}

//playerMovement Normal
void Movement::playerMovementNormal(std::vector<Entity>& entityPlayerStorage)
{
    entityPlayerStorage[0].ptrCTransform->velocity.x = 2;
    entityPlayerStorage[0].ptrCTransform->velocity.y = 2;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        entityPlayerStorage[0].eRectangle.move(-entityPlayerStorage[0].ptrCTransform->velocity.x, 0);
        entityPlayerStorage[0].ptrCTransform->position.x -= entityPlayerStorage[0].ptrCTransform->velocity.x;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        entityPlayerStorage[0].eRectangle.move(entityPlayerStorage[0].ptrCTransform->velocity.x, 0);
        entityPlayerStorage[0].ptrCTransform->position.x += entityPlayerStorage[0].ptrCTransform->velocity.x;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        entityPlayerStorage[0].eRectangle.move(0, -entityPlayerStorage[0].ptrCTransform->velocity.y);
        entityPlayerStorage[0].ptrCTransform->position.y -= entityPlayerStorage[0].ptrCTransform->velocity.y;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        entityPlayerStorage[0].eRectangle.move(0, entityPlayerStorage[0].ptrCTransform->velocity.y);
        entityPlayerStorage[0].ptrCTransform->position.y += entityPlayerStorage[0].ptrCTransform->velocity.y;
    }
}


//playerMovement + Gravity
void Movement::playerMovementGravity(std::vector<Entity>& entityPlayerStorage)
{
    entityPlayerStorage[0].ptrCTransform->velocity.x = 3;
    entityPlayerStorage[0].ptrCTransform->velocity.y = 3;

    if (entityPlayerStorage[0].getIsActive())  //Pomeraj plejera samo ako mu je status isActive == TRUE
//Left
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            rightPressed = false;
            leftPressed  = true;
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setOrigin(entityPlayerStorage[0].ptrCPlayerAssets->sprite.getLocalBounds().width/2 + 7,   //Magicni broj 7 i  10 je korekcija da bi sprajt lepo stao u eRectangle bounding box
                                                                      entityPlayerStorage[0].ptrCPlayerAssets->sprite.getLocalBounds().height/2 - 10);      // Set Origin za sprajt na sredinu jer su sprajtovi za stajanje,
                                                                                                                                       //trcanje, skok razlicite velicine, pa da bi se uklopili sa
                                                                                                                                       //eRectanglom postavlja se setOrigin svaki put
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setTextureRect(sf::IntRect(sprtCntr/5%6 *97, 100,  98, 100));     //Nacin da se uspori animacija i da se napravi loop od 6 sprajta
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setScale(-1, 1);                                                  //Inverzija sprajta
            entityPlayerStorage[0].eRectangle.move(-entityPlayerStorage[0].ptrCTransform->velocity.x, 0);
            entityPlayerStorage[0].ptrCTransform->position.x -= entityPlayerStorage[0].ptrCTransform->velocity.x;
            ++sprtCntr;
        }
//Right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            leftPressed  = false;
            rightPressed = true;
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setOrigin(entityPlayerStorage[0].ptrCPlayerAssets->sprite.getLocalBounds().width/2 + 7,             /// ISTO KAO I KOD LEFT- FORMULA ZA POSTAVLJANE ORIGINA
                                                                     entityPlayerStorage[0].ptrCPlayerAssets->sprite.getLocalBounds().height/2 - 10);           /// NA SREDINU SPRAJTA+++++++++++++


            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setTextureRect(sf::IntRect(sprtCntr/5%6 *97, 100,  98, 100));
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setScale(1, 1);
            entityPlayerStorage[0].eRectangle.move(entityPlayerStorage[0].ptrCTransform->velocity.x, 0);
            entityPlayerStorage[0].ptrCTransform->position.x += entityPlayerStorage[0].ptrCTransform->velocity.x;
            ++sprtCntr;
        }

//Jump
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isJump == false)
        {
            jumpVelocity = 30;

            entityPlayerStorage[0].eRectangle.move(0, -jumpVelocity);
            entityPlayerStorage[0].ptrCTransform->position.y -= jumpVelocity;
            isJump = true;    //Na false se postavlja u koliziji (Game klasa), kad se desi bottom kolizija
            jumpPressed = true;
        }

        else if (isJump == true && jumpVelocity > 0)    //Dok je jumpVelocity vece od nule (trenutno je 30, postavljen u if iznad prilikom pocetka jumpa)
        {
            jumpVelocity -= 1;                        //Smanjuj jumpVelocity svaki frejm

            entityPlayerStorage[0].eRectangle.move(0, -jumpVelocity);
            entityPlayerStorage[0].ptrCTransform->position.y -= jumpVelocity;
        }

//Default position animation of player left
        if (leftPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && jumpPressed == false)   //Da ostane okrenut na levo posle kretanja u levo (default pozicija na levo)
        {
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setOrigin(entityPlayerStorage[0].ptrCPlayerAssets->sprite.getLocalBounds().width/2 -7,
                                                                      entityPlayerStorage[0].ptrCPlayerAssets->sprite.getLocalBounds().height/2);
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setTextureRect(sf::IntRect(sprtCntr/15%5 *67,0, 67,93));
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setScale(-1, 1);
            ++sprtCntr;
        }
//Default position animation of player right
        else if (rightPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && jumpPressed == false)  //Da ostane okrenut na desno posle kretanja na desno (default pozicija na desno)
        {
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setOrigin(entityPlayerStorage[0].ptrCPlayerAssets->sprite.getLocalBounds().width/2 -7,
                                                                      entityPlayerStorage[0].ptrCPlayerAssets->sprite.getLocalBounds().height/2);
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setTextureRect(sf::IntRect(sprtCntr/15%5 *67,0, 67,93));
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setScale(1, 1);
            ++sprtCntr;
        }

//Jump animation left
        if (jumpPressed && leftPressed)   //Ako skoci ulevo da sprajt bude inverzan (okrenut u levo).
        {
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setOrigin(entityPlayerStorage[0].ptrCPlayerAssets->sprite.getLocalBounds().width/2,
                                                                      entityPlayerStorage[0].ptrCPlayerAssets->sprite.getLocalBounds().height/2);
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setTextureRect(sf::IntRect(0, 195,  68, 103));
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setScale(-1, 1);
        }
//Jump animation right
        else if (jumpPressed && rightPressed)   //Ako skoci udesno da sprajt bude okrenut u desno.
        {
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setOrigin(entityPlayerStorage[0].ptrCPlayerAssets->sprite.getLocalBounds().width/2,
                                                                      entityPlayerStorage[0].ptrCPlayerAssets->sprite.getLocalBounds().height/2);
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setTextureRect(sf::IntRect(0, 195,  68, 103));
            entityPlayerStorage[0].ptrCPlayerAssets->sprite.setScale(1, 1);
        }

//Gravity
    entityPlayerStorage[0].eRectangle.move(0, gravity);
    entityPlayerStorage[0].ptrCTransform->position.y += gravity;

    }
}


//enemyMovement
void Movement::enemyMovement(std::vector<Entity>& entityEnemyStorage, std::vector<Entity>& entityBossStorage)
{
//Enemy
    for (Entity& i : entityEnemyStorage)
    {
        if (i.getIsActive())   //Pomeraj samo aktivne enemije.
        {
            int invertVelocity = -1;
            int invertScale;

            if (i.ptrCTransform->position.x < i.ptrCEnemyAssets->xPatrolBegin || i.ptrCTransform->position.x > i.ptrCEnemyAssets->xPatrolEnd)   //Setaj po platformi levo desno do odredjenih koordinata.
            {
                invertScale = (i.ptrCTransform->velocity.x / 2) * -1;   //Negate number za Scale.
                i.ptrCTransform->velocity.x *= invertVelocity;          //Invert velocity.
                i.ptrCEnemyAssets->spriteWalk.setScale(invertScale, 1);
            }

            if (i.ptrCTransform->velocity.x < 0)  //Ako je velocity negativan, krece se na levo (negativno po x osi).
            {
                i.ptrCTransform->position.x -= 2;
                i.eRectangle.setPosition(i.ptrCTransform->position.x, i.ptrCTransform->position.y);
            }
            else if (i.ptrCTransform->velocity.x > 0)   //Ako je velocity pozitivan, krece se na desno (pozitivno po x osi).
            {
                i.ptrCTransform->position.x += 2;
                i.eRectangle.setPosition(i.ptrCTransform->position.x, i.ptrCTransform->position.y);
            }
        }
    }
//Boss
    for (Entity& i : entityBossStorage)
    {
        if (i.getIsActive())   //Pomeraj samo aktivne enemije.
        {
            int invertVelocity = -1;
            int invertScale;

            if (i.ptrCTransform->position.x < i.ptrCEnemyAssets->xPatrolBegin || i.ptrCTransform->position.x > i.ptrCEnemyAssets->xPatrolEnd)   //Setaj po platformi levo desno do odredjenih koordinata.
            {
                invertScale = (i.ptrCTransform->velocity.x / 2) * -1;   //Negate number za Scale.
                i.ptrCTransform->velocity.x *= invertVelocity;          //Invert velocity.
                i.ptrCEnemyAssets->spriteWalk.setScale(invertScale, 1);
            }

            if (i.ptrCTransform->velocity.x < 0)   //Ako je velocity negativan, krece se na levo (negativno po x osi).
            {
                i.ptrCTransform->position.x -= 2;
                i.eRectangle.setPosition(i.ptrCTransform->position.x, i.ptrCTransform->position.y);
            }
            else if (i.ptrCTransform->velocity.x > 0)   //Ako je velocity pozitivan, krece se na desno (pozitivno po x osi).
            {
                i.ptrCTransform->position.x += 2;
                i.eRectangle.setPosition(i.ptrCTransform->position.x, i.ptrCTransform->position.y);
            }
        }
    }
}






