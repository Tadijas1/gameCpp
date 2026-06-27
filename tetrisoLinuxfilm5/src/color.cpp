#include "colors.h"
#include <vector>


using namespace std;

const Color darkGrey = {26, 31, 40, 255};
const Color green = {47, 230, 23, 255};
const Color red = {232, 18, 18, 255};
const Color orange = {226, 116, 17, 255};
const Color yellow = {237, 234, 4, 255};
const Color purple = {166, 0, 247, 255};
const Color cyan = {21, 204, 209, 255};
const Color blue = {13, 63, 216, 255};
const Color lightBlue = {59, 85, 162, 255};
const Color darkBlue = {44, 44, 127, 255};
const Color silver = {192, 192, 192, 255};
const Color brown = {139, 69, 19, 255};
const Color darkRed = {85, 0, 0, 255};

vector<Color> GetCellColors() { return {darkGrey, green, red, orange, yellow, purple, cyan, blue, lightBlue, darkBlue, silver, brown, darkRed}; }