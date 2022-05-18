#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <numeric>
#include <string>
#include <time.h>
#include <thread>
#include <mutex>

#include "RANDOM.h"


// Typedefs
typedef std::vector<std::vector<std::vector<double>>> Vectormap;
typedef std::vector<std::vector<double>> Map;


// Declaring Functions/Procedured
Map createNoise(int order, int range=10, std::vector<std::string> weights={}, int vector_size=1, int threads = 5);
double getMean(Map map);
Vectormap createVecMap(int order, int vec_size=1);
double dotProduct(std::vector<double> v1, std::vector<double> v2);
Map createEmptyMap(int size, double filler = 1);
Map postProcess(Map map);
Map Slope(int size, int depth = 1);
Map vectorItemMult(Map vec1, Map vec2, double scalar = 1);
bool writeToFile(Map map);
void createNoiseRow(int order, int range, int vector_size, int index[2], Vectormap vec);
