
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Cube.h"
#include <GL/freeglut.h>


#define GLM_FORCE_RADIANS 

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

using namespace glm;

GLuint vao;
GLuint vbo[1];
GLboolean wire_frame = false;
GLuint program;
GLboolean change_projection = false;
GLboolean top_view = false;



const double kPI = 3.1415926535897932384626433832795;

mat4 view_matrix(1.0f);
mat4 model_matrix(1.0f);
mat4 projection_matrix(1.0f);
mat4 shear_matrix(1.0f);
mat4 translation_matrix(1.0f);
mat4 rotate_matrix(1.0f);
mat4 scale_matrix(1.0f);

GLuint model_matrix_loc;
GLuint view_matrix_loc;
GLuint projection_matrix_loc;
vec3 eye(0.0f, 0.0f, 3.0f);
vec3 center(0.0f, 0.0f, 0.0f);
vec3 up(0.0, 1.0, 0.0);

GLfloat angle = 0.0f;


/********************************************/



char* ReadFile(const char* filename);
GLuint initShaders(const char* v_shader, const char* f_shader);
void Initialize();
void Display(void);

char* ReadFile(const char* filename){
	FILE* infile;
#ifdef WIN32
	fopen_s(&infile, filename, "rb");
#else
	infile = fopen(filename, "r");
#endif
	if (!infile) {
		printf("Unable to open file %s\n", filename);
		return NULL;
	}

	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	GLchar* source = (GLchar*)malloc(len + 1);
	fread(source, 1, len, infile);
	fclose(infile);
	source[len] = 0;

	return (GLchar*) (source);
}

GLuint initShaders(const char *v_shader, const char *f_shader) {

	GLuint p = glCreateProgram();
	GLuint v = glCreateShader(GL_VERTEX_SHADER);
	GLuint f = glCreateShader(GL_FRAGMENT_SHADER);

	const char * vs = ReadFile(v_shader);
	const char * fs = ReadFile(f_shader);

	glShaderSource(v, 1, &vs, NULL);
	glShaderSource(f, 1, &fs, NULL);
	free((char*)vs);
	free((char*)fs);

	glCompileShader(v);
	GLint compiled;
	glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLsizei len;
		glGetShaderiv(v, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = (GLchar*)malloc(len + 1);
		glGetShaderInfoLog(v, len, &len, log);
		printf("Vertex Shader compilation failed: %s\n",log);
		free(log);
	}

	glCompileShader(f);

	glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLsizei len;
		glGetShaderiv(f, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = (GLchar*)malloc(len + 1);
		glGetShaderInfoLog(f, len, &len, log);
		printf("Fragment Shader compilation failed: %s\n", log);
		free(log);
	}

	glAttachShader(p, v);
	glAttachShader(p, f);
	glLinkProgram(p);

	GLint linked;
	glGetProgramiv(p, GL_LINK_STATUS, &linked);
	if (!linked) {
		GLsizei len;
		glGetProgramiv(p, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = (GLchar*)malloc(len + 1);
		glGetProgramInfoLog(p, len, &len, log);
		printf("Shader linking failed: %s\n", log);
		free(log);
	}
	glUseProgram(p);
	return p;
}

/****************************************************/

void Initialize(void) {

	// Create the program for rendering the model
	program = initShaders("cube_shader.vs", "cube_shader.fs");

	model_matrix_loc = glGetUniformLocation(program, "model_matrix");
	view_matrix_loc = glGetUniformLocation(program, "view_matrix");
	projection_matrix_loc = glGetUniformLocation(program, "projection_matrix");
	createCube();

	view_matrix = glm::lookAt(eye, center, up);
	//glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, (GLfloat*)&view_matrix[0]);
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, (GLfloat*)&model_matrix[0]);
}
/***********************************************************/

void Display(void){

	// Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Setup
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glLineWidth(5.0);


	if (top_view) {

		eye[0] = 0.0;
		eye[1] = 2.0;
		eye[2] = 0.0;

		up[0] = 1.0;
		up[1] = 0.0;
		up[2] = 0.0;

		view_matrix = lookAt(eye, center, up);

	}
	else {
		eye[0] = 0.0;
		eye[1] = 0.0;
		eye[2] = 3.0;

		up[0] = 0.0;
		up[1] = 1.0;
		up[2] = 0.0;
		view_matrix = lookAt(eye, center, up);	
	}
	glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, (GLfloat*)&view_matrix[0]);
	
	


	if (wire_frame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (change_projection) {
		projection_matrix = frustum(-2.0, 2.0, -2.0, 2.0, 2.0, 10.0);
	}
	else {
		projection_matrix = ortho(-2.0, 2.0, -2.0, 2.0, 2.0, 10.0);
	}
	glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, (GLfloat*)&projection_matrix[0]);
	

	
	
	  
	

	//glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, (GLfloat*)&model_matrix[0]);
	
		translation_matrix = translate(mat4(1.0f), vec3(-0.6,-0.6, 0.0));
		model_matrix = translation_matrix;
		glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, (GLfloat*)&model_matrix[0]);
		drawCube();

		translation_matrix = translate(mat4(1.0f), vec3(0.6, 0.6, 0.0));
		rotate_matrix = rotate(mat4(1.0f), radians(45.0f), vec3(1.0f, 0.0f, 0.0f));
		model_matrix = translation_matrix * rotate_matrix;
		glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, (GLfloat*)&model_matrix[0]);
		drawCube();
	
		translation_matrix = translate(mat4(1.0f), vec3(0.6, -0.6, 0.0));
		scale_matrix = scale(mat4(1.0f), vec3(1.5f, 1.5f, 1.0f));
		model_matrix = translation_matrix * scale_matrix;
		glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, (GLfloat*)&model_matrix[0]);
		drawCube();

		translation_matrix = translate(mat4(1.0f), vec3(-0.6f, 0.6f, 0.0f));
		rotate_matrix = rotate(mat4(1.0f), radians(45.0f), vec3(1.0f, 2.0f, 3.0f));
		model_matrix = translation_matrix * rotate_matrix;
		glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, (GLfloat*)&model_matrix[0]);
		drawCube();
		//translation_matrix = translate(mat4(1.0f), vec3(0.0, 0.0, 0.0));
		shear_matrix = { 1, 0.5, 0, 0, 0.5, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		//model_matrix = translation_matrix;
		glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, (GLfloat*)&shear_matrix[0]);
		drawCube();
	//drawCube();

	glFlush();
}

/**************************************************************************************/
void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'q':case 'Q':
		exit(EXIT_SUCCESS);
		break;
	case 'w':case 'W':
		wire_frame = !wire_frame;
		break;
	case 'c':case 'C':
		change_projection = !change_projection;
		
		break;
	case 't':case 'T':
		top_view = !top_view;
		break;

	}
	glutPostRedisplay();
}
/*********************************************************************************************/
void Timer(int n) {

	angle += 5.0f;
	glutPostRedisplay();
	glutTimerFunc(500, Timer, 1);

}
/**********************************************************/

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(600, 600);

	glutCreateWindow("Transformation, Camera, and Projection");

	if (glewInit()) {
		printf("Unable to initialize GLEW ... exiting\n");
	}

	Initialize();
	printf("%s\n", glGetString(GL_VERSION));
	glutDisplayFunc(Display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(500, Timer, 1);
	glutMainLoop();
	return 0;
}

/*************/



