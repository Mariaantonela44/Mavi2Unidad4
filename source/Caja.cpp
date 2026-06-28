#include "Caja.h"

const float SCALE = 30.0f;
const int SCREEN_HEIGHT = 900;

Caja::Caja(b2World* world, float x, float y, float ancho, float alto, Texture2D textura){
    this->ancho = ancho;
    this->alto = alto;
    this->textura = textura;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set( x / SCALE, y / SCALE);

    body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox( ancho / 2 / SCALE, alto / 2 / SCALE);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 1.0f;
    fixture.friction = 0.5f;
    fixture.restitution = 0.1f;

    body->CreateFixture(&fixture);
    body->GetUserData().pointer = 2;
}

Caja::~Caja(){
    if (body){
        body->GetWorld()->DestroyBody(body);
        body = nullptr;
    }
}

void Caja::Dibujar()
{
    b2Vec2 posicionCaja = body->GetPosition();

    float xPantalla = posicionCaja.x * 30.0f;
    float yPantalla = 900 - posicionCaja.y * 30.0f;

    Rectangle texturaCompleta =
    {0,0, (float)textura.width, (float)textura.height};

    Rectangle areaDibujo =
    {xPantalla, yPantalla, ancho, alto};

    Vector2 centroCaja = { ancho / 2, alto / 2 };

    float rotacion = -body->GetAngle() * RAD2DEG;

    DrawTexturePro( textura, texturaCompleta, areaDibujo, centroCaja, rotacion, WHITE);
}

b2Body* Caja::GetBody(){
    return body;
}