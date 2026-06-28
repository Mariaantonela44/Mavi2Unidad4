#include "Player.h"

const float SCALE = 30.0f;
const int SCREEN_HEIGHT = 900;

Player::Player(b2World* world,float x, float y){
    ancho = 100;
    alto = 100;

    estado = 0;
    frameActual = 0;
    tiempoAnimacion = 0;
    mirandoDerecha = true;
    puedeSaltar = true;
    tocandoSuelo = false;
    bloqueadoIzquierda = false;
    bloqueadoDerecha = false;

    // IDLE
    idle[0] = LoadTexture("assets/player/idle/Warrior_Idle_1.png");
    idle[1] = LoadTexture("assets/player/idle/Warrior_Idle_2.png");
    idle[2] = LoadTexture("assets/player/idle/Warrior_Idle_3.png");
    idle[3] = LoadTexture("assets/player/idle/Warrior_Idle_4.png");
    idle[4] = LoadTexture("assets/player/idle/Warrior_Idle_5.png");
    idle[5] = LoadTexture("assets/player/idle/Warrior_Idle_6.png");

    // SALTAR
    jump[0] = LoadTexture("assets/player/Jump/Warrior_Jump_1.png");
    jump[1] = LoadTexture("assets/player/Jump/Warrior_Jump_2.png");
    jump[2] = LoadTexture("assets/player/Jump/Warrior_Jump_3.png");

    // CAMINAR
    run[0] = LoadTexture("assets/player/Run/Warrior_Run_1.png");
    run[1] = LoadTexture("assets/player/Run/Warrior_Run_2.png");
    run[2] = LoadTexture("assets/player/Run/Warrior_Run_3.png");
    run[3] = LoadTexture("assets/player/Run/Warrior_Run_4.png");
    run[4] = LoadTexture("assets/player/Run/Warrior_Run_5.png");
    run[5] = LoadTexture("assets/player/Run/Warrior_Run_6.png");
    run[6] = LoadTexture("assets/player/Run/Warrior_Run_7.png");
    run[7] = LoadTexture("assets/player/Run/Warrior_Run_8.png");


    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / SCALE, y / SCALE);
    bodyDef.fixedRotation = true;

    body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(20.0f / SCALE,40.0f / SCALE );
    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 0.2f;
    fixture.friction = 0.8f;
    body->CreateFixture(&fixture);
    body->GetUserData().pointer = 1;
}

void Player::MoverIzquierda(){
    if (!bloqueadoIzquierda){
        b2Vec2 vel = body->GetLinearVelocity();
        body->SetLinearVelocity(b2Vec2(-5.0f, vel.y));

        estado = 1;
        mirandoDerecha = false;
    }
}

void Player::MoverDerecha(){
    if (!bloqueadoDerecha){
        b2Vec2 vel = body->GetLinearVelocity();
        body->SetLinearVelocity(b2Vec2(5.0f, vel.y));

        estado = 1;
        mirandoDerecha = true;
    }
}

void Player::PuedeSaltar(bool valor){
    tocandoSuelo = valor;
}

void Player::Saltar(){
    b2Vec2 vel = body->GetLinearVelocity();
    if (vel.y >= -0.2f && vel.y <= 0.2f){
        body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 10.0f),true);
        estado = 2;
    }
}


void Player::Detener(){
    b2Vec2 vel = body->GetLinearVelocity();
    body->SetLinearVelocity(b2Vec2(0.0f, vel.y));
    estado = 0;
}

void Player::Actualizar(){
    tiempoAnimacion += GetFrameTime();
    if (tiempoAnimacion >= 0.12f){
        frameActual++;
        tiempoAnimacion = 0;
    }
    b2Vec2 vel = body->GetLinearVelocity();
}

b2Body* Player::GetBody(){
    return body;
}

void Player::Dibujar(){
    b2Vec2 pos = body->GetPosition();

    Texture2D sprite;
    int cantidadFrames = 6;

    if (estado == 0) {
        cantidadFrames = 6;
        sprite = idle[frameActual % cantidadFrames];
    }
    else if (estado == 1){
        cantidadFrames = 8;
        sprite = run[frameActual % cantidadFrames];
    }
    else{
        cantidadFrames = 3;
        sprite = jump[frameActual % cantidadFrames];
    }

    float anchoSprite;

    if (mirandoDerecha){
        anchoSprite = (float)sprite.width;
    }
    else{
        anchoSprite = -(float)sprite.width;
    }

    DrawTexturePro(sprite, Rectangle{ 0, 0, anchoSprite, (float)sprite.height }, Rectangle{ pos.x * SCALE,SCREEN_HEIGHT - pos.y * SCALE,ancho,alto },Vector2{ ancho / 2, alto / 2 },0, WHITE);
}