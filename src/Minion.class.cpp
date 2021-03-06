// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Minion.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/02 13:15:20 by mrajaona          #+#    #+#             //
//   Updated: 2018/06/02 13:15:22 by mrajaona         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Minion.class.hpp"
#include "error.hpp"

					Minion::Minion( void ) :
	AEntity(
		0, 0,
		MINION_DEFAULT_SIZE_X, MINION_DEFAULT_SIZE_Y,
		MINION_DEFAULT_HP,
		MINION_DEFAULT_APPEARANCE
		),
	Enemy(
		0, 0,
		MINION_DEFAULT_SIZE_X, MINION_DEFAULT_SIZE_Y,
		MINION_DEFAULT_HP,
		MINION_DEFAULT_APPEARANCE,
		MINION_DEFAULT_SCORE
		)
{
	// FOR HORDE CREATION
	// std::cerr << BAD_CONSTRUCTOR_ERR << "Minion" << std::endl;
	return ;
}

					Minion::Minion(int posX, int posY, char appearance) :
	AEntity(
		posX, posY,
		MINION_DEFAULT_SIZE_X, MINION_DEFAULT_SIZE_Y,
		MINION_DEFAULT_HP,
		appearance
		),
	Enemy(
		posX, posY,
		MINION_DEFAULT_SIZE_X, MINION_DEFAULT_SIZE_Y,
		MINION_DEFAULT_HP,
		appearance,
		MINION_DEFAULT_SCORE
		)
{
	return ;
}

					Minion::Minion(const Minion & origin) :
	AEntity(
		origin.getPosX(),
		origin.getPosY(),
		origin.getSizeX(),
		origin.getSizeY(),
		origin.getHP(),
		origin.getAppearance()
		),
	Enemy(
		origin.getPosX(),
		origin.getPosY(),
		origin.getSizeX(),
		origin.getSizeY(),
		origin.getHP(),
		origin.getAppearance(),
		origin.getScore()
		)
{
	return ;
}	

					Minion::~Minion( void ) {
						return ;
}	
									// Default destructor
		Minion &	Minion::operator=(Minion const & origin) {
	Enemy::operator=(origin);
	return (*this);
}	
