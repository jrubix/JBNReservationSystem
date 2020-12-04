#pragma once

#include <any>
#include <memory>    // unique_ptr
#include <stdexcept> // runtime_error
#include <string>
#include <vector>

namespace Domain::Room
{
  class RoomHandler
  {
  public:
    struct RoomException : std::runtime_error
    {
      using runtime_error ::runtime_error;
    };
    struct BadCommand : RoomException
    {
      using RoomException::RoomException;
    };
    virtual std::string askavailableroom(std::string date, int guestnum, int nights) = 0;

    virtual ~RoomHandler() noexcept = 0;

    static std::unique_ptr<RoomHandler> createRoomCatalog();

  private:
    // Copy assignment operators, protected to prevent mix derived-type assignments
    RoomHandler &operator=(const RoomHandler &rhs) = default; // copy assignment
    RoomHandler &operator=(RoomHandler &&rhs) = default;      // move assignment
  };

}
