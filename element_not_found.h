#ifndef ELEMENT_NOT_FOUND_H
#define ELEMENT_NOT_FOUND_H

#include <stdexcept>
#include <string>

class element_not_found : public std::logic_error {
public:
	element_not_found(const std::string &message);
};

#endif