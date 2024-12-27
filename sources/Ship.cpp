#include "../headers/Ship.h"
  
Ship::Ship(std::string str){
  length_ = std::stoi(str.substr(0, 1));
  for (int i = 0; i < length_; ++i) 
    segment_status_.push_back(Segment(std::stoi(str.substr(1+i, 1))));
}

Ship::Ship(int length){
  length_ = length;
  segment_status_ = std::vector<Segment>(length_, Segment::FULL);
}

auto Ship::get_length() -> int {
  return length_;
}

auto Ship::get_status_segement(int segment_number) -> Segment{
  return segment_status_[segment_number];
}

auto Ship::hit(int segment_number) -> bool{
  switch (segment_status_[segment_number]) {
  case Segment::DESTROYED:
    break;
  case Segment::FULL:
    segment_status_[segment_number] = Segment::WOUNDED;
    break;
  case Segment::WOUNDED:
    segment_status_[segment_number] = Segment::DESTROYED;
    return full_destroyed();
  }
  return false;
}

auto Ship::double_hit(int segment_number) -> bool {
  switch (segment_status_[segment_number]) {
  case Segment::DESTROYED:
    break;
  case Segment::FULL:
    segment_status_[segment_number] = Segment::DESTROYED;
    return full_destroyed();
  case Segment::WOUNDED:
    segment_status_[segment_number] = Segment::DESTROYED;
    return full_destroyed();
  }
  return false;
}

auto Ship::full_destroyed() -> bool{
  for (Segment status : segment_status_)
    if (status != Segment::DESTROYED) return false;
  destroyed = true;
  return true;
}

auto Ship::is_destroyed() -> bool {
  return destroyed;
}

auto Ship::serialize() -> std::string{
  std::string res;
  res += std::to_string(length_);
  for (int i = 0; i < length_; ++i) 
    res += std::to_string(static_cast<int>(segment_status_[i]));
  res += "&";
  return res; 
}
