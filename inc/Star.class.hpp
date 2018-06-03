/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Star.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudin <vbaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:25:39 by vbaudin           #+#    #+#             */
/*   Updated: 2018/06/02 13:28:22 by vbaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Star_HPP
# define Star_HPP

# include <string>
# include <iostream>
# include <sstream>

// #include "GameEntities.hpp"

struct Star {

  public:

			Star(void);
    		Star( int x, int y );
    		~Star(void);

    int		getY( void ) const;
    int		getX( void ) const;

  private:

    int		_x;
    int		_y;

};


#endif
