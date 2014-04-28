#include "Framework/DrawingWindow.h"
#include <iostream>
#include <windows.h>
#include <math.h>
#include <time.h> 

#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Transform3D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"

#include "Player.h"
#include "Enemy.h"

using namespace std;

#define ROTATE   0.1f
#define SPEED    5
#define NUMENEMY 30
#define TIMER     3

int intScore    = 0;
int intNumLives = 10;
int intTimer    = 3;

string stringLives;
string stringScore;
string stringGameOver;
string stringReset;
string stringPlayAgain;

Text *textNrLives;
Text *textNrScore;
Text *textGameOver;
Text *textPlayAgain;

Player*  playerHuman;
Player*  playerLives;
Rectangle2D* rectangle2DScene;
Visual2D *visual2DMainScreen;
Enemy* enemyTemp;

vector<Enemy*> vectorEnemy;
vector<int>    vectorScores; 

bool boolRotateLeft     = false;
bool boolInit           = false;
bool boolDisplayWeapon  = false;
bool boolLostLife       = false;
bool boolGameOver       = false;
bool* boolStariTaste    = new bool[256];
bool* boolStariSpeciale = new bool[256];

// initializeaza textele2D pentru scor si numarul de vieti
void createText() 
{
	stringLives = "Lives: x"+ to_string(intNumLives);
	stringScore = "Score: "  + to_string(intScore);
	stringGameOver = "GAME OVER !!!";
	stringPlayAgain = "Play Again";
	
	playerLives = new Player(Point2D(DrawingWindow::width - 170,
									 DrawingWindow::height - 48),
							 Color(1, 0, 0));
	playerLives->scaleBody(0.6);
	playerLives->rotateBody(0.5);
	DrawingWindow::addObject2D_to_Visual2D(playerLives->circle2DShield, visual2DMainScreen);
	DrawingWindow::addObject2D_to_Visual2D(playerLives->polygon2DBody, visual2DMainScreen);

	textNrLives = new Text(stringLives, 
						   Point2D((float) DrawingWindow::width - 300, 
								   (float) DrawingWindow::height - 48), 
									Color(1,0,0), 
							BITMAP_TIMES_ROMAN_24);

	DrawingWindow::addText_to_Visual2D(textNrLives, visual2DMainScreen);

	
	textNrScore = new Text(stringScore, 
						   Point2D((float) DrawingWindow::width / 2,  
								   (float) DrawingWindow::height - 48), 
						   Color(0,1,0), 
						   BITMAP_TIMES_ROMAN_24);	
	DrawingWindow::addText_to_Visual2D(textNrScore, visual2DMainScreen);


	textGameOver = new Text(stringGameOver, 
						 Point2D((float) DrawingWindow::width / 2 - 100, 
							     (float) DrawingWindow::height / 2), 
						 Color(1,0,0), 
						 BITMAP_TIMES_ROMAN_24);

	textPlayAgain = new Text(stringPlayAgain, 
						 Point2D((float) DrawingWindow::width / 2 - 75, 
							     (float) DrawingWindow::height / 2 - 24), 
						 Color(0,0,1), 
						 BITMAP_TIMES_ROMAN_24);
}

// initializeaza NUMENEMY inamici plasati random in scena
void createEnemies() 
{
	float floatScaleEnemy  = 0;
	float floatPosX        = 0;
	float floatPosY        = 0;
	float floatEnemySpeedX = 0;
	float floatEnemySpeedY = 0;

	for (int i = 0; i < NUMENEMY; i ++) {

		floatPosX = (float) (20 + rand() % (DrawingWindow::width - 40));
		floatPosY = (float) (20 + rand() % (DrawingWindow::height - 40));

		// verificam ca distanta initiala intre jucator si inamici sa fie 
		// mai mare de 50
		while (playerHuman->getDistance(floatPosX, floatPosY) < 50) {
			floatPosX = (float) (20 + rand() % (DrawingWindow::width - 40));
			floatPosY = (float) (20 + rand() % (DrawingWindow::height - 40));
		}

		// dimensiunea, rotatia, viteza, pozitia inamicilor vor fi random
		enemyTemp = new Enemy(Point2D(floatPosX, floatPosY));
		floatScaleEnemy = (((float) (rand() % 30)) / 100) + 0.3;
		enemyTemp->scaleBody(floatScaleEnemy);
		floatEnemySpeedX = (float) (rand() % 4);
		floatEnemySpeedY = (float) (rand() % 4);
		enemyTemp->setRotation(0.5f);
		enemyTemp->setSpeed(floatEnemySpeedX, floatEnemySpeedY);
		
		vectorEnemy.push_back(enemyTemp);
	}

	for (unsigned int i = 0 ; i < vectorEnemy.size(); i ++) {
		unsigned int uintSize = vectorEnemy[i]->object2DComponents.size();
		for (unsigned int j = 0 ; j < uintSize; j ++) {
			DrawingWindow::addObject2D(vectorEnemy[i]->object2DComponents[j]);
		}
	}

	for (int i = 1; i < 10;i ++) {
		vectorScores.push_back(i * 50);
	}
}

