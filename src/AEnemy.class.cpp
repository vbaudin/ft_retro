// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AEnemy.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/02 10:33:39 by mrajaona          #+#    #+#             //
//   Updated: 2018/06/02 10:33:40 by mrajaona         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "AEnemy.class.hpp"
#include "error.hpp"

			AEnemy::AEnemy( void ) :
	AEntity(0, 0, 0, 0, 0, ' '),
	IShip(0, 0, 0, 0, 0, ' ')
{
	std::cerr << BAD_CONSTRUCTOR_ERR << "AEnemy" << std::endl;
	return ;
}

			AEnemy::AEnemy(
				int posX, int posY,
				int sizeX, int sizeY,
				size_t hp,
				char appearance
				) :
	AEntity(
		posX, posY,
		sizeX, sizeY,
		hp,
		appearance
		),
	IShip(
		posX, posY,
		sizeX, sizeY,
		hp,
		appearance
		)
{
	return ;
}

			AEnemy::AEnemy(const AEnemy & origin) :
	AEntity(
		origin.getPosX(),
		origin.getPosY(),
		origin.getSizeX(),
		origin.getSizeY(),
		origin.getHP(),
		origin.getAppearance()
		),
	IShip(
		origin.getPosX(),
		origin.getPosY(),
		origin.getSizeX(),
		origin.getSizeY(),
		origin.getHP(),
		origin.getAppearance()
		)
{
	return ;
}

			AEnemy::~AEnemy( void ) {
	return ;
}

AEnemy &	AEnemy::operator=(AEnemy const & origin) {
	IShip::operator=(origin);
	return (*this);
}

