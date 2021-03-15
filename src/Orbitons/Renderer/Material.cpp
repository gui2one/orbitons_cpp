#include "Material.h"

namespace Orbitons{

    Ref<Material> Material::create(){

        return MakeRef<PhongMaterial>();
    }
}
