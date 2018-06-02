/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntity.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <mrajaona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 10:33:41 by mrajaona          #+#    #+#             */
/*   Updated: 2018/06/02 14:38:56 by vbaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "AEntity.class.hpp"
#include "error.hpp"

			AEntity::AEntity( void )
{
	std::cerr << BAD_CONSTRUCTOR_ERR << "AEntity" << std::endl;
	return ;
}

			AEntity::AEntity(
				int posX, int posY,
				int sizeX, int sizeY,
				size_t hp,
				char appearance
			) :
	_posX(posX),
	_posY(posY),
	_sizeX(sizeX),
	_sizeY(sizeY),
	_HP(hp),
	_appearance(appearance)
{
	return ;
}

			AEntity::AEntity(const AEntity & origin) :
	_posX(origin.getPosX()),
	_posY(origin.getPosY()),
	_sizeX(origin.getSizeX()),
	_sizeY(origin.getSizeY()),
	_HP(origin.getHP()),
	_appearance(origin.getAppearance())

{
	return ;
}

			AEntity::~AEntity( void ) {
	return ;
}

AEntity &	AEntity::operator=(AEntity const & origin) {
	this->_posX			= origin.getPosX();
	this->_posY			= origin.getPosY();
	this->_sizeX		= origin.getSizeX();
	this->_sizeY		= origin.getSizeY();
	this->_HP			= origin.getHP();
	this->_appearance	= origin.getAppearance();

	return (*this);
}

// getter

int	const &		AEntity::getPosX( void ) const {
	return(this->_posX);
}

int	const &		AEntity::getPosY( void ) const {
	return(this->_posY);
}

int	const &		AEntity::getSizeX( void ) const {
	return(this->_sizeX);
}

int	const &		AEntity::getSizeY( void ) const {
	return(this->_sizeY);
}

char const &	AEntity::getAppearance( void ) const {
	return(this->_appearance);
}

size_t const &	AEntity::getHP( void ) const {
	return (this->_HP);
}

// setter

void		AEntity::setPosX(int value) {
	this->_posX = value;
}

void		AEntity::setPosY(int value) {
	this->_posY = value;
}

void		AEntity::setSizeX(int value) {
	this->_sizeX = value;
}

void		AEntity::setSizeY(int value) {
	this->_sizeY = value;
}

void		AEntity::setAppearance(char appearance) {
	this->_appearance = appearance;
}

void		AEntity::setHP(size_t value) {
	this->_HP = value;
}

// function
void		AEntity::move(int mv_x, int mv_y) {
	this->_posX += mv_x;
	this->_posY += mv_y;
}

void		AEntity::takeDamage( void ) {
	if (this->_HP > 0)
		this->_HP -= 1;
}

void		AEntity::onCollision( void ) {
	this->_HP = 0;
	/* IT IS DEAD */
}
