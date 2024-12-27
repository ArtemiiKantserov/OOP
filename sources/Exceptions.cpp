#include "../headers/Exceptions.h"

const char* LackAbillity::what() const noexcept {
  return "No abilities.";
}

const char* WrongCoordinates::what() const noexcept {
  return "The specified coordinates are outside the field.";
}

const char* IncorrectPlaceShip::what() const noexcept {
  return "The ship is close to or crossing another ship.";
}

