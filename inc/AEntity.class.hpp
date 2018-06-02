// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AEntity.class.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/02 10:32:48 by mrajaona          #+#    #+#             //
//   Updated: 2018/06/02 10:32:49 by mrajaona         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AENTITY_CLASS_HPP
# define AENTITY_CLASS_HPP

class AEntity
{
	private:
		// Entity position
		int			_posX;
		int			_posY;

		// Entity size
		int			_sizeX;
		int			_sizeY;

		// Life
		size_t		_HP;

		// Appearance
		char		_appearance;


					AEntity( void );					// Default constructor

	protected:

	public:
					AEntity(
						int posX, int posY,
						int sizeX, int sizeY,
						size_t hp,
						char appearance
						);
					AEntity(const AEntity & origin);	// Copy constructor
		virtual		~AEntity( void );					// Default destructor
		AEntity &	operator=(AEntity const & origin);	// Assignation overload

		// getter
		int const &		getPosX( void ) const;
		int const &		getPosY( void ) const;
		int const &		getSizeX( void ) const;
		int const &		getSizeY( void ) const;
		char const &	getAppearance( void ) const;
		size_t	const & getHP( void ) const;

		// setter
		void			setPosX(int value);
		void			setPosY(int value);
		void			setSizeX(int value);
		void			setSizeY(int value);
		void			setAppearance(char value);
		void			setHP(size_t value);

		void			move(int mv_x, int mv_y);

		// abstract function
		virtual void	takeDamage( void );
		virtual void	onCollision( void );
};

#endif /* AENTITY_CLASS_HPP */
