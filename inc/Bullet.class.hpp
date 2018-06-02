/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bullet.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <mrajaona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 10:33:03 by mrajaona          #+#    #+#             */
/*   Updated: 2018/06/02 17:46:28 by vbaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULLET_CLASS_HPP
# define BULLET_CLASS_HPP

# include "AEntity.class.hpp"

class Bullet	: virtual public AEntity
{
	private:
		// How the bullet moves
		int			_mvtX;
		int			_mvtY;
		int			_playerId;
		static uint64_t _secs;

					Bullet( void );						// Default constructor

	protected:

	public:
				// Default Player Bullet
					Bullet(
						int posX, int posY,
						int sizeX, int sizeY,
						int mvtX, int mvtY
						);
				// Default Enemy Bullet
					Bullet(
						int posX, int posY,
						int sizeX, int sizeY,
						int mvtX, int mvtY,
						int id
						);
				// Custom Player Bullet
					Bullet(
						int posX, int posY,
						int sizeX, int sizeY,
						int mvtX, int mvtY,
						char appearance
						);
				// Custom Enemy Bullet
					Bullet(
						int posX, int posY,
						int sizeX, int sizeY,
						int mvtX, int mvtY,
						int id,
						char appearance
						);
					Bullet(const Bullet & origin);		// Copy constructor
		virtual		~Bullet( void );					// Default destructor
		Bullet &	operator=(Bullet const & origin);	// Assignation overload

		// getter
		int	const & 		getMvtX( void ) const;
		int	const & 		getMvtY( void ) const;
		int	const & 		getPlayerId( void ) const;
		static uint64_t     getSecs( void );
		// setter
		void				setMvtX(int value);
		void				setMvtY(int value);
		void				setPlayerId(int value);
		static void     setSecs( uint64_t secs );

		// function
		using 			AEntity::move;
		void			move( void );
};

# define BULLET_DEFAULT_APPEARANCE '|'
# define BULLET_DEFAULT_HP			1

#endif /* BULLET_CLASS_HPP */
