#include <iostream>
#include <windows.h>
#include "dependente\freeglut.h"
#include <time.h>
#include <string.h>
#include "Enemy.h"
#include "Camera.h"
#include "Player.h"
#include "Environment.h"
#include <vector>
using namespace std;

int noInamici   = 200;
int noColisions = 0;
int crtLevel    = 0;
int bonusTime   = 100;

bool bonus = false;
bool isGameOver = false;
bool isGameWon = false;

float fieldOfView = 250;
float levelDistance = 20000;
float runDistance = 0;
float positionX = 7.5f;
float positionY = 3.0f;
float positionZ = -20.0f;
float maxSpeed  =  10.0f;
float bonusSpeed  =  20.0f;
float maxPositionX = 15.0f;
float minPositionX = -5.0f;
float tilt = 0;
float width = 0;
float height = 0;


Player* jucator;
Environment* mediu;
vector<Enemy*> inamici;


// fontul cu care vom afisa text pe ecran
void *font = GLUT_BITMAP_TIMES_ROMAN_24;
time_t startTime;
time_t crtTime;

void createPlayer() 
{
	jucator = new Player(positionX, 0, positionZ, maxSpeed, minPositionX, maxPositionX);
}

void createEnvironment() 
{
	mediu = new Environment(levelDistance, minPositionX, maxPositionX);
}

// creeaza inamicii pe cele doua sensuri ale unei strazi
// acestia au viteza, pozitie, sens random 
// astfel vor fi inamici atat mobili cat si statici
void createEnemy() 
{
	float lanePosition = 0;
	float newSpeed = 0;
	for (int i = 0; i < noInamici; i++) {
		srand(i * 1000);
		int crtLane = rand() % 2;
		if (crtLane == 1 ) {
			lanePosition = (float) -7.5 + 10 * (rand() % 3);
		} else {
			lanePosition = (float) -12.5 + 10 * (rand() % 4);
		}
		newSpeed = rand() % 5;
		inamici.push_back(new Enemy(lanePosition, 0 , -i * 100, 
									 newSpeed, crtLane , rand() % 5));
	}
}

// cand numarul de coliziuni permise ajunge 0
// la apasarea tastei F2 se restarteaza jocul
void restart() {
	createEnemy();
	jucator->setPositionZ(positionZ);
	jucator->setPositionX(positionX);
	createEnvironment();
	runDistance = crtLevel * 4000;
	noColisions = 1;
	isGameOver = false;
}

// daca s-a parcurs distanta tinta la nivelul curent
// initializam nivelul urmator
void nextLevel() {
	isGameOver = false;
	isGameWon = false;
	crtLevel ++;
	runDistance += crtLevel * 4000;
	noColisions = crtLevel * 10;
}

// la apasarea unei taste din categoria "normal"
// se efectueaza actiunea specifica
void normalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}

// redimensionarea ecranului
void onResize(int w, int h) {

	if(h == 0)
		h = 1;
	float ratio = (float) 1.0* w / h;
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// setam vieportul sa fie intreaga fereastra
	glViewport(0, 0, w, h);

	// setam noua perspectiva
	gluPerspective(45,ratio,1,1000);

	width = w;
	height = h;
	glMatrixMode(GL_MODELVIEW);
}

// la apasarea tastelor speciale
void pressKey(int key, int xx, int yy) {
	// daca nu am pierdut si nici castigat jocul curent
	// efectuam actiunile specifice masinii
	if (!isGameOver && !isGameWon) {
		switch (key) {
			// mutare stanga + rotire
			case GLUT_KEY_LEFT : 
				if (jucator->setRotate(0)) {
					tilt += 0.2f;
				}
			break;
			// mutare dreapta + rotire
			case GLUT_KEY_RIGHT : 	
				if (jucator->setRotate(1)) {
					tilt -= 0.2f;
				}
			break;
			// deplasare in fata
			case GLUT_KEY_UP : 
				jucator->enableMove();
			break;

			// franare
			case GLUT_KEY_DOWN :
				jucator->disableMove();
				jucator->decelerate();
			break;
			// la apasarea F1 putem seta windowMode sau FullScreen
			case GLUT_KEY_F1 : glutFullScreenToggle(); break;
		}
	} else if (!isGameWon) {
		if ( key ==  GLUT_KEY_F2) {
			restart();
		}
	} else {
		if (key ==  GLUT_KEY_F2) {
			nextLevel();
		}
	}
}

