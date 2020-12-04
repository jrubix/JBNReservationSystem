#include "Domain/Room/RoomCatalog.hpp"
#include "Domain/Room/RoomHandler.hpp"
#include <memory>

namespace Domain::Room
{
  RoomHandler::~RoomHandler() noexcept = default;

  std::unique_ptr<RoomHandler> RoomHandler::createRoomCatalog()
  {
    return std::make_unique<Domain::Room::RoomCatalog>();
  }

} // namespace Domain::Hotel
