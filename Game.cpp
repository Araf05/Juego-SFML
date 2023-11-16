#include "Game.h"

Game::Game(const int& width, const int& height)
{
    initMenu(width, height);
    _newGame = new MenuNewGame;
    if(_newGame == nullptr)
    {
        std::cout<<"Error de asignacion de Memoria: NewGame"<<std::endl;
        exit(-1);
    }
    initGamePlay();
}

Game::~Game()
{
    delete [] _menu;
    delete [] _runGame;
    delete [] _newGame;
}


void Game::initMenu(const int& width, const int& height)
{
    /// si hay archivo de partidas guardadas, mostrar opcion en el menu la opcion Continue y score

    _menu = new Menu(width, height, _hayPartidasGuardadas);
    if(_menu == nullptr)
    {
        std::cout<<"Error de asignacion de Memoria: Menu"<<std::endl;
        exit(-1);
    }
}

void Game::initGamePlay( )
{
    _runGame = new GamePlay();
    if(_runGame == nullptr)
    {
        std::cout<<"Error de asignacion de Memoria: GamePlay"<<std::endl;
        exit(-1);
    }
}

void Game::setEstado(int& ops)
{
    switch(ops)
    {
        case 0: _estado = ESTADOS_GAME::NEWGAME;
        break;
        case 1: _estado = ESTADOS_GAME::GAMEPLAY;
        break;
        case 2: _estado = ESTADOS_GAME::SCORE;
        break;
        case 3: _estado = ESTADOS_GAME::CREDITS;
        break;
        case 4: _estado = ESTADOS_GAME::QUIT;
        break;
    }
}

bool Game::savePartida(const int& puntos)
{
    ArchivoPartidas file("player.dat");
    Partida reg;

    reg.setName(_playerName);
    reg.setPoints(puntos);
    reg.setEstado(true);

    return file.grabarRegistro(reg);
}

void Game::cmd(const sf::Event& event)
{
    switch(_estado)
    {
        case ESTADOS_GAME::MENU:
            _menu->cmd();
        break;
        case ESTADOS_GAME::NEWGAME:
            _newGame->cmd(event);

        break;
        case ESTADOS_GAME::GAMEPLAY:
            _runGame->cmd();
        break;
        case ESTADOS_GAME::SCORE:

        break;
        case ESTADOS_GAME::CREDITS:

        break;
        case ESTADOS_GAME::QUIT:

        break;
    }
}



void Game::update()
{
    int ops = -1;

    switch(_estado)
    {
        case ESTADOS_GAME::MENU:
            _menu->update(ops);
            if(ops!= -1)
            {
                setEstado(ops);
            }
        break;
        case ESTADOS_GAME::NEWGAME:
            _newGame->update();
            if(_newGame->ingreso)
            {
                _estado = ESTADOS_GAME::GAMEPLAY;
                _playerName = _newGame->getName();
                _runGame->setName(_playerName);
            }

        break;
        case ESTADOS_GAME::GAMEPLAY:
            _runGame->update();
            if(_runGame->isGameOver())
            {
                _time++;
                if(_time >= _holdTime)
                {
                    _estado = ESTADOS_GAME::SCORE;
                    savePartida(_runGame->getPoints());
                    _time=0;
                }
            }
        break;
        case ESTADOS_GAME::SCORE:

        break;
        case ESTADOS_GAME::CREDITS:

        break;
        case ESTADOS_GAME::QUIT:
            exit(0);
        break;
    }
}

void Game::draw( sf::RenderWindow& window)
{
    switch(_estado)
    {
        case ESTADOS_GAME::MENU:
            window.draw(*_menu);
        break;
        case ESTADOS_GAME::NEWGAME:
            window.draw(*_newGame);
        break;
        case ESTADOS_GAME::GAMEPLAY:
            window.draw(*_runGame);
        break;
        case ESTADOS_GAME::SCORE:

        break;
        case ESTADOS_GAME::CREDITS:

        break;
        case ESTADOS_GAME::QUIT:

        break;
    }
}
