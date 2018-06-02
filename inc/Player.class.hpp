// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/02 10:33:15 by mrajaona          #+#    #+#             //
//   Updated: 2018/06/02 10:33:15 by mrajaona         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PLAYER_CLASS_HPP
# define PLAYER_CLASS_HPP

# include "IShip.class.hpp"

class Player	: virtual public IShip
{
	private:
		size_t		_score;
		size_t		_lives;
		int			_id;

					Player( void );						// Default constructor

	protected:

	public:
					// Default appearance
					Player(
						int posX, int posY,
						int sizeX, int sizeY,
						int id
						);
					// Custom appearance
					Player(
						int posX, int posY,
						int sizeX, int sizeY,
						int id,
						char appearance
						);
					Player(const Player & origin);		// Copy constructor
		virtual		~Player( void );					// Default destructor
		Player &	operator=(Player const & origin);	// Assignation overload

		// getter
		size_t const &	getScore( void ) const;
		size_t const &	getLives( void ) const;
		int const &		getId( void ) const;

		// setter
		void			setScore(size_t value);
		void			setLives(size_t value);
		void			setId(int value);
};

# define PLAYER_DEFAULT_LIVES		4
# define PLAYER_DEFAULT_APPEARANCE 'A'
# define PLAYER_DEFAULT_HP			1

#endif /* PLAYER_CLASS_HPP */
