
template<class Container, typename std::enable_if<boost::spirit::traits::is_container<Container>::value>::type* >
    Container operator+(Container lhs, const Container& rhs) {
        return lhs += rhs;
    }

template<class Container, typename std::enable_if<boost::spirit::traits::is_container<Container>::value>::type* >
    Container operator+=(Container& lhs, const Container& rhs) {
        lhs.insert(lhs.end(), rhs.begin(), rhs.end());
        return lhs;
    }

template<class Container, typename std::enable_if<boost::spirit::traits::is_container<Container>::value>::type* >
    Container operator+(Container lhs, Container&& rhs) {
        return lhs += rhs;
    }

template<class Container, typename std::enable_if<boost::spirit::traits::is_container<Container>::value>::type* >
    Container operator+=(Container& lhs, Container&& rhs) {
        lhs.insert(lhs.end(),
            std::make_move_iterator(rhs.begin()),
            std::make_move_iterator(rhs.end()));
        return lhs;
    }

template<class Container, typename std::enable_if<boost::spirit::traits::is_container<Container>::value>::type* >
    void print(const Container& input, std::ostream& out) {
        out << "{";
        std::ostream_iterator<typename Container::value_type> out_iterator{out, ", "};
        std::copy(std::begin(input), std::end(input)-1, out_iterator);
        if(input.size())
            out << input.back();
        out << "}";
    }
