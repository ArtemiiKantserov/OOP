#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class LackAbillity : public std::exception {
  public:
    const char* what() const noexcept override;
};

class WrongCoordinates : public std::exception {
  public:
    const char* what() const noexcept override;
};

class IncorrectPlaceShip : public std::exception {
  public:
    const char* what() const noexcept override;
};

#endif