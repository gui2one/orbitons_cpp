#include "Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Orbitons
{
	Texture *Texture::create()
	{
		return new OpenGLTexture();
	}

}
