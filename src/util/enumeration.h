#ifndef RAY_TRACING_ENUMERATION_H
#define RAY_TRACING_ENUMERATION_H

#include <iterator>

template<class Iterator>
class Enumeration {
public:
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using iterator = Iterator;

    Enumeration(Iterator first, Iterator last) : first_(first), last_(last) {}

    iterator begin() const { return first_; }

    iterator end() const { return last_; }

private:
    Iterator first_;
    Iterator last_;
};

#endif //RAY_TRACING_ENUMERATION_H
