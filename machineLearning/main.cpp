#include "common.h"
#include "decision_tree.hpp"

using namespace std;
using namespace ML;

int main(int argc, char ** argv) {
    vector < vector < bool > > train_data = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    vector < bool > train_label = {0, 1, 1, 0};
    DecisionTree <bool, bool> dt;
    dt.unitTest();
    dt.buildTree(train_data, train_label);

    return 0;
}
