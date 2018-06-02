/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudin <vbaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 10:09:17 by vbaudin           #+#    #+#             */
/*   Updated: 2018/06/02 14:29:47 by vbaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"

Map::Map(void) {
  // std::cout << "Basic Contructor" << std::endl;
	return;
}

Map::~Map(void) {
	//Destruction de la Map
}

void    Map::printMap( void ) {

	printScene();
	// printPlayer();
	// printEnnemies();
	// printMissiles();
	// refresh();
}

void    Map::printScene() {

}
