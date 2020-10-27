#include "UI/UserInterfaceHandler.hpp"

#include <memory> // unique_ptr, make_unique

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

#include "UI/SimpleUI.hpp"

namespace UI
{
  UserInterfaceHandler::~UserInterfaceHandler() noexcept = default;

  std::unique_ptr<UserInterfaceHandler> UserInterfaceHandler::createUI()
  {
    // auto & persistantData = TechnicalServices::Persistence::PersistenceHandler::instance();

    return std::make_unique<UI::SimpleUI>();
  }
} // namespace UI
