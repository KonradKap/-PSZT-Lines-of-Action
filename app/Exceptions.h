#pragma once

#include <exception>
#include <stdexcept>

class PawnNotPresentError : public std::runtime_error {
    public:
        explicit PawnNotPresentError(const std::string& what) :
            std::runtime_error(what) {};
        explicit PawnNotPresentError(const char* what) :
            std::runtime_error(what) {};
        virtual ~PawnNotPresentError() {};
};
