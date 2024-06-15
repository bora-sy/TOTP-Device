#pragma once

#include <PagedView.h>

class TestPage : public Page
{
private:
public:
    void OnLoad() override;
    void OnExit() override;
    void OnInput(BtnInput input) override;
    void Periodic() override;
};