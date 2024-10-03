#include "Game.h"

Game::Game()  {}
Game::~Game() {}



//game
void Game::run()
{
//Main window
    const unsigned WINDOW_WIDTH  = 1920;
    const unsigned WINDOW_HEIGHT = 1080;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "NO_NAME", sf::Style::Fullscreen);
    window.setFramerateLimit(60);


//Background picture
    sf::Texture background;
    sf::Sprite sBackground;
    if (!background.loadFromFile("assets/background.jpeg"))
        {
            std::cout << "Failure to load texture!" << "\n";
        }
    sBackground.setTexture(background);
    sBackground.setPosition(0,0);

//Screens
    Screens screens;
//View
    sf::View view;                           //Dole u Render odeljku je setovan view da samo prati plejera po X osi, po Y ne. Znaci da se kamera ne pomera kad plejer skace.
    view.setSize(1600, 900);                 //Velicina view prozora.                                             //Pre render odeljka dole je isto odradjen uslov da view ne izlazi van glavnog prozora.
//Event object
    sf::Event event;
//FPS object
    FPS fps;
//Movement object
    Movement movement;
//Grid object
    GridSystem gridSys(WINDOW_WIDTH, WINDOW_HEIGHT, window, sf::Vector2f(50,50));  //Kreiranje GridSystem objekta
//EntityManager object
    EntityManager manager;
    manager.texturesInitialization();   //Inicijalizacija svih texture i stavljanje u textureTileVec vektor za dalje koriscenje (pointeri na texture).
    manager.soundInit();                //Inicijalizacija zvuka
    manager.musicInit();                //Inicijalizacija vecih sound fajlova za muziku
//Score
    sf::Font font;
    font.loadFromFile("assets/font3.ttf");         //Load font
    sf::Text score("SCORE - " + std::to_string(scoreInt), font, 40);      //Set score on the screen. Na pocetku glavnog game loop-a se setuje pozicija na osnovu View prozora.
                                                                          //Takodje se varijabla unsigned scoreInt konvertuje u string i dodaje se tekstu SCORE.
                                                                          //Varijabla scoreInt je data member ove klase (Game klase).


/// +++++++++ X i Y VRENOSTOTI (rectSize) NE SMEJU DA BUDE NEPARNE, NITI VELICINE RECT SIZE!!!!! ++++++++++
                /// +++++++++ OVO VAZI ZA SVE ENTITIJE ZBOG KOLIZIJE ++++++++++++++++++


///Game Inizialization
    initialization(manager);


//Collision object
    Collision collision;


//Pusti blue screen muziku
manager.musicVec[0]->play();


