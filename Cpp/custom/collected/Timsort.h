#ifndef TIMSORT_H
#define TIMSORT_H

#include <vector>
#include <sstream>
#include "Mergesort.h"

// TODO: fix compare calls here
template<typename T, typename Comparator = std::less<T>>
class TimSort {
public:
    void sort(std::vector<T> a)
    {
        sort(a, 0, a.size());
    }

    void sort(std::vector<T> a, int lo, int hi)
    {
        if (std::is_same<Comparator, void>::value) {
            // uses a legacy mergesort in Java
            // Mergesort::sort(a, lo, hi); // TODO: fix
            Mergesort::sort(a);
            return;
        }
        _range_check(a.size(), lo, hi);
        int n_remaining = hi - lo;
        if (n_remaining < 2) {
            return;
        }

        if (n_remaining < _min_merge) {
            int init_run_length = _count_run_and_make_ascending(a, lo, hi, _comparator);
            _binary_sort(a, lo, hi, lo + init_run_length, _comparator);
            return;
        }

        TimSort<T> ts{a};
        int min_run = _min_run_length(n_remaining);
        do {
            int run_length = _count_run_and_make_ascending(a, lo, hi, _comparator);

            if (run_length < min_run) {
                int force = n_remaining <= min_run ? n_remaining : min_run;
                _binary_sort(a, lo, lo + force, lo + run_length, _comparator);
                run_length = force;
            }

            ts._push_run(lo, run_length);
            ts._merge_collapse();

            lo += run_length;
            n_remaining -= run_length;
        } while (n_remaining != 0);

        if (_debug) { utility::assert(lo == hi, ""); }
        ts._merge_force_collapse();
        if (_debug) { utility::assert(ts._stack_size == 1, ""); }
    }

private:
    static const int _min_merge = 32;
    const std::vector<T> a;
    const Comparator<T> _comparator;
    static const int _initial_min_gallop = 7;
    int _min_gallop = _initial_min_gallop;
    static const int _initial_tmp_storage_size = 256;
    std::vector<T> _tmp;
    int _stack_size = 0;  // Number of pending runs on stack
    // const std::vector<int> _run_base;
    std::vector<int> _run_base;
    // const std::vector<int> _run_length;
    std::vector<int> _run_length;
//    static const bool _debug = false; -> to get rid of inspection
    static bool _debug = false;

    TimSort(std::vector<T>& a) : a{a}, _comparator{}
    {
        auto length = a.size();
        _tmp.reserve(length < 2 * _initial_tmp_storage_size ? length >> 1 : _initial_tmp_storage_size);
        auto stack_length = (length < 120 ? 5 : length < 1542 ? 10 : length < 119151 ? 19 : 40);
        _run_base.reserve(stack_length);
        _run_length.reserve(stack_length);
    }

    void _binary_sort(std::vector<T> a, int lo, int hi, int start, Comparator<T> c)
    {
        if (_debug) { utility::assert(lo <= start && start <= hi, ""); }
        if (start == lo) {
            ++start;
        }
        for (; start < hi; ++start) {
            T pivot = a[start];

            int left = lo;
            int right = start;
            if (_debug) { utility::assert(left <= right, ""); }

            while (left < right) {
                int mid = (left + right) >> 1;
                if (c.compare(pivot, a[mid]) < 0) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }
            if (_debug) { utility::assert(left == right, ""); }
            int n = start - left;

            switch (n) {
                case 2:
                    a[left + 2] = a[left + 1];
                case 1:
                    a[left + 1] = a[left];
                    break;
                default:
                    std::copy_n(a.begin() + left, n, a.begin() + left + 1);
            }
            a[left] = pivot;
        }
    }

