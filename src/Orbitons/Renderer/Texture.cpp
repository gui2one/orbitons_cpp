#include "Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"

Orbitons::Ref<Texture> Texture::create(){
	return Orbitons::MakeRef<OpenGLTexture>();
}
