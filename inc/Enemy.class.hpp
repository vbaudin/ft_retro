// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Enemy.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/02 10:32:38 by mrajaona          #+#    #+#             //
//   Updated: 2018/06/02 10:32:45 by mrajaona         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ENEMY_CLASS_HPP
# define ENEMY_CLASS_HPP

# include "AEntity.class.hpp"

class Enemy	: virtual public AEntity
{
	private:
		int			_score;

					Enemy( void );						// Default constructor

	protected:

	public:
					Enemy(
						int posX, int posY,
						int sizeX, int sizeY,
						size_t hp,
						char appeance,
						int score
						);
					Enemy(const Enemy & origin);		// Copy constructor
		virtual		~Enemy( void );					// Default destructor
		Enemy &	operator=(Enemy const & origin);	// Assignation overload

		// getter
		int const &	getScore( void ) const;

		// setter
		void		setScore(int value);

};

# define ENEMY_DEFAULT_APPEARANCE	'V'
# define ENEMY_DEFAULT_SCORE		100

#endif /* ENEMY_CLASS_HPP */
