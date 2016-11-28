#ifndef PART_10_LINKED_LISTS_CONSTITER_H
#define PART_10_LINKED_LISTS_CONSTITER_H

#include <iterator>

namespace dss {
    template<class Container>
    class ConstIter;

    template<class Container>
    ConstIter<Container> operator+(typename ConstIter<Container>::difference_type lhs, const ConstIter<Container> &rhs);

    template<class Container>
    class ConstIter {
    public:
        friend class Container;

        typedef typename Container::iterator Iter;

        ConstIter();

        ConstIter(const Iter &i);

        typedef typename std::iterator_traits<Iter>::value_type value_type;
        typedef typename std::iterator_traits<Iter>::difference_type difference_type;

        typedef typename std::iterator_traits<Iter>::iterator_category
                iterator_category;

        typedef typename Container::const_pointer pointer;
        typedef typename Container::const_reference reference;

        bool operator==(const ConstIter &rhs) const;

        bool operator!=(const ConstIter &rhs) const;

        bool operator>=(const ConstIter &rhs) const;

        bool operator<=(const ConstIter &rhs) const;

        bool operator>(const ConstIter &rhs) const;

        bool operator<(const ConstIter &rhs) const;

        pointer operator->() const;

        reference operator*() const;

        reference operator[](difference_type offset) const;

        ConstIter operator+(difference_type offset) const;

        ConstIter operator-(difference_type offset) const;

        difference_type operator-(const ConstIter &rhs) const;

        ConstIter &operator++();

        ConstIter &operator--();

        ConstIter operator++(int n);

        ConstIter operator--(int n);

        ConstIter &operator+=(difference_type offset);

        ConstIter &operator-=(difference_type offset);

    private:
        Iter _i;
    };

    template<class Container>
    inline ConstIter<Container>::ConstIter() {
        // ...
    }

    template<class Container>
    inline ConstIter<Container>::ConstIter(const Iter &i) :
            _i(i) {
        // ...
    }

    template<class Container>
    inline bool ConstIter<Container>::operator==(const ConstIter &rhs) const {
        return _i == rhs._i;
    }

    template<class Container>
    inline bool ConstIter<Container>::operator!=(const ConstIter &rhs) const {
        return _i != rhs._i;
    }

    template<class Container>
    inline typename ConstIter<Container>::pointer
    ConstIter<Container>::operator->() const {
        return _i.operator->();
    }

    template<class Container>
    inline typename ConstIter<Container>::reference
    ConstIter<Container>::operator*() const {
        return *_i;
    }

    template<class Container>
    inline ConstIter<Container> &ConstIter<Container>::operator++() {
        ++_i;

        return *this;
    }

    template<class Container>
    inline ConstIter<Container> &ConstIter<Container>::operator--() {
        --_i;

        return *this;
    }

    template<class Container>
    inline ConstIter<Container> ConstIter<Container>::operator++(int n) {
        return _i++;
    }

    template<class Container>
    inline ConstIter<Container> ConstIter<Container>::operator--(int n) {
        return _i--;
    }

    template<class Iter>
    inline bool ConstIter<Iter>::operator>=(const ConstIter &rhs) const {
        return _i >= rhs._i;
    }

    template<class Iter>
    inline bool ConstIter<Iter>::operator<=(const ConstIter &rhs) const {
        return _i <= rhs._i;
    }

    template<class Iter>
    inline bool ConstIter<Iter>::operator>(const ConstIter &rhs) const {
        return _i > rhs._i;
    }

    template<class Iter>
    inline bool ConstIter<Iter>::operator<(const ConstIter &rhs) const {
        return _i < rhs._i;
    }

    template<class Iter>
    inline typename ConstIter<Iter>::reference ConstIter<Iter>::operator[](
            difference_type offset) const {
        return _i[offset];
    }

    template<class Iter>
    inline ConstIter<Iter> ConstIter<Iter>::operator+(
            difference_type offset) const {
        return ConstIter(_i + offset);
    }

    template<class Iter>
    inline ConstIter<Iter> ConstIter<Iter>::operator-(
            difference_type offset) const {
        return ConstIter(_i - offset);
    }

    template<class Iter>
    inline typename ConstIter<Iter>::difference_type
    ConstIter<Iter>::operator-(const ConstIter &rhs) const {
        return _i - rhs._i;
    }

    template<class Iter>
    inline ConstIter<Iter> &ConstIter<Iter>::operator+=(difference_type offset) {
        _i += offset;

        return *this;
    }

    template<class Iter>
    inline ConstIter<Iter> &ConstIter<Iter>::operator-=(difference_type offset) {
        _i -= offset;

        return *this;
    }

    template<class Iter>
    inline ConstIter<Iter> operator+(typename ConstIter<Iter>::difference_type lhs,
                                     const ConstIter<Iter> &rhs) {
        return rhs + lhs;
    }
};

#endif //PART_10_LINKED_LISTS_CONSTITER_H
