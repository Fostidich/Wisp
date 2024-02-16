//
// Created by kello on 13/12/23.
//

#ifndef FILES_H
#define FILES_H


#include <string>

/**
 * Path is returned without the executable name, with a slash as final char
 * @return the executable path
 */
std::string getExecutableDir();

/**
* Directory is returned with the executable name in the end
* @return the executable directory
*/
std::string getExecutablePath();


#endif //FILES_H
