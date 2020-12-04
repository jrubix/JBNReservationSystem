#pragma once

#include <any>
#include <memory>    // unique_ptr
#include <stdexcept> // runtime_error
#include <string>
#include <vector>

namespace Domain::Hotel
{
  class HotelHandler
  {
  public:
    struct HotelException : std::runtime_error
    {
      using runtime_error ::runtime_error;
    };
    struct BadCommand : HotelException
    {
      using HotelException::HotelException;
    };

    virtual std::any executeCommand(const std::string &command, const std::vector<std::string> &args) = 0;

    virtual ~HotelHandler() noexcept = 0;
    static std::unique_ptr<HotelHandler> createHotel();

  protected:
    // Copy assignment operators, protected to prevent mix derived-type assignments
    HotelHandler &operator=(const HotelHandler &rhs) = default; // copy assignment
    HotelHandler &operator=(HotelHandler &&rhs) = default;      // move assignment
  };

} // namespace Domain::Hotel
