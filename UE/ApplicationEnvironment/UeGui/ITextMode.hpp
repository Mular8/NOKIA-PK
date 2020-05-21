#pragma once
#include "BaseMode.hpp"
#include "IUeGui.hpp"

namespace ue
{

class IUeGui::ITextMode : public IUeGui::BaseMode
{
public:
    virtual ~ITextMode() = default;
    virtual void setText(const std::string& text) = 0;
};

}
