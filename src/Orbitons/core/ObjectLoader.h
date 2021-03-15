#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "../pch.h"

#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace Orbitons{
	class ObjLoader{
		public:
			ObjLoader();
			// ~ObjLoader();
			Mesh assimp_load(std::string file_path);
			

	};
}
#endif
