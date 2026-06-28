#include "Sensor.h"

const float SCALE = 30.0f;
const int SCREEN_HEIGHT = 900;

Sensor::Sensor(b2World* world, float x, float y, float ancho, float alto)
{
    this->ancho = ancho;
    this->alto = alto;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x / SCALE, y / SCALE);

    body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox((ancho / 2) / SCALE, (alto / 2) / SCALE);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.isSensor = true;

    body->CreateFixture(&fixture);

    // Identificador del sensor
    body->GetUserData().pointer = 3;
}

b2Body* Sensor::GetBody()
{
    return body;
}

void Sensor::Dibujar()
{
    b2Vec2 pos = body->GetPosition();

    Rectangle rect = {pos.x * SCALE - ancho / 2,SCREEN_HEIGHT - pos.y * SCALE - alto / 2,ancho,alto};

    DrawRectangleLinesEx(rect, 4, RED); 
}