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

                ~DecisionTree() {
                }

                // discrete features
                // vs continuous features
                void buildTree(const vector < vector <T1> > & feature_set, const vector < T2 > & label_set) {
                    // row: ds, col: fs
                    size_t data_size, feature_size; 
                    vector < bool > selected; // has been selected as branch feature or not

                    data_size = feature_set.size();
                    assert(data_size > 0);
                    feature_size = feature_set[0].size();
                    selected.resize(feature_size, false);

                    // build tree
                    _root = _build(feature_set, label_set, selected);
#ifdef DEBUG
                    cerr << _root.getNodeType() << endl;
                    cerr << _root.getFeatureId() << endl;
#endif

                }
#ifdef DEBUG
                void unitTest() {
                    cerr << "Bahhh!" << endl;
                }
#endif

            private:

                TreeNode < T1 > _build(const vector < vector <T1> > & feature_set, const vector < T2 > & label_set, vector < bool > & selected) {
                    TreeNode < T1 > temp;
                    
                    // check input 
                    // check output
                    set < T2 > output_set;
                    for(size_t fdx = 0; fdx < selected.size(); fdx++) { // maybe wrong
                        if(selected[fdx] != false) {
                            temp.addInstance(fdx);
                            // output_set.insert(label_set[fdx]);
                        }
                    }
                    if(output_set.size() == 0) {
                        // TODO
                        temp.setNodeType(AOS);
                    }
                    // find maximum information gain

                    return temp;
                }

                TreeNode < T1 > _root;
        };
}

#endif
