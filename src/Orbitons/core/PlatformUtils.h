#ifndef PLATFORM_UTILS_H
#define PLATFORM_UTILS_H

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "core.h"
#include <string>
#include <optional>
#include <stdio.h>
#include <iostream>

#ifdef ORBITONS_PLATFORM_WINDOWS
#include <windows.h>
#include <commdlg.h>

class PlatformUtils{
public:

    static std::optional<std::string> openFileialog(std::string file_path){
        OPENFILENAMEA ofn;
        char szFile[260];
        HWND hwnd;
        HANDLE hf;

        // Initialize OPENFILENAME
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = NULL;
        ofn.lpstrFile = (LPSTR)szFile;
        // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
        // use the contents of szFile to initialize itself.
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;        



        if(GetOpenFileNameA(&ofn) == TRUE){

            return ofn.lpstrFile;
        };

        return std::nullopt;
    }
private:

};

#endif /* ORBITONS_PLATFORM_WINDOWS */
#endif /* PLATFORM_UTILS_H */