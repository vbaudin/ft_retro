// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IShip.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/02 10:33:11 by mrajaona          #+#    #+#             //
//   Updated: 2018/06/02 10:33:12 by mrajaona         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ISHIP_CLASS_HPP
# define ISHIP_CLASS_HPP

# include "AEntity.class.hpp"

class IShip	: virtual public AEntity
{
	private:
					IShip( void );						// Default constructor

	protected:

	public:
					IShip(
						int posX, int posY,
						int sizeX, int sizeY,
						size_t hp,
						char appearance
						);
					IShip(const IShip & origin);		// Copy constructor
		virtual		~IShip( void );						// Default destructor
		IShip &		operator=(IShip const & origin);	// Assignation overload
};

#endif /* ISHIP_CLASS_HPP */
