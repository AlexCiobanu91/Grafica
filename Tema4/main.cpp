//-------------------------------------------------------------------------------------------------
// Descriere: fisier main
//
// Autor: student
// Data: today
//-------------------------------------------------------------------------------------------------

//incarcator de meshe
#include "lab_mesh_loader.hpp"
//geometrie: drawSolidCube, drawWireTeapot...
#include "lab_geometry.hpp"
//incarcator de shadere
#include "lab_shader_loader.hpp"
//interfata cu glut, ne ofera fereastra, input, context opengl
#include "lab_glut.hpp"
//texturi
#include "lab_texture_loader.hpp"
//time
#include <ctime>

class Laborator : public lab::glut::WindowListener{
  typedef struct particleFormat{
		float positionX, positionY, positionZ;				// pozitia unui vertex (x,y,z)	
		float speedX, speedY, speedZ;			
    float colorR, colorG, colorB;			
    float texX, texY;
  } particle;

private:
	// matrici modelare pentru cele 3 obiecte
	glm::mat4 modelMatGirl, particleModelmatrix;

	// matrici 4x4 pt modelare vizualizare proiectie
	glm::mat4 view_matrix, projection_matrix;	

	// id-ul de opengl al obiectelor de tip program shader
	unsigned int gl_program_shader, particleShader;	

	// containere opengl pentru vertecsi, indecsi si stare
	unsigned int girlAsleep_vbo,   girlAsleep_ibo,   girlAsleep_vao;					
	unsigned int girlAnnoyed_vbo,  girlAnnoyed_ibo,  girlAnnoyed_vao;			
	unsigned int girlSurprise_vbo, girlSurprise_ibo, girlSurprise_vao;		

	unsigned int screen_width, screen_height, stare, timpStare;
	
	// texturi
	unsigned int girl_texture;
  unsigned int particle_texture;
	// vectori pozitie lumina si pozitia ovchiului
	glm::vec3 light_position, eye_position;
	unsigned int material_shininess;
	float material_kd, material_ks;
  

  glm::vec3 particleEmitterPosition;

  unsigned int nrParticles;
  std::vector<particle> particleVector;
  std::vector<glm::vec3> particleSpeeds;
  std::vector<glm::vec3> particlePosition;
  std::vector<glm::vec3> particleColor;
  std::vector<lab::VertexFormat> girlAsleepVertices, girlAnnoyedVertices, girlSurpriseVertices;
  std::vector<unsigned int> girlAsleepIndices,  girlAnnoyedIndices, girlSurpriseIndices;
  std::vector<unsigned int> particleIndices;

  unsigned int particleVAO;
  unsigned int particleVBO;
  unsigned int particleIBO;

  unsigned int nrFrames, crtFrame, crtParticleTime;
  float crtParticleFrame, animationTime;
  time_t initialTime, initialParticleTime, crtTime;
  double newTime;
public:
	
  void loadGirl(const std::string &filename, int stare)
  {
		//incarca vertecsii si indecsii din fisier
		std::vector<lab::VertexFormat> vertices;
		std::vector<unsigned int> indices;
		lab::_loadObjFile(filename, vertices, indices);
		std::cout<<"Mesh Loader : am incarcat fisierul "<<filename<<std::endl;

		//legatura intre atributele vertecsilor si pipeline, datele noastre sunt INTERLEAVED.
		switch (stare) {
			case 1:
					girlAsleepVertices = vertices;
          girlAsleepIndices = indices;
			break;
			case 2:
         girlAnnoyedVertices = vertices;
         girlAnnoyedIndices = indices;
      break;
      case 3:
        girlSurpriseVertices = vertices;
        girlSurpriseIndices = indices;
      break;
    }
  }

	void loadGirls()
	{
		// GIRL ASLEEP
		loadGirl("resurse\\girl_sleep.obj", 1);	
		
		// GIRL ANNOYED 
		loadGirl("resurse\\girl_annoyed.obj", 2);	

		// GIRL SURPRISE
		loadGirl("resurse\\girl_surprise.obj", 3);	
	}

