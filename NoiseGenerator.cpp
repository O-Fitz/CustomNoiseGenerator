#include "src/include.h"

// Structs def
struct ThreadingStore{
    std::vector<double> row;
    int index;
};

// Gloabls
RANDOM randomGen(time(0));
std::vector<ThreadingStore> threadingstore;
std::mutex myMutex;


// Main function
int main(int argc, char** argv)
{
    std::string str_order = argv[1];
    int order = stoi(str_order);

    std::vector<std::string> weights_list = {};
    Map map = createNoise(order, 20, weights_list, 1, 5);
    //Map map = Slope(order, 20);
    //std::cout << map[0][-1];
    writeToFile(map);
}


// Defining Functions/Procedures
double getMean(Map map) {
    double sum = 0;
    for (auto& x : map) {
        for (auto& y : x) {
            sum += y;
        }
    }
    return sum/(map.size()*map.size());
}

Vectormap createVecMap(int order, int vec_size) {
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
        vec.push_back(dim);
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

Map createEmptyMap(int size, double filler) {
    Map zeromap;
    std::vector<double> row;
    for (int y = 0; y < size; y++) {
        row.push_back(filler);
    }
    for (int x = 0; x < size; x++) {
        zeromap.push_back(row);
    }
    return zeromap;
}

Map postProcess(Map map) {
    double mean = getMean(map);
    Map map2;
    for (int x = 0; x < map.size(); x++) {
        map2.push_back({});
        for (int y = 0; y < map.size(); y++) {
            map2[x].push_back(abs(map[x][y] - mean));
        }
    }
    double max = map[0][0];
    for (auto const & row : map){
        double m = row.max_size();
        if (m > 5*mean){
            m = max;
        }
        else if (m > max){
            max = m;
        }
    }
    for (int x = 0; x<map.size(); x++){
        for (int y = 0; y<map.size(); y++){
            map2[x][y] = map2[x][y]/max;
        }
    }
    
    return map2;
}

Map Slope(int size, int depth) {
    Map map;
    for (int x = 0; x < size; x++) {
        std::vector<double> row;
        for (int y = 0; y < size; y++) {
            double n =  (size-abs(x - double(size)/2) - abs(y - double(size) / 2) / size);
            if (x == 1 && y == 1){
                std::cout << n << std::endl;
                std::cout << abs(x - double(size)/2) << std::endl;
                std::cout << abs(y - double(size) / 2) << std::endl;
                n = size/3;
            }
            row.push_back(n);
        }
        map.push_back(row);
    }
    return map;
}

Map vectorItemMult(Map vec1, Map vec2, double scalar) {
    if (vec1.size() != vec2.size() || vec1[0].size() != vec2[0].size()) {
        std::cout << "vectorItemMult: VECTORS ARENT SAME SIZE\n";
        return createEmptyMap(vec1.size(), 0);
    }
    Map vecproduct = createEmptyMap(vec1.size());
    for (int x = 0; x < vec1.size(); x++) {
        for (int y = 0; y < vec2.size(); y++) {
            vecproduct[x][y] = vec1[x][y] * vec2[x][y] * scalar;
        }
    }
    return vecproduct;
}

Map createNoise(int order, int range, std::vector<std::string> weights, int vector_size, int threads) {

    if (threads > order){
        threads = order;
    }

    Map noise_map = createEmptyMap(order);
    Vectormap vec = createVecMap(order, vector_size);

    double n;

    /*for (int x = 0; x < order; x++) {
        std::vector<double> row;
        for (int y = 0; y < order; y++) {
            n = 0;
            for (int i = -range; i <= range; i++) {
                 for (int j = -range; j <= range; j++) {
                    if (x+i >= order || x+i < 0 || y+j >= order || y+j < 0) {
                        double f1 = randomGen.randomDoubleRange(-vector_size, vector_size);
                        double f2 = sqrt(pow(vector_size, 2) - pow(f1, 2))*randomGen.randomNegative();
                        std::vector<double> f = { f1, f2 };
                        n += vector_size * 0.5 - 1 *dotProduct(f, vec[x][y]);
                    }
                    else{
                        n += vector_size * 0.5 - 1 * dotProduct(vec[x][y], vec[(x+i)][(y+j)]);
                    }
                 }
            }
            row.push_back(n);
        }
        noise_map.push_back(row);
    }*/

    int difference = order / threads;
    int end = order;
    int start = order - difference + 1;
    std::vector<std::thread> thread_list;

    /*for (int i=0; i < threads; i++){
        std::cout << "Thread started: " << i << ", Start: " << start << ", End: " << end << std::endl;
        int index[2] = {start, end};
        thread_list.push_back(std::move(std::thread(createNoiseRow, order, range, vector_size, index, vec)));
        start = end+1;
        end = start+(order/threads);
        if (end > order) {
            end = order;
        }
        
    }*/

    int index[2];

    while (start >= 0) {
        std::cout << "Thread started-> " << ", Start: " << start << ", End: " << end << std::endl;
        index[0] = start;
        index[1] = end;
        thread_list.push_back(std::move(std::thread(createNoiseRow, order, range, vector_size, index, vec)));
        end -= difference;
        start -= difference;
    }
    index[0] = 0;
    index[1] = end;
    thread_list.push_back(std::move(std::thread(createNoiseRow, order, range, vector_size, index, vec)));

    std::cout << "\n-------------\n";
    std::cout << thread_list.size() << " " << threads <<  std::endl;
    for (int th = threads; th >= 0; th--) {
        thread_list[th].join();
        std::cout << thread_list.size() << std::endl;
    }

    for (int i = 0; i<=threads; i++){
        noise_map[threadingstore[i].index] = threadingstore[i].row;
    }

    Map weightmap = createEmptyMap(order, 1.0);
    for (auto& tag : weights) {
        // ADD WEIGHTMAP STATEMENTS HERE:
        if (tag == "SLOPE") {
            weightmap = vectorItemMult(weightmap, Slope(order));
        }
        else {
            std::cout << "Weight map does not exist";
        }
    }
    noise_map = (vectorItemMult(weightmap, noise_map));
    //noise_map = postProcess(noise_map);

    return noise_map;
}


bool writeToFile(Map map) {
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

void createNoiseRow(int order, int range, int vector_size, int index[2], Vectormap vec){
    std::lock_guard<std::mutex> guard(myMutex);
    double n;
    std::vector<double> row;
    ThreadingStore thrd;
    
    for (int x = index[0]; x <= index[1]; x++){
        thrd.index = x;
        for (int y = 0; y < order; y++) {
            n = 0;
            for (int i = -range; i <= range; i++) {
                for (int j = -range; j <= range; j++) {
                    if (x+i >= order || x+i < 0 || y+j >= order || y+j < 0) {
                        double f1 = randomGen.randomDoubleRange(-vector_size, vector_size);
                        double f2 = sqrt(pow(vector_size, 2) - pow(f1, 2))*randomGen.randomNegative();
                        std::vector<double> f = { f1, f2 };
                        n += vector_size * 0.5 - 1 *dotProduct(f, vec[x][y]);
                    }
                    else{
                        n += vector_size * 0.5 - 1 * dotProduct(vec[x][y], vec[(x+i)][(y+j)]);
                    }
                }
            }
            row.push_back(n);
            //std::cout << row << "row\n";
        }
        thrd.row = row;
        threadingstore.push_back(thrd);
    }
    std::cout << "Thread Finished: " << index[0] << " " << index[1] << std::endl;
}
