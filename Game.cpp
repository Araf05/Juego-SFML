#include "Game.h"

Game::Game(const int& width, const int& height)
{
    _width = width;
    _height = height;
    initMenu(_width, _height);
//    leerPartidas();

}

Game::~Game()
{
    delete [] _menu;
    delete [] _runGame;
    delete [] _newGame;
    delete [] _score;
}

void Game::initNewGame()
{
    _newGame = new MenuNewGame;
    if(_newGame == nullptr)
    {
        std::cout<<"Error de asignacion de Memoria: NewGame"<<std::endl;
        exit(-1);
    }
}

void Game::initMenu(const int& width, const int& height)
{
    /// si hay archivo de partidas guardadas, mostrar opcion en el menu la opcion Continue y score
    _menu = new Menu(width, height);
    if(_menu == nullptr)
    {
        std::cout<<"Error de asignacion de Memoria: Menu"<<std::endl;
        exit(-1);
    }
}

void Game::initGamePlay( std::string nombre, int puntos)
{
    _runGame = new GamePlay(nombre, puntos);
    if(_runGame == nullptr)
    {
        std::cout<<"Error de asignacion de Memoria: GamePlay"<<std::endl;
        exit(-1);
    }
}

void Game::initCredit()
{
    _credits = new Credit;
    if(_credits == nullptr)
    {
        std::cout<<"Error de asignacion de Memoria: Credit"<<std::endl;
        exit(-1);
    }
}

void Game::initScore()
{
    _score = new Score();
    if(_score == nullptr)
    {
        std::cout<<"Error de asignacion de Memoria: Score"<<std::endl;
        exit(-1);
    }
}



void Game::setEstadoMenu(int& ops)
{
    switch(ops)
    {
        case 0:
            _estado = ESTADOS_GAME::NEWGAME;
            initNewGame();
        break;
        case 1:
             _estado = ESTADOS_GAME::CONTINUE;
             initContinue();
        break;
        case 2:
            _estado = ESTADOS_GAME::SCORE;
            initScore();
        break;
        case 3:
            _estado = ESTADOS_GAME::CREDITS;
            initCredit();
        break;
        case 4: _estado = ESTADOS_GAME::QUIT;
        break;
    }
}



bool Game::savePartida(const int& puntos)
{
    ArchivoPartidas file("player.dat");
    Partida reg;

    std::cout << _playerName << std::endl;
    reg.setName(_playerName);
    reg.setPoints(puntos);
    reg.setEstado(true);

    return file.grabarRegistro(reg);
}

void Game::leerPartidas()
{
    ArchivoPartidas file("player.dat");
    Partida reg;
    int cantReg = file.contarRegistros();
    if(cantReg == -1)
    {
        std::cout << "No hay archivo de partidas" << std::endl;
        return;
    }
    _hayPartidasGuardadas = true;
    for(int i = 0; i < cantReg; i++)
    {
        reg = file.leerRegistro(i);
        _playerName = reg.getName();
        _points = reg.getPoints();
    }
    std::cout<<_playerName<<std::endl;
    std::cout<<_points<<std::endl;
}

bool Game::updateFileScore(Puntaje nuevoPuntaje)
{
    ArchivoPuntajes file("puntajes.dat");
    Puntaje reg;
    int cantReg = file.contarRegistros();
    Puntaje aux;

    for(int i=0; i<cantReg; i++)
    {
        reg = file.leerRegistro(i);
        if(reg.getPoints() < nuevoPuntaje.getPoints())
        {
            aux = reg;
            file.modificar(i, nuevoPuntaje);
            for(int j=i+1; j<cantReg; j++)
            {
                reg = file.leerRegistro(j);
                file.modificar(j, aux);
                aux = reg;
            }
            return true;
        }
    }
    return false;
}