  void createParticles()
  {
    int crtIt = 0;
    for (unsigned int i = 0; i < nrParticles * 4; i += 4) { 
     
      particle temp;
      float x = particleEmitterPosition.x;
      float y = particleEmitterPosition.y;
      float z = particleEmitterPosition.z;
      temp.positionX = x - 0.5f; temp.positionY = y + 0.5f; temp.positionZ = z;
      srand (i * 20);
      temp.colorR = ((float) (rand() % 100)) / 100; 
      srand (i * 30);
      temp.colorG = ((float) (rand() % 100)) / 100; 
      srand (i * 40);
      temp.colorB = ((float) (rand() % 100)) / 100; 
      srand (i * 50);
      temp.speedX = 0.005f + ((float) (rand() % 100)) / 1000;
      srand (i * 60);
      int dirY = ((rand() % 2) == 0 ? -1 : 1);
      srand (i * 80);
      temp.speedY = crtIt * dirY * (((float) (rand() % 100)) / 10000);
      crtIt = 1 - crtIt;
      temp.speedZ = 0;
      temp.texX = 0; temp.texY = 1;
      particleVector.push_back(temp);

      temp.positionX = x + 0.5f; temp.positionY = y + 0.5f; temp.positionZ = z;
      temp.colorR = ((float) (rand() % 100)) / 100; 
      temp.colorG = ((float) (rand() % 100)) / 100; 
      temp.colorB = ((float) (rand() % 100)) / 100; 
      temp.texX = 1; temp.texY = 1;
      particleVector.push_back(temp);

      temp.positionX = x + 0.5f; temp.positionY = y - 0.5f; temp.positionZ = z;
      temp.colorR = ((float) (rand() % 100)) / 100; 
      temp.colorG = ((float) (rand() % 100)) / 100; 
      temp.colorB = ((float) (rand() % 100)) / 100; 
      temp.texX = 1; temp.texY = 0;
      particleVector.push_back(temp);

      temp.positionX = x - 0.5f; temp.positionY = y - 0.5f; temp.positionZ = z;
      temp.colorR = ((float) (rand() % 100)) / 100; 
      temp.colorG = ((float) (rand() % 100)) / 100; 
      temp.colorB = ((float) (rand() % 100)) / 100; 
      temp.texX = 0; temp.texY = 0;
      particleVector.push_back(temp);

      particleIndices.push_back(0 + i);
      particleIndices.push_back(1 + i);
      particleIndices.push_back(2 + i);

      particleIndices.push_back(0 + i);
      particleIndices.push_back(2 + i);
      particleIndices.push_back(3 + i);

    }
    particleModelmatrix = glm::mat4(1,0,0,0,  0,1,0,0, 0,0,1,0, 0,0,0,1);
   }

	Laborator()
	{
		glClearColor(0.5,0.5,0.5,1);
		glClearDepth(1);			
		glEnable(GL_DEPTH_TEST);	
		
		// incarca shaderul ce raspunde de animatia fetei
		gl_program_shader = lab::loadShader("shadere\\shader_vertex.glsl",
                                        "shadere\\shader_fragment.glsl");

		// incarca shaderul ce raspunde de generatorul de particule
		particleShader    = lab::loadShader("shadere\\shader_vertex_particle.glsl",
                                        "shadere\\shader_fragment_particle.glsl");

    // incarca texturile
    girl_texture = lab::loadTextureBMP("resurse\\girl_texture.bmp");
    particle_texture = lab::loadTextureBMP("resurse\\music.bmp");

    // genereaza particulele
    nrParticles = 100;
    particleEmitterPosition = glm::vec3(-7, 7, 0);
    crtParticleTime = 0;
   
		// incarca cele 3 stari ale fetei
     createParticles();
		 loadGirls();
     
		// matrici de modelare si vizualizare
		modelMatGirl = glm::mat4(1,0,0,0,  0,1,0,0, 0,0,1,0, 0,0,0,1);
		view_matrix = glm::lookAt(glm::vec3(0,7,5), glm::vec3(0,7,0), glm::vec3(0,1,0));

		// desenare wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
    // setare variabile initiale pentru controul animatiei
    stare = 0; nrFrames = 60; crtFrame = 0; timpStare = 10;

		// setare lumina si materiale 
		eye_position = glm::vec3(0,10,50);
		light_position = glm::vec3(10,7,25);
		material_shininess = 100;
		material_kd = 0.5;
		material_ks = 0.5;

    // intram in modul FullScreen
     glutFullScreenToggle();

     time(&initialTime);
  }

	~Laborator()
	{
		glDeleteProgram(gl_program_shader);
	}

	void notifyBeginFrame()
	{

	}

