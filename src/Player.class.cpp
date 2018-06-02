/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <mrajaona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 10:33:49 by mrajaona          #+#    #+#             */
/*   Updated: 2018/06/02 14:11:08 by vbaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Player.class.hpp"
#include "error.hpp"

			Player::Player( void ) :
	AEntity(0, 0, 0, 0, 0, ' '),
	IShip(0, 0, 0, 0, 0, ' ')
{
	std::cerr << BAD_CONSTRUCTOR_ERR << "Player" << std::endl;
	return ;
}

// Default appearance
			Player::Player(
				int posX, int posY,
				int sizeX, int sizeY,
				int id
				) :
	AEntity(
		posX, posY,
		sizeX, sizeY,
		PLAYER_DEFAULT_HP,
		PLAYER_DEFAULT_APPEARANCE
		),
	IShip(
		posX, posY,
		sizeX, sizeY,
		PLAYER_DEFAULT_HP,
		PLAYER_DEFAULT_APPEARANCE
		),
	_score(0),
	_lives(PLAYER_DEFAULT_LIVES - 1),
	_id(id)
{
	return ;
}

// Custom appearance
			Player::Player(
				int posX, int posY,
				int sizeX, int sizeY,
				int id,
				char appearance
				) :
	AEntity(
		posX, posY,
		sizeX, sizeY,
		PLAYER_DEFAULT_HP,
		appearance
		),
	IShip(
		posX, posY,
		sizeX, sizeY,
		PLAYER_DEFAULT_HP,
		appearance
		),
	_score(0),
	_lives(PLAYER_DEFAULT_LIVES - 1),
	_id(id)
{
	std::cout << getPosX() << " " << getPosY() << std::endl;
	return ;
}

			Player::Player(const Player & origin) :
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
		),
	_score(0),
	_lives(PLAYER_DEFAULT_LIVES - 1),
	_id(origin.getId())
{
	return ;
}

			Player::~Player( void ) {
	return ;
}

Player &	Player::operator=(Player const & origin) {
	IShip::operator=(origin);
	this->_score 	= origin.getScore();
	this->_lives	= origin.getLives();
	this->_id		= origin.getId();
	return (*this);
}

// getter

size_t const &	Player::getScore( void ) const {
	return (this->_score);
}

size_t const &	Player::getLives( void ) const {
	return (this->_lives);
}

int const &		Player::getId( void ) const {
	return (this->_id);
}

// setter

void			Player::setScore(size_t value) {
	this->_score = value;
}

void			Player::setLives(size_t value) {
	this->_lives = value;
}

void			Player::setId(int value) {
	this->_id = value;
}
