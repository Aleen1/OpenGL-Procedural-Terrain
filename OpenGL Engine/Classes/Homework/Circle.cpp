#include "Circle.h"
#include<cstdio>
#include<iostream>
#include<iomanip>

#define NrPCT 100

Circle::Circle()
{
	center = Vector3();
	radius = 0.0;
}

Circle::Circle(Vector3 _center, float _radius, Color color)
{
	center = _center;
	radius = _radius;

	std::vector<Vector3> points = Circumference();
	GLfloat vertices[5 * NrPCT];
	GLfloat colors[5 * NrPCT];

	int crt = 4;
	vertices[0] = center.x; vertices[1] = center.y; vertices[2] = center.z; vertices[3] = 1.0f;
	colors[0] = color.r; colors[1] = color.g; colors[2] = color.b; colors[3] = color.a;

	for (int i = 0; i < NrPCT; ++i) {
		vertices[crt++] = points[i].x;
		vertices[crt++] = points[i].y;
		vertices[crt++] = 0.0f;
		vertices[crt++] = 1.0f;

	}

	vertices[crt++] = vertices[4];
	vertices[crt++] = vertices[5];
	vertices[crt++] = vertices[6];
	vertices[crt++] = vertices[7];

	crt = 4;
	for (int i = 0; i <= NrPCT; ++i) {
		colors[crt++] = color.r;
		colors[crt++] = color.g;
		colors[crt++] = color.b;
		colors[crt++] = color.a;
	}

	GLuint  indices[2 * NrPCT];
	for (int i = 0; i <= NrPCT + 1; ++i) {
		indices[i] = i;
	}

	vertexArray = new VertexArray();
	Buffer* positionBuffer = new Buffer(vertices, (NrPCT + 2) * 4, 4);
	Buffer* colorBuffer = new Buffer(colors, (NrPCT + 2) * 4, 4);
	indexBuffer = new IndexBuffer(indices, NrPCT + 2);

	vertexArray->AddBuffer(positionBuffer, 0);
	vertexArray->AddBuffer(colorBuffer, 1);

	//worldMatrix = Matrix4(1.0f);
	shader = new Shader("Shaders/Shader.vert", "Shaders/Shader.frag");
}

void Circle::Draw() {
	shader->Bind();
	vertexArray->Bind();
	indexBuffer->Bind();

	//shader->SetUniformMatrix4fv("gWorld", worldMatrix);
	shader->SetUniformMatrix4fv("gWorld", transform->matrix);
	glDrawElements(GL_TRIANGLE_FAN, indexBuffer->GetCount(), GL_UNSIGNED_INT, 0);

	indexBuffer->Unbind();
	vertexArray->Unbind();
	shader->Unbind();
}

std::vector<Vector3> Circle::Circumference()
{
	std::vector<Vector3> circlePoints;

	float alfa = ToRadians(360.0f / NrPCT);
	Vector3 initPoint(center.x, center.y + radius, 0);
	circlePoints.push_back(initPoint);

	Vector3 point;
	float x = initPoint.x, y = initPoint.y;
	for (int i = 0; i < NrPCT + 1; ++i) {
		alfa = ToRadians((i + 1) * (360.0f / NrPCT));

		point.x = center.x + (x - center.x) * cos(alfa) - (y - center.y) * sin(alfa);
		point.y = center.y + (x - center.x) * sin(alfa) + (y - center.y) * cos(alfa);
		point.z = 0;
		circlePoints.push_back(point);
	}

	return circlePoints;
}

Circle::~Circle()
{
}
