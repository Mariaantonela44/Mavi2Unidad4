#include "Mundo.h"

Mundo::Mundo() : world(b2Vec2(0.0f, -9.8f)){
}

void Mundo::Actualizar(){
    world.Step( 1.0f / 60.0f,  8, 3 );
}

b2World* Mundo::GetWorld(){
    return &world;
}