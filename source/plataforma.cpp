#include "Plataforma.h"

const float ESCALA = 30.0f;

Plataforma::Plataforma(){
    body = nullptr;
    ancho = 0;
    alto = 0;
    textura = { 0 };

}

void Plataforma::Crear(b2World* world,float x,float y,float ancho,float alto, Texture2D textura){
    this->ancho = ancho;
    this->alto = alto;
    this->textura = textura;
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set( x / ESCALA,y / ESCALA);
    body = world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox( (ancho / 2) / ESCALA, (alto / 2) / ESCALA);

    body->CreateFixture(&shape, 1.0f);
}

void Plataforma::Draw(){
    b2Vec2 pos = body->GetPosition();

    DrawTexturePro( textura, Rectangle{ 0, 0, (float)textura.width, (float)textura.height},
        Rectangle{pos.x * ESCALA, 900 - pos.y * ESCALA, ancho, alto},
        Vector2{ ancho / 2, alto / 2 }, 0, WHITE );
}