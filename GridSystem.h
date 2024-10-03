/*KLASA ZA ISCRTAVANJE GRIDA NA GLAVNI EKRAN.
  -KONSTRUKTOR PRIMA 3 ARGUMENTA: REZOLUCIJA GLAVNOG PROZORA PO DUZINI (U PIXELIMA),
                                  REZOLUCIJA GLAVNOG PROZORA PO SIRINI (U PIXELIMA),
                                  REFERENCA NA GLAVNI PROZOR,
                                  SF::VEKTORF SA DIMENZIJAMA CETVOROUGLA (DIMENZIJE JEDNOG CLANA GRIDA)

  -POPULATEGRIDVEC FUNKCIJA POPUNJAVA VEKTOR GRID CLANOVIMA, DODELJUJE IM DIMENZIJE, POZICIJU, BOJU...
  -TOGGLEGRID FUNKCIJA SE POZIVA IZ MAIN-a, POSTAVLJA CLAN BOOL ISACTIVATED (FLAG) NA TRUE ILI FALSE (GRID UPALJEN/UGASEN) AKO JE ODREDJENI TASTER PRITISNUT.
  -DRAW FUNKCIJA SE POZIVA IZ MAIN-a. CRTA GRID NA GLAVNI EKRAN, POZIVA SE IZ RENDER ODELJKA u main().

*/
#ifndef GRIDSYSTEM_H
#define GRIDSYSTEM_H
#include <SFML/Graphics.hpp>
#include <vector>


class GridSystem
{
    private:
        bool                            _isActivated = false;       //Da li je upaljena grid mapa (flag)
        sf::RenderWindow&               _window;      //Reference varijabla za skladistenje reference sf::RenderWindow. Inicijalizacija u inizijalizacionoj listi (konstruktor)
        const sf::Vector2f              _rectSize;    //Velicina jednog cetvorougla
        sf::Vector2u                    _windowSize;  //Rezolucija glavnog prozora
        std::vector<sf::RectangleShape> _gridVec;     //Vector za skladistenje grid clanova (cetvorougla)

        void populateGridVec();                       //Puni vektor grid cetvorouglovima


    public:
        GridSystem (const unsigned& windowWidth, const unsigned& windowHeight, sf::RenderWindow& window, const sf::Vector2f& rectSize);    //Konstruktor

        void draw ();       //Draw funkcija, prima referencu na glavni prozor. Crta grid na glavni prozor

        void toggleGrid();                          //Menja vrednost clana bool isActivated (upaljen/ugasen grid), koristi se u main()

        virtual ~GridSystem();

    protected:




};

#endif // GRIDSYSTEM_H