///MAIN LOOP
    while(window.isOpen())
    {
        std::cout << "Velicina soundVeca: " << manager.soundVec.size() << "\n";

        for (Entity& i : manager.entityEnemyStorage)
        {
            std::cout << "Patrol position begin: " << i.ptrCEnemyAssets->xPatrolBegin << " " << "Patrol position end: " << i.ptrCEnemyAssets->xPatrolEnd << "\n";
        }


      ///START_WINDOW LOOP (Blue Screen)
        while (!screens.getIsGameStart() && window.isOpen())
        {
            //Pozovi startScreen
            screens.startScreen(window, view);

            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();

                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F4))  //Paljenje grida (postavljanje flega na ukljuceno ili iskljuceno true/false)
                {
                    gridSys.toggleGrid();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    //Promeni muziku pilikom pritiska space. Ovde je mesto gde igra menja svoj STATE, prelazi iz jedan ekran u drugi.
                    manager.musicVec[0]->stop();
                    //manager.musicVec[1]->setVolume(0);
                    manager.musicVec[1]->play();
                    manager.musicVec[1]->setLoop(true);

                    //Ako je space pritisnut, setuj flag za pokretanje igre na true
                    screens.setIsGameStart();
                    //Restartuj igru
                    restart(manager, screens, movement);
                }
            }


            //Rendering start window (blue screen)
            gridSys.draw();
            window.display();
        }


       //FPS
       fps.update();
	   std::ostringstream ss;
	   ss << fps.getFPS();
	   window.setTitle(ss.str());



    ///SETTING PREVIOUS POSITION
        manager.setPrevPos();       //Setovanje varijable prevPos iz Entity.Ctransform->prevPos. Funkcija se nalazi u EntityManager. Mora ovde na pocetak main while loop-a.


    ///SCORE- Setovanje pozicije na osnovu View prozora (prati view prozor a ne glavni prozor).
        sf::Vector2f scorePos1 = view.getCenter();  //Da prati view prozor a ne glavni
        scorePos1.x = scorePos1.x - 790;
        scorePos1.y = scorePos1.y - 400;

        sf::Text score("SCORE - " + std::to_string(scoreInt), font, 40);  //Ovde se integer pretvara u string kako bi se ispisao na ekran i dodaje se tekstu SCORE.

        score.setPosition(scorePos1);



        std::cout << "Broj pointera: " << manager.textureTileVec.size() << "\n";


    ///EVENT LOOP

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                //vrati na pocetni ekran (blue screen)
                manager.musicVec[1]->stop();
                manager.musicVec[0]->play();
                screens.setIsGameStartFalse();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F4))  //Paljenje grida (postavljanje flega na ukljuceno ili iskljuceno true/false)
            {
                gridSys.toggleGrid();
            }
        }


    ///MOVEMENT
        //enemy
        movement.enemyMovement(manager.entityEnemyStorage, manager.entityBossStorage);
        //player
        movement.playerMovementGravity(manager.entityPlayerStorage);


 //       std::cout << "Counter: " << movement.sprtCntr << "\n";  //counter


    ///COLLISION
    //Enemy
        for (Entity& i: manager.entityEnemyStorage)
        {
            //PROXIMITY---Ako su objekti blizi od 100 piksela, propusti ih kroz koliziju.
            if (manager.distance(manager.entityPlayerStorage[0].ptrCTransform->position, i.ptrCTransform->position))
            {
                 // Proveravaj samo aktivne entitije i kada je plejer aktivan
                if  (i.getIsActive() && manager.entityPlayerStorage[0].getIsActive())
                {
                    if (collision.isCollision(manager.entityPlayerStorage[0], i))
                    {
                        std::cout << "Kolizija se desila!!!\n";

                    //Right collision
                        if (collision.isRightCollision(manager.entityPlayerStorage[0], i))
                        {
                            //Korekcija plejera
                            manager.entityPlayerStorage[0].ptrCTransform->position.x -= collision.overlap.x;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                            std::cout << "RIGHT COLLISION!!\n";

                            --manager.entityPlayerStorage[0].ptrCPlayerAssets->health;  //Smanji plejeru health za jedan
                            manager.entityPlayerStorage[0].ptrCPlayerAssets->isPlayerHit = true;  //Flag za oduzimanje healtha u entityManager->draw, water+health sekcija
                            manager.entityPlayerStorage[0].destroy();  //Ne unistava plejera, samo ga trenutno postavlja na Inactive dok traje animacija oduzimanja healtha

                            //play sound if player has nomore health
                            if (manager.entityPlayerStorage[0].ptrCPlayerAssets->health == 0)
                            {
                                manager.musicVec[1]->stop();
                                manager.soundVec[3].play();
                            }

                            //Ovo je dodatna provera za top i bottom koliziju u okviru right kolizije jer pri sudaru dva objekta koja se krecu postoji bug koji ne koriguje kako treba
                            //i kao rezultat toga javljaju se dve kolizije istovremeno (right i top kolizija ili right i bottom). Ova linija dole koriguje taj bug.
                            if (collision.isTopCollision(manager.entityPlayerStorage[0], i))
                            {
                                continue;
                            }
                            if (collision.isBottomCollision(manager.entityPlayerStorage[0], i))
                            {
                                continue;
                            }
                        }
                    //Left collision
                        else if (collision.isLeftCollision(manager.entityPlayerStorage[0], i))
                        {
                            //Korekcija plejera
                            manager.entityPlayerStorage[0].ptrCTransform->position.x += collision.overlap.x;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                            std::cout << "LEFT COLLISION!!!\n";

                            --manager.entityPlayerStorage[0].ptrCPlayerAssets->health;  //Smanji plejeru health za jedan
                            manager.entityPlayerStorage[0].ptrCPlayerAssets->isPlayerHit = true;  //Flag za oduzimanje healtha u entityManager->draw, water+health sekcija
                            manager.entityPlayerStorage[0].destroy();  //Ne unistava plejera, samo ga trenutno postavlja na Inactive dok traje animacija oduzimanja healtha

                            //play sound if player has no more health
                            if (manager.entityPlayerStorage[0].ptrCPlayerAssets->health == 0)
                            {
                                manager.musicVec[1]->stop();
                                manager.soundVec[3].play();
                            }


                            //Ovo je dodatna provera za top i bottom koliziju u okviru left kolizije jer pri sudaru dva objekta koja se krecu postoji bug koji ne koriguje kako treba
                            //i kao rezultat toga javljaju se dve kolizije istovremeno (right i top kolizija ili right i bottom). Ova linija dole koriguje taj bug i preskace dalja ispitivanja kolizije.
                            if (collision.isTopCollision(manager.entityPlayerStorage[0], i))
                            {
                                continue;
                            }
                            if (collision.isBottomCollision(manager.entityPlayerStorage[0], i))
                            {
                                continue;
                            }
                        }
                    //Top collision
                        if (collision.isTopCollision(manager.entityPlayerStorage[0], i))
                        {
                            manager.entityPlayerStorage[0].ptrCTransform->position.y += collision.overlap.y;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                            std::cout << "TOP COLLISION!!!\n";

                        }
                    //Bottom collision
                        else if (collision.isBottomCollision(manager.entityPlayerStorage[0], i))
                        {
                            std::cout << "BOTTOM COLLISION!!!\n";

                            --i.ptrCEnemyAssets->health;    //Oduzmi jedan health enemiju
                            manager.entityPlayerStorage[0].ptrCPlayerAssets->isEnemyHit = true;
                            scoreInt += 1000;  //500 poena za kostura
                            //play sound
                            manager.soundVec[0].play();

                         }
                    }
                }
            }
        }

    //Boss
        for (Entity& i: manager.entityBossStorage)
        {
            //PROXIMITY---Ako su objekti blizi od 100 piksela, propusti ih kroz koliziju.
            if (manager.distance(manager.entityPlayerStorage[0].ptrCTransform->position, i.ptrCTransform->position))
            {
                // Proveravaj samo aktivne entitije i kada je plejer aktivan
                if  (i.getIsActive() && manager.entityPlayerStorage[0].getIsActive())
                {
                    if (collision.isCollision(manager.entityPlayerStorage[0], i))
                    {
                        std::cout << "Kolizija se desila!!!\n";

                    //Right collision
                        if (collision.isRightCollision(manager.entityPlayerStorage[0], i))
                        {
                            //Korekcija plejera
                            manager.entityPlayerStorage[0].ptrCTransform->position.x -= collision.overlap.x;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                            std::cout << "RIGHT COLLISION!!\n";

                            --manager.entityPlayerStorage[0].ptrCPlayerAssets->health;  //Smanji plejeru health za jedan
                            manager.entityPlayerStorage[0].ptrCPlayerAssets->isPlayerHit = true;  //Flag za oduzimanje healtha u entityManager->draw, water+health sekcija
                            manager.entityPlayerStorage[0].destroy();  //Ne unistava plejera, samo ga trenutno postavlja na Inactive dok traje animacija oduzimanja healtha

                            //play sound if player has no more health
                            if (manager.entityPlayerStorage[0].ptrCPlayerAssets->health == 0)
                            {
                                manager.musicVec[1]->stop();
                                manager.soundVec[3].play();
                            }

                            //Ovo je dodatna provera za top i bottom koliziju u okviru right kolizije jer pri sudaru dva objekta koja se krecu postoji bug koji ne koriguje kako treba
                            //i kao rezultat toga javljaju se dve kolizije istovremeno (right i top kolizija ili right i bottom). Ova linija dole koriguje taj bug.
                            if (collision.isTopCollision(manager.entityPlayerStorage[0], i))
                            {
                                continue;
                            }
                            if (collision.isBottomCollision(manager.entityPlayerStorage[0], i))
                            {
                                continue;
                            }
                        }
                    //Left collision
                        else if (collision.isLeftCollision(manager.entityPlayerStorage[0], i))
                        {
                            //Korekcija plejera
                            manager.entityPlayerStorage[0].ptrCTransform->position.x += collision.overlap.x;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                            std::cout << "LEFT COLLISION!!!\n";

                            --manager.entityPlayerStorage[0].ptrCPlayerAssets->health;  //Smanji plejeru health za jedan
                            manager.entityPlayerStorage[0].ptrCPlayerAssets->isPlayerHit = true;  //Flag za oduzimanje healtha u entityManager->draw, water+health sekcija
                            manager.entityPlayerStorage[0].destroy();  //Ne unistava plejera, samo ga trenutno postavlja na Inactive dok traje animacija oduzimanja healtha

                            //play sound if player has no more health
                            if (manager.entityPlayerStorage[0].ptrCPlayerAssets->health == 0)
                            {
                                manager.musicVec[1]->stop();
                                manager.soundVec[3].play();
                            }


                            //Ovo je dodatna provera za top i bottom koliziju u okviru left kolizije jer pri sudaru dva objekta koja se krecu postoji bug koji ne koriguje kako treba
                            //i kao rezultat toga javljaju se dve kolizije istovremeno (right i top kolizija ili right i bottom). Ova linija dole koriguje taj bug i preskace dalja ispitivanja kolizije.
                            if (collision.isTopCollision(manager.entityPlayerStorage[0], i))
                            {
                                continue;
                            }
                            if (collision.isBottomCollision(manager.entityPlayerStorage[0], i))
                            {
                                continue;
                            }
                        }
                    //Top collision
                        if (collision.isTopCollision(manager.entityPlayerStorage[0], i))
                        {
                            manager.entityPlayerStorage[0].ptrCTransform->position.y += collision.overlap.y;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                            std::cout << "TOP COLLISION!!!\n";
                        }
                    //Bottom collision
                        else if (collision.isBottomCollision(manager.entityPlayerStorage[0], i))
                        {
                            std::cout << "BOTTOM COLLISION!!!\n";

                            --i.ptrCEnemyAssets->health;    //Oduzmi jedan health enemiju
                            manager.entityPlayerStorage[0].ptrCPlayerAssets->isEnemyHit = true;

                            if (i.ptrCEnemyAssets->health == 0)  //kad ubijes Boss-a, score +3000 poena.
                            {
                                //play sound
                                manager.soundVec[1].setVolume(30);
                                manager.soundVec[1].play();
                                scoreInt += 3000;
                            }
                        }
                    }
                }
            }
        }

    //Normal Tiles
        for (Entity& i: manager.entityTreeStorage)
        {
            if (manager.distance(manager.entityPlayerStorage[0].ptrCTransform->position, i.ptrCTransform->position))  //PROXIMITY---Ako su objekti blizi od 100 piksela, propusti ih kroz koliziju.
            {
                if (i.getIsActive())   // Proveravaj samo aktivne entitije
                {
                    if (collision.isCollision(manager.entityPlayerStorage[0], i))
                    {
                    //Poluga za kraj igrice
                        if (i.getTag() == "tile14" && !manager.entityBossStorage[0].getIsActive())  //Ako je bila bilo kakva kolizija  sa polugom za kraj igrice, i ako je ubijen Boss,
                        {                                                                           //postavi animaciju na true (moze da se pomeri poluga)
                            //play sound
                            manager.musicVec[1]->stop();
                            manager.soundVec[4].setVolume(20);
                            manager.soundVec[4].play();

                            i.ptrCTileAssets->animation = true;
                            continue;
                        }
                        else if (i.getTag() == "tile14" && manager.entityBossStorage[0].getIsActive())  //Ako je bila kolizija sa polugom za kraj igrice i ako je Boss jos uvek ziv,
                        {                                                                               //predji u drugu iteraciju i ne proveravaj tile14 na koliziju jer zelim da
                            continue;                                                                   //moze da prodje kroz polugu a ne da udara u nju.
                        }
                            std::cout << "Kolizija se desila!!!\n";

                    //UGLOVI
                    //Right-Top
                        if (collision.isRightCollision(manager.entityPlayerStorage[0], i) && collision.isTopCollision(manager.entityPlayerStorage[0], i))
                        {
                            manager.entityPlayerStorage[0].ptrCTransform->position.x -= collision.overlap.x;
                            manager.entityPlayerStorage[0].ptrCTransform->position.y -= collision.overlap.y;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                        }
                    //Right-Bottom
                        else if (collision.isRightCollision(manager.entityPlayerStorage[0], i) && collision.isBottomCollision(manager.entityPlayerStorage[0], i))
                        {
                            manager.entityPlayerStorage[0].ptrCTransform->position.x -= collision.overlap.x;
                            manager.entityPlayerStorage[0].ptrCTransform->position.y += collision.overlap.y;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                        }
                    //Left-Top
                        if (collision.isLeftCollision(manager.entityPlayerStorage[0], i) && collision.isTopCollision(manager.entityPlayerStorage[0], i))
                        {
                            manager.entityPlayerStorage[0].ptrCTransform->position.x += collision.overlap.x;
                            manager.entityPlayerStorage[0].ptrCTransform->position.y -= collision.overlap.y;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                        }
                    //Left-Bottom
                        else if (collision.isLeftCollision(manager.entityPlayerStorage[0], i) && collision.isBottomCollision(manager.entityPlayerStorage[0], i))
                        {
                            manager.entityPlayerStorage[0].ptrCTransform->position.x += collision.overlap.x;
                            manager.entityPlayerStorage[0].ptrCTransform->position.y += collision.overlap.y;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                        }
                    ///////////////
                    //Right
                        if (collision.isRightCollision(manager.entityPlayerStorage[0], i))
                        {
                            manager.entityPlayerStorage[0].ptrCTransform->position.x -= collision.overlap.x;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                            std::cout << "RIGHT COLLISION!!\n";
                        }
                    //Left
                        else if (collision.isLeftCollision(manager.entityPlayerStorage[0], i))
                        {
                            manager.entityPlayerStorage[0].ptrCTransform->position.x += collision.overlap.x;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                            std::cout << "LEFT COLLISION!!!\n";
                        }
                    //Top
                        if (collision.isTopCollision(manager.entityPlayerStorage[0], i))
                        {
                            manager.entityPlayerStorage[0].ptrCTransform->position.y += collision.overlap.y;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                            std::cout << "TOP COLLISION!!!\n";

                            movement.jumpVelocity = 0;             //Kad udari u plafon, jumpVelocity na 0

                            if (i.getTag() == "tile0" || i.getTag() == "tile1" || i.getTag() == "tile2")   //Samo navedene tiles unisti prilikom kolizije(sledi animacija i unistavanje tile-a).
                            {                            //Morao sam ovaj uslov da ubacim ovde jer sam stavio obicne tile i ove neunistive u isti vektor. Da bi se izbeglo unistavanje i ovih tile-ova, ovaj uslov to sprecava.
                                i.ptrCTileAssets->animation = true;   //Ako je plejer udario glavom tile odozdo postavi bool na true. Prestaje da se crta rectangle sa spritom i entity postaje inactive
                            }
                        }
                    //Bottom
                        else if (collision.isBottomCollision(manager.entityPlayerStorage[0], i))
                        {
                            manager.entityPlayerStorage[0].ptrCTransform->position.y -= collision.overlap.y;
                            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                            std::cout << "BOTTOM COLLISION!!!\n";

                            movement.isJump = false;           //Ako bude bottom kolizija postavi isJump na false, moze ponovo da skace
                            movement.jumpPressed = false;       // Skok vise nije u toku, animacija za skok se prekida
                        }
                    }
                }
            }
        }
    //Special Tiles
        for (Entity& i: manager.entitySpecialTilesStorage)
        {
            if (manager.distance(manager.entityPlayerStorage[0].ptrCTransform->position, i.ptrCTransform->position))  //PROXIMITY---Ako su objekti blizi od 100 piksela, propusti ih kroz koliziju.
            {
                if (collision.isCollision(manager.entityPlayerStorage[0], i))
                {
                    std::cout << "Kolizija se desila!!!\n";

                //Right
                    if (collision.isRightCollision(manager.entityPlayerStorage[0], i))
                    {
                        manager.entityPlayerStorage[0].ptrCTransform->position.x -= collision.overlap.x;
                        manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                        std::cout << "RIGHT COLLISION!!\n";
                    }
                //Left
                    else if (collision.isLeftCollision(manager.entityPlayerStorage[0], i))
                    {
                        manager.entityPlayerStorage[0].ptrCTransform->position.x += collision.overlap.x;
                        manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                        std::cout << "LEFT COLLISION!!!\n";
                    }
                //Top
                    if (collision.isTopCollision(manager.entityPlayerStorage[0], i))
                    {
                        manager.entityPlayerStorage[0].ptrCTransform->position.y += collision.overlap.y;
                        manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                        std::cout << "TOP COLLISION!!!\n";

                        //play sound samo jednom, dok je aktivan. Posle udarca odmah pelazi u neaktivan sto znaci da ce biti zvuk samo jednom.
                        if (i.getIsActive())
                        {
                            manager.soundVec[2].play();
                        }
                        movement.jumpVelocity = 0;             //Kad udari u plafon, jumpVelocity na 0

                        i.ptrCTileAssets->animation = true;   //Ako je plejer udario glavom tile odozdo postavi bool na true. Krece animacija za special tile, objekat ostaje ziv, kao i shape.

                        if (!i.getIsActive())    //Preskoci ako je vec udaren (ako je vec dao bodove, postavljen je na inaktive, linija ispod).
                        {                        //Ovaj uslov nije postavljen na pocetak provere kolizije za special tiles jer zelim da i dalje radi proveru na koliziju.
                            continue;
                        }
                        scoreInt += 500;    //score +500 poena
                        i.destroy();        //Stavi na inactive da bi samo jednom otkucao poene. U suprotnom special tile moze da se udara nebrojeno puta i uvek da otkuca poene.
                    }
                //Bottom
                    else if (collision.isBottomCollision(manager.entityPlayerStorage[0], i))
                    {
                        manager.entityPlayerStorage[0].ptrCTransform->position.y -= collision.overlap.y;
                        manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
                        std::cout << "BOTTOM COLLISION!!!\n";

                        movement.isJump = false;           //Ako bude bottom kolizija postavi isJump na false, moze ponovo da skace
                        movement.jumpPressed = false;       // Skok vise nije u toku, animacija za skok se prekida
                    }
                }
            }
        }


    ///Funkcija koja omogucava odbijanje plejera kad skoci neprijatelju na glavu. isEnemyHit se postavlja na true kada kolizija registruje Enemy->bottom i Boss->bottom koliziju.
        //Algoritma za ovu funkciju je uzet iz Movement klase->playerMovement + Gravity, odeljak JUMP i prilagodjen ovoj svrsi.
        if (manager.entityPlayerStorage[0].ptrCPlayerAssets->isEnemyHit == true && jumpVelocity > 0)
        {
            manager.entityPlayerStorage[0].ptrCTransform->position.y -= jumpVelocity;  //jumpVelocity je varijabla koja pripada ovoj klasi Game. Postavljena je na 25
            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);

            jumpVelocity -= 1;                        //Smanjuj jumpVelocity svaki frejm
        }
        else if (manager.entityPlayerStorage[0].ptrCPlayerAssets->isEnemyHit && jumpVelocity == 0)  //Kad varijabla dostigne nulu
        {
            jumpVelocity = 25;                                                                      //Resetuj jumpVelocity opet na 25
            manager.entityPlayerStorage[0].ptrCPlayerAssets->isEnemyHit = false;                    //Resetuj isEnemyHit na false
        }

    ///Funkcija koja oduzima 2 healtha ako plejer padne u vodu (ode ispod odredjene Y ose.
        if (manager.entityPlayerStorage[0].ptrCTransform->position.y > 1050 && manager.entityPlayerStorage[0].ptrCPlayerAssets->health > 0)
        {
            //play sound
            manager.musicVec[1]->stop();
            manager.soundVec[3].play();

            --manager.entityPlayerStorage[0].ptrCPlayerAssets->health;  //Oduzima po jedan healt po frejmu
            manager.entityPlayerStorage[0].ptrCPlayerAssets->isPlayerHit = true;  //Flag za oduzimanje healtha u entityManager->draw, water+health sekcija
        }

    ///Funkcije koja ogranicava plejeru izlaz van mape, levo i desno
        if (manager.entityPlayerStorage[0].ptrCTransform->position.x < 25)
        {
            manager.entityPlayerStorage[0].ptrCTransform->position.x += 3;
            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
        }
        else if (manager.entityPlayerStorage[0].ptrCTransform->position.x > 1895)
        {
            manager.entityPlayerStorage[0].ptrCTransform->position.x -= 3;
            manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
        }



    ///View Update
        //(da view ne bi izlazio van glavnog ekrana, da bi ostao u granicama velicine glavnog prozora
        view.setCenter(manager.entityPlayerStorage[0].ptrCTransform->position.x, 625);   //Prati plejera osim u ova dva slucaja dole, na pocetak ekrana i na kraj ekrana.

        if (manager.entityPlayerStorage[0].ptrCTransform->position.x < 800)
        {
            view.setCenter(800, 625);
        }
        else if (manager.entityPlayerStorage[0].ptrCTransform->position.x > 1120)
        {
            view.setCenter(1120,625);
        }

    ///View Center
        //sluzi da se posalje kao argument manager.draw funkciji odmah ispod u Rendering. Da ne bi slao view kao argument, poslacu ovu varijablu. Salje poziciju centra View prozora
       // sf::Vector2f screenCenter = view.getCenter();  //Koordinate centra View ekrana a ne glavnog ekrana.



    ///Game Restart
	   if (screens.getRestartGame())
       {
            restart(manager, screens, movement);
       }


    ///RENDERING

        window.clear(sf::Color::Black);

    //Background
        window.draw(sBackground);        //Pozadinska slika
    //Grid System
        gridSys.draw();
    //Score Text
        window.draw(score);
    //Enitites
        manager.draw(window, view);            //Updejtuje i crta sve entitije
    //Update sprite
        manager.updateSprite();          //Sprite je ovde jer prvo bi trebao plejer da se updejtuje pa onda da ga prati sprite. Updejtuje poziciju player sprajta
    //Prikaz screen uspesno zavrsen level
        if (manager.entityPlayerStorage[0].ptrCPlayerAssets->isLeverActivated)
        {
            screens.finishScreen(window, view, scoreInt, manager);
        }
    //Prikaz neuspesno zavrsenog levela
        if (manager.entityPlayerStorage[0].ptrCPlayerAssets->health == 0)
        {
            screens.endScreen(window, view, scoreInt, manager);
        }
    //View                           //View mora ovde jer prvo mora plejer da se updejtuje pa onda View
        window.setView(view);
    //Display
        window.display();

    }
}


