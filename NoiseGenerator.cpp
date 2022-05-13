#include "src/include.h"

RANDOM randomGen(time(0));


struct Vectormap {
    std::vector<std::vector<std::vector<double>>> vectormap;
};


double getMean(std::vector<std::vector<double>> map) {
    double sum = 0;
    for (auto& x : map) {
        for (auto& y : x) {
            sum += y;
        }
    }
    return sum/(map.size()*map.size());
}

Vectormap createVecMap(int order, int vec_size=1) {
    Vectormap vec;
    RANDOM randomGen(time(0));
    for (int x = 0; x < order; x++) {
        std::vector<std::vector<double>> dim;
        for (int y = 0; y < order; y++) {
            double f1 = randomGen.randomDoubleRange(-vec_size, vec_size);
            double f2 = sqrt(pow(vec_size, 2)-pow(f1, 2))*randomGen.randomNegative();
            std::vector<double> f = { f1, f2 };
            dim.push_back(f);
        }
        vec.vectormap.push_back(dim);
    }
    return vec;
}

double dotProduct(std::vector<double> v1, std::vector<double> v2) {
    if (v1.size() != v2.size()) {
        throw std::invalid_argument("v1 and v2 must be the same size");
    }
    double sum = 0;
    for (unsigned int i = 0; i < v1.size(); i++) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

std::vector<std::vector<double>> createEmptyMap(int size, double filler = 1) {
    std::vector<std::vector<double>> zeromap;
    std::vector<double> row;
    for (int y = 0; y < size; y++) {
        row.push_back(filler);
    }
    for (int x = 0; x < size; x++) {
        zeromap.push_back(row);
    }
    return zeromap;
}

std::vector<std::vector<double>> postProcess(std::vector<std::vector<double>> map) {
    double mean = getMean(map);
    std::cout << mean << std::endl;
    std::vector<std::vector<double>> map2;
    for (int x = 0; x < map.size(); x++) {
        map2.push_back({});
        for (int y = 0; y < map.size(); y++) {
            map2[x].push_back(abs(map[x][y] - mean));
        }
    }
    double max = map[0][0];
    //std::cout << max << std::endl;
    for (auto const & row : map){
        double m = row.max_size();
        if (m > 5*mean){
            m == max;
        }
        else if (m > max){
            //std::cout << m;
            max = m;
        }
    }
    std::cout << max << std::endl;
    for (int x = 0; x<map.size(); x++){
        for (int y = 0; y<map.size(); y++){
            map2[x][y] = map2[x][y]/max;
        }
    }
    
    return map2;
}

std::vector<std::vector<double>> Slope(int size, int depth = 1) {
    std::vector<std::vector<double>> map;
    for (int x = 0; x < size; x++) {
        std::vector<double> row;
        for (int y = 0; y < size; y++) {
            double n =  (size-abs(x - double(size)/2) - abs(y - double(size) / 2) / size);
            //std::cout << x << " " << y << " " << n << std::endl;
           row.push_back(n);
        }
        map.push_back(row);
    }
    return map;
}

std::vector<std::vector<double>> vectorItemMult(std::vector<std::vector<double>> vec1, std::vector<std::vector<double>> vec2, double scalar = 1) {
    if (vec1.size() != vec2.size() || vec1[0].size() != vec2[0].size()) {
        std::cout << "VECTORS ARENT SAME SIZE";
        return createEmptyMap(vec1.size(), 0);
    }
    std::vector<std::vector<double>> vecproduct = createEmptyMap(vec1.size());
    for (int x = 0; x < vec1.size(); x++) {
        for (int y = 0; y < vec2.size(); y++) {
            vecproduct[x][y] = vec1[x][y] * vec2[x][y] * scalar;
        }
    }
    return vecproduct;
}

std::vector<std::vector<double>> createNoise(int order, int range = 10, std::vector<std::string> weights = {}, int vector_size = 1) {
    std::vector<std::vector<double>> noise_map;
    Vectormap vec = createVecMap(order, vector_size);

    double n;

    for (int x = 0; x < order; x++) {
        std::vector<double> row;
        for (int y = 0; y < order; y++) {
            n = 0;
            for (int i = -range; i <= range; i++) {
                for (int j = -range; j <= range; j++) {
                    if (x+i >= order || x+i < 0 || y+j >= order || y+j < 0) {
                        double f1 = randomGen.randomDoubleRange(-vector_size, vector_size);
                        double f2 = sqrt(pow(vector_size, 2) - pow(f1, 2))*randomGen.randomNegative();
                        std::vector<double> f = { f1, f2 };
                        n += vector_size * 0.5 - 1 *dotProduct(f, vec.vectormap[x][y]);
                    }
                    else{
                        n += vector_size * 0.5 - 1 * dotProduct(vec.vectormap[x][y], vec.vectormap[(x+i)][(y+j)]);
                    }
                }
            }
            row.push_back(n);
        }
        noise_map.push_back(row);
    }
    std::vector<std::vector<double>> weightmap = createEmptyMap(order, 1.0);
    for (auto& i : weights) {
        if (i == "SLOPE") {
            weightmap = vectorItemMult(weightmap, Slope(order));
        }
        else {
            std::cout << "Weight map does not exist";
        }
    }
    noise_map = (vectorItemMult(weightmap, noise_map));
    noise_map = postProcess(noise_map);

    return noise_map;
    //return Slope(order);
}



bool writeToFile(std::vector<std::vector<double>> map) {
    std::ofstream file;
    file.open("field.txt");
    file << map.size() << "\n";
    if (file.is_open()) {
        for (auto& x : map) {
            for (auto& y : x) {
                file << y << "\n";
            }
        }
        file.close();
        return true;
    }
    return false;
}

int main(int argc, char** argv)
{
    

    std::string str_order = argv[1];

    //std::cout << str_order << std::endl;

    int order = stoi(str_order);
    //int order = 5;

    Vectormap v = createVecMap(order);
    std::vector<std::string> weights = { "SLOPE" };
    std::vector<std::vector<double>> map = createNoise(order, 20);
    writeToFile(map);
}

