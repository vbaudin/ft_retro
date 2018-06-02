/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IShip.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <mrajaona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 10:33:46 by mrajaona          #+#    #+#             */
/*   Updated: 2018/06/02 14:39:01 by vbaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "IShip.class.hpp"
#include "error.hpp"

			IShip::IShip( void ) :
	AEntity(0, 0, 0, 0, 0, ' ')
{
	std::cerr << BAD_CONSTRUCTOR_ERR << "IShip" << std::endl;
	return ;
}

			IShip::IShip(
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
		)
{
	return ;
}

			IShip::IShip(const IShip & origin) :
	AEntity(
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

			IShip::~IShip( void ) {
	return ;
}

IShip &		IShip::operator=(IShip const & origin) {
	AEntity::operator=(origin);
	return (*this);
}