 void bindAsleepGirl()
 {
   glGenVertexArrays(1, &girlAsleep_vao);

	 //vertex buffer object -> un obiect in care tinem vertecsii
   glGenBuffers(1, &girlAsleep_vbo);
   glBindBuffer(GL_ARRAY_BUFFER, girlAsleep_vbo);
	 glBufferData(GL_ARRAY_BUFFER, girlAsleepVertices.size()*sizeof(lab::VertexFormat), &girlAsleepVertices[0], GL_STATIC_DRAW);

		//index buffer object -> un obiect in care tinem indecsii
		glGenBuffers(1, &girlAsleep_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, girlAsleep_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, girlAsleepIndices.size()*sizeof(unsigned int), &girlAsleepIndices[0], GL_STATIC_DRAW);

		//legatura intre atributele vertecsilor si pipeline, datele noastre sunt INTERLEAVED.
		int pipe = glGetAttribLocation(gl_program_shader, "in_position_Asleep");
		glEnableVertexAttribArray(pipe);
		glVertexAttribPointer(pipe,3,GL_FLOAT,GL_FALSE,sizeof(lab::VertexFormat),(void*)0);				     
				
		pipe = glGetAttribLocation(gl_program_shader, "in_normals_Asleep");
		glEnableVertexAttribArray(pipe);
		glVertexAttribPointer(pipe,3,GL_FLOAT,GL_FALSE,sizeof(lab::VertexFormat),(void*)(sizeof(float)*3));		

		pipe = glGetAttribLocation(gl_program_shader, "in_texcoord_Asleep");
		glEnableVertexAttribArray(pipe);
		glVertexAttribPointer(pipe, 2,GL_FLOAT,GL_FALSE,sizeof(lab::VertexFormat),(void*)(2*sizeof(float)*3));		
 }

 void bindAnnoyedGirl()
 {
   glGenVertexArrays(1, &girlAnnoyed_vao);

	 //vertex buffer object -> un obiect in care tinem vertecsii
   glGenBuffers(1, &girlAnnoyed_vbo);
   glBindBuffer(GL_ARRAY_BUFFER, girlAnnoyed_vbo);
	 glBufferData(GL_ARRAY_BUFFER, girlAnnoyedVertices.size()*sizeof(lab::VertexFormat), &girlAnnoyedVertices[0], GL_STATIC_DRAW);

		//index buffer object -> un obiect in care tinem indecsii
		glGenBuffers(1, &girlAsleep_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, girlAnnoyed_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, girlAnnoyedIndices.size()*sizeof(unsigned int), &girlAnnoyedIndices[0], GL_STATIC_DRAW);

		//legatura intre atributele vertecsilor si pipeline, datele noastre sunt INTERLEAVED.
		int pipe = glGetAttribLocation(gl_program_shader, "in_position_Annoyed");
		glEnableVertexAttribArray(pipe);
		glVertexAttribPointer(pipe,3,GL_FLOAT,GL_FALSE,sizeof(lab::VertexFormat),(void*)0);				     
				
		pipe = glGetAttribLocation(gl_program_shader, "in_normals_Annoyed");
		glEnableVertexAttribArray(pipe);
		glVertexAttribPointer(pipe,3,GL_FLOAT,GL_FALSE,sizeof(lab::VertexFormat),(void*)(sizeof(float)*3));		

		pipe = glGetAttribLocation(gl_program_shader, "in_texcoord_Annoyed");
		glEnableVertexAttribArray(pipe);
		glVertexAttribPointer(pipe, 2,GL_FLOAT,GL_FALSE,sizeof(lab::VertexFormat),(void*)(2*sizeof(float)*3));		
 }

 void bindSurpriseGirl()
 {
   glGenVertexArrays(1, &girlSurprise_vao);

	 //vertex buffer object -> un obiect in care tinem vertecsii
   glGenBuffers(1, &girlSurprise_vbo);
   glBindBuffer(GL_ARRAY_BUFFER, girlSurprise_vbo);
	 glBufferData(GL_ARRAY_BUFFER, girlSurpriseVertices.size()*sizeof(lab::VertexFormat), &girlSurpriseVertices[0], GL_STATIC_DRAW);

		//index buffer object -> un obiect in care tinem indecsii
   glGenBuffers(1, &girlSurprise_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, girlSurprise_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, girlSurpriseIndices.size()*sizeof(unsigned int), &girlSurpriseIndices[0], GL_STATIC_DRAW);

		//legatura intre atributele vertecsilor si pipeline, datele noastre sunt INTERLEAVED.
		int pipe = glGetAttribLocation(gl_program_shader, "in_position_Surprised");
		glEnableVertexAttribArray(pipe);
		glVertexAttribPointer(pipe,3,GL_FLOAT,GL_FALSE,sizeof(lab::VertexFormat),(void*)0);				     
				
		pipe = glGetAttribLocation(gl_program_shader, "in_normals_Surprised");
		glEnableVertexAttribArray(pipe);
		glVertexAttribPointer(pipe,3,GL_FLOAT,GL_FALSE,sizeof(lab::VertexFormat),(void*)(sizeof(float)*3));		

		pipe = glGetAttribLocation(gl_program_shader, "in_texcoord_Surprised");
		glEnableVertexAttribArray(pipe);
		glVertexAttribPointer(pipe, 2,GL_FLOAT,GL_FALSE,sizeof(lab::VertexFormat),(void*)(2*sizeof(float)*3));		
 }