///Initialization
void Game::initialization(EntityManager& manager)
{
    std::string storeConfigFileLine;                          //storeConfigFileLine- Skladistenje jedne linije config fajla.
    std::string entityType;                                   //entityType- Prvi argument AddEntity funkcije.

    sf::Vector2f entityPosition, entitySize, entityVelocity;  //Ostali argumenti za popunjavanje funkcije AddEntity.
    unsigned enemyPatrolBegin, enemyPatrolEnd;                //Za Enemy i Boss granice u koje patrolira.
                                                              //addEntity funkcija ne prima ove argumente, oni se ubacuju nakon kreiranja svih entitija. Postoji poseban config fajl
                                                              //samo za ovo - configPatrol.txt

    std::ifstream inputStream;                //Otvori config fajl.
    inputStream.open("assets/config.txt");

    if (inputStream)                          //Ako je fajl otvoren.
    {
        while (std::getline(inputStream, storeConfigFileLine))                //Ucitaj jednu liniju iz config fajla u storeConfigFileLine.
        {
            std::istringstream parseConfigLine(storeConfigFileLine);          //Pokupi samo reci bez razmaka iz storeConfigFileLine.
            while (parseConfigLine >> entityType                              //Upisi rec po rec u navedene varijable
                                   >> entityPosition.x >> entityPosition.y
                                   >> entitySize.x >> entitySize.y
                                   >> entityVelocity.x >> entityVelocity.y)
            {
                manager.addEntity(entityType, entityPosition, entitySize, entityVelocity);
            }
        }
    }
    else
    {
        std::cout << "ERROR LOADING GAME CONFIGURATION FILE!!!" << "/n";
        exit(100);
    }

    inputStream.close();          //Zatvori config fajl. Ovo je neophodno da bih opet mogao da koristim istu varijablu za otvaranje drugog fajla.

//Enemy Patrol initialization (mora ovako zbog loseg dizajna)
  //Funkcija za patrol se nalazi u Movement klasi, poziva se u main game loop.
    inputStream.open("assets/configPatrol.txt");

    if (inputStream)                          //Ako je fajl otvoren.
    {
        unsigned indexEnemy = 0;
        unsigned indexBoss  = 0;
        while (std::getline(inputStream, storeConfigFileLine))                //Ucitaj jednu liniju iz config fajla u storeConfigFileLine.
        {
            std::istringstream parseConfigLine(storeConfigFileLine);          //Pokupi samo reci bez razmaka iz storeConfigFileLine.
            while (parseConfigLine >> entityType >> enemyPatrolBegin >> enemyPatrolEnd)
            {
                if (entityType == "Enemy")
                {
                    manager.entityEnemyStorage[indexEnemy].ptrCEnemyAssets->xPatrolBegin = enemyPatrolBegin;
                    manager.entityEnemyStorage[indexEnemy].ptrCEnemyAssets->xPatrolEnd   = enemyPatrolEnd;
                    ++indexEnemy;
                }
                else if (entityType == "Boss")
                {
                    manager.entityBossStorage[indexBoss].ptrCEnemyAssets->xPatrolBegin = enemyPatrolBegin;
                    manager.entityBossStorage[indexBoss].ptrCEnemyAssets->xPatrolEnd   = enemyPatrolEnd;
                    ++indexBoss;
                }
            }
        }
    }
    else
    {
        std::cout << "ERROR LOADING PATROL CONFIGURATION FILE!!!" << "\n";
        exit(100);
    }

    inputStream.close();

}


