#ifndef CAJA_H
#define CAJA_H 

#include "box2d.h"
#include "raylib.h"

class Caja
{
private:

    b2Body* body;
    Texture2D textura;
    float ancho;
    float alto;

public:

    Caja(b2World* world, float x, float y,float ancho,float alto, Texture2D textura);
    ~Caja();
    void Dibujar();

    b2Body* GetBody();
};
#endif