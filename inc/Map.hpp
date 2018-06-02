/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudin <vbaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 10:09:23 by vbaudin           #+#    #+#             */
/*   Updated: 2018/06/02 13:20:06 by vbaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <ncurses.h>

#include <string>
#include <iostream>
#include <sstream>
#include <sys/time.h>

class Map {

	public:

		Map( void ); // Canonical
    Map ( int x, int y);
		~Map( void ); // Canonical
    void printMap( void );

	private:

    void printScene();

		// Ennemy *_ennemyMap[30];
		// AllyMissile *_allyMissiles[20];
		// Player              **_map;
};


#endif