///Restart
void Game::restart(EntityManager& manager, Screens& screens, Movement& movement)
{
    //Reset movable entities to start positions (Player. Enemy, Boss)
//Player
    manager.entityPlayerStorage[0].ptrCPlayerAssets->isLeverActivated = false;    //Postavljanje Player-a na pocetne vrednosti
    manager.entityPlayerStorage[0].ptrCPlayerAssets->health = 2;
    manager.entityPlayerStorage[0].ptrCTransform->position = manager.entityPlayerStorage[0].ptrCTransform->positionRestart;
    manager.entityPlayerStorage[0].eRectangle.setPosition(manager.entityPlayerStorage[0].ptrCTransform->position);
    this->scoreInt = 0;    //Postavljanje score na nula;
    manager.entityPlayerStorage[0].ptrCPlayerAssets->frameCount = 0;  //Frame count iz komponente PlayerAssets isto mora da se resetuje na nula.
    manager.entityPlayerStorage[0].ptrCPlayerAssets->isPlayerHit = false;  //Ako je slucajno ostao fleg da je pleyer izgubio health i nije se resetovao, ovde se resetuje.
    movement.isJump = true;   //Movement- resetuje se jump da ne bi mogao da skoci u vazduh na pocetak igre
    manager.entityPlayerStorage[0].revive();
//Water + Health
    for (Entity& i : manager.entityWaterStorage)     //Vracanje srca (health) na ekran
    {
        if (i.getTag() == "tile15")
        {
            i.revive();
        }
    }
//Enemy
    for (Entity& i : manager.entityEnemyStorage)                     //Vracanje Enemy na pocetne vrednosti
    {
        i.ptrCEnemyAssets->health = 1;
        i.ptrCTransform->position = i.ptrCTransform->positionRestart;
        i.eRectangle.setPosition(i.ptrCTransform->position);
        i.ptrCEnemyAssets->frameCount = 0;
        i.ptrCEnemyAssets->frameCountDeath = 0;
        i.revive();
    }
//Boss
    for (Entity& i : manager.entityBossStorage)                      //Vracanje Boss na pocetne pozicije
    {
        i.ptrCEnemyAssets->health = 3;
        i.ptrCTransform->position = i.ptrCTransform->positionRestart;
        i.eRectangle.setPosition(i.ptrCTransform->position);
        i.ptrCEnemyAssets->frameCount = 0;
        i.ptrCEnemyAssets->frameCountDeath = 0;
        i.revive();
    }
//Normal tiles (TreeStorage)- normal tiles, neunistivi tiles i poluga za kraj levela
    for (Entity& i : manager.entityTreeStorage)
    {
        i.eRectangle.setPosition(i.ptrCTransform->positionRestart);  //Za tile se pozicija tokom igre ne menja, ostaje ista
        i.ptrCTileAssets->animation = false;
        i.ptrCTileAssets->frameCount = 0;
        if (i.getTag() == "tile14")   //Poluga za kraj levela. Resetuje se sprite na pocetnu poziciju.
        {
            i.eRectangle.setTextureRect(sf::IntRect(0,0, 50,50)); //prva slika u sheet-u
        }
        i.revive();
    }
//Special tiles
    for (Entity& i : manager.entitySpecialTilesStorage)
    {
        i.eRectangle.setPosition(i.ptrCTransform->positionRestart);  //Za tile se pozicija tokom igre ne menja, ostaje ista
        i.ptrCTileAssets->animation = false;
        i.ptrCTileAssets->frameCount = 0;
        i.eRectangle.setTexture(manager.textureTileVec[4]);           //Vrati default sprite na eRectangle za special tile
        i.revive();
    }

    //Vrati fleg u klasi Screens da nije vise restart == true, kako bi opet moglo da se restartuje kad zatreba.
    screens.setRestartGameFalse();
}