    int _count_run_and_make_ascending(std::vector<T> a, int lo, int hi, Comparator<T> c)
    {
        if (_debug) { utility::assert(lo < hi, ""); }
        int run_hi = lo + 1;
        if (run_hi == hi) {
            return 1;
        }

        if (c.compare(a[run_hi++], a[lo]) < 0) {
            while (run_hi < hi && c.compare(a[run_hi], a[run_hi - 1]) < 0) {
                ++run_hi;
            }
            _reverse_range(a, lo, run_hi);
        } else {
            while (run_hi < hi && c.compare(a[run_hi], a[run_hi - 1]) >= 0) {
                ++run_hi;
            }
        }
        return run_hi - lo;
    }

    static void _reverse_range(std::vector<T>& a, int lo, int hi)
    {
        hi--;
        while (lo < hi) {
            T t = a[lo];
            a[lo++] = a[hi];
            a[hi--] = t;
        }
    }

    static int _min_run_length(int n)
    {
        if (_debug) { utility::assert(n >= 0, ""); }
        int r = 0;
        while (n >= _min_merge) {
            r |= (n & 1);
            n >>= 1;
        }
        return n + r;
    }

    void _push_run(int rb, int rl)
    {
        _run_base[_stack_size] = rb;
        _run_length[_stack_size] = rl;
        ++_stack_size;
    }

    void _merge_collapse()
    {
        while (_stack_size > 1) {
            int n = _stack_size - 2;
            if (n > 0 && _run_length[n - 1] <= _run_length[n] + _run_length[n + 1]) {
                if (_run_length[n - 1] < _run_length[n + 1]) {
                    n--;
                }
                _merge_at(n);
            } else if (_run_length[n] <= _run_length[n + 1]) {
                _merge_at(n);
            } else {
                break;
            }
        }
    }

    void _merge_force_collapse()
    {
        while (_stack_size > 1) {
            int n = _stack_size - 2;
            if (n > 0 && _run_length[n - 1] < _run_length[n + 1]) {
                n--;
            }
            _merge_at(n);
        }
    }

    void _merge_at(int i)
    {
        if (_debug) { utility::assert(_stack_size >= 2, ""); }
        if (_debug) { utility::assert(i >= 0, ""); }
        if (_debug) { utility::assert(i == _stack_size - 2 || i == _stack_size - 3, ""); }
        int base1 = _run_base[i];
        int len1 = _run_length[i];
        int base2 = _run_base[i + 1];
        int len2 = _run_length[i + 1];
        if (_debug) { utility::assert(len1 > 0 && len2 > 0, ""); }
        if (_debug) { utility::assert(base1 + len1 == base2, ""); }
        _run_length[i] = len1 + len2;
        if (i == _stack_size - 3) {
            _run_base[i + 1] = _run_base[i + 2];
            _run_length[i + 1] = _run_length[i + 2];
        }
        _stack_size--;
        int k = _gallop_right(a[base2], a, base1, len1, 0, _comparator);
        if (_debug) { utility::assert(k >= 0, ""); }
        base1 += k;
        len1 -= k;
        if (len1 == 0) {
            return;
        }
        len2 = _gallop_left(a[base1 + len1 - 1], a, base2, len2, len2 - 1, _comparator);
        if (_debug) { utility::assert(len2 >= 0, ""); }
        if (len2 == 0) {
            return;
        }

        if (len1 <= len2) {
            _merge_lo(base1, len1, base2, len2);
        } else {
            _merge_hi(base1, len1, base2, len2);
        }
    }

