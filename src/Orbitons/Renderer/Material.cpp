#include "Material.h"

Orbitons::Ref<Material> Material::create(){

    return Orbitons::MakeRef<PhongMaterial>();
}
