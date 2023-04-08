#include <cassert>
#include <cmath>
#include <string>

#include "Grapic.h"

using namespace grapic;
using namespace std;

// Primary Structs

struct Hex { int q, r, s, col,row; };
struct HexVertex { int Vertex[6][2]; };
struct Complex { float re, im; };
struct Color { int r, g, b, a;};

// Variables

const int Screen_Size = 512;
const int CellSize = 32;
const float UpdateDelay = 1.0f;
const Color Colors[]{
        {255,45,255,255},
        {45,255,45,255},
        {0,0,0,0}};

// Constant

const float Sqrt3d2 = 0.866025404f;
const float Sqrt3   = 1.732050807f;
const float Sqrt3d3 = 0.577350269f;
const int VCellCount = Screen_Size / CellSize;
const int HCellCount = Screen_Size / CellSize;

// Enumerations

enum CellState { None, Alive, Dead };
enum HexDir { O = -1, NE, E, SE, SW, W, NW };

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

Complex PositionFromHexPosition(Hex hexPosition) { return mkComplex(CellSize * (Sqrt3 * hexPosition.q + Sqrt3d2 * hexPosition.r),CellSize * 1.5f * hexPosition.r);}

Hex mkHexPosition(int col, int row) { int q = col - (row - (row & 1)) / 2, r = row, s = -q - r; assert(q + r + s == 0); return {q, r, s, col, row}; }

Hex mkHexPosition(int q, int r, int s) { assert(q + r + s == 0); return {q, r, s, q + (r - (r & 1)) / 2, r}; }

static Hex HexRound(float fQ, float fR, float fS) {
    int q = lround(fQ), r = lround(fR), s = lround(fS);
    int qDelta = abs(q - fQ), rDelta = abs(r - fR), sDelta = abs(s - fS);
    if (qDelta > rDelta && qDelta > sDelta) q = -r - s;
    else if (rDelta > sDelta) r = -q - s;
    else s = -q - r;
    return mkHexPosition(q, r, s);
}

