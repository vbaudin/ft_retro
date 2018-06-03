#include "Game.hpp"

		Game::Game(void) :
	_gameOver( false ),
	_maxY( 50 ),
	_maxX( 70 )
{

	for (int i = 0 ; i < MAX_BULLETS_N ; i++) {
		this->_allyBullet[i] = 0;
	}
	for (int i = 0 ; i < MAX_BULLETS_N ; i++) {
		this->_enemyBullet[i] = 0;
	}
	for (int j = 0 ; j < MAX_ENEMIES_N ; j++) {
		this->_enemies[j] = 0;
	}
	this->_boss = 0;

	struct timeval	tv;
	gettimeofday(&tv, 0);
	time( &this->_start );
	srand (time(NULL));
	this->_bossFight = false;
	this->_scoreLastBoss = 0;

	createScene();

	_window	= initscr();

	if (
		COLS > _maxX + 5
		&& LINES > _maxY + 5
		) {
		_sizeOK = true;
	} else {
		_sizeOK = false;
	}

	_game	= subwin(
		stdscr,
		_maxY + 2,
		_maxX + 2,
		(LINES / 2) - (_maxY / 2),
		(COLS / 2) - (_maxX / 2)
		);
	box(_game, ACS_VLINE, ACS_HLINE);

	clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	timeout(10);

	getch();
	clear();

	_player 			= new Player(_maxX / 2, _maxY, 1, 1, 1);
	_timeEnemiesCreated	= 0;
	_timeEnemiesMoved	= ((tv.tv_sec) * 10 + (tv.tv_usec) / 100000);
	_timeEnemiesShooted	= ((tv.tv_sec) * 10 + (tv.tv_usec) / 100000);
	_timeBossShooted	= ((tv.tv_sec) * 10 + (tv.tv_usec) / 100000);
	_timeBossStart 		= 0;
	_enemyHP			= 1;

	std::cerr << this->_player->getLives();

	return;
}

		Game::Game( Game const & rhs ) {
	*this = rhs;
	return;
}

		Game::~Game(void) {
	// stars do not need a delete

	// delete players
	if (_player)
		delete _player;

	// delete remaining bullets
	for (int i = 0; i < MAX_BULLETS_N ; i++) {
		if (this->_allyBullet[i] != 0)
			delete this->_allyBullet[i];
	}

	for (int i = 0; i < MAX_BULLETS_N ; i++) {
		if (this->_enemyBullet[i] != 0)
			delete this->_enemyBullet[i];
	}

	// delete remaining enemies
	for (int j = 0 ; j < MAX_ENEMIES_N ; j++) {
		if (this->_enemies[j] != 0)
			delete this->_enemies[j];
	}

	// delete boss
	if (_boss)
		delete _boss;

	// delete _game
	endwin();

	// delete _window
	endwin();

	return;
}