// initializare nava jucator pe o pozitie random din harta
void createPlayer() 
{	
	float floatPosX = (float) (20 + rand() % (DrawingWindow::width - 60));
	float floatPosY = (float) (20 + rand() % (DrawingWindow::height - 60));

	playerHuman = new Player(Point2D(floatPosX, floatPosY), Color(1, 0, 0));
	playerHuman->scaleBody(0.5);
	playerHuman->setNormalSpeed(SPEED);
	playerHuman->setWeaponSpeed(SPEED /2);

	DrawingWindow::addObject2D(playerHuman->circle2DShield);
	DrawingWindow::addObject2D(playerHuman->polygon2DBody);
}

// initializeaza scena, mai exact dreptunghiul negru in interiorul
// caruia se va desfasura jocul
void createScene(Rectangle2D* &rectangle2DScene)
{
	rectangle2DScene = new Rectangle2D(Point2D(0,0), 
									   (float) DrawingWindow::width, 
									   (float) DrawingWindow::height, 
									   Color(0,0,0),
									   true);
	DrawingWindow::addObject2D(rectangle2DScene);
}

// functia care initializeaza jocul
void DrawingWindow::init()
{
	visual2DMainScreen = new Visual2D(0, 0, (float) width, (float) height, 
									  0, 0, width, height);
	addVisual2D(visual2DMainScreen);
	
	srand((unsigned int)time(NULL));

	createText();
	createPlayer();
	createEnemies();
	createScene(rectangle2DScene);

	boolInit = true;
}

// afiseaza arma dupa apasarea tastei corespunzatoare
void enableWeapon() 
{
	if (playerHuman->getWeaponState() && !boolDisplayWeapon) {
		DrawingWindow::removeObject2D(rectangle2DScene);
		DrawingWindow::addObject2D(playerHuman->polygon2DDrill);
		DrawingWindow::addObject2D(rectangle2DScene);
		boolDisplayWeapon = true;
	} else if (!playerHuman->getWeaponState() && boolDisplayWeapon) {
		DrawingWindow::removeObject2D(playerHuman->polygon2DDrill);
		boolDisplayWeapon = false;
	}
}

// veifica coliziunea corpului navei jucatorului cu navele inamice
void checkShipCollision()
{
	for (unsigned int i = 0; i < vectorEnemy.size(); i ++) {
		if (playerHuman->hasColidedShip(vectorEnemy[i]->floatCenterX, 
										vectorEnemy[i]->floatCenterY, 
										vectorEnemy[i]->floatRadius)) {
			cout << "Ship colided with enemy " << i << endl;
			cout << "Ship center " <<  playerHuman->floatCenterX << " " << playerHuman->floatCenterY << endl;
			cout << "Enemy center " << vectorEnemy[i]->floatCenterX << " " << vectorEnemy[i]->floatCenterY << endl;
			vectorEnemy[i]->boolPlayerCollision = true;
			vectorEnemy[i]->changeDirection();
			cout << endl << endl;
			boolLostLife = true;
		}
	}
}

// verifica coliziunea dintre 2 inamici
void checkEnemyColision()
{
	for (unsigned int i = 0; i < vectorEnemy.size(); i ++) {
		for (unsigned int j = 0; j < vectorEnemy.size(); j ++) {
			if (i == j) {
				continue;
			}
			if (vectorEnemy[i]->hasColidedShip(vectorEnemy[j]->floatCenterX, 
											   vectorEnemy[j]->floatCenterY, 
											   vectorEnemy[j]->floatRadius)) {
				vectorEnemy[i]->changeDirection();
				vectorEnemy[j]->changeDirection();
			}
		}
	}
}

// veifica coliziunea armei jucatorului cu navele inamice
void checkWeaponCollision()
{
	for (unsigned int i = 0; i < vectorEnemy.size(); i ++) {
		if (boolDisplayWeapon && 
			playerHuman->hasColidedWeapon(vectorEnemy[i]->floatCenterX,
										  vectorEnemy[i]->floatCenterY)) {
			cout << "Weapon colided with enemy " << i << endl;
			
			for (unsigned int j = 0 ; j < vectorEnemy[i]->object2DComponents.size(); j ++) {
				DrawingWindow::removeObject2D(vectorEnemy[i]->object2DComponents[j]);
			}

			intScore += vectorScores[vectorEnemy[i]->getEnemyNo()];
			vectorEnemy.erase(vectorEnemy.begin() + i);
		} 	
	}
}

