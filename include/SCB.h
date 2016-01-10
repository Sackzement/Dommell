#pragma once
#include <Ngin/libs.h>
#include <cstdio>
#include <vector>
using std::vector;

#include <Ngin/window.h>
#include <Ngin/renderer.h>

const char * gameName = "Super Crate Box";

const int resX = 1920,
          resY = 1080,
          aspX = 16,
          aspY = 9;

bool quit = false;



void  separate(vector<uint> &into, uint num);

uint calcBiggestMulti(uint x, uint y);


int startGame(int argc, char** argv);


