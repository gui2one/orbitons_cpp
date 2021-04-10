#include "Orbitons.h"
#include "core.h"

//#include "boost/lexical_cast.hpp"
//#include "boost/uuid/random_generator.hpp"
//#include "boost/uuid/uuid_io.hpp"
//#include "iostream"
using namespace Orbitons;

Application *app = Application::getInstance();

int main(int argc, char **argv)
{

    app->run();

    exit(EXIT_SUCCESS);
    return 0;
}