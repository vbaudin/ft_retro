#ifndef GAME_HPP
# define GAME_HPP

# include <string>
# include <iostream>
# include <sstream>
# include <sys/time.h>
# include <ncurses.h>

# include "Star.class.hpp"

# include "AEntity.class.hpp"
# include "Bullet.class.hpp"
# include "Enemy.class.hpp"
# include "Minion.class.hpp"
# include "Player.class.hpp"
# include "Boss.class.hpp"

# include "error.hpp"

# define MAX_STARS_N	50
# define MAX_PLAYERS_N	1
# define MAX_ENEMIES_N	100
# define MAX_BULLETS_N	20

class Game {

	public:

				Game( void ); // Canonical
				Game( Game const & rhs ); // Canonical
				~Game( void ); // Canonical VIRTUAL ???
    	void	play( void );


	private:

		bool		_sizeOK;

		WINDOW *	_window;
		WINDOW *	_game;
		bool		_gameOver;

		int			_maxY;
		int			_maxX;

		time_t		_start;
		uint64_t	_timeEnemiesCreated;
		uint64_t	_timeEnemiesMoved;
		uint64_t	_timeEnemiesShooted;
		uint64_t	_timeBossShooted;
		uint64_t	_timeBossStart;
		bool		_bossFight;
		size_t		_scoreLastBoss;

		size_t		_enemyHP;

		Star		_stars[MAX_STARS_N];
		Player *	_player;
		Enemy *		_enemies[MAX_ENEMIES_N];
		Bullet *	_allyBullet[MAX_BULLETS_N];
		Bullet *	_enemyBullet[MAX_BULLETS_N];
		Boss *		_boss;

		void 	isGameOver( void );

		void	createEnemies( uint64_t num );
		void	createBoss( void );

		void	makeEnemiesFired( void );

		void	enemyShoot(Enemy * inst);
		void	bossShoot(Boss * inst);

		bool	isPossibleToShoot(int y, int x);
		bool	enemyIsPossibleToShoot(int y, int x);
		void	createAllyMissile( int y, int x );
		void	createEnemyMissile( int y, int x );

		void	clockBasedTiming( void );
		void	moveAllyMissiles( uint64_t num );
		void	moveEnemyMissiles( uint64_t num );
		void	moveEnemies( void );
		void	moveBoss( void );

		void	checkOutsideMap(void);
		void	checkCollisions(void);

		void	killMissiles(void);
		void	killEnemies(void);
		void	killBoss(void);

		void	createScene( void );
		void	printScene( void );
		void	printEntity(AEntity * inst);
		void	printBoss(Boss * inst);
		void	hideEntity(AEntity * inst);
		void	hideBoss(Boss * inst);
		void	printEnemies( void );
		void	printMissiles( void );
		void	hideEnemies( void );

};

# define MSG_GAME_OVER		"Game Over. Thanks for playing (PRESS 'q')"
# define MSG_SCORE			"Your Score : %9zu"
# define MSG_TIME			"Time: %''4d secs"
# define SCORE_BOSS_APPEAR	1500
# define ENEMY_MAX_HP		100
# define BOSS_MAX_HP		9999
# define BOSS_TIME			30 * 10

#endif
