#include "Debug.h"

#include <iostream>

void DECLSPEC ETB::Debug::Print(const std::string& message) {
	std::cout << message << "\n";
}