void	Game::play(void) {
	int ch;

	if (this->_sizeOK == false) {
		clear();
		mvprintw(LINES / 2,
			COLS / 2 - strlen(ERR_WIN_SMALL) / 2,
			ERR_WIN_SMALL);
		while ( 42 ) {
			ch = getch();
			if (ch == 'q') {
				clear();
				return;
			}
		}
	}

	while( !(this->_gameOver) ) {
		box(_game, ACS_VLINE, ACS_HLINE);

		printScene();
		printEntity(_player);
		clockBasedTiming();
		printEnemies();
		printMissiles();

		ch = getch();

		if (ch == ' ') {
				createAllyMissile(this->_player->getPosY(), this->_player->getPosX());
		} else if (ch == KEY_RESIZE) {
			clear();
			mvprintw(LINES / 2,
				COLS / 2 - strlen(ERR_WIN_RESIZED) / 2,
				ERR_WIN_RESIZED);
			while ( 42 ) {
				ch = getch();
				if (ch == 'q') {
					clear();
					return;
				}
			}
		} else if (ch == 'q') {
		  	break ;
		}
		else {
			if (ch == KEY_LEFT && this->_player->getPosX() != 1) {
				hideEntity(this->_player);
				this->_player->move( -1, 0 );
			}
			if (ch == KEY_RIGHT && this->_player->getPosX() < _maxX) {
				hideEntity(this->_player);
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
		isGameOver();
		// Clear la page
		// clear();
		wrefresh(_game);
	}
	clear();
	box(_game, ACS_VLINE, ACS_HLINE);
	mvwprintw(_game, _maxY / 2, _maxX / 2 - strlen(MSG_GAME_OVER) / 2, MSG_GAME_OVER);
	mvwprintw(_game, _maxY / 2 + 1, _maxX / 2 - (strlen(MSG_SCORE) + 9) / 2, MSG_SCORE, this->_player->getScore());
	while ( 42 ) {
		ch = getch();
		if (ch == 'q') {
			endwin();
			return;
		}
	}
}

// ClockTiming

void	Game::clockBasedTiming( void ) {
	int diff;
	time_t End;

	time (& End);
	struct timeval tv;
	gettimeofday(&tv, 0);
	uint64_t time_in_mill = ((tv.tv_sec) * 10 + (tv.tv_usec) / 100000); // convert tv_sec & tv_usec to millisecond

	diff = difftime (End, this->_start);
	if (this->_player->getScore() > SCORE_BOSS_APPEAR + this->_scoreLastBoss)
		this->_bossFight = true;
	if (this->_bossFight == false) {
		if (this->_timeEnemiesCreated == 0 || this->_timeEnemiesCreated + 50 < time_in_mill) {
			this->_timeEnemiesCreated = time_in_mill;
			createEnemies( time_in_mill );
		}
	} else {
		int i	= 0;
		while (i < MAX_ENEMIES_N && this->_enemies[i] == 0) {
			i++;
		}
		if (i == MAX_ENEMIES_N // no enemies
			&& this->_boss == 0) {
			createBoss();
		}
	}

	if (this->_boss == 0) {
		if (this->_timeEnemiesMoved + 5 < time_in_mill) {
			this->_timeEnemiesMoved = time_in_mill;
			moveEnemies();
			makeEnemiesFired();
		}
		if (this->_timeEnemiesShooted + 1 < time_in_mill) {
			this->_timeEnemiesShooted = time_in_mill;
			moveEnemyMissiles( time_in_mill );
		}
	} else {

		if (this->_timeEnemiesMoved + 2 < time_in_mill) {
			this->_timeEnemiesMoved = time_in_mill;
			moveBoss();
		}

		if (this->_timeEnemiesShooted + 1 < time_in_mill) {
			this->_timeEnemiesShooted = time_in_mill;
			moveEnemyMissiles( time_in_mill );
		}

		if (this->_timeBossShooted + 5 < time_in_mill) {
			this->_timeBossShooted = time_in_mill;
			bossShoot(this->_boss);
		}

		if (this->_timeBossStart + BOSS_TIME < time_in_mill) {
			this->_timeBossStart = 0;
			this->_gameOver = 1;
		}

	}

	moveAllyMissiles( time_in_mill );

	mvwprintw(_game, 1, 1, "  HP  : %d", this->_player->getHP());
	mvwprintw(_game, 2, 1, "Score : %d", this->_player->getScore());
	mvwprintw(_game, 1, _maxX / 2 - (strlen(MSG_TIME) + 4) / 2, MSG_TIME, diff);

	if (this->_boss != 0) {
		mvwprintw(_game, 1, this->_maxX - 1 - 10 , "BOSS HP:%4d", this->_boss->getHP());
		mvwprintw(_game, 2, this->_maxX - 1 - 10 , "TIMER  :%4d",
			(this->_timeBossStart + BOSS_TIME - time_in_mill) / 10
			);
	}
}

void Game::isGameOver(void) {
	if (this->_player->getHP() < 1)
		this->_gameOver = 1;
}

// Create Entities

void	Game::createEnemies( uint64_t num ) {
	(void)num;
	int i = 0;
	int j = 0;
	int x = 0;

	char	tab[] = {'V', 'W', 'U', 'Y'};
	char	appear = tab[rand() % 4];

	while (x < 2 || x > 60) {
		x = rand() % (_maxX);
	}
	// mvwprintw(_game, 2, 20, " Rand : %d", x);

	while (i < 5 && j < MAX_ENEMIES_N) {
		if (this->_enemies[j] == 0) {
			this->_enemies[j] = new Minion(x + (i * 2), 5, appear);
			this->_enemies[j]->setHP(this->_enemyHP);
			i++;
		}
		j++;
	}

	while (i < 9 && j < MAX_ENEMIES_N)
	{
		if (this->_enemies[j] == 0) {
			this->_enemies[j] = new Minion(x + (i % 5 * 2) + 1, 4, appear);
			this->_enemies[j]->setHP(this->_enemyHP);
			i++;
		}
		j++;
	}

	i = 0;
	while (i < 5 && j < MAX_ENEMIES_N) {
		if (this->_enemies[j] == 0) {
			this->_enemies[j] = new Minion(x + (i * 2), 3, appear);
			this->_enemies[j]->setHP(this->_enemyHP);
			i++;
		}
		j++;
	}
}

void	Game::createBoss( void ) {
	this->_boss = new Boss(2, 3);
	this->_boss->setPosX((this->_maxX / 2) - (this->_boss->getSizeX() / 2));

	if (this->_enemyHP < ENEMY_MAX_HP)
		this->_boss->setHP(this->_boss->getHP() * this->_enemyHP);
	else
		this->_boss->setHP(BOSS_MAX_HP);

	struct timeval tv;
	gettimeofday(&tv, 0);
	this->_timeBossStart = ((tv.tv_sec) * 10 + (tv.tv_usec) / 100000); // convert tv_sec & tv_usec to millisecond

}

// shoot

void	Game::enemyShoot(Enemy * inst) {
	if (!inst)
		return ;
	if (enemyIsPossibleToShoot(inst->getPosY() + 1, inst->getPosX()))
	createEnemyMissile(inst->getPosY() + 1, inst->getPosX());
}

void	Game::bossShoot(Boss * inst) {
	if (!inst)
		return ;
	if (enemyIsPossibleToShoot(
			this->_boss->getPosY() + this->_boss->getSizeY(),
			this->_boss->getPosX() + this->_boss->getSizeX() - 2 - 1))
		createEnemyMissile(
			this->_boss->getPosY() + this->_boss->getSizeY(),
			this->_boss->getPosX() + this->_boss->getSizeX() - 2 - 1);
	if (enemyIsPossibleToShoot(
			this->_boss->getPosY() + this->_boss->getSizeY(),
			this->_boss->getPosX() + 2))
		createEnemyMissile(
			this->_boss->getPosY() + this->_boss->getSizeY(),
			this->_boss->getPosX() + 2);
}

bool	Game::isPossibleToShoot(int y, int x) {

	int i = 0;

	while (i < 10) {
		if (this->_allyBullet[i] != 0) {
			if (this->_allyBullet[i]->getPosX() == x
				&& this->_allyBullet[i]->getPosY() == y)
			return (0);
		}
		i++;
	}
	return (1);
}

bool	Game::enemyIsPossibleToShoot(int y, int x) {

	int i = 0;

	while (i < 10) {
		if (this->_enemyBullet[i] != 0) {
			if (this->_enemyBullet[i]->getPosX() == x
				&& this->_enemyBullet[i]->getPosY() == y)
			return (0);
		}
		i++;
	}
	return (1);
}


void	Game::createAllyMissile( int y, int x ) {

	int i = 0;

	if (isPossibleToShoot(y, x)) {
		while ( this->_allyBullet[i]) {
			i++;
		}
		if ( i < (MAX_BULLETS_N - 1))
		this->_allyBullet[i] = new Bullet(
							_player->getPosX(),
							_player->getPosY() - 1,
							1, 1,
							0, -1,
							_player->getId()
						);
	}
}

void	Game::createEnemyMissile( int y, int x ) {

	int i = 0;

	if (isPossibleToShoot(y, x)) {
		while ( this->_enemyBullet[i]) {
			i++;
		}
		if ( i < (MAX_BULLETS_N - 1))
		this->_enemyBullet[i] = new Bullet(
							x, y,
							1, 1,
							0, 1
						);
	}
}

void  Game::makeEnemiesFired( void ) {
	int test;
	for (int i = 0; i < MAX_ENEMIES_N; i++) {

	test = rand() % 40;

	if (test == 0 && this->_enemies[i] != 0)
		enemyShoot(this->_enemies[i]);
	}
}


// Move Entities

void	Game::moveAllyMissiles( uint64_t num ) {

	int i = 0;

	Bullet::setSecs( num );
	while (i < MAX_BULLETS_N) {
		if (this->_allyBullet[i] != 0) {
			hideEntity(this->_allyBullet[i]);
			this->_allyBullet[i]->move();
		}
		i++;
	}
}

void	Game::moveEnemyMissiles( uint64_t num ) {

	int i = 0;

	Bullet::setSecs( num );
	while (i < MAX_BULLETS_N) {
		if (this->_enemyBullet[i] != 0) {
			hideEntity(this->_enemyBullet[i]);
			this->_enemyBullet[i]->move();
		}
		i++;
	}
}

void	Game::moveEnemies( void ) {

	int i = 0;

	while (i < MAX_ENEMIES_N) {

		if (this->_enemies[i] != 0) {
			hideEntity(this->_enemies[i]);
			this->_enemies[i]->move(0, 1);
		}
		i++;
	}
}

void	Game::moveBoss( void ) {
	static int	direction = 1;

	// Boss moving pattern
	hideBoss(this->_boss);
	if (this->_boss->getPosY() < 10)
		this->_boss->move(0, 1);
	else {
		if (
			(direction == -1 && this->_boss->getPosX() == 1)
			||
			(direction == 1 && this->_boss->getPosX() == this->_maxX - this->_boss->getSizeX() + 1)
			)
		{
				direction *= -1;
		}
		this->_boss->move(direction, 0);
	}
}

// Check collisions

void	Game::checkOutsideMap(void) {

	int i = 0;

	while (i < MAX_ENEMIES_N) {
		if (this->_enemies[i] != 0) {
			if (this->_enemies[i]->getPosY() > this->_maxY - 1) {
				this->_enemies[i]->onCollision();
				this->_player->takeDamage();
			}
		}
		i++;
	}

	i = 0;

	while (i < MAX_BULLETS_N) {

		if (this->_allyBullet[i] != 0) {
			if (this->_allyBullet[i]->getPosY() < 4) {
				hideEntity(this->_allyBullet[i]);
				this->_allyBullet[i]->onCollision();
			}
		}

		if (this->_enemyBullet[i] != 0) {
			if (this->_enemyBullet[i]->getPosY() > this->_maxY - 1) {
				hideEntity(this->_enemyBullet[i]);
				this->_enemyBullet[i]->onCollision();
			}
		}

		i++;
	}

}

void	Game::checkCollisions(void) {

	int i = 0;
	int j = 0;
	int k = 0;

	while (i < MAX_ENEMIES_N) {
		if (this->_enemies[i] != 0) {
			j = 0;
			while (j < MAX_BULLETS_N) {

				if (this->_allyBullet[j] != 0) {
					if (
					this->_enemies[i]->getPosX() == this->_allyBullet[j]->getPosX()
					&& this->_enemies[i]->getPosY() == this->_allyBullet[j]->getPosY()
					) {
						this->_enemies[i]->takeDamage();
						this->_allyBullet[j]->takeDamage();

						if (this->_enemies[i]->getHP() == 0)
							this->_player->editScore(this->_enemies[i]->getScore());
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

	j = 0;
	while (j < MAX_BULLETS_N) {
		if (this->_allyBullet[j] != 0) {
			k = 0;
			while (k < MAX_BULLETS_N) {
				if (
					this->_enemyBullet[k] != 0
					&& this->_enemyBullet[k]->getPosX() == this->_allyBullet[j]->getPosX()
					&& this->_enemyBullet[k]->getPosY() == this->_allyBullet[j]->getPosY()
				) {
					this->_enemyBullet[k]->takeDamage();
					this->_allyBullet[j]->takeDamage();
				}
				k++;
			}
		}

		if (this->_enemyBullet[j] != 0) {
			k = 0;
			if (this->_player->getPosX() == this->_enemyBullet[j]->getPosX()
			&& this->_player->getPosY() == this->_enemyBullet[j]->getPosY()
			) {
				this->_player->takeDamage();
				this->_enemyBullet[j]->takeDamage();
			}

			while (k < MAX_ENEMIES_N) {
				if (
					this->_enemies[k] != 0
				&&	this->_enemies[k]->getPosX() == this->_enemyBullet[j]->getPosX()
				&&	this->_enemies[k]->getPosY() == this->_enemyBullet[j]->getPosY()
				) {
					this->_enemies[k]->takeDamage();
					this->_enemyBullet[j]->takeDamage();
				}
				k++;
			}

		}

		j++;
	}

	if (this->_boss != 0) {
		j = 0;
		while (j < MAX_BULLETS_N) {
			if (this->_allyBullet[j] != 0) {
				if (

					// check bullet X
					(
							this->_allyBullet[j]->getPosX() >=	this->_boss->getPosX()
						&&	this->_allyBullet[j]->getPosX() <	(this->_boss->getPosX() + this->_boss->getSizeX())
					)

					&&
					// check bullet Y
					(
							this->_allyBullet[j]->getPosY() >=	this->_boss->getPosY()
						&&	this->_allyBullet[j]->getPosY() <	(this->_boss->getPosY() + this->_boss->getSizeY())
					)
					/*
					this->_boss->getPosX() == this->_allyBullet[j]->getPosX()
					&& this->_boss->getPosY() == this->_allyBullet[j]->getPosY()
					*/
					)
				{
					this->_boss->takeDamage();
					this->_allyBullet[j]->takeDamage();

					if (this->_boss->getHP() == 0)
						this->_player->editScore(this->_boss->getScore());
				}
			}
			j++;
		}
	}

}

// Delete Entities

void	Game::killMissiles(void) {

	int i = 0;

	while (i < MAX_BULLETS_N) {

		if (this->_allyBullet[i] != 0) {
			if (this->_allyBullet[i]->getHP() <= 0) {
				hideEntity(this->_allyBullet[i]);
				delete this->_allyBullet[i];
				this->_allyBullet[i] = 0;
			}
		}

		if (this->_enemyBullet[i] != 0) {
			if (this->_enemyBullet[i]->getHP() <= 0) {
				hideEntity(this->_enemyBullet[i]);
				delete this->_enemyBullet[i];
				this->_enemyBullet[i] = 0;
			}
		}

		i++;
	}
}

void	Game::killEnemies(void) {

	int i = 0;

	while (i < MAX_ENEMIES_N) {
		if (this->_enemies[i] != 0) {
			if (this->_enemies[i]->getHP() <= 0) {
				hideEntity(this->_enemies[i]);
				delete this->_enemies[i];
				this->_enemies[i] = 0;
			}
		}
		i++;
	}

	if (this->_boss != 0 && this->_boss->getHP() == 0) {
		killBoss();
	}

}

void	Game::killBoss(void) {
	if (this->_boss == 0
		|| this->_boss->getHP() > 0)
		return ;
	hideBoss(this->_boss);
	mvwprintw(_game, 1, this->_maxX - 1 - 10 , "            ");
	mvwprintw(_game, 2, this->_maxX - 1 - 10 , "            ");
	delete this->_boss;
	this->_bossFight = false;
	this->_scoreLastBoss = this->_player->getScore();
	this->_boss = 0;
	if (this->_enemyHP < ENEMY_MAX_HP)
		this->_enemyHP++;
	this->_timeBossStart = 0;
}

// Print game screen

void	Game::createScene( void ) {

	int i = 0;
	int x = 0;
	int y = 0;
	while ( i < MAX_STARS_N ) {
		x = rand() % _maxX;
		y = rand() % _maxY;
		if (y > 2 && x > 1 && x < 68 && y < 48) {
			_stars[i] = Star( x, y );
			i++;
		}
	}
}

void	Game::printScene( void ) {

	int i = 0;

	while ( i < MAX_STARS_N ) {
		mvwaddch(_game, this->_stars[i].getY(), this->_stars[i].getX(), '.');
		i++;
	}
}

void	Game::printEnemies( void ) {
	for (int i = 0; i < MAX_ENEMIES_N; i++) {
		if (this->_enemies[i] != 0) {
			printEntity(this->_enemies[i]);
		}
	}

	if (this->_boss != 0)
			printBoss(this->_boss);
}

void	Game::printMissiles( void ) {
	for (int i = 0; i < MAX_BULLETS_N; i++) {
		if (this->_allyBullet[i] != 0) {
			printEntity(this->_allyBullet[i]);
		}
		if (this->_enemyBullet[i] != 0) {
			printEntity(this->_enemyBullet[i]);
		}
	}
}

void 	Game::printEntity(AEntity * inst) {
	if (inst)
		mvwaddch(_game, inst->getPosY(), inst->getPosX(), inst->getAppearance());
}

void 	Game::printBoss(Boss * inst) {
	if (inst) {
		mvwprintw(_game, inst->getPosY(), inst->getPosX(), BOSS_LINE_1);
		mvwprintw(_game, inst->getPosY() + 1, inst->getPosX(), BOSS_LINE_2);
		mvwprintw(_game, inst->getPosY() + 2, inst->getPosX(), BOSS_LINE_3);
	}
}

void 	Game::hideEntity(AEntity * inst) {
	if (inst)
		mvwaddch(_game, inst->getPosY(), inst->getPosX(), ' ');
}

void 	Game::hideBoss(Boss * inst) {
	if (inst) {
		mvwprintw(_game, inst->getPosY(), inst->getPosX(), BOSS_HIDE);
		mvwprintw(_game, inst->getPosY() + 1, inst->getPosX(), BOSS_HIDE);
		mvwprintw(_game, inst->getPosY() + 2, inst->getPosX(), BOSS_HIDE);
	}
}
