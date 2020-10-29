#include "Domain/Hotel/Hotel.hpp"
#include "Domain/Hotel/HotelHandler.hpp"
namespace Domain::Hotel
{
  HotelHandler::~HotelHandler() noexcept = default;
  std::unique_ptr<HotelHandler> HotelHandler::createHotel()
  {
    return std::unique_ptr<HotelHandler>();
  }
}
