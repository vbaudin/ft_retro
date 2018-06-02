/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bullet.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <mrajaona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 10:33:43 by mrajaona          #+#    #+#             */
/*   Updated: 2018/06/02 17:47:58 by vbaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bullet.class.hpp"
#include "error.hpp"

			Bullet::Bullet( void ) :
	AEntity(0, 0, 0, 0, 0, ' ')
{
	std::cerr << BAD_CONSTRUCTOR_ERR << "Bullet" << std::endl;
	return ;
}


// Default Player Bullet
			Bullet::Bullet(
				int posX, int posY,
				int sizeX, int sizeY,
				int mvtX, int mvtY,
				int id
				) :
	AEntity(
		posX, posY,
		sizeX, sizeY,
		BULLET_DEFAULT_HP,
		BULLET_DEFAULT_APPEARANCE
		),
	_mvtX(mvtX),
	_mvtY(mvtY),
	_playerId(id)
{
	return ;
}

// Default Enemy Bullet
			Bullet::Bullet(
				int posX, int posY,
				int sizeX, int sizeY,
				int mvtX, int mvtY
				) :
	AEntity(
		posX, posY,
		sizeX, sizeY,
		BULLET_DEFAULT_HP,
		BULLET_DEFAULT_APPEARANCE
		),
	_mvtX(mvtX),
	_mvtY(mvtY),
	_playerId(0)
{
	return ;
}

// Custom Player Bullet
			Bullet::Bullet(
				int posX, int posY,
				int sizeX, int sizeY,
				int mvtX, int mvtY,
				int id,
				char appearance
				) :
	AEntity(
		posX, posY,
		sizeX, sizeY,
		BULLET_DEFAULT_HP,
		appearance
		),
	_mvtX(mvtX),
	_mvtY(mvtY),
	_playerId(id)
{
	return ;
}

// Custom Enemy Bullet
			Bullet::Bullet(
				int posX, int posY,
				int sizeX, int sizeY,
				int mvtX, int mvtY,
				char appearance
				) :
	AEntity(
		posX, posY,
		sizeX, sizeY,
		BULLET_DEFAULT_HP,
		appearance
		),
	_mvtX(mvtX),
	_mvtY(mvtY),
	_playerId(0)
{
	return ;
}

			Bullet::Bullet(const Bullet & origin) :
	AEntity(
		origin.getPosX(),
		origin.getPosY(),
		origin.getSizeX(),
		origin.getSizeY(),
		origin.getHP(),
		origin.getAppearance()
		),
	_mvtX(origin.getMvtX()),
	_mvtY(origin.getMvtY()){
	return ;
}

			Bullet::~Bullet( void ) {
	return ;
}

Bullet &	Bullet::operator=(Bullet const & origin) {
	AEntity::operator=(origin);
	this->_mvtX	= origin.getMvtX();
	this->_mvtY	= origin.getMvtY();

	return (*this);
}

// getter

int	const & 		Bullet::getMvtX( void ) const {
	return (this->_mvtX);
}

int	const & 		Bullet::getMvtY( void ) const {
	return (this->_mvtY);
}

int	const & 		Bullet::getPlayerId( void ) const {
	return (this->_playerId);
}

uint64_t Bullet::getSecs( void ) {

	return Bullet::_secs;
}
// setter

void Bullet::setSecs( uint64_t secs ) {

	Bullet::_secs = secs;
	return;
}

void				Bullet::setMvtX(int value) {
	this->_mvtX = value;
}

void				Bullet::setMvtY(int value) {
	this->_mvtY = value;
}

void				Bullet::setPlayerId(int value) {
	this->_playerId = value;
}

void				Bullet::move( void ) {
	this->move(this->_mvtX, this->_mvtY);
}

uint64_t Bullet::_secs = 0;