// cand ridicam degetul de pe o tasta
void releaseKey(int key, int x, int y) {
	// daca nu am pierdut si nici nu am castigat
	if (!isGameOver && !isGameWon) {
		switch (key) {
			// revenire la rotirea initiala
			case GLUT_KEY_LEFT :
			case GLUT_KEY_RIGHT : 
				jucator->disableRotate();
			break;

			// acceleratia devine 0
			case GLUT_KEY_UP :
			case GLUT_KEY_DOWN :
			jucator->disableMove();
			break;
		}
	}
}

// muta si afiseaza inamicii
// daca acestia se afla in campul vizual al jucatorului
void renderEnemy() 
{
	for (int i = 0; i < noInamici; i++) {
		if (inamici[i]->isInFront(jucator->getPositionZ(), fieldOfView)) {
			inamici[i]->move();
			inamici[i]->render();
		}
	}

}

void setOrthographicProjection() {

	glMatrixMode(GL_PROJECTION);
	
	// salvam matrice precedenta ce contine setarile
	// pentru proiectia perspectiva
	glPushMatrix();

	glLoadIdentity();

	// se creeaza o proiectie ortografica 2D
	gluOrtho2D(0, width, height, 0);

	glMatrixMode(GL_MODELVIEW);
}

// intoarce la proiectie perspectiva
void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

// afiseaza pe ecran cu fontul stabilit mai sus
// caracterele din stringul primit ca parametru
// la pozitia (x,y)
void renderBitmapString(float x, float y, void *font, string str) 
{

  char *c;
  glRasterPos2f(x, y);
  for (int i = 0; i < str.size(); i++) {
    glutBitmapCharacter(font, str[i]);
  }
}

// afisam textul de game over la pierderea jocului
void printGameOver()
{
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	renderBitmapString(width / 2, height / 2, font, "GAME OVER !!!");
	renderBitmapString(width / 2, height / 2  + 24, font, "Press F2 to restart !");
	glPopMatrix();
	restorePerspectiveProjection();
}

// afisam textul de game won la castigarea jocului
void printGameWon()
{
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	renderBitmapString(width / 2, height / 2, font, "CONGRATULATIONS LEVEL WON !!!");
	renderBitmapString(width / 2, height / 2  + 24, font, "Press F2 for next level!");
	glPopMatrix();

	restorePerspectiveProjection();
}

// afisam diverse informatii cu privire la starea jocului
void printText()
{
	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();

	// in functie de viteza jucatorului se modifica culoarea
	// textului
	if (jucator->getSpeed() < maxSpeed / 4) {
		glColor3f(0.0f, 0.0f, 0.0f);
	} else if (jucator->getSpeed() < 2 * maxSpeed / 4) {
		glColor3f(0.0f, 0.0f, 1.0f);
	} else if (jucator->getSpeed() < 3 * maxSpeed / 4) {
		glColor3f(0.0f, 1.0f, 0.0f);
	} else if (jucator->getSpeed() < maxSpeed * 1.2)  {
		glColor3f(1.0f, 0.0f, 0.5f);
	} else {
		glColor3f(0.5, 0, 0.510);
	}

	char tempString[50];
	// afisam viteza in partea dreapta jos
	sprintf(tempString, "Speed: %.2f Km/h",jucator->getSpeed() * 20);
	renderBitmapString(width - 200, height - 20, font, tempString);

	// afisam timpul ramas pana la pierderea nivelului curent
	 struct tm curentTime;
	
	 time(&crtTime);
	curentTime = *localtime(&crtTime);

	int secunde = difftime(crtTime, startTime);
	int ore =  secunde / 3600;
	int minute =  (secunde  - ore * 3600) / 60;
	secunde = secunde  - ore * 3600 - minute * 60;
    sprintf(tempString, "Time: %02d:%02d:%02d", ore, minute, secunde);
	renderBitmapString(width / 2 - 300, 30, font, tempString);

	// afisam distanta ramasa pana la castigarea nivelului curent
	sprintf(tempString, "DistanceLeft: %.0f" , runDistance + jucator->getPositionZ());
	renderBitmapString(width / 2 - 100, 30, font, tempString);

	// afisam numarul de coliziuni ramase
	sprintf(tempString, "Colisions Left: %d", noColisions);
	renderBitmapString(width / 2 + 200, 30, font, tempString);

	// daca e activat bonusul se afiseaza cat timp mai e bonusul activ
	if (bonus) {
		jucator->setMaxSpeed(bonusSpeed);
		sprintf(tempString, "Bonus Left: %d", bonusTime);
		renderBitmapString(width / 2 - 500, 30, font, tempString);
	}
	glPopMatrix();
	restorePerspectiveProjection();
}

