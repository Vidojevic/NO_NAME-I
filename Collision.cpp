#include "Collision.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}


//IS COLLISION
bool Collision::isCollision(const Entity& entityA, const Entity& entityB)
{
    //Distance and Overlap algorythm
    sf::Vector2f distance;        //Distance between objects. Koristi se trenutno samo kod prve funkcije isCollision
    distance.x = abs (entityB.eRectangle.getPosition().x - entityA.eRectangle.getPosition().x);
    distance.y = abs (entityB.eRectangle.getPosition().y - entityA.eRectangle.getPosition().y);

    overlap.x = ((entityA.ptrCBoundingBox->halfSizeBB.x + entityB.ptrCBoundingBox->halfSizeBB.x) - distance.x);
    overlap.y = ((entityA.ptrCBoundingBox->halfSizeBB.y + entityB.ptrCBoundingBox->halfSizeBB.y) - distance.y);

    //Previous frame distance and Previous overlap frame algorythm. Koristi se u sve ostale funkcije (isRight, isLeft, isTop, isBottom), izracunava se ovde zbog optimizacije i brzine
    sf::Vector2f prevPosDistance;    //Previous frame distance between 2 objects
    prevPosDistance.x = abs (entityB.eRectangle.getPosition().x - entityA.ptrCTransform->prevPos.x);
    prevPosDistance.y = abs (entityB.eRectangle.getPosition().y - entityA.ptrCTransform->prevPos.y);

    prevOverlap.x = ((entityA.ptrCBoundingBox->halfSizeBB.x + entityB.ptrCBoundingBox->halfSizeBB.x) - prevPosDistance.x);
    prevOverlap.y = ((entityA.ptrCBoundingBox->halfSizeBB.y + entityB.ptrCBoundingBox->halfSizeBB.y) - prevPosDistance.y);

    if (distance.x < (entityA.ptrCBoundingBox->halfSizeBB.x + entityB.ptrCBoundingBox->halfSizeBB.x) && distance.y < (entityA.ptrCBoundingBox->halfSizeBB.y + entityB.ptrCBoundingBox->halfSizeBB.y))
    {
        return true;
    }

    return false;

}


//RIGHT COLLISION
bool Collision::isRightCollision(const Entity& entityA, const Entity& entityB)
{

    if ( prevOverlap.y > 0 && entityA.eRectangle.getPosition().x < entityB.eRectangle.getPosition().x)
    {
        return true;
    }

    return false;

}


//LEFT COLLISION
bool Collision::isLeftCollision(const Entity& entityA, const Entity& entityB)
{

    if ( prevOverlap.y > 0 && entityA.eRectangle.getPosition().x > entityB.eRectangle.getPosition().x)
    {
        return true;
    }

    return false;

}


//TOP COLLISION
bool Collision::isTopCollision(const Entity& entityA, const Entity& entityB)
{

    if ( prevOverlap.x > 0 && entityA.eRectangle.getPosition().y > entityB.eRectangle.getPosition().y )
    {
        return true;
    }

    return false;

}


//BOTTOM COLLISION
bool Collision::isBottomCollision(const Entity& entityA, const Entity& entityB)
{

    if ( prevOverlap.x > 0 && entityA.eRectangle.getPosition().y < entityB.eRectangle.getPosition().y)
    {
        return true;
    }

    return false;

}















