#include "Parasol.h"
unsigned int parasol_vao;
void createParasol() {
	GLfloat vertices[] = {
					0.0, 0.5, 0.0,
					2.0 * cos(radians(0.0)), 0.0, 2.0 * sin(radians(0.0)) ,
					2.0 * cos(radians(60.0)),0.0, 2.0 * sin(radians(60.0)), // Index OAB

					0.0, 0.5, 0.0,
					2.0 * cos(radians(60.0)),0.0, 2.0 * sin(radians(60.0)),
					2.0 * cos(radians(120.0)), 0.0, 2.0 * sin(radians(120.0)), // Index 0BC

					0.0, 0.5, 0.0, 
					2.0 * cos(radians(120.0)), 0.0, 2.0 * sin(radians(120.0)), 
					2.0 * cos(radians(180.0)), 0.0, 2.0 * sin(radians(180.0)), // Index OCD

					0.0, 0.5, 0.0,
					2.0 * cos(radians(180.0)), 0.0, 2.0 * sin(radians(180.0)),
					2.0 * cos(radians(240.0)), 0.0, 2.0 * sin(radians(240.0)), // Index 0DE


					0.0, 0.5, 0.0,
					2.0 * cos(radians(240.0)), 0.0, 2.0 * sin(radians(240.0)), 
					2.0 * cos(radians(300.0)), 0.0, 2.0 * sin(radians(300.0)),//Index OEF

					0.0, 0.5, 0.0,
					2.0 * cos(radians(300.0)), 0.0, 2.0 * sin(radians(300.0)),
					2.0 * cos(radians(0.0)), 0.0, 2.0 * sin(radians(0.0)),//Index OFA
				


	};
	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, // Red

		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, // Yellow

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, // Green

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, // Blue

		0.0f, 1.0f, 1.0f, 
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, // Cyan

		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, // Magenta





	};
	
	glGenVertexArrays(1, &parasol_vao);
	glBindVertexArray(parasol_vao);
	unsigned int handle[2];
	glGenBuffers(2, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	




}
void drawParasol() {
	glBindVertexArray(parasol_vao);
	glDrawArrays(GL_TRIANGLES, 0, 18);


}