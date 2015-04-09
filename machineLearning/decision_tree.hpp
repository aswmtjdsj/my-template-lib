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
                    cerr << _root.getNumInstances() << endl;
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

                    // label->size: data size
                    // select->size: feature size

                    // related instance number
                    temp.setNumInstances(label_set.size());
                    
                    // check input 
                    bool feature_the_same = true;
                    for(size_t fdx = 0; fdx < selected.size(); fdx++) {
                        if(selected[fdx] != false) {
                            set < T1 > cur_values;
                            for(size_t ddx = 0; ddx < label_set.size(); ddx++) {
                                cur_values.insert(feature_set[ddx][fdx]);
                            }
                            if(cur_values.size() != 1) {
                                feature_the_same = false;
                            }
                        }
                    }

                    // all features have the same value
                    if(feature_the_same) {
                        temp.setNodeType(AIS);
                        return temp;
                    }

                    // check output
                    set < T2 > output_set;
                    for(size_t ddx = 0; ddx < label_set.size(); ddx++) { // maybe wrong
                        output_set.insert(label_set[ddx]);
                    }

                    // labels are the same
                    if(output_set.size() == 1) {
                        temp.setNodeType(AOS);
                        return temp;
                    }

                    temp.setNodeType(MIG);
                    // find maximum information gain
                    int best_feature = -1;
                    for(size_t fdx = 0; fdx < selected.size(); fdx++) {
                        if(selected[fdx] != false) {
                            // TODO
                        }
                    }

                    // split
                    temp.setFeatureId(best_feature);

                    // choose branches (discrete)
                    set < T1 > values_of_feature;
                    for(size_t ddx = 0; ddx < label_set.size(); ddx++) {
                        values_of_feature.insert(feature_set[ddx][best_feature]);
                    }

                    selected[best_feature] = true;
                    for(auto v: values_of_feature) {
                        vector < vector <T1> > children_feature_set;
                        vector < T2 > children_label_set;
                        for(size_t ddx = 0; ddx < label_set.size(); ddx++) {
                            if(feature_set[ddx][best_feature] == v) {
                                children_feature_set.push_back(feature_set[ddx]);
                                children_label_set.push_back(label_set[ddx]);
                            }
                        }
                        temp.addChild(_build(children_feature_set, children_label_set, selected), v);
                    }

                    return temp;
                }

                TreeNode < T1 > _root;
        };
}

#endif
