#pragma once
#include <Ngin/libs.h>
#include <cstdio>
#include <vector>
using std::vector;

typedef unsigned int uint;

#include <Ngin/Window.h>
#include <Ngin/Renderer.h>

static const char * gameName = "Super Crate Box";

static const int resX = 1920,
          resY = 1080,
          aspX = 16,
          aspY = 9;

static Window win;
static Renderer ren;

static bool quit = false;



void  separate(vector<uint> &into, uint num);

uint calcBiggestMulti(uint x, uint y);


int startGame(int argc, char** argv);


