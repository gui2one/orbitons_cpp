#ifndef TEXTURE_H
#define TEXTURE_H

#include "core.h"
#include "pch.h"
namespace Orbitons
{

	class Texture
	{
	public:
		static Texture *create();

		virtual ~Texture(){};
		virtual void load(std::string path) = 0;
		virtual void setData(int width, int height, unsigned char *buffer) = 0;

		virtual unsigned int getID() = 0;
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual int getBPP() = 0;
		virtual void bind(unsigned int slot = 0) = 0;
		// virtual void unbind(unsigned int slot = 0) = 0;

	private:
	};
}

#endif /* TEXTURE_H */
