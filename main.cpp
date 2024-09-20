#include "bitmap.h"

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "No arguments were passed." << std::endl;
        return 1;
    }
    else if (argc > 2) {
        std::cerr << "Too many arguments passed." << std::endl;
        return 1;
    }

    Bitmap bmp;
    if (!bmp.open(argv[1])) {
        std::cerr << "Error opening file '" << argv[1] << "'!" << std::endl;
        return 1;
    }

    try {
        bmp.read();

        std::cout << "Width    = " << bmp.getWidth() << std::endl;
        std::cout << "Height   = " << bmp.getHeight() << std::endl;
        std::cout << "BitCount = " << bmp.getBitCount() << std::endl;

        bmp.display();
        bmp.close();
    }
    catch(std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}
