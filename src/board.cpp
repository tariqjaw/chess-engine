#pragma once
#include <stdio.h>
#include <iostream>
#include "board.hpp"

Board::~Board(){
  delete bitboard;
}
