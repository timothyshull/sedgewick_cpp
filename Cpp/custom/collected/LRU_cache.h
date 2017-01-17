#ifndef COLLECTED_LRU_CACHE_H
#define COLLECTED_LRU_CACHE_H

#include <vector>

template<typename N, typename V>
class LRU_cache {
private:
    std::vector<V> oa;
    std::size_t size;

public:
    explicit LRU_cache(int var1) : size_t{static_cast<size_t>(var1)} {}

    LRU_cache() = delete;

    virtual V create(N& var1);

    // TODO: ?
    virtual bool has_name(V& var1, N& var2);

    template<typename T>
    static void move_to_front(std::vector<T>& vec, int front_index)
    {
        T tmp = vec[front_index];
        for (int i = front_index; i > 0; --i) {
            vec[i] = vec[i - 1];
        }
        vec[0] = tmp;
    }

    V& for_name(N& var1)
    {
        if (oa.empty()) {
            oa.resize(size);
        } else {
            for (int i = 0; i < oa.size(); i++) {
                V& tmp = oa[i];
                if (tmp && has_name(tmp, var1)) {
                    if (i > 0) {
                        move_to_front(oa, i);
                    }
                    return tmp;
                }
            }
        }

        V var5 = create(var1);
        // TODO: may not be necessary with std::vector
        oa[oa.size() - 1] = var5;
        int index = static_cast<int>(oa.size() - 1);
        move_to_front(oa, index);
        return var5;
    }
};

#endif //COLLECTED_LRU_CACHE_H