    int _gallop_left(T key, std::vector<T> a, int base, int length, int hint, Comparator<T> c)
    {
        if (_debug) { utility::assert(length > 0 && hint >= 0 && hint < length, ""); }
        int last_of_s = 0;
        int ofs = 1;
        if (c.compare(key, a[base + hint]) > 0) {

            int max_of_s = length - hint;
            while (ofs < max_of_s && c.compare(key, a[base + hint + ofs]) > 0) {
                last_of_s = ofs;
                ofs = (ofs << 1) + 1;
                if (ofs <= 0) {
                    ofs = max_of_s;
                }
            }
            if (ofs > max_of_s) {
                ofs = max_of_s;
            }

            last_of_s += hint;
            ofs += hint;
        } else {

            const int max_of_s = hint + 1;
            while (ofs < max_of_s && c.compare(key, a[base + hint - ofs]) <= 0) {
                last_of_s = ofs;
                ofs = (ofs << 1) + 1;
                if (ofs <= 0) {
                    ofs = max_of_s;
                }
            }
            if (ofs > max_of_s) {
                ofs = max_of_s;
            }

            int tmp = last_of_s;
            last_of_s = hint - ofs;
            ofs = hint - tmp;
        }
        if (_debug) { utility::assert(-1 <= last_of_s && last_of_s < ofs && ofs <= length, ""); }

        ++last_of_s;
        while (last_of_s < ofs) {
            int m = last_of_s + ((ofs - last_of_s) >> 1);
            if (c.compare(key, a[base + m]) > 0) {
                last_of_s = m + 1;  // a[base + m] < key
            } else {
                ofs = m;
            }          // key <= a[base + m]
        }
        if (_debug) { utility::assert(last_of_s == ofs, ""); }    // so a[base + ofs - 1] < key <= a[base + ofs]
        return ofs;
    }

    int _gallop_right(T key, std::vector<T> a, int base, int length, int hint, Comparator<T> c)
    {
        if (_debug) { utility::assert(length > 0 && hint >= 0 && hint < length, ""); }
        int ofs = 1;
        int last_of_s = 0;
        if (c.compare(key, a[base + hint]) < 0) {

            int max_of_s = hint + 1;
            while (ofs < max_of_s && c.compare(key, a[base + hint - ofs]) < 0) {
                last_of_s = ofs;
                ofs = (ofs << 1) + 1;
                if (ofs <= 0) {
                    ofs = max_of_s;
                }
            }
            if (ofs > max_of_s) {
                ofs = max_of_s;
            }

            int tmp = last_of_s;
            last_of_s = hint - ofs;
            ofs = hint - tmp;
        } else {

            int max_of_s = length - hint;
            while (ofs < max_of_s && c.compare(key, a[base + hint + ofs]) >= 0) {
                last_of_s = ofs;
                ofs = (ofs << 1) + 1;
                if (ofs <= 0) {
                    ofs = max_of_s;
                }
            }
            if (ofs > max_of_s) {
                ofs = max_of_s;
            }

            last_of_s += hint;
            ofs += hint;
        }
        if (_debug) { utility::assert(-1 <= last_of_s && last_of_s < ofs && ofs <= length, ""); }
        ++last_of_s;
        while (last_of_s < ofs) {
            int m = last_of_s + ((ofs - last_of_s) >> 1);
            if (c.compare(key, a[base + m]) < 0) {
                ofs = m;
            } else {
                last_of_s = m + 1;
            }
        }
        if (_debug) { utility::assert(last_of_s == ofs, ""); }
        return ofs;
    }

