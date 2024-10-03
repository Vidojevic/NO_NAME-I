#include "Screens.h"

Screens::Screens()
{
    font1.loadFromFile("assets/font1.otf");
    font2.loadFromFile("assets/font2.ttf");
    font3.loadFromFile("assets/font3.ttf");
}

Screens::~Screens()
{
}


//startScreen (Blue Screen)
void Screens::startScreen(sf::RenderWindow& window, sf::View& view)
{
    sf::Text text1("NO_NAME", font2, 150);
    text1.setPosition(500, 500);

    //Postavlja se view na text1
    view.setCenter(text1.getPosition().x +575, text1.getPosition().y + 200);

    sf::Text text2("Press SPACE to start the game", font1, 50);
    text2.setPosition(650, 725);

    sf::Text text3("Quit Game <Esc>", font1, 20);
    text3.setPosition(300, 1100);

    window.clear(sf::Color::Blue);

    window.draw(text1);
    if (frameCount%80 < 40)  //Blinkanje teksta 2. Ako je ostatak manji od 40 prikazi text, ako je veci ne iscrtavaj tekst.
                             //Posto modulo od 80 ima 80 razlicitih vrednosti, to znaci da ce prikazivanje
    {                        //i ne prikazivanje teksta vremenski isto.
        window.draw(text2);
    }
    window.draw(text3);
    window.setView(view);   //Obavezno je da se i View ovde renderuje inace nema efekat postavljanja view.setCenter

    ++frameCount;

}


//finishScreen
void Screens::finishScreen(sf::RenderWindow& window, sf::View& view, unsigned score, EntityManager& manager)
{

    //Set text position to View window center
    sf::Vector2f screenCenter1 = view.getCenter();  //Koordinate centra View ekrana za text1.Uvek se pojavljuje u centar View ekrana a ne celog glavnog ekrana.
    screenCenter1.x = screenCenter1.x - 425;        //Korekcija je potrebna jer origin je levi gornji ugao teksta a ne centar teksta.
    screenCenter1.y = screenCenter1.y - 150;        //

    sf::Vector2f screenCenter2 = view.getCenter();  //Koordinate centra View ekrana za text2.Uvek se pojavljuje u centar View ekrana a ne celog glavnog ekrana.
    screenCenter2.x = screenCenter2.x - 250;        //Korekcioja je potrebna jer origin je levi gornji ugao teksta a ne centar teksta.
    screenCenter2.y = screenCenter2.y + 50;         //

    sf::Vector2f screenCenter3 = view.getCenter();  //Koordinate centra view ekrana za text2.Uvek se pojavljuje u centar view ekrana a ne celog glavnog ekrana.
    screenCenter3.x = screenCenter3.x - 530;        //Korekcioja je potrebna jer origin je levi gornji ugao teksta a ne centar teksta.
    screenCenter3.y = screenCenter3.y - 50 ;        //

    //Ispis na ekran
    sf::Text text1("CONGRATULATIONS!!!", font1, 80);   //80 je velicina fonta
    text1.setPosition(screenCenter1);

    sf::Text text3("Your Score: " + std::to_string(scoreToShow), font3, 70);
    text3.setPosition(screenCenter2);
    if (scoreToShow < score)   //Puni score
    {
        scoreToShow += 50;
    }


    sf::Text text2("Do you want to start again? Y/N", font1, 60);
    text2.setPosition(screenCenter3);

    window.draw(text1);
    window.draw(text2);
    window.draw(text3);

    //Da li zelite da nastavite- input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))  //Restartuje igru
    {
        manager.musicVec[1]->play();
        restartGame = true;  //Fleg member ove klase koristi se da uzme input sa ekrana i pokrene funkciju restart u Game klasi.
        scoreToShow = 0;     //Resetuj score data member (Ne mesati sa intsScore iz Game klase). Ovaj ovde sluzi da bi se score punio (efekat postepeng punjenja)
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))  //Vraca na plavi ekran
    {
        //Pusti muziku za blue screen. Ovde je mesto gde igra menja svoj STATE, prelazi iz jedan ekran u drugi.
        manager.musicVec[1]->stop();
        manager.musicVec[0]->play();
        manager.musicVec[0]->setLoop(true);

        isGameStart =  false;  //Ovaj fleg vraca na pocetni ekrna (plavi ekran).
        scoreToShow = 0;       //Resetuj score data member (Ne mesati sa intsScore iz Game klase). Ovaj ovde sluzi da bi se score punio (efekat postepeng punjenja)
//        restartGame = true;    //Pokrece se restart kako bi se svi entity vratili na svoje pocetne vrednosti, kad se pritisne space iz plavog ekrana da mapa bude spremna.
    }
}


