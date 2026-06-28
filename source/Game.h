#ifndef GAME_H
#define GAME_H

#include "Mundo.h"
#include "player.h"
#include "Caja.h"
#include "Plataforma.h"
#include "sensor.h"
#include "ContactListener.h"

#include <vector>

class Game
{
private:

    Mundo mundo;

    ContactListener listener;

    Player* player;

    std::vector<Caja*> cajas;

    Plataforma piso;
    Plataforma plataforma1;
    Plataforma plataforma2;
    Plataforma limiteIzquierdo;
    Plataforma limiteDerecho;
    Plataforma limiteSuperior;

    Sensor* sensor;
    b2WeldJoint* joint = nullptr;
    Caja* cajaAgarrada = nullptr;

    Texture2D fondo;
    Texture2D texturaCaja;
    Texture2D texturaPlataforma;

    bool gano;
    bool perdio;
    void ReiniciarJuego();
    void CargarRecursos();
    void CrearObjetos();
    void ProcesarControles();
    void Update();
    void Draw();

public:

    Game();
    ~Game();

    void Run();
};

#endif