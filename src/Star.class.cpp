/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Star.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudin <vbaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:24:43 by vbaudin           #+#    #+#             */
/*   Updated: 2018/06/02 13:25:01 by vbaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Star.class.hpp"

	Star::Star(void) {
  // std::cout << "Star Detruit !!" << std::endl;
}

	Star::Star( int x, int y ) :
	_x( x ),
	_y( y )
{
  // std::cout << "Nouveau Star creer !!" << std::endl;
}

	Star::~Star(void) {
  // std::cout << "Star Detruit !!" << std::endl;
}

int	Star::getY( void ) const {
  return (this->_y);
}

int	Star::getX( void ) const {
  return (this->_x);
}
