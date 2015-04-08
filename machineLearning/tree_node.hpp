#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "common.h"

using namespace std;

namespace ML {
    typedef enum {UIN, AIS, AOS, MIG} node_type;
    // unsize_tialized, all input the same, all output the same, maximum information gain -> size_ternal nodes

    template <typename T>
        class TreeNode {
            public:

                TreeNode() {
                    _node_type = UIN;
                    _feature_id = -1;
                    _values.clear();
                    _children.clear();
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

                void addInstance(const size_t & id) {
                    _instance_ids.push_back(id);
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

                vector < size_t > getInstanceIds() {
                    return _instance_ids;
                }

            private:
                vector < TreeNode < T > > _children;
                size_t _feature_id;
                node_type _node_type;
                vector < T > _values; // discrete split
                vector < size_t > _instance_ids;
        };
}

#endif
