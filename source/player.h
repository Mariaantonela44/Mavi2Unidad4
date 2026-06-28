#ifndef PLAYER_H
#define PLAYER_H    

#include "raylib.h"
#include "box2d.h"

class Player
{
private:
    b2Body* body;
   
    float ancho;
    float alto;

    Texture2D idle[6];
    Texture2D run[8];
    Texture2D jump[3];

    int estado;
    int frameActual;
    float tiempoAnimacion;
    bool puedeSaltar;
    bool mirandoDerecha;
    bool tocandoSuelo;
    bool bloqueadoIzquierda;
    bool bloqueadoDerecha;

public:
     b2Body* GetBody();
    Player(b2World* world,float x, float y);
    void MoverIzquierda();
    void MoverDerecha();
    void Saltar();
    void Detener();
    void PuedeSaltar(bool valor);
    void Actualizar();
    void Dibujar();
}; 
#endif
