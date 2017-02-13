#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <stack>
#include <iostream>

template<typename Item_type>
class Stack : public std::deque<Item_type> {
public:
    Stack(std::size_t capacity) : std::deque{capacity} {}

    // inline bool is_full() const { return size() == max_size(); }

    inline void push(Item_type& item) { push_back(item); }

    inline void push(Item_type&& item) { push_back(item); }

    Item_type pop() { return pop_back(); }
};

template<typename Item_type>
inline void show_movement(Item_type disk, std::string& from, std::string& to) { std::cout << "Moving the disk " << disk << " from " << from << " to " << to << "\n"; }

template<typename Item_type>
void shift(Stack<Item_type>& src, Stack<Item_type>& dest, std::string& s_label, std::string& d_label)
{
    if (src.empty()) {
        show_movement(dest.back(), d_label, s_label);
        src.push(dest.pop());
    } else if (dest.empty()) {
        show_movement(src.back(), s_label, d_label);
        dest.push(src.pop());
    } else if (src.back() > dest.back()) {
        show_movement(dest.back(), d_label, s_label);
        src.push(dest.pop());
    } else {
        show_movement(src.back(), s_label, d_label);
        dest.push(src.pop());
    }
}

template<typename Item_type>
void iterative_towers_of_hanoi(std::size_t num_disks, Stack<Item_type>& src, Stack<Item_type>& aux, Stack<Item_type>& dest)
{
    int i;
    int moves;
    std::string s_label{"source stack"};
    std::string d_label{"destination stack"};
    std::string a_label{"auxiliary stack"};

    if (num_disks % 2 == 0) {
        std::string tmp{d_label};
        d_label = a_label;
        a_label = tmp;
    }
    moves = static_cast<int>(std::pow(2, num_disks) - 1);

    for (i = static_cast<int>(num_disks); i >= 1; --i) {
        src.push(i);
    }

    for (i = 1; i <= moves; ++i) {
        if (i % 3 == 1) {
            shift(src, dest, s_label, d_label);
        } else if (i % 3 == 2) {
            shift(src, aux, s_label, a_label);
        } else if (i % 3 == 0) {
            shift(aux, dest, a_label, d_label);
        }
    }
}

int main()
{
    std::size_t num_disks{3};

    Stack src{num_disks};
    Stack dest{num_disks};
    Stack aux{num_disks};

    iterative_towers_of_hanoi(num_disks, src, aux, dest);
    return 0;
}