bool Game::saveScore(const int& puntos)
{
    ArchivoPuntajes file("puntajes.dat");
    Puntaje reg;

    reg.setName(_playerName);
    reg.setPoints(puntos);
    reg.setEstado(true);

    int cantReg = file.contarRegistros();
    std::cout<<"CATIDAD DE REGISTROS ANTES DE GRABAR"<< cantReg<<std::endl;
    if(cantReg<5)
    {
        file.grabarRegistro(reg);
        return updateFileScore(reg);
    }

    return updateFileScore(reg);
}

void Game::initContinue()
{
    leerPartidas();
    initGamePlay(_playerName, _points);
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
        case ESTADOS_GAME::CONTINUE:
            _runGame->cmd();
        break;
        case ESTADOS_GAME::GAMEPLAY:
            _runGame->cmd();
        break;
        case ESTADOS_GAME::SCORE:
            _score->cmd();
        break;
        case ESTADOS_GAME::CREDITS:
            _credits->cmd();
        break;
        case ESTADOS_GAME::QUIT:
            std::cout<<"salir"<<std::endl;
        break;
    }
}

void Game::handlerState()
{
    if((_estado == ESTADOS_GAME::NEWGAME)&&(_newGame->ingreso) )
    {
        _estado = ESTADOS_GAME::GAMEPLAY;
        _playerName = _newGame->getNombre();
        initGamePlay(_playerName, 0);
        _newGame->ingreso = false;
    }
    if((_estado == ESTADOS_GAME::CREDITS) && (_credits->volverMenu()) )
    {
        _estado = ESTADOS_GAME::MENU;
        initMenu(_width, _height);
    }
    if((_estado == ESTADOS_GAME::GAMEPLAY) && (_runGame->exitGame()) )
    {
//        savePartida(_runGame->getPoints());
//       if( saveScore(_runGame->getPoints()) ) std::cout<<"Score actualizado"<<std::endl;
        _estado = ESTADOS_GAME::MENU;
        initMenu(_width, _height);
        _time=0;
    }
    if((_estado == ESTADOS_GAME::CONTINUE) && (_runGame->exitGame()) )
    {
//        savePartida(_runGame->getPoints());
//        if( saveScore(_runGame->getPoints()) ) std::cout<<"Score actualizado"<<std::endl;
        _estado = ESTADOS_GAME::MENU;
        initMenu(_width, _height);
        _time=0;
    }
    if((_estado == ESTADOS_GAME::SCORE) && (_score->volverMenu()) )
    {
        _estado = ESTADOS_GAME::MENU;
        initMenu(_width, _height);
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
                setEstadoMenu(ops);
            }
        break;
        case ESTADOS_GAME::NEWGAME:
            _newGame->update();
            if(_newGame->ingreso)
            {
                handlerState();
            }
        break;
        case ESTADOS_GAME::CONTINUE:
            _runGame->update();
            if(_runGame->exitGame())
            {
                _time++;
                if(_time>=40)
                {
                   handlerState();
                   _time = 0;
                }
            }
        break;
        case ESTADOS_GAME::GAMEPLAY:
            _runGame->update();
            if(_runGame->exitGame())
            {
                 _time++;
                if(_time>=40)
                {
                   handlerState();
                   _time = 0;
                }
            }
        break;
        case ESTADOS_GAME::SCORE:
            _score->update();
            if(_score->volverMenu())
            {
                _time++;
                if(_time >= 60)
                {
                    handlerState();
                    _time=0;
                }
            }
        break;
        case ESTADOS_GAME::CREDITS:
            _credits->update();
            if(_credits->volverMenu())
            {
                _time++;
                if(_time >= 60)
                {
                    handlerState();
                    _time=0;
                }
            }
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
        case ESTADOS_GAME::CONTINUE:
            window.draw(*_runGame);
        break;
        case ESTADOS_GAME::GAMEPLAY:
            window.draw(*_runGame);
        break;
        case ESTADOS_GAME::SCORE:
            window.draw(*_score);
        break;
        case ESTADOS_GAME::CREDITS:
            window.draw(*_credits);
        break;
        case ESTADOS_GAME::QUIT:

        break;
    }
}