    void _merge_lo(int base1, int len1, int base2, int len2)
    {
        if (_debug) { utility::assert(len1 > 0 && len2 > 0 && base1 + len1 == base2, ""); }
        std::vector<T> new_a{a};
        std::vector<T> new_tmp = _ensure_capacity(len1);
        std::copy_n(new_a.begin() + base1, len1, new_tmp.begin());
        int cursor1 = 0;
        int cursor2 = base2;
        int dest = base1;

        new_a[dest++] = new_a[cursor2++];
        if (--len2 == 0) {
            std::copy_n(new_tmp.begin() + cursor1, len1, new_a.begin() + dest);
            return;
        }
        if (len1 == 1) {
            std::copy_n(new_tmp.begin() + cursor2, len2, new_a.begin() + dest);
            new_a[dest + len2] = new_tmp[cursor1];
            return;
        }
        Comparator<T> new_c{_comparator};
        int new_min_gallop{_min_gallop};
        outer:
        while (true) {
            int count1 = 0;
            int count2 = 0;

            do {
                if (_debug) { utility::assert(len1 > 1 && len2 > 0, ""); }
                if (new_c.compare(new_a[cursor2], new_tmp[cursor1]) < 0) {
                    new_a[dest++] = new_a[cursor2++];
                    ++count2;
                    count1 = 0;
                    if (--len2 == 0) {
                        goto end_outer;
                    }
                } else {
                    new_a[dest++] = new_tmp[cursor1++];
                    ++count1;
                    count2 = 0;
                    if (--len1 == 1) {
                        goto end_outer;
                    }
                }
            } while ((count1 | count2) < new_min_gallop);

            do {
                if (_debug) { utility::assert(len1 > 1 && len2 > 0, ""); }
                count1 = _gallop_right(new_a[cursor2], new_tmp, cursor1, len1, 0, new_c);
                if (count1 != 0) {
                    std::copy_n(new_tmp.begin() + cursor1, count1, new_a.begin() + dest);
                    dest += count1;
                    cursor1 += count1;
                    len1 -= count1;
                    if (len1 <= 1) {
                        goto end_outer;
                    }
                }
                new_a[dest++] = new_a[cursor2++];
                if (--len2 == 0) {
                    goto end_outer;
                }
                count2 = _gallop_left(new_tmp[cursor1], new_a, cursor2, len2, 0, new_c);
                if (count2 != 0) {
                    std::copy_n(new_a.begin() + cursor2, count2, new_a.begin() + dest);
                    dest += count2;
                    cursor2 += count2;
                    len2 -= count2;
                    if (len2 == 0) {
                        goto end_outer;
                    }
                }
                new_a[dest++] = new_tmp[cursor1++];
                if (--len1 == 1) {
                    goto end_outer;
                }
                new_min_gallop--;
            } while (count1 >= _initial_min_gallop | count2 >= _initial_min_gallop);
            if (new_min_gallop < 0) {
                new_min_gallop = 0;
            }
            new_min_gallop += 2;
        }
        end_outer:
        _min_gallop = new_min_gallop < 1 ? 1 : new_min_gallop;
        if (len1 == 1) {
            if (_debug) { utility::assert(len2 > 0, ""); }
            std::copy_n(new_a.begin() + cursor2, len2, new_a.begin() + dest);
            new_a[dest + len2] = new_tmp[cursor1];
        } else if (len1 == 0) {
            throw utility::Illegal_argument_exception("Comparison method violates its general contract!");
        } else {
            if (_debug) { utility::assert(len2 == 0, ""); }
            if (_debug) { utility::assert(len1 > 1, ""); }
            std::copy_n(new_tmp.begin() + cursor1, len1, new_a.begin() + dest);
        }
    }

