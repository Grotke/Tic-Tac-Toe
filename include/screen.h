#include <SDL.h>
#include "button.h"

#ifndef SCREEN_H_
#define SCREEN_H_
class Screen
{
    public:
        void render();
        void clearScreen();
        void deleteScreen();
        void addButton(Button button);
        void disableAllButtons();
        void enableAllButtons();

} ;

#endif
