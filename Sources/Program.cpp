#include <cassert>
#include <cmath>

#include "Grapic.h"

using namespace grapic;
using namespace std;

// Primary Structs

struct HexPosition { int Q, R, S; };
struct HexVertex { int Vertex[6][2]; };
struct Complex { float re, im; };
struct Color { int r, g, b, a; };

// Variables

const int Screen_Size = 512;
const int CellSize = 32;
const float UpdateDelay = 1.0f;
const Color Colors[]{
        {255,45,255,255},
        {45,255,45,255},
        {0,0,0,0}};

// Constant

const int VCellCount = (int)Screen_Size / CellSize;
const int HCellCount = (int)Screen_Size / CellSize;
const float Sqrt3d2 = 0.866025404f;
const float Sqrt3   = 1.732050807f;
const float Sqrt3d3 = 0.577350269f;

// Enumerations

enum CellState { None, Alive, Dead };
enum HexDir { O, NE, E, SE, SW, W, NW };

// Complex

Complex mkComplex(float re, float im) { return {re, im}; }
Complex mkComplexExp(float r, float theta_deg) {
  float theta_rad = theta_deg * M_PI / 180;
  return {r * cos(theta_rad), r * sin(theta_rad)};
}

Complex operator+(Complex a, Complex b) { return {a.re + b.re, a.im + b.im}; }
Complex operator-(Complex a, Complex b) { return {a.re - b.re, a.im - b.im}; }
Complex operator*(float a, Complex b) { return {b.re * a, b.im * a}; }
Complex operator*(Complex a, float b) { return b * a; }
Complex operator/(Complex a, float b) { return {a.re / b, a.im / b}; }
Complex operator/(Complex a, int b) { return {a.re / b, a.im / b}; }
Complex operator*(Complex a, Complex b) {
  return {a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re};
}
Complex rotate(Complex a, Complex pivot, float angle_deg) {
  return (a - pivot) * mkComplexExp(1, angle_deg) + pivot;
}
Complex rotate(Complex a, float re, float im, float angle_deg) {
  return rotate(a, mkComplex(re, im), angle_deg);
}
Complex scale(Complex a, Complex b, float lamda) { return (a - b) * lamda + b; }
Complex scale(Complex a, float re, float im, float lamda) {
  return scale(a, mkComplex(re, im), lamda);
}
Complex lerp(Complex a, Complex b, float t) { return (1 - t) * a + t * b; }
Complex normalize(Complex c) {
  float norm = sqrt(c.re * c.re + c.im * c.im);
  return mkComplex(c.re / norm, c.im / norm);
}

// Interpolation

float lerp(float a, float b, float t) { return (a * (1 - t)) + (b * t); }
int lerp(int a, int b, float t) { return (a * (1 - t)) + (b * t); }
Color lerp(Color a, Color b, float t) {
  return {lerp(a.r, b.r, t), lerp(a.g, b.g, t), lerp(a.b, b.b, t),
          lerp(a.a, b.a, t)};
}

// HexCell

Complex PositionFromHexPosition(HexPosition hexPosition) {
  return mkComplex(CellSize * (Sqrt3 * hexPosition.Q + Sqrt3d2 * hexPosition.R),
                   CellSize * 1.5f * hexPosition.R);
}

HexPosition mkHexPosition(int col, int row) {
  int q = col - (row - (row & 1)) / 2;
  int r = row;
  int s = -q - r;
  assert(q + r + s == 0);
  return {q, r, s};
}

HexPosition mkHexPosition(int q, int r, int s) {
  assert(q + r + s == 0);
  return {q, r, s};
}
static HexPosition HexRound(float fQ, float fR, float fS) {
  int q = lround(fQ);
  int r = lround(fR);
  int s = lround(fS);

  int qDelta = abs(q - fQ);
  int rDelta = abs(r - fR);
  int sDelta = abs(s - fS);

  if (qDelta > rDelta && qDelta > sDelta)
    q = -r - s;
  else if (rDelta > sDelta)
    r = -q - s;
  else
    s = -q - r;

  return mkHexPosition(q, r, s);
}
static HexPosition HexRound(float fQ, float fR) {
  return HexRound(fQ, fR, -fQ - fR);
}
static HexPosition Snap(float x, float z) {
  return HexRound((Sqrt3d3 * x - (1.0f / 3.0f) * z) / CellSize,
                  ((2.0f / 3.0f) * z) / CellSize);
}
static HexPosition Snap(Complex position) {
  return Snap(position.re, position.im);
}

static bool operator==(HexPosition a, HexPosition b) {
  return a.Q == b.Q && a.R == b.R && a.S == b.S;
}

static bool operator!=(HexPosition a, HexPosition b) { return !(a == b); }

static HexPosition operator+(HexPosition a, HexPosition b) {
  return mkHexPosition(a.Q + b.Q, a.R + b.R, a.S + b.S);
}

