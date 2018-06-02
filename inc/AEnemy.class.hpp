// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AEnemy.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/02 10:32:38 by mrajaona          #+#    #+#             //
//   Updated: 2018/06/02 10:32:45 by mrajaona         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AENEMY_CLASS_HPP
# define AENEMY_CLASS_HPP

# include "IShip.class.hpp"

class AEnemy	: virtual public IShip
{
	private:

					AEnemy( void );						// Default constructor

	protected:

	public:
					AEnemy(
						int posX, int posY,
						int sizeX, int sizeY,
						size_t hp,
						char appeance
						);
					AEnemy(const AEnemy & origin);		// Copy constructor
		virtual		~AEnemy( void );					// Default destructor
		AEnemy &	operator=(AEnemy const & origin);	// Assignation overload
};

# define ENEMY_DEFAULT_APPEARANCE 'V'

#endif /* AENEMY_CLASS_HPP */
