#include "ShadeBasic.h"
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

using namespace glm;
unsigned int shade_vao;

void createShade()
{
	float side = 2.0f;
	const int numVertices = 12;
	vec4 shade_vertices[numVertices] = {
		// front triangle

	   {0.0,  side * 2 , 0.0, 1.0f},    // index 0
	   {-side, 0.0, side, 1.0f},      // index 1
	   {side, 0.0, side, 1.0f},      // index 2

	   // right triangle

	   {0.0,  side * 2, 0.0, 1.0f},     //index 3
	   {side, 0.0, side, 1.0f},       //index 4
	   {side, 0.0, -side, 1.0f},      //index 5

	   // back triangle
	  {0.0,  side * 2, 0.0, 1.0f},     // index 6
	  {side, 0.0, -side, 1.0f},      //index 7
	  {-side, 0.0, -side, 1.0f},      // index 8

	   //left triangle

	  { 0.0,  side * 2, 0.0, 1.0f},     // index 9
	  {-side, 0.0, -side, 1.0f},     // index 10
	  { -side, 0.0, side, 1.0f},      // index 11

	};

	vec3 P0 = vec3(shade_vertices[0]);
	vec3 P1 = vec3(shade_vertices[1]);
	vec3 P2 = vec3(shade_vertices[2]);
	vec3 P3 = vec3(shade_vertices[5]);
	vec3 P4 = vec3(shade_vertices[8]);

	vec3 normalF = normalize(vec3(cross(P1 - P0, P2 - P0)));

	vec3 normalR = normalize(vec3(cross(P2 - P0, P3 - P0)));

	vec3 normalB = normalize(vec3(cross(P3 - P0, P4 - P0)));

	vec3 normalL = normalize(vec3(cross(P4 - P0, P1 - P0)));


	// Triangle back normal calculation



	vec3 shade_normals[numVertices] = {
		{normalF},
		{normalF},
		{normalF},

		{normalR},
		{normalR},
		{normalR},

		{normalB},
		{normalB},
		{normalB},

		{normalL},
		{normalL},
		{normalL},

	};


	glGenVertexArrays(1, &shade_vao);
	glBindVertexArray(shade_vao);

	unsigned int handle[3];
	glGenBuffers(3, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * (numVertices), shade_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);  // Vertex position

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * numVertices, shade_normals, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);  // Vertex normal

	glBindVertexArray(0);

}

void drawShade() {
	glBindVertexArray(shade_vao);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glBindVertexArray(0);
}
