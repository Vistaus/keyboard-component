/*
 * Copyright 2013 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ubuntuapplicationapiwrapper.h"

#ifdef QT_OPENGL_ES_2
#include <ubuntu/ui/ubuntu_ui_session_service.h>
#include <ubuntu/application/ui/window_properties.h>
  #define HAVE_UBUNTU_PLATFORM_API
#endif

#include <QtGlobal>
#include <QByteArray>

UbuntuApplicationApiWrapper::UbuntuApplicationApiWrapper()
    : m_runningOnMir(false)
{
    if (qgetenv("QT_QPA_PLATFORM") == "ubuntumirclient") {
        m_runningOnMir = false;
    }
}

void UbuntuApplicationApiWrapper::reportOSKVisible(const int x, const int y, const int width, const int height)
{
#ifdef HAVE_UBUNTU_PLATFORM_API
    if (!m_runningOnMir) { // following method not implemented on Mir
        ubuntu_ui_report_osk_visible(x, y, width, height);
    }
#else
    Q_UNUSED(x)
    Q_UNUSED(y)
    Q_UNUSED(width)
    Q_UNUSED(height)
#endif
}

void UbuntuApplicationApiWrapper::reportOSKInvisible()
{
#ifdef HAVE_UBUNTU_PLATFORM_API
    if (!m_runningOnMir) { // following method not implemented on Mir
        ubuntu_ui_report_osk_invisible();
    }
#endif
}

int UbuntuApplicationApiWrapper::oskWindowRole() const
{
#ifdef HAVE_UBUNTU_PLATFORM_API
    return static_cast<int>(U_ON_SCREEN_KEYBOARD_ROLE);
#else
    return 7;
#endif
}

