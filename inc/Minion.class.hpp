// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Minion.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/02 13:15:12 by mrajaona          #+#    #+#             //
//   Updated: 2018/06/02 13:15:13 by mrajaona         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MINION_CLASS_HPP
# define MINION_CLASS_HPP

# include "Enemy.class.hpp"

class Minion	: virtual public Enemy
{
	private:

	protected:

	public:
					Minion( void );						// Default constructor
					Minion(int posX, int posY);
					Minion(int posX, int posY, char appearance);
					Minion(const Minion & origin);		// Copy constructor
		virtual		~Minion( void );					// Default destructor
		Minion &	operator=(Minion const & origin);	// Assignation overload
};

# define MINION_DEFAULT_APPEARANCE	'V'
# define MINION_DEFAULT_HP			1
# define MINION_DEFAULT_SIZE_X		1
# define MINION_DEFAULT_SIZE_Y		1
# define MINION_DEFAULT_SCORE		100

#endif /* MINION_CLASS_HPP */
