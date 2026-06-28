#ifndef SENSOR_H
#define SENSOR_H

#include "box2d.h"
#include "raylib.h"

class Sensor
{
private:
    b2Body* body;

    float ancho;
    float alto;

public:
    Sensor(b2World* world, float x, float y, float ancho, float alto);

    b2Body* GetBody();

    void Dibujar();
};

#endif
