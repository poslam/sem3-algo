#pragma once 
#include <vector>
#include <memory>
#include <cmath>

typedef long long llong;

namespace lab2 {
    bool is_2_power(int num);

    class persistent_tree { 
    private:
        struct _node {
            std::shared_ptr<_node> l;
            std::shared_ptr<_node> r;
            int l_ind;
            int r_ind;
            bool is_leaf;
            llong val;
        };
        std::vector<std::shared_ptr<_node>> _roots;

        int _primary_nodes_count;
        int _nodes_count;
        int _height;

        llong _inner_get_sum(std::shared_ptr<_node> cur_node, int l, int r) const;
        std::shared_ptr<_node> _inner_set_elem(std::shared_ptr<_node> cur_node, int leaf_pos, llong val);

    public:
        persistent_tree(std::vector<llong> arr);

        void set_elem(int version, int pos, llong val);
        llong get_elem(int version, int pos) const;
        llong get_sum(int version, int l, int r) const;
    };
}