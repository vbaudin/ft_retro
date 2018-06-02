#ifndef GAME_HPP
# define GAME_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <sys/time.h>

#include "Map.hpp"
#include "Star.class.hpp"
#include "Player.class.hpp"
#include "Bullet.class.hpp"
#include "Minion.class.hpp"

#include "AEntity.class.hpp"
#include "AEnemy.class.hpp"

class Game {

	public:

		Game( void ); // Canonical
		Game( Game const & rhs ); // Canonical
		~Game( void ); // Canonical VIRTUAL ???
    void play( void );


	private:

		  WINDOW *_game;
      bool                _gameOver;
      int        _maxY;
  	  int        _maxX;

			void	createScene( void );
			void	printScene( void );
			void	printEntity(AEntity * inst);
			void	hideEntity(AEntity * inst);
			void  printEnemies( void );
			void  hideEnemies( void );

			bool  isPossibleToShoot(int y, int x);
			void  createAllyMissile( int y, int x );
			void  createEnemies( uint64_t num );

			void clockBasedTiming( void );
			void moveMissiles( uint64_t num );
			void moveEnemies( void );
			void checkCollisions(void);
			void killMissiles(void);
			void killEnemies(void);
			void checkOutsideMap(void);

			time_t _start;
			uint64_t _timeEnemiesCreated;
			uint64_t _timeEnemiesMoved;
			Map _map;
			Star	_stars[31];
			Player *_player;
			AEnemy *_enemies[20];
			Bullet *_bullet[10];
};


#endif
