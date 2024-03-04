#include "../hpp/lib.h"

#include <string>
#include <version.h>



int version() {
	//return PROJECT_VERSION_PATCH;
	return std::stoi(VER_CNT);

}
