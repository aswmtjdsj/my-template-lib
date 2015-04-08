#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include "common.h"
#include "tree_node.hpp"

using namespace std;

namespace ML {
    // T1 for feature data type
    // T2 for label data type
    template <typename T1, typename T2>
        class DecisionTree {

            public:
                DecisionTree() {
                }

                DecisionTree(const size_t & _ds, const size_t & _fs) {
                    // TODO
                }

                ~DecisionTree() {
                    _features.clear();
                    _dimensions.clear();
                    _labels.clear();
                    _selected.clear();
                }

                // row: ds, col: fs
                void setDataSize(const size_t & _s) {
                    _data_size = _s;
                    _features.reserve(_data_size);
                    _dimensions.reserve(_data_size);
                    _labels.reserve(_data_size);
                }

                void setFeatureSize(const size_t & _s) {
                    _feature_size = _s;
                    _selected = vector < bool > (_feature_size, false);
                }

                void loadFeature(const vector <T1> & _f, const T2 & _l) {
                    _features.push_back(_f);
                    for(size_t _idx = 0; _idx < _feature_size; _idx++) {
                        _dimensions.insert(_f[_idx]);
                    }
                    _labels.push_back(_l);
                }

            private:
                size_t _feature_size, _data_size;
                vector < vector <T1> > _features;
                vector < set <T1> > _dimensions; // dimension of every feature
                vector < T2 > _labels;
                vector < bool > _selected; // has been seleted as branch feature or not
        };
}

#endif