// functie ce animeaza inamcii: rotatie + translatie
void animateEnemies()
{
	for (unsigned int i = 0; i < vectorEnemy.size(); i ++) {
		vectorEnemy[i]->rotateBody();
		vectorEnemy[i]->moveBody((float) DrawingWindow::width, (float) DrawingWindow::height);	
	}
}

// dupa contactul cu o nava inamica se scade numarul de vieti
void decreaseLives() 
{
	if (boolLostLife) {
		intNumLives --;
		boolLostLife = false;
	}

	if (intNumLives <= 0) {
		boolGameOver = true;
	}
}

// face update la textele afisate pe ecran
void RedrawText()
{
	stringLives ="Lives: x "+ to_string(intNumLives);
	textNrLives->text = stringLives;

	stringScore ="Score: "  + to_string(intScore);
	textNrScore->text = stringScore;
}

// afiseaza mesajul de GameOVER !!
void displayGameOver() 
{
	DrawingWindow::addText_to_Visual2D(textGameOver, visual2DMainScreen);
}

// efectueaza miscari in functie de tastele apasate
void doMovement() 
{
	if (boolStariTaste[27]) {
		exit(0);
	}
		
	if (boolStariSpeciale[KEY_LEFT]) {
		playerHuman->rotateBody(ROTATE);
	}

	if (boolStariSpeciale[KEY_RIGHT]){
		playerHuman->rotateBody(-ROTATE);
	}

	if (boolStariSpeciale[KEY_UP]) {
		playerHuman->moveBody((float) DrawingWindow::width, 
							  (float) DrawingWindow::height);
	}

	if (boolStariTaste[KEY_SPACE]) {
		if (!playerHuman->getWeaponState()) {
			playerHuman->activateWeapon();
		} else {
			playerHuman->deactivateWeapon();
		}
		boolStariTaste[KEY_SPACE] = false;
	}
}

//functia care permite animatia
void DrawingWindow::onIdle()
{
	if (boolGameOver) {
		displayGameOver();
	} else {	
		doMovement();
		checkShipCollision();
		checkWeaponCollision();
		animateEnemies();
		checkEnemyColision();
		enableWeapon();
		decreaseLives();
		RedrawText();
	} 
}


//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	if (boolInit) {
		visual2DMainScreen->fereastra(0, 0, (float) width, (float) height);
		visual2DMainScreen->poarta   (0, 0, width, height);

		playerLives->setPosition(width - 170, height - 40);

		textNrLives->pos = Point2D((float) width - 300, (float) height - 48);
		
		textNrScore->pos = Point2D((float) (width / 2) - 10, 
								   (float) height - 48);
		textGameOver->pos = Point2D((float) width / 2 - 100, (float) height / 2);
		textPlayAgain->pos = Point2D((float) width / 2 - 75, (float) height / 2 - 24);

		removeObject2D(rectangle2DScene);
		rectangle2DScene = new Rectangle2D(Point2D(0,0), (float) width,
										   (float) height, Color(0, 0, 0), 
										   true);
		addObject2D(rectangle2DScene);
	}
}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
	int intPosX = (int) visual2DMainScreen->xLog(x);
	int intPosY = (int) visual2DMainScreen->yLog(y);
	if (boolGameOver) {
		if (intPosX > width / 2 - 75  && intPosX < width / 2 + 30 &&
			intPosY > height / 2 - 24 && intPosY < height / 2) {
			cout << "PLAY AGAIN LADDY !!!" << endl;
		}
	}
}

void keyPressed (unsigned char key, int x, int y) 
{
	boolStariTaste[key] = true;
}

void keyUp (unsigned char key, int x, int y) 
{
	boolStariTaste[key] = false; 
}

void keySpecialPressed (int key, int x, int y)
{
	boolStariSpeciale[key] = true;
}

void keySpecialUp (int key, int x, int y) 
{
	boolStariSpeciale[key] = false;
}

int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 1024, 600, 200, 0, "Geometry Wars");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events
	glutSpecialFunc(keySpecialPressed); // Tell GLUT to use the method "keySpecial" for special key presses
	glutSpecialUpFunc(keySpecialUp); // Tell GLUT to use the method "keySpecialUp" for special up key events
	memset(boolStariTaste,    false, 256);
	memset(boolStariSpeciale, false, 256);
	
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;
}