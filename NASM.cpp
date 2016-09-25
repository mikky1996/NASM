#include <iostream>
#include <fstream>
#include <cstring>
#include "Motherboard.hpp"
int main() {
    std::string s2;
	std::cin >> s2;
	Motherboard MB;
	MB.Initialize_var(s2);
	MB.compilation(s2);
	MB.Create_obj_file();
	MB.start(s2);
}