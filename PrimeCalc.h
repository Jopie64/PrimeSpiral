#pragma once
#include <functional>
void DrawPrimeSpiral(std::function<void (int devider)> progress, HDC hdc, const RECT& rect);
