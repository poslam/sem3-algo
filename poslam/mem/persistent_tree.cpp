#include "persistent_tree.h"

typedef long long llong;

namespace lab2 {
    bool is_2_power(int num) {
        return num & (num - 1) == 0;
    }

    llong persistent_tree::_inner_get_sum(std::shared_ptr<_node> cur_node, int l_ind, int r_ind) const {
        if(cur_node->l_ind - cur_node->r_ind > 0) {
            return 0;
        }
        else if(cur_node->l_ind == l_ind && cur_node->r_ind == r_ind) {
            return cur_node->val;
        }
        else {
            if(!cur_node->is_leaf) {
                llong l_sum = _inner_get_sum(cur_node->l, std::max(cur_node->l->l_ind, l_ind), std::min(cur_node->l->r_ind, r_ind));
                llong r_sum = _inner_get_sum(cur_node->r, std::max(cur_node->r->l_ind, l_ind), std::min(cur_node->r->r_ind, r_ind));
                return l_sum + r_sum;
            }
            else {
                return 0;
            }
        }
    }

    std::shared_ptr<persistent_tree::_node> persistent_tree::_inner_set_elem(std::shared_ptr<_node> cur_node, int leaf_pos, llong val) {
        if(cur_node->is_leaf) {
            std::shared_ptr<_node> new_node = std::make_shared<_node>(_node({nullptr, nullptr, leaf_pos, leaf_pos, true, val}));
            return new_node;
        }
        else {
            std::shared_ptr<_node> l_node;
            std::shared_ptr<_node> r_node;
            if(leaf_pos <= cur_node->l->r_ind) {
                l_node = _inner_set_elem(cur_node->l, leaf_pos, val);
                r_node = cur_node->r;
            }
            else {
                l_node = cur_node->l;
                r_node = _inner_set_elem(cur_node->r, leaf_pos, val);
            }
            llong val = l_node->val + r_node->val;
            std::shared_ptr<_node> new_node = 
                std::make_shared<_node>(_node({l_node, r_node, cur_node->l_ind, cur_node->r_ind, false, val}));
            return new_node;
        }
    }

    persistent_tree::persistent_tree(std::vector<llong> arr) {
        int nodes_count;

        if(!is_2_power(arr.size())) {
            double log2 = std::log2(arr.size());
            nodes_count = static_cast<int>(std::pow(2, std::ceil(log2)));
        }
        else {
            nodes_count = arr.size();
        }

        _primary_nodes_count = nodes_count;
        _nodes_count = nodes_count * 2 - 1;
        _height = static_cast<int>(log2(_nodes_count + 1));

        std::vector<std::shared_ptr<_node>> layer1;
        std::vector<std::shared_ptr<_node>> layer2;

        std::shared_ptr<std::vector<std::shared_ptr<_node>>> cur_layer;
        std::shared_ptr<std::vector<std::shared_ptr<_node>>> prev_layer;

        cur_layer = std::make_shared<std::vector<std::shared_ptr<_node>>>(layer1);
        prev_layer = std::make_shared<std::vector<std::shared_ptr<_node>>>(layer2);

        for(int i = 0; i < nodes_count; i++) {
            llong val = i < arr.size() ? arr[i] : 0;
            cur_layer->push_back(std::make_shared<_node>(_node({nullptr, nullptr, i, i, true, val})));
        }

        cur_layer.swap(prev_layer);

        for(; prev_layer->size() != 1;) {
            for(int i = 0; i < prev_layer->size() / 2; i++) {
                std::shared_ptr<_node> l = (*prev_layer)[2 * i];
                std::shared_ptr<_node> r = (*prev_layer)[2 * i + 1];
                llong val = l->val + r->val;
                int l_ind = l->l_ind;
                int r_ind = r->r_ind;
                cur_layer->push_back(std::make_shared<_node>(_node({l, r, l_ind, r_ind, false, val})));
            }
            cur_layer.swap(prev_layer);
            cur_layer->clear();
        }

        _roots.push_back((*prev_layer)[0]);
    }

    void persistent_tree::set_elem(int version, int pos, llong val) {
        _roots.push_back(_inner_set_elem(_roots[version], pos, val));
    }

    llong persistent_tree::get_elem(int version, int pos) const {
        return get_sum(version, pos, pos);
    }

    llong persistent_tree::get_sum(int version, int l, int r) const {
        return _inner_get_sum(_roots[version], l, r);
    }
}
