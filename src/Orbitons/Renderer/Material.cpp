#include "Material.h"

namespace Orbitons
{

    Material *Material::create()
    {

        return new PhongMaterial();
    }
}
