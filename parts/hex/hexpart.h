// SPDX-FileCopyrightText: 2023 Joshua Goins <josh@redstrate.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "physis.hpp"
#include "qhexview.h"

class HexPart : public QHexView
{
public:
    explicit HexPart(QWidget *parent = nullptr);

    void loadFile(physis_Buffer buffer);
};