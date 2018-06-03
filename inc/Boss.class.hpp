// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Boss.class.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/03 09:57:30 by mrajaona          #+#    #+#             //
//   Updated: 2018/06/03 09:57:32 by mrajaona         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef BOSS_CLASS_HPP
# define BOSS_CLASS_HPP

# include "Enemy.class.hpp"

class Boss	: virtual public Enemy
{
	private:

	protected:

	public:
					Boss( void );					// Default constructor
					Boss(int posX, int posY);
					Boss(const Boss & origin);		// Copy constructor
		virtual		~Boss( void );					// Default destructor
		Boss &	operator=(Boss const & origin);		// Assignation overload
};

# define BOSS_DEFAULT_APPEARANCE	'W'
# define BOSS_DEFAULT_HP			100
# define BOSS_DEFAULT_SIZE_X		9
# define BOSS_DEFAULT_SIZE_Y		3
# define BOSS_DEFAULT_SCORE			10000

# define BOSS_LINE_1	"\\_\\___/_/"
# define BOSS_LINE_2	" \\XOOOX/ "
# define BOSS_LINE_3	"    V    "

# define BOSS_HIDE		"         "	

#endif /* BOSS_CLASS_HPP */
