// SPDX-FileCopyrightText: 2023 Joshua Goins <josh@redstrate.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "novusmainwindow.h"

struct GameData;

class MainWindow : public NovusMainWindow
{
public:
    MainWindow(GameData *data);

private:
    GameData *data = nullptr;
};