 void sendGirlParameters()
 {
    // trimite variabile uniforme la shader
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "view_matrix"),       1, false, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "projection_matrix"), 1, false, glm::value_ptr(projection_matrix));
		glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "model_matrix"),      1, false, glm::value_ptr(modelMatGirl));
		
    glUniform3f(glGetUniformLocation(gl_program_shader, "light_position"), light_position.x, light_position.y, light_position.z);
		glUniform3f(glGetUniformLocation(gl_program_shader, "eye_position"),   eye_position.x, eye_position.y, eye_position.z);

		glUniform1i(glGetUniformLocation(gl_program_shader, "material_shininess"),material_shininess);
		glUniform1f(glGetUniformLocation(gl_program_shader, "material_kd"),       material_kd);
		glUniform1f(glGetUniformLocation(gl_program_shader, "material_ks"),       material_ks);
 }

 void sendParticleParameters()
 {
   // trimite variabile uniforme la shader
		glUniformMatrix4fv(glGetUniformLocation(particleShader, "view_matrix"),       1, false, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(glGetUniformLocation(particleShader, "projection_matrix"), 1, false, glm::value_ptr(projection_matrix));
    glUniformMatrix4fv(glGetUniformLocation(particleShader, "model_matrix"), 1, false, glm::value_ptr(particleModelmatrix));
 }

 void animateGirl()
  {
		// foloseste shaderul
		glUseProgram(gl_program_shader);
    
    sendGirlParameters();
    // setam textura fetei ca textura activa si o bind-uim 
		glActiveTexture(GL_TEXTURE0 + girl_texture);
		glBindTexture(GL_TEXTURE_2D, girl_texture);

    // trimitem textura la shader
	  glUniform1i(glGetUniformLocation(gl_program_shader, "textura1"), girl_texture); 

    // trimitem animatia curenta la shader
		glUniform1i(glGetUniformLocation(gl_program_shader, "stare"), stare);

    // trimitem numarul de cadre per animatie la shader
    glUniform1i(glGetUniformLocation(gl_program_shader, "nr_frames"), nrFrames);

		glUniform1i(glGetUniformLocation(gl_program_shader, "frame"), crtFrame);

    bindAsleepGirl();
    bindSurpriseGirl();
    bindAnnoyedGirl();
    glDrawElements(GL_TRIANGLES, girlAsleepIndices.size(), GL_UNSIGNED_INT, 0);
  }

 void bindParticles()
 {
    glGenVertexArrays(1, &particleVAO);
    
    //vertex buffer object -> un obiect in care tinem vertecsii
    glGenBuffers(1,&particleVBO);
		glBindBuffer(GL_ARRAY_BUFFER, particleVBO);
    glBufferData(GL_ARRAY_BUFFER, particleVector.size()*sizeof(lab::VertexFormat), &particleVector[0], GL_STATIC_DRAW);

		//index buffer object -> un obiect in care tinem indecsii
    glGenBuffers(1,&particleIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, particleIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, particleIndices.size()*sizeof(unsigned int), &particleIndices[0], GL_STATIC_DRAW);
    
    int pipe = glGetAttribLocation(particleShader, "in_position");
		glEnableVertexAttribArray(pipe);
    glVertexAttribPointer(pipe, 3, GL_FLOAT, GL_FALSE, sizeof(particle),(void*)0);		
 
    pipe = glGetAttribLocation(particleShader, "in_speed");
		glEnableVertexAttribArray(pipe);
		glVertexAttribPointer(pipe, 3, GL_FLOAT, GL_FALSE, sizeof(particle),(void*)(sizeof(float)*3));				     
				
		pipe = glGetAttribLocation(particleShader, "in_color");
		glEnableVertexAttribArray(pipe);
	  glVertexAttribPointer(pipe,3,GL_FLOAT,GL_FALSE, sizeof(particle),(void*)(2*sizeof(float)*3));		

    pipe = glGetAttribLocation(particleShader, "in_texcoord");
		glEnableVertexAttribArray(pipe);
	  glVertexAttribPointer(pipe,2,GL_FLOAT,GL_FALSE, sizeof(particle),(void*)(3*sizeof(float)*3));		
 }

 void animateParticles()
 {
    // foloseste shaderul
    glUseProgram(particleShader);

    sendParticleParameters();
     // setam textura fetei ca textura activa si o bind-uim 
    glActiveTexture(GL_TEXTURE0 + particle_texture);
		glBindTexture(GL_TEXTURE_2D, particle_texture);

    // trimitem textura la shader
	  glUniform1i(glGetUniformLocation(particleShader, "textura1"), particle_texture); 

    glUniform1i(glGetUniformLocation(particleShader, "crtTime"), crtParticleFrame);
    
    bindParticles();
    glDrawElements(GL_TRIANGLES, particleIndices.size() , GL_UNSIGNED_INT, 0);

  }

  // functia de afisare (lucram cu banda grafica)
	void notifyDisplayFrame() 
  {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    time(&crtTime);
    newTime = difftime(crtTime, initialTime);
    crtFrame ++;

     // la un anumit numar de cadre schimba intre animatii
    bool enParticle = false;
    if (crtFrame > nrFrames) {
      stare ++;
      crtFrame = 0;
       
      if (stare > 3) {
        stare = 0;
      }
    }

    if (stare > 0  && stare < 3) {
      crtParticleFrame += 4;
      // particulele dispar cand fata adoarme din nou
    } else {
      crtParticleFrame = 0;
    }

    animateGirl();
    animateParticles();
	}

	void notifyEndFrame(){}
	// functei care e chemata cand se schimba dimensiunea ferestrei initiale
	void notifyReshape(int width, int height, int previos_width, int previous_height){
		//reshape
		if(height == 0) height = 1;
		float aspect = (float)width / (float)height;
		screen_width = width;
		screen_height = height;

		glViewport(0, 0, screen_width, screen_height);
		projection_matrix = glm::perspective(75.0f, aspect,0.1f, 10000.0f);
	}


	// --------------------------------------------------------------------------------------------
	// functii de input output --------------------------------------------------------------------
	
	//tasta apasata
	void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == 27) {
			glutLeaveFullScreen(); 
			lab::glut::close();	// ESC inchide glut si 
		}
		if(key_pressed == 32) {
			//SPACE reincarca shaderul si recalculeaza locatiile (offseti/pointeri)
			glDeleteProgram(gl_program_shader);
			gl_program_shader = lab::loadShader("shadere\\shader_vertex.glsl", "shadere\\shader_fragment.glsl");
		}
		if(key_pressed == 'w'){
			static bool wire =true;
			wire=!wire;
			glPolygonMode(GL_FRONT_AND_BACK, (wire?GL_LINE:GL_FILL));
		}
	}
	//tasta ridicata
	void notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y){	}
	//tasta speciala (up/down/F1/F2..) apasata
	void notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == GLUT_KEY_F1) glutFullScreenToggle();
	}
	//tasta speciala ridicata
	void notifySpecialKeyReleased(int key_released, int mouse_x, int mouse_y){}
	//drag cu mouse-ul
	void notifyMouseDrag(int mouse_x, int mouse_y){ }
	//am miscat mouseul (fara sa apas vreun buton)
	void notifyMouseMove(int mouse_x, int mouse_y){ }
	//am apasat pe un boton
	void notifyMouseClick(int button, int state, int mouse_x, int mouse_y){ }
	//scroll cu mouse-ul
	void notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y){ }

};

int main(){
	//initializeaza GLUT (fereastra + input + context OpenGL)
	lab::glut::WindowInfo window(std::string("Tema4 - Animatie"),800,600,100,100,true);
	lab::glut::ContextInfo context(2,1,false);
	lab::glut::FramebufferInfo framebuffer(true,true,true,true);
	lab::glut::init(window,context, framebuffer);

	// initializeaza GLEW (ne incarca functiile openGL, altfel ar trebui sa facem asta manual!)
	glewExperimental = true;
	glewInit();
	std::cout<<"GLEW:initializare"<<std::endl;

  Laborator mylab;
	lab::glut::setListener(&mylab);

	// taste
	std::cout<<"Taste:"<<std::endl<<"\tESC ... iesire"<<std::endl<<"\tSPACE ... reincarca shadere"<<std::endl<<"\tw ... toggle wireframe"<<std::endl;

	// run
	lab::glut::run();

	return 0;
}