static Hex HexRound(float fQ, float fR) { return HexRound(fQ, fR, -fQ - fR); }
static Hex Snap(float x, float z) { return HexRound((Sqrt3d3 * x - (1.0f / 3.0f) * z) / CellSize,((2.0f / 3.0f) * z) / CellSize); }
static Hex Snap(Complex position) { return Snap(position.re, position.im); }
static bool operator==(Hex a, Hex b) { return a.q == b.q && a.r == b.r && a.s == b.s; }
static bool operator!=(Hex a, Hex b) { return !(a == b); }
static Hex operator+(Hex a, Hex b) { return mkHexPosition(a.q + b.q, a.r + b.r, a.s + b.s); }
static Hex operator-(Hex a, Hex b) { return mkHexPosition(a.q - b.q, a.r - b.r, a.s - b.s); }
Hex Delta(HexDir dir) {
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

static Hex operator+(Hex a, HexDir b) { return a + Delta(b); }
static Hex operator-(Hex a, HexDir b) { return a - Delta(b); }
static Hex operator*(Hex a, int k) { return mkHexPosition(a.q * k, a.r * k, a.s * k); }
Hex HexPositionFromPosition(Complex position) { return Snap(position); }
//static int Length(Hex location) { return (abs(location.q) + abs(location.r) + abs(location.s)) / 2; }
//static int Distance(Hex a, Hex b) { return Length(a - b); }

// Tools

void setColor(Color col) { color(col.r,col.g,col.b,col.a); }

// Game of Life

struct Cell {
    Hex location;
    int neighbors[6];
    CellState state;
    CellState nextState;
};

struct World {
    float Time, dT;
    float updateTime;
    bool pauseMode;
    bool displayHex;
    Cell cells[VCellCount * HCellCount];
};

bool isValidCoordinate(int col,int row) { return -1 < col && col < HCellCount && -1 < row && row < VCellCount; }
bool isValidCoordinate(Hex location) {return isValidCoordinate(location.col, location.row);}

Cell mkCell(int col, int row,CellState state) {
    Cell cell{};
    cell.location = mkHexPosition(col, row);
    cell.state = state;
    cell.nextState = CellState::Dead;
    for (int i = 0; i < 6; ++i) {
        Hex test = Delta((HexDir)i) + cell.location;
        cell.neighbors[(HexDir)i] = isValidCoordinate(test)? test.col + test.row * HCellCount : -1;
    }
    return cell;
}


HexVertex GetHexPoints(Cell cell) {
    Complex
    position = PositionFromHexPosition(cell.location),
    N = position + mkComplex(0,CellSize),
    NW = rotate(N,position,60),
    SW = rotate(N,position,120),
    S = rotate(N,position,180),
    SE = rotate(N,position,240),
    NE = rotate(N,position,300);
    return {{{N.re,N.im},{NW.re,NW.im},{SW.re,SW.im},{S.re,S.im},{SE.re,SE.im},{NE.re,NE.im},}};
}
void SetState(World& world,int col,int row,CellState state) { if (isValidCoordinate(col, row)) world.cells[col + row * HCellCount].state = state; }

World WorldInit() {
    std::cout << "HCellCount: " << HCellCount << std::endl;
    std::cout << "VCellCount: " << VCellCount << std::endl;
    World world = {};
    world.Time = 0;
    world.dT = 0;
    world.updateTime = 0;
    world.displayHex = false;
    world.pauseMode = true;
    for (int col = 0; col < HCellCount; ++col)
        for (int row = 0; row < VCellCount; ++row)
            world.cells[col + row * HCellCount] = mkCell(col, row, CellState::Dead);

    // Start Systems

    /*// Flicker
    SetState(world,4,6,Alive);
    SetState(world,5,6,Alive);*/

    /*//Clapper
    SetState(world,4,6,Alive);
    SetState(world,5,6,Alive);
    SetState(world,5,7,Alive);
    SetState(world,5,8,Alive);*/

    SetState(world,4,6,Alive);
    SetState(world,4,8,Alive);
    SetState(world,5,6,Alive);
    SetState(world,5,7,Alive);
    SetState(world,5,8,Alive);

    return world;
}

// TODO Animate state applying with interpolation
void applyNextState(Cell &cell) { cell.state = cell.nextState; cell.nextState = CellState::Dead; }
void findNextState(World &world, Cell &cell) {

    int aliveNeighbors = 0;
    for (int &neighbor: cell.neighbors)
        if (neighbor != -1 && world.cells[neighbor].state == CellState::Alive)
            aliveNeighbors++;

    // Rules
    // Overpopulation
    if(aliveNeighbors > 3) cell.nextState = CellState::Dead;
    // Reproduction
    if(aliveNeighbors == 2 && cell.state == CellState::Dead) cell.nextState = CellState::Alive;
    // Random
    //if(aliveNeighbors == 0 && cell.state == CellState:: Dead && random()%100 > 90) cell.nextState = CellState::Alive;
}
void tick(World &world)
{
    world.updateTime = world.Time;

    for (Cell& cell: world.cells) findNextState(world, cell);
    for (Cell& cell: world.cells) applyNextState(cell);
}

void update(World &world) {

    // Time
    world.dT = elapsedTime() - world.Time;
    world.Time = elapsedTime();

    if (isMousePressed(SDL_BUTTON_LEFT))
    {
        int x,y; mousePos(x, y);
        Hex hex = Snap(x,y);
        if(isValidCoordinate(hex)) SetState(world,hex.col,hex.row,CellState::Alive);
    }

    // Toggle PlayMode
     world.pauseMode  = isKeyPressed(SDLK_SPACE) ?  !world.pauseMode : -1;

    // Next Button and // Auto Update
    if ((world.pauseMode && isKeyPressed(SDLK_RIGHT)) ||
        (!world.pauseMode && world.Time - world.updateTime > UpdateDelay))
        tick(world);
}



void draw(const World &world, const Cell &cell) {

    // Current Cell
    setColor(Colors[cell.state]);
    polygonFill(GetHexPoints(cell).Vertex, 6);

    // HexGrid
    setColor({0,0,0,255});
    polygon(GetHexPoints(cell).Vertex, 6);

    // Debug : Display Hexagon locations
    if(world.displayHex)
    {
        Complex position = PositionFromHexPosition(cell.location);
        color(255,45,45,255);
        print(position.re + 10,position.im,to_string(cell.location.col).c_str());
        color(45,255,45,255);
        print(position.re - 10,position.im, to_string(cell.location.row).c_str());
    }
}

void draw(const World &system) { for (Cell cell: system.cells) draw(system, cell); }

int main(int, char **) {
    winInit("[Hex Game of Life]", Screen_Size, Screen_Size);
    setKeyRepeatMode(false);
    World world = WorldInit();
    do {
        winClear();
        update(world);
        draw(world);
    } while (!winDisplay());
    winQuit();
}
