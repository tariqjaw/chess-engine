#pragma once
#include <stdio.h>
#include <bitset>
#include <iostream>
#include "types.hpp"


class HashKey {
  private:
    U64 piece_keys[13][60];
    U64 castle_keys[16];
    U64 side_key;
  public:
    HashKey();
    U64 Rand64();
    U64 PositionKey(Board b);

};
