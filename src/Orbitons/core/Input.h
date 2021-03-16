#ifndef INPUT_H
#define INPUT_H

#include "Application.h"

namespace Orbitons
{
    
    class Input{
    public:
        static bool isKeyPressed(const int keycode);
        static bool isMouseButtonClicked(int button);
        static glm::vec2 getMousePos();
    private:

    };
} // namespace Orbitons

#endif /* INPUT_H */