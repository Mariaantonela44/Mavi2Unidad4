#include "Game.h"

Game::Game()
{
    InitWindow(1600, 900, "TP Integrador");
    SetTargetFPS(60);

    gano = false;
    perdio = false;

    player = nullptr;

    mundo.GetWorld()->SetContactListener(&listener);

    CargarRecursos();
    CrearObjetos();
}

Game::~Game()
{
    delete player;

    for (int i = 0; i < cajas.size(); i++)
    {
        delete cajas[i];
    }

    UnloadTexture(fondo);
    UnloadTexture(texturaCaja);
    UnloadTexture(texturaPlataforma);

    CloseWindow();
}

void Game::CargarRecursos()
{
    fondo = LoadTexture("assets/fondo3.png");
    texturaCaja = LoadTexture("assets/caja.png");
    texturaPlataforma = LoadTexture("assets/plataforma1.png");
}

void Game::CrearObjetos()
{
    player = new Player(mundo.GetWorld(), 250, 200);

    limiteIzquierdo.Crear(
        mundo.GetWorld(),
        0,
        450,
        30,
        900,
        texturaPlataforma
    );

    limiteDerecho.Crear(
        mundo.GetWorld(),
        1600,
        450,
        30,
        900,
        texturaPlataforma
    );

    limiteSuperior.Crear(
        mundo.GetWorld(),
        800,
        900,
        1600,
        30,
        texturaPlataforma
    );

    piso.Crear(
        mundo.GetWorld(),
        800,
        40,
        1600,
        80,
        texturaPlataforma);

    plataforma1.Crear(
        mundo.GetWorld(),
        500,
        250,
        300,
        30,
        texturaPlataforma);

    plataforma2.Crear(
        mundo.GetWorld(),
        1100,
        250,
        300,
        30,
        texturaPlataforma);

    sensor = new Sensor(
        mundo.GetWorld(),
        1450,
        70,
        300,
        300
    );

    for (int i = 0; i < 5; i++)
    {
        cajas.push_back( new Caja( mundo.GetWorld(), 150 + i * 70,  450, 50, 50, texturaCaja));
    }
}
void Game::ReiniciarJuego()
{
    if (joint != nullptr)
    {
        mundo.GetWorld()->DestroyJoint(joint);
        joint = nullptr;
        cajaAgarrada = nullptr;
    }

    for (int i = 0; i < cajas.size(); i++)
    {
        delete cajas[i];
    }

    cajas.clear();

    for (int i = 0; i < 5; i++)
    {
        cajas.push_back( new Caja( mundo.GetWorld(), 150 + i * 70, 450, 50,  50,  texturaCaja ));
    }

    // Reiniciar al jugador
    player->GetBody()->SetTransform( b2Vec2(250.0f / 30.0f, 200.0f / 30.0f), 0 );
    player->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
    listener.cajasEnSensor = 0;
    gano = false;
    perdio = false;

}

void Game::ProcesarControles()
{
    if (IsKeyDown(KEY_LEFT))
        player->MoverIzquierda();
    else if (IsKeyDown(KEY_RIGHT))
        player->MoverDerecha();
    else
        player->Detener();


    if (IsKeyPressed(KEY_SPACE))
        player->Saltar();
    if (IsKeyPressed(KEY_E))
    {
        // Si ya tiene una caja, la suelta
        if (joint != nullptr)
        {
            mundo.GetWorld()->DestroyJoint(joint);
            joint = nullptr;
            cajaAgarrada = nullptr;
        }
        else
        {
            // Buscar una caja cercana
            for (int i = 0; i < cajas.size(); i++)
            {
                b2Vec2 posPlayer = player->GetBody()->GetPosition();
                b2Vec2 posCaja = cajas[i]->GetBody()->GetPosition();

                float dx = posPlayer.x - posCaja.x;
                float dy = posPlayer.y - posCaja.y;

                float distancia = sqrt(dx * dx + dy * dy);

                if (distancia < 2.0f)
                {
                    cajaAgarrada = cajas[i];

                    b2WeldJointDef weld;

                    weld.bodyA = player->GetBody();
                    weld.bodyB = cajaAgarrada->GetBody();

                    weld.localAnchorA.Set(0.8f, 0.0f);
                    weld.localAnchorB.Set(0.0f, 0.0f);

                    joint = (b2WeldJoint*)mundo.GetWorld()->CreateJoint(&weld);

                    break;
                }
            }
        }
    }
    if (gano || perdio)
    {
        if (IsKeyPressed(KEY_R))
        {
            ReiniciarJuego();
        }
        return;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (listener.cajasEnSensor == 5)
        {
            gano = true;
            perdio = false;
        }
        else
        {
            gano = false;
            perdio = true;
        }
    }

}


void Game::Update()
{
    mundo.Actualizar();

    player->Actualizar();

}

void Game::Draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawTexturePro(
        fondo,
        Rectangle{ 0, 0, (float)fondo.width, (float)fondo.height },
        Rectangle{ 0, 0, 1600.0f, 900.0f },
        Vector2{ 0, 0 },
        0.0f,
        WHITE
    );

    piso.Draw();

    plataforma1.Draw();

    plataforma2.Draw();

    sensor->Dibujar();

    player->Dibujar();

    DrawText("E - Agarrar / Soltar caja", 20, 60, 20, WHITE);
    DrawText("R - para reiniciar", 20, 80, 20, WHITE);

    for (int i = 0; i < cajas.size(); i++)
    {
        cajas[i]->Dibujar();
    }

    DrawText( TextFormat("Cajas: %i / 5", listener.cajasEnSensor), 20, 20, 30, WHITE);

    if (gano){
        DrawText( "GANASTE",  650,  100, 60, GREEN);
    }

    if (perdio){
        DrawText("PERDISTE", 650, 100, 60, RED);
    }

    EndDrawing();
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        ProcesarControles();

        Update();

        Draw();
    }
}