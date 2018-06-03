// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Boss.class.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/03 09:57:21 by mrajaona          #+#    #+#             //
//   Updated: 2018/06/03 09:57:23 by mrajaona         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Boss.class.hpp"
#include "error.hpp"

					Boss::Boss( void ) :
	AEntity(
		0, 0,
		BOSS_DEFAULT_SIZE_X, BOSS_DEFAULT_SIZE_Y,
		BOSS_DEFAULT_HP,
		BOSS_DEFAULT_APPEARANCE
		),
	Enemy(
		0, 0,
		BOSS_DEFAULT_SIZE_X, BOSS_DEFAULT_SIZE_Y,
		BOSS_DEFAULT_HP,
		BOSS_DEFAULT_APPEARANCE,
		BOSS_DEFAULT_SCORE
		)
{
	// FOR HORDE CREATION
	// std::cerr << BAD_CONSTRUCTOR_ERR << "Boss" << std::endl;
	return ;
}

					Boss::Boss(int posX, int posY) :
	AEntity(
		posX, posY,
		BOSS_DEFAULT_SIZE_X, BOSS_DEFAULT_SIZE_Y,
		BOSS_DEFAULT_HP,
		BOSS_DEFAULT_APPEARANCE
		),
	Enemy(
		posX, posY,
		BOSS_DEFAULT_SIZE_X, BOSS_DEFAULT_SIZE_Y,
		BOSS_DEFAULT_HP,
		BOSS_DEFAULT_APPEARANCE,
		BOSS_DEFAULT_SCORE
		)
{
	return ;
}

					Boss::Boss(const Boss & origin) :
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

					Boss::~Boss( void ) {
						return ;
}	
									// Default destructor
Boss &				Boss::operator=(Boss const & origin) {
	Enemy::operator=(origin);
	return (*this);
}	
