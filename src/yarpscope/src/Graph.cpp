/*
 *  This file is part of Yarp Port Scope
 *
 *  Copyright (C) 2012 Daniele E. Domenichelli <daniele.domenichelli@iit.it>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Graph.h"
#include "Debug.h"
#include "PortReader.h"

#include <gtkdataboxmm/lines.h>
#include <gtkdataboxmm/bars.h>
#include <gtkdataboxmm/points.h>

#include <glibmm/ustring.h>
#include <gdkmm/color.h>

namespace {
    const Gdk::Color colorRed("Red");
    const Gdk::Color colorGreen("Green");
    const Gdk::Color colorBlue("Blue");
    const Gdk::Color colorCyan("Cyan");
    const Gdk::Color colorMagenta("Magenta");
    const Gdk::Color colorYellow("Yellow");
}


class YarpScope::Graph::Private
{
public:
    Private(Graph *parent):
        parent(parent),
        X_plot(NULL),
        Y_plot(NULL),
        bufSize(PortReader::instance().bufSize()),
        curr(0)
    {
    }

    ~Private()
    {
        if (X_plot) {
            delete [] X_plot;
        }
        if (Y_plot) {
            delete [] Y_plot;
        }
    }

    static YarpScope::Graph::Type stringToType(Glib::ustring typeStr);

    void update(bool increment);

    Graph * const parent;

    Glib::ustring title;
    Glib::RefPtr<GDatabox::Graph> graph;
    const float *X;
    const float *Y;
    const float *T;

    float *X_plot;
    float *Y_plot;

    int plotSize;
    int bufSize;
    int curr;
};


YarpScope::Graph::Type YarpScope::Graph::Private::stringToType(Glib::ustring typeStr)
{
    if (!typeStr.compare("points")) {
        return YarpScope::Graph::TypePoints;
    } else if (!typeStr.compare("lines")) {
        return YarpScope::Graph::TypeLines;
    } else if (!typeStr.compare("bars")) {
        return YarpScope::Graph::TypeBars;
    }
    return YarpScope::Graph::TypeUnset;
}

void YarpScope::Graph::Private::update(bool increment)
{
#if 0
    // TODO enable
    if ((curr + 1) % plotSize) {
        curr = (curr + 1) % bufSize;
        return;
    }
#endif // 0
    for (int i = 0; i < plotSize; i++) {
        Y_plot[(plotSize - 1) - i] = Y[(curr - i) % bufSize];
    }

    if (increment) {
        curr = (curr + 1) % bufSize;
    }
}


YarpScope::Graph::Graph(const Glib::ustring &remote,
                         int index,
                         const Glib::ustring &title,
                         const Glib::ustring &color,
                         const Glib::ustring &type,
                         int size,
                         int plotSize) :
    mPriv(new Private(this))
{
    g_assert(plotSize > 0);
    if (remote.empty()) {
        fatal() << "Impossible to create a graph; remote is empty";
    }

    g_assert(index >= 0);
    if (index < 0) {
        fatal() << "Impossible to create a graph; index < 0";
    }

    g_assert(size > 0);
    if (size <= 0) {
        fatal() << "Impossible to create a graph; size <= 0";
    }

    g_assert(!remote.empty());
    if (plotSize <= 0) {
         fatal() << "Impossible to create a graph; plot size <= 0";
    }

    if (!title.empty()) {
        mPriv->title = title;
    } else {
        std::ostringstream oss;
        oss << remote << index;
        mPriv->title = oss.str();
    }

    if (color.empty()) {
        // TODO choose one color from a list
    }

    mPriv->X = YarpScope::PortReader::instance().X(remote, index);
    mPriv->Y = YarpScope::PortReader::instance().Y(remote, index);
    mPriv->T = YarpScope::PortReader::instance().T(remote, index);

    g_assert(mPriv->X && mPriv->Y && mPriv->T);
    if (!mPriv->X || !mPriv->Y || !mPriv->T) {
        fatal() << "Impossible to create a graph; plot size; untracked remote/index" << remote << index;
    }

    mPriv->plotSize = plotSize;
    mPriv->X_plot = new float[plotSize];
    mPriv->Y_plot = new float[plotSize];
    for (int i = 0; i < mPriv->plotSize; i++) {
        mPriv->X_plot[i] = i;
        mPriv->Y_plot[i] = 0;
    }

    switch (Private::stringToType(type)) {
    case TypeUnset :
    case TypeLines :
        mPriv->graph = GDatabox::Lines::create(plotSize, mPriv->X_plot, mPriv->Y_plot, Gdk::Color(color), size);
        break;
    case TypePoints :
        mPriv->graph = GDatabox::Points::create(plotSize, mPriv->X_plot, mPriv->Y_plot, Gdk::Color(color), size);
        break;
    case TypeBars :
        mPriv->graph = GDatabox::Bars::create(plotSize, mPriv->X_plot, mPriv->Y_plot, Gdk::Color(color), size);
        break;
    }

}

YarpScope::Graph::~Graph()
{
    delete mPriv;
}

Glib::RefPtr< GDatabox::Graph > YarpScope::Graph::graph() const
{
    return mPriv->graph;
}

const Glib::ustring& YarpScope::Graph::title() const
{
    return mPriv->title;
}

void YarpScope::Graph::update(bool increment)
{
    mPriv->update(increment);
}
