#include <GL/glew.h> // glew must be included before the main gl libs
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <cstdlib>
#include <GL/glut.h> // doing otherwise causes compiler shouting
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier
#include "include/object.h"
#include "include/universe.h"
#include "include/shader.h"
#include "include/mesh.h"
#include "include/texture.h"
Object::Object(Universe* d, Shader *shade, int width, int height)
{
	daemon = d;
	environment = nullptr;
	shader = shade;
	mesh = new Mesh("board.obj");
	texture = new Texture("board.png");
	initialize(width, height);
}

Object::Object (Universe *d, Shader *shade, std::string obName, float obMass, float obDensity, int width, int height)
{
	daemon = d;
	environment = nullptr;
	shader = shade;
	name = obName;
	mass = obMass;
	density = obDensity;
	mesh = new Mesh("board.obj");
	texture = new Texture("board.png");
	initialize(width, height);
}

bool Object::initialize(int width, int height)
{
	view = glm::lookAt(glm::vec3(0.0, 8.0, -16.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up
	projection = glm::perspective(45.0f, float(width) / float(height), 0.01f, 100.0f); 
	return true;
}

void Object::render()
{
    mvp = projection * view * model;//premultiply the matrix
    shader->Bind();
	texture->Bind();//Bind the textures
    shader->Update(mvp);
	mesh->Draw();
	for(unsigned int i=0; i<inventory.size(); i++)//Iterate through inventory
		inventory[i]->render();//Render each child
}

void Object::reshape(int width, int height)
{
	projection = glm::perspective(45.0f, float(width) / float(height), 0.01f, 100.0f);//Reset projection
	for(unsigned int i=0; i<inventory.size(); i++)//Iterate through inventory
		inventory[i]->reshape(width, height);//Reshape each child
}

void Object::update(float dt)
{
	orbit.angle += dt * M_PI / 2; //move through 90 degrees a second
	if (rotation.active)
	{//spin 90 degrees a second
		if(rotation.inverse)
			rotation.angle -= dt * M_PI / 2;//counter-clockwise
		else
			rotation.angle += dt * M_PI / 2;//clockwise
	}//else, don't spin
	if(environment == nullptr)
		model = glm::translate(glm::mat4(0.1f), glm::vec3(8.0 * sin(orbit.angle), 0.0, 8.0 * cos(orbit.angle))) * glm::rotate(glm::mat4(1.0f), rotation.angle, glm::vec3(0, 1, 0));
	else
		model = glm::translate(environment->getModel(), glm::vec3(8.0 * sin(orbit.angle), 0.0, 8.0 * cos(orbit.angle))) * glm::rotate(glm::mat4(1.0f), rotation.angle, glm::vec3(0, 1, 0));
	//Iterate through inventory
	for(unsigned int i=0; i<inventory.size(); i++)
		inventory[i]->update(dt);
}

void Object::eventMove(Object *ob)
{
	if(environment != nullptr)
		environment->release();//this);
	environment = ob;
	ob->receive(this);
}

void Object::receive(Object *ob)
{
	inventory.push_back(ob);
}

void Object::release()
{
	//TODO: Need a search algorithm to remove
	inventory.pop_back();
}

float Object::getMass()
{
	return mass;
}

float Object::getDensity()
{
	return density;
}

glm::mat4 Object::getModel()
{
	return model;
}

Object *Object::getEnvironment()
{
	return environment;
}

vector<Object*> Object::getInventory()
{
	return inventory;
}