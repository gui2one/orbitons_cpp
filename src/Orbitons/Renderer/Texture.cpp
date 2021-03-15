#include "Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Orbitons{
	Orbitons::Ref<Texture> Texture::create(){
		return Orbitons::MakeRef<OpenGLTexture>();
	}

}
