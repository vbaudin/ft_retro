// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Enemy.class.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/02 10:33:39 by mrajaona          #+#    #+#             //
//   Updated: 2018/06/02 10:33:40 by mrajaona         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Enemy.class.hpp"
#include "error.hpp"

			Enemy::Enemy( void ) :
	AEntity(0, 0, 0, 0, 0, ' ')
{
	std::cerr << BAD_CONSTRUCTOR_ERR << "Enemy" << std::endl;
	return ;
}

			Enemy::Enemy(
				int posX, int posY,
				int sizeX, int sizeY,
				size_t hp,
				char appearance,
				int score
				) :
	AEntity(
		posX, posY,
		sizeX, sizeY,
		hp,
		appearance
		),
	_score(score)
{
	return ;
}

			Enemy::Enemy(const Enemy & origin) :
	AEntity(
		origin.getPosX(),
		origin.getPosY(),
		origin.getSizeX(),
		origin.getSizeY(),
		origin.getHP(),
		origin.getAppearance()
		),
	_score(origin.getScore())
{
	return ;
}

			Enemy::~Enemy( void ) {
	return ;
}

Enemy &		Enemy::operator=(Enemy const & origin) {
	AEntity::operator=(origin);
	this->_score = origin.getScore();
	return (*this);
}

// getter
int const &	Enemy::getScore( void ) const {
	return (this->_score);
}

// setter
void		Enemy::setScore(int value){
	this->_score = value;
}