static HexPosition operator-(HexPosition a, HexPosition b) {
    return mkHexPosition(a.Q - b.Q, a.R - b.R, a.S - b.S);
}
HexPosition Delta(HexDir dir) {
    switch (dir) {
        case O:return mkHexPosition(0, 0, 0);
        case NE:return mkHexPosition(1, -1, 0);
        case E:return mkHexPosition(1, 0, -1);
        case SE:return mkHexPosition(0, 1, -1);
        case SW:return mkHexPosition(-1, 1, 0);
        case W:return mkHexPosition(-1, 0, 1);
        case NW:return mkHexPosition(0, -1, 1);
    }
}

HexDir Opposite(HexDir dir) {
    switch (dir) {
        case O:return HexDir::O;
        case NE:return HexDir::SW;
        case E:return HexDir::W;
        case SE:return HexDir::NW;
        case SW:return HexDir::NE;
        case W:return HexDir::E;
        case NW:return HexDir::SE;
    }
}

static HexPosition operator+(HexPosition a, HexDir b) { return a + Delta(b); }
static HexPosition operator-(HexPosition a, HexDir b) { return a - Delta(b); }
static HexPosition operator*(HexPosition a, int k) { return mkHexPosition(a.Q * k, a.R * k, a.S * k); }
HexPosition HexPositionFromPosition(Complex position) { return Snap(position); }
static int Length(HexPosition hexPosition) { return (abs(hexPosition.Q) + abs(hexPosition.R) + abs(hexPosition.S)) / 2; }
static int Distance(HexPosition a, HexPosition b) { return Length(a - b); }

// Tools

void setColor(Color col) { color(col.r,col.g,col.b,col.a); }

// Game of Life

struct Cell {
    HexPosition hexPosition;
    int col, row;
    int neighbors[6];
    CellState state;
    CellState nextState;
};

struct World {
    float Time, dT;

    float updateTime;

    Cell cells[VCellCount * HCellCount];
};

Cell mkCell(int col, int row,CellState state = CellState::None) {
    Cell cell{};
    cell.col = col;
    cell.row = row;
    cell.state = state;
    cell.hexPosition = mkHexPosition(col,row);
    cell.nextState = CellState::None;
    for (int &neighbor : cell.neighbors) neighbor = -1;
    return cell;
}

HexVertex GetHexPoints(Cell cell) {
    Complex
    position = PositionFromHexPosition(cell.hexPosition),
    N = position + mkComplex(0,CellSize),
    NW = rotate(N,position,60),
    SW = rotate(N,position,120),
    S = rotate(N,position,180),
    SE = rotate(N,position,240),
    NE = rotate(N,position,300);
    return {{{N.re,N.im},{NW.re,NW.im},{SW.re,SW.im},{S.re,S.im},{SE.re,SE.im},{NE.re,NE.im},}};
}

World WorldInit() {
  std::cout << "HCellCount: " << HCellCount << std::endl;
  std::cout << "VCellCount: " << VCellCount << std::endl;
  World world = {};
  world.Time = 0;
  world.dT = 0;
  world.updateTime = 0;
  for (int col = 0; col < HCellCount; ++col)
    for (int row = 0; row < VCellCount; ++row)
      world.cells[col + row * HCellCount] = mkCell(col, row, CellState::Dead);

  // Test
  world.cells[21].state = Alive;

  return world;
}

void DetermineNextState(World &world, Cell &cell) {

    //int aliveNeighbors = 0;
    //for (int &neighbor: cell.neighbors)
        //if (neighbor != -1 && world.cells[neighbor].state == CellState::Alive)
            //aliveNeighbors++;


    // Test Rules
    switch (cell.state) {

        case None:  cell.nextState = CellState::Alive; break;
        case Alive: cell.nextState = CellState::Dead;  break;
        case Dead:  cell.nextState = CellState::Alive; break;
    }


    // True Rules
    // if(aliveNeighbors > 3) cell.nextState = CellState::Dead;
    // if(aliveNeighbors == 2 && cell.state == CellState::Dead) cell.nextState =
    // CellState::Alive;
}
void ApplyNextState(Cell &cell) { cell.state = cell.nextState; cell.nextState = CellState::None; }

void update(World &world) {

    // Time
    world.dT = elapsedTime() - world.Time;
    world.Time = elapsedTime();

    if(world.Time - world.updateTime > UpdateDelay)
    {
        world.updateTime = world.Time;

        // Cell
        for (Cell& cell: world.cells) DetermineNextState(world, cell);
        for (Cell& cell: world.cells) ApplyNextState(cell);
    }
}

void draw(const World &system, const Cell &cell) {
    switch (cell.state) {
        case None: setColor(Colors[CellState::None]); polygonFill(GetHexPoints(cell).Vertex, 6); break;
        case Alive: setColor(Colors[CellState::Alive]); polygonFill(GetHexPoints(cell).Vertex, 6); break;
        case Dead: setColor(Colors[CellState::Dead]); polygonFill(GetHexPoints(cell).Vertex, 6); break;
    }
}

void draw(const World &system) { for (Cell cell: system.cells) draw(system, cell); }

int main(int, char **) {
    winInit("[Hex Game of Life]", Screen_Size, Screen_Size);
    World world = WorldInit();
    do {
        winClear();
        update(world);
        draw(world);
    } while (!winDisplay());
    winQuit();
}