//endScreen
void Screens::endScreen(sf::RenderWindow& window, sf::View& view, unsigned score, EntityManager& manager)
{

    //Set text position to View window center
    sf::Vector2f screenCenter1 = view.getCenter();  //Koordinate centra View ekrana za text1.Uvek se pojavljuje u centar View ekrana a ne celog glavnog ekrana.
    screenCenter1.x = screenCenter1.x - 250;        //Korekcija je potrebna jer origin je levi gornji ugao teksta a ne centar teksta.
    screenCenter1.y = screenCenter1.y - 150;        //

    sf::Vector2f screenCenter2 = view.getCenter();  //Koordinate centra View ekrana za text2.Uvek se pojavljuje u centar View ekrana a ne celog glavnog ekrana.
    screenCenter2.x = screenCenter2.x - 490;        //Korekcioja je potrebna jer origin je levi gornji ugao teksta a ne centar teksta.
    screenCenter2.y = screenCenter2.y + 50;         //

    sf::Vector2f screenCenter3 = view.getCenter();  //Koordinate centra view ekrana za text2.Uvek se pojavljuje u centar view ekrana a ne celog glavnog ekrana.
    screenCenter3.x = screenCenter3.x - 240;        //Korekcioja je potrebna jer origin je levi gornji ugao teksta a ne centar teksta.
    screenCenter3.y = screenCenter3.y - 50 ;        //

    sf::Text text1("GAME OVER", font1, 80);   //80 je velicina fonta
    text1.setPosition(screenCenter1);

    sf::Text text2("Do you want to try again? Y/N", font1, 60);
    text2.setPosition(screenCenter2);

    sf::Text text3("Your Score: " + std::to_string(scoreToShow), font3, 70);
    text3.setPosition(screenCenter3);
    if (scoreToShow < score)   //Puni score
    {
        scoreToShow += 50;
    }

    window.draw(text1);
    window.draw(text2);
    window.draw(text3);

    //Da li zelite da nastavite- input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))  //Restartuje igru
    {
        manager.musicVec[1]->play();
        restartGame = true;  //Fleg member ove klase koristi se da uzme input sa ekrana i pokrene funkciju restart u Game klasi.
        scoreToShow = 0;     //Resetuj score data member (Ne mesati sa intsScore iz Game klase). Ovaj ovde sluzi da bi se score punio (efekat postepeng punjenja)
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))   //Vraca na plavi ekran
    {
        //Pusti muziku za blue screen. Ovde je mesto gde igra menja svoj STATE, prelazi iz jedan ekran u drugi.
        manager.musicVec[1]->stop();
        manager.musicVec[0]->play();
        manager.musicVec[0]->setLoop(true);

        isGameStart =  false;  //Ovaj fleg vraca na pocetni ekrna (plavi ekran).
        scoreToShow = 0;       //Resetuj score data member (Ne mesati sa intsScore iz Game klase). Ovaj ovde sluzi da bi se score punio (efekat postepeng punjenja)
//        restartGame = true;    //Pokrece se restart kako bi se svi entity vratili na svoje pocetne vrednosti, kad se pritisne space iz plavog ekrana da mapa bude spremna.
    }
}


//getIsGameStart
bool Screens::getIsGameStart()
{
    return isGameStart == true ? true : false;
}


//setIsGameStart
void Screens::setIsGameStart()
{
    isGameStart = true;
}


//setIsGameStartFalse
void Screens::setIsGameStartFalse()
{
    isGameStart = false;
}


//getRestartGame
bool Screens::getRestartGame()
{
    return restartGame == true ? true : false;
}


//setRestartGameFalse
void Screens::setRestartGameTrue()                                 //Vraca restartGame na false. Koristi se u Game->restart funkciji.
{
    restartGame = true;
}


//setRestartGameFalse
void Screens::setRestartGameFalse()                                 //Vraca restartGame na false. Koristi se u Game->restart funkciji.
{
    restartGame = false;
}






