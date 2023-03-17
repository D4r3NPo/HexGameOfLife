#include <cassert>
#include "Hex.h"

Complex PositionFromHexPosition(HexPosition hexPosition) {
    return mkComplex(Size * (Sqrt3 * hexPosition.Q + Sqrt3d2 * hexPosition.R), Size * 1.5f * hexPosition.R);
}

HexPosition HexPositionFromPosition(Complex position) {
    return Snap(position);
}

HexPosition mkHexPosition(int col, int row) {
    int q = col - (row - (row & 1)) / 2;
    int r = row;
    int s = -q - r;
    assert(q+r+s== 0);
    return {q ,r , s};
}

HexPosition mkHexPosition(int q, int r, int s) {
    assert(q + r + s == 0);
    return {q, r, s};
}

static HexPosition Snap(Complex position) {
    return Snap(position.re, position.im);
}

static HexPosition Snap(float x, float z) {
    return HexRound((Sqrt3d3 * x - (1.0f / 3.0f) * z) / Size, ((2.0f / 3.0f) * z) / Size);
}

static HexPosition HexRound(float fQ, float fR) {
    return HexRound(fQ, fR, -fQ - fR);
}

static HexPosition HexRound(float fQ, float fR, float fS)
{
    int q = lround(fQ);
    int r = lround(fR);
    int s = lround(fS);

    int qDelta = abs(q - fQ);
    int rDelta = abs(r - fR);
    int sDelta = abs(s - fS);

    if (qDelta > rDelta && qDelta > sDelta) q = -r - s;
    else if (rDelta > sDelta) r = -q - s;
    else s = -q - r;

    return mkHexPosition(q, r, s);
}

static bool operator==(HexPosition a, HexPosition b) {
    return a.Q == b.Q && a.R == b.R && a.S == b.S;
}

static bool operator!=(HexPosition a, HexPosition b) {
    return !(a == b);
}

static HexPosition operator+(HexPosition a, HexPosition b) {
    return mkHexPosition(a.Q + b.Q, a.R + b.R, a.S + b.S);
}

static HexPosition operator-(HexPosition a, HexPosition b) {
    return mkHexPosition(a.Q - b.Q, a.R - b.R, a.S - b.S);
}

static HexPosition operator+(HexPosition a, HexDir b) {
    return a + Delta(b);
}

static HexPosition operator-(HexPosition a, HexDir b) {
    return a - Delta(b);
}

static HexPosition operator*(HexPosition a, int k) {
    return mkHexPosition(a.Q * k, a.R * k, a.S * k);
}

static int Length(HexPosition hexPosition) {
    return (abs(hexPosition.Q) + abs(hexPosition.R) + abs(hexPosition.S)) / 2;
}

static int Distance(HexPosition a, HexPosition b) {
    return Length(a - b);
}

HexPosition Delta(HexDir dir) {
    switch (dir) {
        case O:
            return mkHexPosition(0, 0, 0);
        case NE:
            return mkHexPosition(1, -1, 0);
        case E:
            return mkHexPosition(1, 0, -1);
        case SE:
            return mkHexPosition(0, 1, -1);
        case SW:
            return mkHexPosition(-1, 1, 0);
        case W:
            return mkHexPosition(-1, 0, 1);
        case NW:
            return mkHexPosition(0, -1, 1);
    }
}

HexDir Opposite(HexDir dir) {
    switch (dir) {
        case O:
            return HexDir::O;
        case NE:
            return HexDir::SW;
        case E:
            return HexDir::W;
        case SE:
            return HexDir::NW;
        case SW:
            return HexDir::NE;
        case W:
            return HexDir::E;
        case NW:
            return HexDir::SE;
    }
}