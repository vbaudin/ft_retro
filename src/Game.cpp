 #include "Game.hpp"

Game::Game(void) : _gameOver( false ), _maxY( 50 ), _maxX( 70 ), _map( Map() ) {

	for (int i = 0; i < 10; i++) {
			this->_bullet[i] = 0;
		}
	for (int j = 0; j < 20; j++) {
			this->_enemies[j] = 0;
		}
	struct timeval tv;
	gettimeofday(&tv, 0);
	srand (time(NULL));

	createScene();

  initscr();


  _game = subwin(stdscr, _maxY + 2, _maxX + 2, (LINES / 2) - (_maxY / 2), (COLS / 2) - (_maxX / 2));
  box(_game, ACS_VLINE, ACS_HLINE);
  // mvwprintw(_game, 0 + 1, 0 + 1, "Ceci est la fenetre de jeu");

  clear();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(10);

  getch();
  endwin();
	clear();

	_player = new Player(_maxX / 2, _maxY, 1, 1, 1);
	_timeEnemiesCreated = 0;
	_timeEnemiesMoved = ((tv.tv_sec) * 10 + (tv.tv_usec) / 100000);


	return;
}

Game::Game( Game const & rhs ) {

	*this = rhs;
	return;
}

Game::~Game(void) {
	if (_player)
		delete _player;
	return;
}

void Game::play(void) {
	int ch;

	while( !(this->_gameOver) ) {
		box(_game, ACS_VLINE, ACS_HLINE);

		printScene();
		printEntity(_player);
		printEnemies();
		clockBasedTiming();

		ch = getch();

		if (ch == ' ') {
				createAllyMissile(this->_player->getPosY(), this->_player->getPosX());
		} else if (ch == KEY_RESIZE) {
			clear();
			mvprintw(LINES / 2, COLS / 2 - strlen("WINDOW RESIZE DETECTED, PLEASE QUIT THE GAME (PRESS 'q')") / 2, "WINDOW RESIZE DETECTED, PLEASE QUIT THE GAME (PRESS 'q')");
			while ( 42 ) {
				ch = getch();
				if (ch == 'q') {
					clear();
					endwin();
					return;
				}
			}
		} else if (ch == 'q') {
		  	break ;
		}
		else {
			if (ch == KEY_LEFT && this->_player->getPosX() != 1) {
				mvwaddch(_game, this->_player->getPosY(), this->_player->getPosX(), ' ');
				this->_player->move( -1, 0 );
			}
			if (ch == KEY_RIGHT && this->_player->getPosX() < _maxX) {
				mvwaddch(_game, this->_player->getPosY(), this->_player->getPosX(), ' ');
				this->_player->move( 1, 0 );
			}
		}
		// Verifier les vivants et morts
		checkOutsideMap();
		checkCollisions();
		// Tuer les morts
		killEnemies();
		killMissiles();
		// declarer ou non le gameOver set gameOver a 1
		// isGameOver();
		// Clear la page
		// clear();
		wrefresh(_game);
	}
	clear();
	// mvprintw(LINES / 2, COLS / 2 - strlen("Game Over. Thanks for playing (PRESS 'q')") / 2, "Game Over. Thanks for playing (PRESS 'q')");
	// while ( 42 ) {
	// 	ch = getch();
	// 	if (ch == 'q') {
	// 		endwin();
	// 		return;
	// 	}
}

void  Game::killMissiles(void) {

	int i = 0;

	while (i < 20) {
		if (this->_bullet[i] != 0) {
			if (this->_bullet[i]->getHP() <= 0){
				hideEntity(this->_bullet[i]);
				delete this->_bullet[i];
				this->_bullet[i] = 0;
			}
		}
		i++;
	}
}

void  Game::killEnemies(void) {

	int i = 0;

	while (i < 20) {
		if (this->_enemies[i] != 0) {
			if (this->_enemies[i]->getHP() <= 0){
				hideEntity(this->_enemies[i]);
				delete this->_enemies[i];
				this->_enemies[i] = 0;
			}
		}
		i++;
	}
}

void  Game::checkOutsideMap(void) {

	int i = 0;

	while (i < 20) {
		if (this->_enemies[i] != 0) {
			if (this->_enemies[i]->getPosY() > this->_maxY - 1)
			this->_enemies[i]->onCollision();
		}
		i++;
	}
	i = 0;
	while (i < 20) {
		if (this->_bullet[i] != 0) {
			if (this->_bullet[i]->getPosY() < 3) {
				mvwaddch(_game, this->_bullet[i]->getPosY(), this->_bullet[i]->getPosX(), ' ');
				this->_bullet[i]->onCollision();
			}
		}
		i++;
	}
}

