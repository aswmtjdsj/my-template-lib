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
#ifdef DEBUG
                    for(auto d: feature_set) {
                        for(auto f: d) {
                            cerr << f << ", ";
                        } cerr << endl;
                    }
#endif

                    // label->size: data size
                    // select->size: feature size

                    // related instance number
                    temp.setNumInstances(label_set.size());
                    
                    // check input 
                    bool feature_the_same = true;
                    for(size_t fdx = 0; fdx < selected.size(); fdx++) {
                        if(selected[fdx] == false) {
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

                    // find maximum information gain
                    temp.setNodeType(MIG);

                    map < T1, int > count_label;
                    for(auto l: label_set) {
                        count_label[l]++;
                    }

                    // H(Y) = - sigma(p(y) * log(p(y))
                    double h_y = 0;
                    for(auto c: count_label) {
                        double p = c.second * 1. / label_set.size();
                        h_y += p * log(p);
                    }
                    h_y = - h_y;

#ifdef DEBUG
                    cerr << "H(Y): " << h_y << endl;
#endif

                    int best_feature = -1;
                    double best_ig = -1.;
                    for(size_t fdx = 0; fdx < selected.size(); fdx++) {
                        if(selected[fdx] == false) {
                            // TODO
                            // IG(Xi) = H(Y) - H(Y|Xi)
                            // H(Y) = - sigma(p(y) * log(p(y))
                            // H(Y|Xi) = sigma(p(xij) * H(Y|xij))
                            // = sigma(p(xij) * [- sigma(p(y|xij) * log(p(y|xij)))]
                            // = -sigma"y, xij"(p(xij, y) * log(p(y|xij)))
                            // = -sigma"y, xij"(p(xij, y) * log(p(xij, y)/p(xij)))
                            map < T1, map < T2, int > > count_value_with_label;
                            for(size_t ddx = 0; ddx < label_set.size(); ddx++) {
                                count_value_with_label[feature_set[fdx][ddx]][label_set[ddx]]++;
                            }
                            double h_y_x = 0.;
                            for(auto x: count_value_with_label) {
                                double p_x_with_no_fraction = x.second.size() * 1.;
                                for(auto x_y: x.second) {
                                    double p_x_y_w_n_f = x_y.second * 1. / label_set.size();
                                    h_y_x += p_x_y_w_n_f * log(p_x_y_w_n_f / p_x_with_no_fraction);
                                }
                            }
                            h_y_x = - h_y_x;
                            double ig = h_y - h_y_x;
#ifdef DEBUG
                            cerr << "IG: " << h_y << endl;
#endif
                            if(best_ig < ig) {
                                best_ig = ig;
                                best_feature = fdx;
                            }
                        }
                    }

                    assert(best_feature != -1);
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
