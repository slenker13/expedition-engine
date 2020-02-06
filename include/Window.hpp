#include <SDL2/SDL.h>

#include <string>

namespace Expedition {
    class Window {
        public:
            Window();

            // Create window
            bool init(std::string name, int width, int height);

            // Delete window
            void free();

            // Create renderer from window
            bool createRenderer();

            // Handle window events
            void handleEvent(SDL_Event& e);

            // Get renderer
            SDL_Renderer* getRenderer();

            // Window dimensions
            int getWidth();
            int getHeight();

            //  Window focii
            bool hasMouseFocus();
            bool hasKeyboardFocus();
            bool isMinimized();

        private:
            // Window data
            SDL_Window* m_window;

            // Window renderer
            SDL_Renderer* m_renderer;

            // Window dimensions
            int m_width;
            int m_height;

            // Window focus
            bool m_mouseFocus;
            bool m_keyboardFocus;
            bool m_fullScreen;
            bool m_minimized;
    };
}