void Game::clockBasedTiming( void ) {

	int diff;
	time_t End;

	time (& End);
	struct timeval tv;
	gettimeofday(&tv, 0);
	uint64_t time_in_mill = ((tv.tv_sec) * 10 + (tv.tv_usec) / 100000); // convert tv_sec & tv_usec to millisecond
	diff = difftime (End, this->_start);
	if (this->_timeEnemiesCreated == 0 || this->_timeEnemiesCreated + 100 < time_in_mill) {
		this->_timeEnemiesCreated = time_in_mill;
		createEnemies( time_in_mill );
	}
	if (this->_timeEnemiesMoved + 5 < time_in_mill) {
		this->_timeEnemiesMoved = time_in_mill;
		moveEnemies();
	}
	moveMissiles( time_in_mill );
	mvprintw(0, 0, /*"duration : %''4d secs   */"lives : %d", diff, this->_player->getLives());
}

bool  Game::isPossibleToShoot(int y, int x) {

	int i = 0;

	while (i < 20) {
		if (this->_bullet[i] != 0) {
			if (this->_bullet[i]->getPosX() == x && this->_bullet[i]->getPosY() == y)
			return (0);
		}
		i++;
	}
	return (1);
}

void  Game::createEnemies( uint64_t num ) {
	(void)num;
	int i = 0;
	int j = 0;
	int x = 0;

	while (x < 2 || x > 40) {
		x = rand() % (_maxX);
	}

	while (i < 5 && j < 20) {
		if (this->_enemies[j] == 0) {
			this->_enemies[j] = new Minion(x + (i * 2), 3);
			i++;
		}
		j++;
	}
}

void  Game::createAllyMissile( int y, int x ) {

	int i = 0;

	if (isPossibleToShoot(y, x)) {
		while ( this->_bullet[i]) {
			i++;
		}
		if ( i < 19)
		this->_bullet[i] = new Bullet(_player->getPosX(),
							_player->getPosY() - 1,
							1, 1,
							0, -1,
							_player->getId()
						);

	}
}

void Game::moveMissiles( uint64_t num ) {

	int i = 0;

	Bullet::setSecs( num );
	while (i < 20) {

		if (this->_bullet[i] != 0) {
			mvwaddch(_game, this->_bullet[i]->getPosY(), this->_bullet[i]->getPosX(), ' ');
			this->_bullet[i]->move();
			mvwaddch(_game, this->_bullet[i]->getPosY(), this->_bullet[i]->getPosX(), '|');
		}
		i++;
	}
}

void Game::moveEnemies( void ) {

	int i = 0;

	while (i < 20) {

		if (this->_enemies[i] != 0) {
			mvwaddch(_game, this->_enemies[i]->getPosY(), this->_enemies[i]->getPosX(), ' ');
			this->_enemies[i]->move(0, 1);
		}
		i++;
	}
}

void  Game::createScene( void ) {

	int i = 0;
	int x = 0;
	int y = 0;
	while ( i < 30 ) {
		x = rand() % _maxX;
		y = rand() % _maxY;
		if (y > 2 && x > 0 && x < 69 && y < 49) {
			_stars[i] = Star( x, y );
			i++;
		}
	}
}

void  Game::printScene( void ) {

	int i = 0;

	while ( i < 30 ) {
		mvwaddch(_game, this->_stars[i].getY(), this->_stars[i].getX(), '.');
		i++;
	}
}

void  Game::printEnemies( void ) {
	for (int i = 0; i < 20; i++) {
		if (this->_enemies[i] != 0) {
			printEntity(this->_enemies[i]);
		}
	}
}

void 	Game::printEntity(AEntity * inst) {
	// std::cout << this->_player->getPosY() << " " << _player->getPosX() << std::endl;
	//std::cout << inst->getPosY() << " " << inst->getPosX() << " " << inst->getAppearance() << std::endl;
	mvwaddch(_game, inst->getPosY(), inst->getPosX(), inst->getAppearance());
}

void 	Game::hideEntity(AEntity * inst) {
	// std::cout << this->_player->getPosY() << " " << _player->getPosX() << std::endl;
	//std::cout << inst->getPosY() << " " << inst->getPosX() << " " << inst->getAppearance() << std::endl;
	mvwaddch(_game, inst->getPosY(), inst->getPosX(), ' ');
}

void  Game::checkCollisions(void) {

	int i = 0;
	int j = 0;

	while (i < 20) {
		if (this->_enemies[i] != 0) {
			j = 0;
			while (j < 20) {
				if (this->_bullet[j] != 0) {
					if (this->_enemies[i]->getPosX() == this->_bullet[j]->getPosX()
					&& this->_enemies[i]->getPosY() == this->_bullet[j]->getPosY()) {
						this->_enemies[i]->takeDamage();
						this->_bullet[j]->takeDamage();
					}
				}
				j++;
			}
			if (this->_enemies[i]->getPosX() == this->_player->getPosX()
			&& this->_enemies[i]->getPosY() == this->_player->getPosY()) {
				this->_enemies[i]->takeDamage();
				this->_player->takeDamage();
			}
		}
		i++;
	}
}
