#include <cassert>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

#include "Grapic.h"

using namespace grapic;
using namespace std;

// Primary Structs

struct Hex { int q, r, s, col,row; };
struct HexVertex { int Vertex[6][2]; };
struct Complex { float re, im; };
struct Color { int r, g, b, a;};

// Settings

const string defaultWorld = "Data/default.txt";
const string defaultSaveName = "Data/world.txt";
const int Screen_Size = 768;
const int CellSize = 24;
const float UpdateDelay = 0.5f;
const Color Colors[]{
        {255,45,255,255},
        {45,255,45,255},
        {25,25,25,255}};

// Constant

const float Sqrt3d2 = 0.866025404f;
const float Sqrt3   = 1.732050807f;
const float Sqrt3d3 = 0.577350269f;
const int VCellCount = Screen_Size / CellSize;
const int HCellCount = Screen_Size / CellSize;
const int MaxRules = 10;

// Enumerations

enum CellState { None, Alive, Dead };
enum HexDir { O = -1, NE, E, SE, SW, W, NW };

// Variable

int menu_selection = 0;

// Complex

Complex mkComplex(float re, float im) { return {re, im}; }
Complex mkComplexExp(float r, float theta_deg) { float theta_rad = theta_deg * M_PI / 180; return {r * cos(theta_rad), r * sin(theta_rad)}; }
Complex operator+(Complex a, Complex b) { return {a.re + b.re, a.im + b.im}; }
Complex operator-(Complex a, Complex b) { return {a.re - b.re, a.im - b.im}; }
Complex operator*(float a, Complex b) { return {b.re * a, b.im * a}; }
Complex operator*(Complex a, float b) { return b * a; }
Complex operator/(Complex a, float b) { return {a.re / b, a.im / b}; }
Complex operator/(Complex a, int b) { return {a.re / b, a.im / b}; }
Complex operator*(Complex a, Complex b) { return {a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re}; }
Complex rotate(Complex a, Complex pivot, float angle_deg) { return (a - pivot) * mkComplexExp(1, angle_deg) + pivot; }
Complex rotate(Complex a, float re, float im, float angle_deg) { return rotate(a, mkComplex(re, im), angle_deg); }
Complex scale(Complex a, Complex b, float lamda) { return (a - b) * lamda + b; }
Complex scale(Complex a, float re, float im, float lamda) { return scale(a, mkComplex(re, im), lamda); }
Complex lerp(Complex a, Complex b, float t) { return (1 - t) * a + t * b; }
Complex normalize(Complex c) { float norm = sqrt(c.re * c.re + c.im * c.im); return mkComplex(c.re / norm, c.im / norm); }

// Interpolation

float lerp(float a, float b, float t) { return (a * (1 - t)) + (b * t); }
int lerp(int a, int b, float t) { return (a * (1 - t)) + (b * t); }
Color lerp(Color a, Color b, float t) { return {lerp(a.r, b.r, t), lerp(a.g, b.g, t), lerp(a.b, b.b, t),lerp(a.a, b.a, t)}; }

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
static Hex Delta(HexDir dir) { switch (dir) { case O:return mkHexPosition(0, 0, 0); case NE:return mkHexPosition(1, -1, 0); case E:return mkHexPosition(1, 0, -1); case SE:return mkHexPosition(0, 1, -1); case SW:return mkHexPosition(-1, 1, 0); case W:return mkHexPosition(-1, 0, 1); case NW:return mkHexPosition(0, -1, 1); } }
static HexDir Opposite(HexDir dir) { switch (dir) { case O:return HexDir::O; case NE:return HexDir::SW; case E:return HexDir::W; case SE:return HexDir::NW; case SW:return HexDir::NE; case W:return HexDir::E; case NW:return HexDir::SE; } }
static Hex operator+(Hex a, HexDir b) { return a + Delta(b); }
static Hex operator-(Hex a, HexDir b) { return a - Delta(b); }
static Hex operator*(Hex a, int k) { return mkHexPosition(a.q * k, a.r * k, a.s * k); }
static Hex HexPositionFromPosition(Complex position) { return Snap(position); }
//static int Length(Hex location) { return (abs(location.q) + abs(location.r) + abs(location.s)) / 2; }
//static int Distance(Hex a, Hex b) { return Length(a - b); }

// Tools