    void _merge_hi(int base1, int len1, int base2, int len2)
    {
        if (_debug) { utility::assert(len1 > 0 && len2 > 0 && base1 + len1 == base2, ""); }
        std::vector<T> new_a{a};
        std::vector<T> new_tmp = _ensure_capacity(len2);
        std::copy_n(new_a.begin() + base2, len2, new_tmp.begin());
        int cursor1 = base1 + len1 - 1;
        int cursor2 = len2 - 1;
        int dest = base2 + len2 - 1;
        new_a[dest--] = new_a[cursor1--];
        if (--len1 == 0) {
            std::copy_n(new_tmp.begin(), len2, new_a.begin() + (dest - (len2 - 1)));
            return;
        }
        if (len2 == 1) {
            dest -= len1;
            cursor1 -= len1;
            std::copy_n(new_a.begin() + cursor1 + 1, len1, new_a.begin() + dest + 1);
            new_a[dest] = new_tmp[cursor2];
            return;
        }
        Comparator<T> new_c{_comparator};
        int new_min_gallop{_min_gallop};
        outer:
        while (true) {
            int count1 = 0;
            int count2 = 0;

            do {
                if (_debug) { utility::assert(len1 > 0 && len2 > 1, ""); }
                if (new_c.compare(new_tmp[cursor2], new_a[cursor1]) < 0) {
                    new_a[dest--] = new_a[cursor1--];
                    ++count1;
                    count2 = 0;
                    if (--len1 == 0) {
                        goto end_outer;
                    }
                } else {
                    new_a[dest--] = new_tmp[cursor2--];
                    ++count2;
                    count1 = 0;
                    if (--len2 == 1) {
                        goto end_outer;
                    }
                }
            } while ((count1 | count2) < new_min_gallop);

            do {
                if (_debug) { utility::assert(len1 > 0 && len2 > 1, ""); }
                count1 = len1 - _gallop_right(new_tmp[cursor2], new_a, base1, len1, len1 - 1, new_c);
                if (count1 != 0) {
                    dest -= count1;
                    cursor1 -= count1;
                    len1 -= count1;
                    std::copy_n(new_a.begin() + cursor1 + 1, count1, new_a.begin() + dest + 1);
                    if (len1 == 0) {
                        goto end_outer;
                    }
                }
                new_a[dest--] = new_tmp[cursor2--];
                if (--len2 == 1) {
                    goto end_outer;
                }
                count2 = len2 - _gallop_left(new_a[cursor1], new_tmp, 0, len2, len2 - 1, new_c);
                if (count2 != 0) {
                    dest -= count2;
                    cursor2 -= count2;
                    len2 -= count2;
                    std::copy_n(new_tmp.begin() + cursor2 + 1, count2, new_a.begin() + dest + 1);
                    if (len2 <= 1) {
                        goto end_outer;
                    }

                }
                new_a[dest--] = new_a[cursor1--];
                if (--len1 == 0) {
                    goto end_outer;
                }
                new_min_gallop--;
            } while (count1 >= _initial_min_gallop | count2 >= _initial_min_gallop);
            if (new_min_gallop < 0) {
                new_min_gallop = 0;
            }
            new_min_gallop += 2;
        }
        end_outer:
        _min_gallop = new_min_gallop < 1 ? 1 : new_min_gallop;
        if (len2 == 1) {
            if (_debug) { utility::assert(len1 > 0, ""); }
            dest -= len1;
            cursor1 -= len1;
            std::copy_n(new_a.begin() + cursor1 + 1, len1, new_a.begin() + dest + 1);
            new_a[dest] = new_tmp[cursor2];
        } else if (len2 == 0) {
            throw utility::Illegal_argument_exception("Comparison method violates its general contract!");
        } else {
            if (_debug) { utility::assert(len1 == 0, ""); }
            if (_debug) { utility::assert(len2 > 0, ""); }
            std::copy_n(new_tmp.begin(), len2, new_a.begin() + (dest = -(len2 - 1)));
        }
    }

    std::vector<T> _ensure_capacity(int min_capacity)
    {
        if (_tmp.size() < min_capacity) {
            int new_size = min_capacity;
            new_size |= new_size >> 1;
            new_size |= new_size >> 2;
            new_size |= new_size >> 4;
            new_size |= new_size >> 8;
            new_size |= new_size >> 16;
            ++new_size;
            if (new_size < 0) {
                new_size = min_capacity;
            } else {
                new_size = std::min(new_size, a.size() >> 1);
            }
            _tmp.clear();
            _tmp.reserve(new_size);
        }
        return _tmp;
    }

    static void _range_check(int vector_size, int from_index, int to_index)
    {
        std::stringstream ss;
        if (from_index > to_index) {
            ss << "from_index(" << from_index << ") > to_index(" << to_index + ")";
            throw utility::Illegal_argument_exception(ss.str());
        }
        if (from_index < 0) {
            ss << from_index;
            throw utility::Index_out_of_bounds_exception(ss.str());
            // throw ArrayIndexOutOfBoundsException(from_index);
        }
        if (to_index > vector_size) {
            ss << to_index;
            throw utility::Index_out_of_bounds_exception(ss.str());
            // throw ArrayIndexOutOfBoundsException(to_index);
        }
    }
};

#endif // TIMSORT_H
