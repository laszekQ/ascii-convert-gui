#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <vector>
#include <initializer_list>
#include <Python.h>

using char_vector = std::vector< std::vector<char> >;

int getBrightness(sf::Color pixel)
{
    int r = pixel.r;
    int g = pixel.g;
    int b = pixel.b;
    int bright = (r + g + b) / 3;

    return bright;
}

char pixelsToASCII(std::initializer_list<sf::Color> pixels, std::string &gradient, char c_mode)
{
    float bright = 0;
    for(const auto& pixel : pixels)
        bright += getBrightness(pixel);
    bright /= pixels.size();

    float step = 255 / (gradient.length() - 1);
    int index = bright / step;

    if(c_mode == 'd')
        index = gradient.length() - index - 1;
    
    return gradient[index];
}

char_vector imgToAscii(sf::Image &img, std::string gradient, int grad_n, char c_mode, int mode)
{
    const uint32_t WIDTH  = img.getSize().x;
    const uint32_t HEIGHT = img.getSize().y;
    uint32_t height = HEIGHT / (1 + (mode == 2));
    uint32_t width = WIDTH * (1 + (mode == 3));
    char_vector out(height, std::vector<char>(width));

    gradient = gradient.substr(0, grad_n);

    int step_y = 1 + (mode == 2);

    for(uint32_t i = 0; i <= HEIGHT - step_y; i += step_y)
    {
        int x = 0;
        for(uint32_t j = 0; j < WIDTH; j++)
        {
            char c = 0;
            int y = i;
            switch(mode)
            {
            case 1:
            {
                sf::Color pixel = img.getPixel({j, i});
                c = pixelsToASCII({pixel}, gradient, c_mode);
                out[i][j] = c;
                break;
            }
            case 2:
            {
                sf::Color pixel1 = img.getPixel({j, i});
                sf::Color pixel2 = img.getPixel({j, i + 1});
                c = pixelsToASCII({pixel1, pixel2}, gradient, c_mode);
                y /= 2;
                out[y][j] = c;
                break;
            }
            case 3:
            {
                sf::Color pixel = img.getPixel({j, i}); 
                c = pixelsToASCII({pixel}, gradient, c_mode);
                out[i][x] = c;
                out[i][x + 1] = c;
                x += 2;
                break;
            }
            default:
                return out;
            }
        }
    }

    return out;
}

static PyObject* convertToAscii(PyObject* self, PyObject* args)
{
    char* FILE_IN;
    char* C_MODE;
    char* GRADIENT_CSTR;
    int   GRAD;
    int   MODE;
    if(!PyArg_ParseTuple(args, "sssii", &FILE_IN, &C_MODE, &GRADIENT_CSTR, &GRAD, &MODE)){
        return NULL;
    }

    std::string GRADIENT(GRADIENT_CSTR);
    char COLOR_MODE = std::string(C_MODE)[0];

    sf::Image img_in;
    if(!img_in.loadFromFile(FILE_IN))
        return NULL;

    char_vector out_vec = imgToAscii(img_in, GRADIENT, GRAD, COLOR_MODE, MODE);
    std::string out = "";
    for(auto y : out_vec)
    {
        for(auto x : y)
            out += x;
        out += '\n';
    }

    return PyUnicode_FromString(out.c_str());    
}

static PyMethodDef moduleMethods[] = {
    {"convert", convertToAscii, METH_VARARGS, "Return converted ascii text."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef ascii_module = {
    PyModuleDef_HEAD_INIT,
    "ascii_convert",
    NULL,
    -1,
    moduleMethods
};

extern "C" PyMODINIT_FUNC PyInit_ascii_convert(void) {
    return PyModule_Create(&ascii_module);
}