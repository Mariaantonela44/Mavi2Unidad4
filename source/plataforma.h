#ifndef PLATAFORMA_H
#define PLATAFORMA_H 

#include "raylib.h"
#include "box2d.h"

class Plataforma
{
private:

    b2Body* body;

    float ancho;
    float alto;

    Texture2D textura;

public:

    Plataforma();
    void Crear(b2World* world,float x,float y,float ancho,float alto,Texture2D textura);
    void Draw();
};

#endif