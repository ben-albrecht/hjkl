// Texture wrapper class

#include <SDL.h>
#include <string>

class LTexture
{
    public:
        // Constructor
        LTexture();

        // Deconstructor
        ~LTexture();

        // Loads image at given path
        bool loadFromFile(std::string path);

        // Deallocate texture
        void free();

        // Render texture at given point
        void render(int x, int y);

        // Get image dimensions
        int getWidth();
        int getHeight();

    private:
        // The actual hardware texture
        SDL_Texture* mTexture;

        // Image dimensions
        int mWidth;
        int mHeight;
};
