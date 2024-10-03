#include "GridSystem.h"



//Constructor
GridSystem::GridSystem (const unsigned& windowWidth, const unsigned& windowHeight, sf::RenderWindow& window, const sf::Vector2f& rectSize)
                        : _window(window),         //Inicijalizaciona lista
                          _rectSize(rectSize)

{

    _windowSize.x = windowWidth / rectSize.x;     //Rezolucija podeljena sa velicinom pravougaonika
    _windowSize.y = windowHeight / rectSize.y;

    std::vector<sf::RectangleShape> _gridVec (_windowSize.x * _windowSize.y);       //Inicijalizacija velicine vektora za pravougaonike

}


//Destructor
GridSystem::~GridSystem()
{
    //destructor
}


//ToggleGrid: Napuni vektor grid pravougaonicima
void GridSystem::populateGridVec ()
{

    for (unsigned char i=0; i < _windowSize.x; ++i)
    {
        for (unsigned char j=0; j < _windowSize.y; ++j)
        {
            sf::RectangleShape lRect(_rectSize);         //lRect - Local variable
            lRect.setPosition((i*50), (j*50) );
            lRect.setFillColor(sf::Color::Transparent);
            lRect.setOutlineThickness(1);
            lRect.setOutlineColor(sf::Color::White);
            _gridVec.push_back(lRect);
        }
    }

}


//Draw: Iscrtaj grid na ekran
void GridSystem::draw()
{
    if (_isActivated == true)        //Ako je bool na true iscrtaj grid na glavni prozor
    {
        for (auto& i: _gridVec)
        {
            _window.draw(i);
        }
    }

}



void GridSystem::toggleGrid()  //Menja vrednost bool clana isActivated na true/false. Koristi se u main()
{
    if (_gridVec.empty())     //Ako je vektor prazan, napuni ga grid clanovima (cetvorouglovima)
        populateGridVec();

    if (!_isActivated)       //Ako je bool clan isActivated na false, postavi ga na true
        _isActivated = true;
    else if (_isActivated)   //Ako je bool clan isActivated na true, postavi ga na false
        _isActivated = false;

}








