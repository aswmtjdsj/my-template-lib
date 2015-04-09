#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "common.h"

using namespace std;

namespace ML {
    typedef enum {UIN, AIS, AOS, MIG} node_type;
    // un-initialized, all input the same, all output the same, maximum information gain -> size_ternal nodes

    template <typename T>
        class TreeNode {
            public:

                TreeNode() {
                    _node_type = UIN;
                    _feature_id = -1;
                    _values.clear();
                    _num_of_instances = 0;
                }

                void addChild(const TreeNode <T> & child, const T & value) {
                    _children.push_back(child);
                    _values.push_back(value);
                }

                void setFeatureId(const size_t & id) {
                    _feature_id = id;
                }

                void setNodeType(const node_type & type) {
                    _node_type = type;
                }

                void setNumInstances(const size_t & num) {
                    _num_of_instances = num;
                }

                vector < TreeNode < T > > getChildren() {
                    return _children;
                }

                size_t getFeatureId() {
                    return _feature_id;
                }

                vector < T > getValues() {
                    return _values;
                }

                node_type getNodeType() {
                    return _node_type;
                }

                size_t getNumInstances() {
                    return _num_of_instances;
                }

            private:
                vector < TreeNode < T > > _children;
                size_t _feature_id;
                node_type _node_type;
                vector < T > _values; // discrete split
                size_t _num_of_instances;
        };
}

#endif
