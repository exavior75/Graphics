# Linux
CC=g++
LIBS= -lglut -lGLEW -lGL -lfreeimageplus -lassimp -I"../bin/sound/include" -I/usr/local/include/bullet  -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath

# For Macs uncomment the next line and comment out the previous one
#CC=clang++
#LIBS=  -framework OpenGL -framework GLUT -framework Cocoa -lGLEW -stdlib=libc++
# Assuming you want to use a recent compiler

# Compiler flags
CXXFLAGS= -g -Wall -Wextra -std=c++0x -pthread $(DEFS)


OUTPUT = ../bin/Project
MAIN = ../src/main.cpp
SHADERLOADER = ../src/shaderloader.cpp
SHADERLOADERH = ../src/shaderloader.h
RENDERER = ../src/renderer.cpp
RENDERERH = ../src/renderer.h
ENTITYMANAGER = ../src/entitymanager.cpp
ENTITYMANAGERH = ../src/entitymanager.h
ENTITY = ../src/entity.cpp
ENTITYH = ../src/entity.h
CONFIG = ../src/config.cpp
CONFIGH = ../src/config.h
CAMERA = ../src/camera.cpp
CAMERAH = ../src/camera.h
PHYSICS = ../src/physics.cpp
PHYSICSH = ../src/physics.h
ENTPHYSICS = ../src/entityphysics.cpp
ENTPHYSICSH = ../src/entityphysics.h
LIGHT = ../src/light.cpp
LIGHTH = ../src/light.h
SPRITE = ../src/sprite.cpp
SPRITEH = ../src/sprite.h
GAME = ../src/game.cpp
GAMEH = ../src/game.h
FLATRENDERER = ../src/flatRenderer.cpp
FLATRENDERERH = ../src/flatRenderer.h
DEPTHRENDERER = ../src/depthRenderer.cpp
DEPTHRENDERERH = ../src/depthRenderer.h

all: main

main: main.o config.o entity.o entitymanager.o shaderloader.o camera.o renderer.o entityphysics.o physics.o light.o sprite.o game.o flatRenderer.o depthRenderer.o
	$(CC) $(CXXFLAGS) -o $(OUTPUT) main.o config.o entity.o entitymanager.o shaderloader.o camera.o renderer.o entityphysics.o physics.o light.o sprite.o game.o flatRenderer.o depthRenderer.o $(LIBS) ../bin/sound/bin/linux-gcc-64/libIrrKlang.so

main.o: $(MAIN) $(CONFIGH) $(SHADERLOADERH) $(RENDERERH) $(ENTITYH) $(ENTITYMANAGERH)
	$(CC) $(CXXFLAGS) -c $(MAIN) $(LIBS)

entitymanager.o: $(ENTITYMANAGER) $(ENTITYMANAGERH) $(CONFIGH) $(ENTITYH)
	$(CC) $(CXXFLAGS) -c $(ENTITYMANAGER) $(LIBS)

game.o: $(ENTITY) $(GAME) $(GAMEH) $(ENTITYH) $(CONFIGH) $(PHYSICSH)
	$(CC) $(CXXFLAGS) -c $(GAME) $(LIBS)

entity.o: $(ENTITY) $(ENTITYH) $(CONFIGH) $(ENTPHYSICSH) $(LIGHTH) $(RENDERERH)
	$(CC) $(CXXFLAGS) -c $(ENTITY) $(LIBS)

entityphysics.o: $(ENTPHYSICS) $(ENTPHYSICSH) $(PHYSICSH) $(ENTITYH)
	$(CC) $(CXXFLAGS) -c $(ENTPHYSICS) $(LIBS)

physics.o: $(PHYSICS) $(PHYSICSH)
	$(CC) $(CXXFLAGS) -c $(PHYSICS) $(LIBS)

shaderloader.o: $(SHADERLOADER) $(SHADERLOADERH) $(CONFIGH)
	$(CC) $(CXXFLAGS) -c $(SHADERLOADER) $(LIBS)

config.o: $(CONFIG) $(CONFIGH) $(ENTITYMANAGERH) $(SHADERLOADERH) $(CAMERAH) $(PHYSICSH) $(LIGHTH) $(GAMEH) $(RENDERERH)
	$(CC) $(CXXFLAGS) -c $(CONFIG) $(LIBS)

renderer.o: $(RENDERER) $(RENDERERH) $(SHADERLOADERH) $(ENTITYH) $(CONFIGH) $(SPRITEH) $(FLATRENDERERH)
	$(CC) $(CXXFLAGS) -c $(RENDERER) $(LIBS)

camera.o: $(CAMERA) $(CAMERAH) $(ENTITYH)
	$(CC) $(CXXFLAGS) -c $(CAMERA) $(LIBS)

light.o: $(LIGHT) $(LIGHTH) $(CONFIGH)
	$(CC) $(CXXFLAGS) -c $(LIGHT) $(LIBS)

sprite.o: $(SPRITE) $(SPRITEH) $(CONFIGH)
	$(CC) $(CXXFLAGS) -c $(SPRITE) $(LIBS)

flatRenderer.o: $(FLATRENDERER) $(FLATRENDERERH) $(RENDERER) $(CONFIG) $(SPRITE)
	$(CC) $(CXXFLAGS) -c $(FLATRENDERER) $(LIBS)

depthRenderer.o: $(DEPTHRENDERER) $(DEPTHRENDERERH) $(RENDERER) $(CONFIG)
	$(CC) $(CXXFLAGS) -c $(DEPTHRENDERER) $(LIBS)

clean:
	rm ../bin/Project *.o
