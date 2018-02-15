#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>


#include "h/bitlib.h"

using namespace std;

#include "h/lfsr.h"

/*
 * usage: lfsr <size> <taps> <seed> <output>
 */

struct parms {
  bool valid;
  int size;
  int output;
  int seed;
  vector<int> taps;
};

struct parms parse(int argc, char * argv[]) {
  struct parms p;
  char * pch;

  if (argc != 4) {
    cout << argv[0] << " takes 3 positional arguments" << endl;
    cout << argv[0] << " <taps> <seed> <output>" << endl;
    p.valid = false;
    return p;
  }

  // taps and register size
  pch = strtok(argv[1], ",");
  while(pch != NULL) {
    p.taps.push_back(stoi(pch));
    pch = strtok(NULL, ",");
  }
  sort(p.taps.begin(), p.taps.end());
  p.size = p.taps[p.taps.size() - 1];

  p.seed = stoi(argv[2]);
  p.output = stoi(argv[3]);

  return p;
}

int main(int argc, char* argv[]) {
  struct parms p = parse(argc, argv);
  lfsr reg(p.size, p.seed);
  reg.set_taps(p.taps);
  
  cout << " --- debug information ---" << endl;
  cout << "register size: " << p.size << endl;
  cout << " taps: " << endl;
  for (int i = 0; i < p.taps.size() ; i++)
    cout << p.taps[i] << endl;
  cout << "seed: " << p.seed << endl;
  cout << "output bits: " << p.output << endl;

  int i = p.output;
  while (i > 64) {
    cout << hex << reg.generate(64);
    i -= 64;
  }

  cout << hex << reg.generate(i);
  cout << endl;

  return 0;
}
