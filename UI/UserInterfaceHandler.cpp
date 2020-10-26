#include "UI/UserInterfaceHandler.hpp"

#include <memory>    // unique_ptr, make_unique

#include "UI/BaseUI.hpp"



namespace UI {
  UserInterfaceHandler::~UserInterfaceHandler() noexcept = default;

  std::unique_ptr<UserInterfaceHandler> UserInterfaceHandler::createUI(){

      return std::make_unique<UI::BaseUI>();

  }
}    // namespace UI
