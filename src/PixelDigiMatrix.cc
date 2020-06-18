#include "PixelDigiMatrix.h"
#include <cmath>

PixelDigiMatrix::PixelDigiMatrix(int layer,
                                 int ladder,
                                 float thickness,
                                 double pixelSizeX,
                                 double pixelSizeY,
                                 float ladderLength,
                                 float ladderWidth):
    _layer(layer),
    _ladder(ladder),
    _thickness(thickness),
    _pixelSizeX(abs(pixelSizeX)),
    _pixelSizeY(abs(pixelSizeY)),
    _ladderLength(ladderLength > 0 ? ladderLength : 0),
    _ladderWidth(ladderWidth > 0 ? ladderWidth : 0),
    x_size(ceil(ladderWidth / pixelSizeX)),
    y_size(ceil(ladderLength / pixelSizeY)),
    pixels(x_size * y_size)
{}

PixelDigiMatrix::~PixelDigiMatrix()
{}

void PixelDigiMatrix::Reset()
{
    pixels.assign(pixels.size(), {0, 0});
}

void PixelDigiMatrix::UpdatePixel(int x, int y, PixelData data)
{
    pixels[index(x, y)] = data;
}

void PixelDigiMatrix::Apply(PixelTransformation l_expr)
{
    for (long unsigned int k = 0; k < pixels.size(); k++)
    {
        pixels[k] = l_expr(pixels[k]);
    }
}

PixelData PixelDigiMatrix::GetPixel(int x, int y)
{
    return pixels[index(x, y)];
}

void PixelDigiMatrix::TransformXYToCellID(double x, double y, int & ix, int & iy)
{
    double yInLadder = y + _ladderLength / 2;
    iy = int(yInLadder / _pixelSizeY);

    double xInLadder = x + _ladderWidth / 2;
    ix = int(xInLadder / _pixelSizeX);
}

void PixelDigiMatrix::TransformCellIDToXY(int ix, int iy, double & x, double & y)
{
    y = ((0.5 + double(iy)) * _pixelSizeY) - _ladderLength / 2;
    x = ((0.5 + double(ix)) * _pixelSizeX) - _ladderWidth / 2;
}