void setColor(Color col) { color(col.r,col.g,col.b,col.a); }

// Game of Life

struct Cell {
    Hex location;
    int neighbors[6];
    CellState previousState,state,nextState;
};

struct World {
    float Time, dT;
    float updateTime;
    bool pauseMode;
    bool isDisplayingHex,isDisplayingGrid;
    Cell cells[VCellCount * HCellCount];
    bool rules[MaxRules];
};

bool isValidCoordinate(int col,int row) { return -1 < col && col < HCellCount && -1 < row && row < VCellCount; }
bool isValidCoordinate(Hex location) {return isValidCoordinate(location.col, location.row);}

Cell mkCell(int col, int row,CellState state) {
    Cell cell{};
    cell.location = mkHexPosition(col, row);
    cell.previousState = CellState::Dead;
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
    N  = position + mkComplex(0,CellSize),
    NW = rotate(N,position,60),
    SW = rotate(N,position,120),
    S  = rotate(N,position,180),
    SE = rotate(N,position,240),
    NE = rotate(N,position,300);
    return {{{N.re,N.im},{NW.re,NW.im},{SW.re,SW.im},{S.re,S.im},{SE.re,SE.im},{NE.re,NE.im},}};
}

void SetState(World& world,int col,int row,CellState state) { if (isValidCoordinate(col, row)) world.cells[col + row * HCellCount].state = state; }

void save(World& world,const string& name) {
    ofstream savedWorld;
    savedWorld.open(name);
    for (Cell &cell: world.cells) savedWorld << cell.state << "\n";
    savedWorld.close();
}

void load(World& world,const string& name) {
    ifstream loadedWorld (name);
    if (loadedWorld.is_open()) {
        int i = 0;
        string line;
        while (getline(loadedWorld, line)) {
            world.cells[i].state = (CellState) std::stoi(line);
            i++;
        }
        loadedWorld.close();
    }
    else cout << "Unable to open file";
}

World WorldInit() {
    std::cout << "HCellCount: " << HCellCount << std::endl;
    std::cout << "VCellCount: " << VCellCount << std::endl;
    World world = {};
    world.Time = 0;
    world.dT = 0;
    world.updateTime = 0;
    world.isDisplayingHex = false;
    world.isDisplayingGrid = true;
    world.pauseMode = true;
    for (int col = 0; col < HCellCount; ++col)
        for (int row = 0; row < VCellCount; ++row)
            world.cells[col + row * HCellCount] = mkCell(col, row, CellState::Dead);

    load(world,defaultWorld);
    return world;
}

void applyNextState(Cell &cell)
{
    cell.previousState = cell.state;
    cell.state = cell.nextState;
    cell.nextState = CellState::Dead;
}

void findNextState(World& world, Cell &cell) {

    int aliveNeighbors = 0;
    for (int &neighbor: cell.neighbors)
        if (neighbor != -1 && world.cells[neighbor].state == CellState::Alive)
            aliveNeighbors++;

    // Rules
    // Random Spawn
    if(world.rules[0]){ if(aliveNeighbors == 0 && cell.state == CellState:: Dead && random()%100 > 50) cell.nextState = CellState::Alive; }
    // Reproduction
    if(world.rules[1]){ if(aliveNeighbors == 2 && cell.state == CellState::Dead) cell.nextState = CellState::Alive; }
    // Overpopulation
    if(world.rules[2]){ if(aliveNeighbors > 5) cell.nextState = CellState::Dead; }
    if(world.rules[3]){}
    if(world.rules[4]){}
    if(world.rules[5]){}
    if(world.rules[6]){}
    if(world.rules[7]){}
    if(world.rules[8]){}
    if(world.rules[9]){}
}

