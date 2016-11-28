#ifndef PART_10_LINKED_LISTS_REVERSEITER_H
#define PART_10_LINKED_LISTS_REVERSEITER_H

#include <iterator>

namespace dss {
    template<class Iter>
    class ReverseIter;

    template<class Iter>
    ReverseIter<Iter> operator+(typename ReverseIter<Iter>::difference_type lhs,
                                const ReverseIter<Iter> &rhs);

    template<class Iter>
    class ReverseIter {
    public:
        typedef typename std::iterator_traits<Iter>::difference_type difference_type;
        typedef typename std::iterator_traits<Iter>::pointer pointer;
        typedef typename std::iterator_traits<Iter>::reference reference;
        typedef typename std::iterator_traits<Iter>::value_type value_type;
        typedef typename std::iterator_traits<Iter>::iterator_category
                iterator_category;

        ReverseIter();

        explicit ReverseIter(const Iter &i);

        template<class OtherIter>
        ReverseIter(const ReverseIter<OtherIter> &source);

        Iter base() const;

        bool operator==(const ReverseIter &rhs) const;

        bool operator!=(const ReverseIter &rhs) const;

        bool operator>=(const ReverseIter &rhs) const;

        bool operator<=(const ReverseIter &rhs) const;

        bool operator>(const ReverseIter &rhs) const;

        bool operator<(const ReverseIter &rhs) const;

        pointer operator->() const;

        reference operator*() const;

        reference operator[](difference_type offset) const;

        ReverseIter operator+(difference_type offset) const;

        ReverseIter operator-(difference_type offset) const;

        difference_type operator-(const ReverseIter &rhs) const;

        ReverseIter &operator++();

        ReverseIter &operator--();

        ReverseIter operator++(int n);

        ReverseIter operator--(int n);

        ReverseIter &operator+=(difference_type offset);

        ReverseIter &operator-=(difference_type offset);

    private:
        Iter _i;
    };

    template<class Iter>
    inline ReverseIter<Iter>::ReverseIter() {
        // ...
    }

    template<class Iter>
    inline ReverseIter<Iter>::ReverseIter(const Iter &i) :
            _i(i) {
        // ...
    }

    template<class Iter>
    template<class OtherIter>
    inline ReverseIter<Iter>::ReverseIter(const ReverseIter<OtherIter> &source):
            _i(source.base()) {
        // ...
    }

    template<class Iter>
    inline Iter ReverseIter<Iter>::base() const {
        return _i;
    }

    template<class Iter>
    inline bool ReverseIter<Iter>::operator==(const ReverseIter &rhs) const {
        return _i == rhs._i;
    }

    template<class Iter>
    inline bool ReverseIter<Iter>::operator!=(const ReverseIter &rhs) const {
        return _i != rhs._i;
    }

    template<class Iter>
    inline typename ReverseIter<Iter>::pointer
    ReverseIter<Iter>::operator->() const {
        Iter temp = _i;
        --temp;

        return &(*temp);
    }

    template<class Iter>
    inline typename ReverseIter<Iter>::reference
    ReverseIter<Iter>::operator*() const {
        Iter temp = _i;
        --temp;

        return *temp;
    }

    template<class Iter>
    inline ReverseIter<Iter> &ReverseIter<Iter>::operator++() {
        --_i;

        return *this;
    }

    template<class Iter>
    inline ReverseIter<Iter> &ReverseIter<Iter>::operator--() {
        ++_i;

        return *this;
    }

    template<class Iter>
    inline ReverseIter<Iter> ReverseIter<Iter>::operator++(int n) {
        return _i--;
    }

    template<class Iter>
    inline ReverseIter<Iter> ReverseIter<Iter>::operator--(int n) {
        return _i++;
    }

    template<class Iter>
    inline bool ReverseIter<Iter>::operator>=(const ReverseIter &rhs) const {
        return _i <= rhs._i;
    }

    template<class Iter>
    inline bool ReverseIter<Iter>::operator<=(const ReverseIter &rhs) const {
        return _i >= rhs._i;
    }

    template<class Iter>
    inline bool ReverseIter<Iter>::operator>(const ReverseIter &rhs) const {
        return _i < rhs._i;
    }

    template<class Iter>
    inline bool ReverseIter<Iter>::operator<(const ReverseIter &rhs) const {
        return _i > rhs._i;
    }

    template<class Iter>
    inline typename ReverseIter<Iter>::reference ReverseIter<Iter>::operator[](
            difference_type offset) const {
        return _i[-offset - 1];
    }

    template<class Iter>
    inline ReverseIter<Iter> ReverseIter<Iter>::operator+(
            difference_type offset) const {
        return ReverseIter(_i - offset);
    }

    template<class Iter>
    inline ReverseIter<Iter> ReverseIter<Iter>::operator-(
            difference_type offset) const {
        return ReverseIter(_i + offset);
    }

    template<class Iter>
    inline typename ReverseIter<Iter>::difference_type
    ReverseIter<Iter>::operator-(const ReverseIter &rhs) const {
        return rhs._i - _i;
    }

    template<class Iter>
    inline ReverseIter<Iter> &ReverseIter<Iter>::operator+=(difference_type offset) {
        _i -= offset;

        return *this;
    }

    template<class Iter>
    inline ReverseIter<Iter> &ReverseIter<Iter>::operator-=(difference_type offset) {
        _i += offset;

        return *this;
    }

    template<class Iter>
    inline ReverseIter<Iter> operator+(
            typename ReverseIter<Iter>::difference_type lhs,
            const ReverseIter<Iter> &rhs) {
        return rhs + lhs;
    }
};

#endif //PART_10_LINKED_LISTS_REVERSEITER_H