void onIdle() 
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.098, 0.098, 0.439,1);
	// resetam toate transformarile
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// setam nou pozitie a camerei in spatele jucatorului
	// si punctul spre care se priveste in pozitia jucatorului
	// astfel camera va urmari tot timpul jucatorul
	positionX = jucator->getPositionX();
	positionZ = jucator->getPositionZ() -1.0f;
	gluLookAt(positionX, 3.0, positionZ + 10, 
			  positionX, 3.0,  positionZ,
			  0.0f + tilt, 1,  0.0f );
	
	// renderizam blocurile si drumul
	mediu->renderRoads(3);
	mediu->renderEnvironment(jucator->getPositionZ());

	// daca nu am castigat si nici pierdut
	if (!isGameOver && !isGameWon) {
		// renderizam inamicii si jucatorul
		renderEnemy();
		jucator->render();
		// efectuam miscarea jucatorului
		jucator->moveCar();
	
		// verificam coliziunea cu inamicii
		for (int i = 0; i < noInamici; i++) {
			if (inamici[i]->isInFront(jucator->getPositionZ(), fieldOfView)) {
				if (jucator->checkForColision(inamici[i]->getPositionZ(),
					inamici[i]->getPositionX(), inamici[i]->getRadius())) {

						if (inamici[i]->getNumber() == 4) {
							// la coliziunea cu un bonus activam acel bonus
							bonus = true;
						} else {
							// la coliziunea cu un inamic decrementam numarul de coliziuni
							// ramase
							noColisions--;
							inamici[i]->setPositionZ(inamici[i]->getPositionZ() + 100);
							break;
						}
						
				}
			}
		}	
	} else if (isGameWon) {
		//daca am castigat afisam textul de castig 
		printGameWon();
	} else if (isGameOver) {
		//daca am pierdut afisam textul de pierdere 
		printGameOver();
	} 

	// daca numarul de coliziuni ramase a scazut sub 0 
	// am pierdut
	if (noColisions < 0){
		isGameOver = true;
	}
	// daca am parcurs distanta necesara am castigat nivelul
	if (runDistance + jucator->getPositionZ() <= 0) {
		isGameWon = true;
	}
	// daca e bonusul activ decrementam timpul in care bonusul este
	// activ
	if (bonus) {
		bonusTime -= 0.1;
		if (bonusTime <= 0) {
			bonus = false;
			bonusTime = 100;
		}
	} else {
		/// daca bonusul nu mai e activ resetam viteza la parametri normali
		jucator->setMaxSpeed(maxSpeed);
	}

	// afisam textele
	printText();
	glutSwapBuffers();
	glutPostRedisplay();
}

void init() 
{
	// init GLUT si creare ferestre
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("Tema2-EGC");

	// functiile de lucru
	glutDisplayFunc(onIdle);
	glutReshapeFunc(onResize);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(normalKeys);
	glutSpecialFunc(pressKey);

	// ignora tastele ce sunt tinute apasate
	glutIgnoreKeyRepeat(1);


	glutSpecialUpFunc(releaseKey);
	glEnable(GL_DEPTH_TEST);

	createPlayer();
	createEnvironment();
	createEnemy();
	nextLevel();
	glutFullScreenToggle();
}

int main(int argc, char **argv)
{
	// initializare glut
	glutInit(&argc, argv);

	time(&startTime);
	// initializare paramtri GLUT si parametri joc
	init();

	// intram in onIdle()
	glutMainLoop();

	return 1;
}