void drawRules(World& world) {
    fontSize(15); setColor({255, 255, 255, 255});
    string rules[] = {
            string("==== Rules ===\n"),
            string("[") + string(world.rules[0] ? "X" : "  ") + string("] 0 Random Spawn\n"),
            string("[") + string(world.rules[1] ? "X" : "  ") + string("] 1 Reproduction\n"),
            string("[") + string(world.rules[2] ? "X" : "  ") + string("] 2 Overpopulation\n")
    };
    for (int i = 0; i < 4; ++i) print(25, Screen_Size - (25 * (i + 1)), rules[i].c_str());
}
void updateRules(World& world)
{
    for (int i = 0; i < MaxRules; ++i)  if(isKeyPressed(SDLK_0 + i)) world.rules[i] = !world.rules[i];
}
void tick(World &world) {
    world.updateTime = world.Time;

    for (Cell &cell: world.cells) findNextState(world, cell);
    for (Cell &cell: world.cells) applyNextState(cell);
}
bool validMousePosition(int x,int y)
{
    return !(x<100 && y<100);
}
void killAllCells(World& world)
{
    for (Cell &cell: world.cells) cell.state = CellState::Dead;
}
void spawnCellAtMousePosition(World& world){
    int x,y; mousePos(x, y);
    if(!validMousePosition(x,y)) return;
    Hex hex = Snap(x,y);
    if(isValidCoordinate(hex)) SetState(world,hex.col,hex.row,CellState::Alive);
}
void killCellAtMousePosition(World& world)
{
    int x,y; mousePos(x, y);
    if(!validMousePosition(x,y)) return;
    Hex hex = Snap(x,y);
    if(isValidCoordinate(hex)) SetState(world,hex.col,hex.row,CellState::Dead);
}


void input(World& world)
{
    if (isMousePressed(SDL_BUTTON_LEFT)) spawnCellAtMousePosition(world);
    if (isMousePressed(SDL_BUTTON_RIGHT)) killCellAtMousePosition(world);
    if (isKeyPressed(SDLK_RETURN)) killAllCells(world);
    if (isKeyPressed(SDLK_SPACE)) world.pauseMode = !world.pauseMode; // Toggle PlayMode
    if (isKeyPressed(SDLK_c)) world.isDisplayingHex = !world.isDisplayingHex; // Toggle HexLocation
    if (isKeyPressed(SDLK_g)) world.isDisplayingGrid = !world.isDisplayingGrid; // Toggle Grid
    if (isKeyPressed(SDLK_s)) save(world,defaultSaveName);
    if (isKeyPressed(SDLK_d)) save(world,defaultWorld);
    if (isKeyPressed(SDLK_l)) load(world,defaultSaveName);

    // Next Button and // Auto Update
    if ((world.pauseMode && isKeyPressed(SDLK_RIGHT)) || (!world.pauseMode && world.Time - world.updateTime > UpdateDelay))
        tick(world);
}
void update(World &world) {

    // Time
    world.dT = elapsedTime() - world.Time;
    world.Time = elapsedTime();

    input(world);
}

void draw(const World &world, const Cell &cell) {

    if (world.pauseMode) setColor(Colors[cell.state]);
    else {
        float t = world.Time * UpdateDelay - floor(world.Time * UpdateDelay);
        setColor(lerp(Colors[cell.previousState], Colors[cell.state], t));
    }

    polygonFill(GetHexPoints(cell).Vertex, 6);

    if(world.isDisplayingGrid)
    {
        setColor({0,0,0,255});
        polygon(GetHexPoints(cell).Vertex, 6);
    }

    if(world.isDisplayingHex)
    {
        Complex position = PositionFromHexPosition(cell.location);
        color(255,45,45,255);
        print(position.re + 10,position.im,to_string(cell.location.col).c_str());
        color(45,255,45,255);
        print(position.re - 10,position.im, to_string(cell.location.row).c_str());
    }
}

void draw(const World &system) { for (Cell cell: system.cells) draw(system, cell); }
void menuInit(Menu& menu)
{
    menu_add(menu,"Save");
    menu_add(menu,"Load");
    menu_add(menu,"Startup");
}
int menuUpdate(World& world,Menu& menu)
{
    int hot_menu_selection = menu_select(menu);
    if(hot_menu_selection != menu_selection)
    {
        menu_selection = hot_menu_selection;
        switch(menu_selection)
        {
            case 0 : save(world,defaultSaveName); break;
            case 1 : load(world,defaultSaveName); break;
            case 2 : load(world,defaultWorld); break;
        }
    }
}
int main(int, char **) {
    winInit("[Hex Game of Life]", Screen_Size, Screen_Size);
    setKeyRepeatMode(false);
    Menu menu;
    menuInit(menu);
    World world = WorldInit();
    do {
        winClear();
        update(world);
        draw(world);
        menuUpdate(world,menu);
        menu_draw(menu);
        updateRules(world);
        drawRules(world);
    } while (!winDisplay());
    winQuit();
}
