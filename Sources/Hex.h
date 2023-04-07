#ifndef Hex_H
#define Hex_H

#include "Complex.hpp"
#include <cmath>

const float Sqrt3d2 = 0.866025404f;
const float   Sqrt3 = 1.732050807f;
const float Sqrt3d3 = 0.577350269f;
const float Size    = 1.0f;

enum HexDir { O, NE, E, SE, SW, W, NW };

struct HexPosition { int Q,R,S; };
struct HexVertex { int Vertex[6][2];};

Complex PositionFromHexPosition(HexPosition hexPosition);
HexPosition HexPositionFromPosition(Complex position);
HexPosition mkHexPosition(int col,int row);
HexPosition mkHexPosition(int q,int r,int s);
static HexPosition Snap(Complex position);
static HexPosition Snap(float x, float z);
static HexPosition HexRound(float fQ, float fR);
static HexPosition HexRound(float fQ, float fR, float fS);
HexPosition Delta(HexDir dir);
static bool operator ==(HexPosition a, HexPosition b);
static bool operator !=(HexPosition a, HexPosition b);
static HexPosition operator +(HexPosition a, HexPosition b);
static HexPosition operator -(HexPosition a, HexPosition b);
static HexPosition operator +(HexPosition a, HexDir b);
static HexPosition operator -(HexPosition a, HexDir b);
static HexPosition operator *(HexPosition a, int k);
static int Length(HexPosition hexPosition);
static int Distance(HexPosition a, HexPosition b);
HexDir Opposite(HexDir dir);
HexVertex GetHexVertex(HexPosition position, float cellSize);

#endif //Hex_H
