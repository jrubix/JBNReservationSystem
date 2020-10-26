#pragma once

#include <memory>    // std::unique_ptr

#include "UI/UserInterfaceHandler.hpp"




namespace UI
{
  /*****************************************************************************
  ** Simple UI definition
  **   Simple UI is a console application meant only as a driver to the Domain Layer
  **   application. This UI will someday be replaced by a more sophisticated, user
  **   friendly implementation
  ******************************************************************************/
  class BaseUI : public UI::UserInterfaceHandler
  {
    public:
      // Constructors
      BaseUI();

      // Operations
      void launch() override;
      void logo() override;
      // Destructor
      ~BaseUI() noexcept override;


    private:
      // These smart pointers hold pointers to lower architectural layer's interfaces

  };
} // namespace UI
