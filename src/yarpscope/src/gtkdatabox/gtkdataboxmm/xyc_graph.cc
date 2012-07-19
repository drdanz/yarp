// Generated by gtkmmproc -- DO NOT MODIFY!


#include <glibmm.h>

#include <gtkdataboxmm/xyc_graph.h>
#include <gtkdataboxmm/private/xyc_graph_p.h>


/* Copyright (c) 2012  Daniele E. Domenichelli <daniele.domenichelli@iit.it>
 *
 * This file is part of gtkdataboxmm.
 *
 * gtkdataboxmm is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 2.1 of the License,
 * or (at your option) any later version.
 *
 * gtkdataboxmm is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkdatabox_xyc_graph.h>

namespace GDatabox
{

} // namespace GDatabox

namespace
{
} // anonymous namespace


namespace Glib
{

Glib::RefPtr<GDatabox::XYCGraph> wrap(GtkDataboxXYCGraph* object, bool take_copy)
{
  return Glib::RefPtr<GDatabox::XYCGraph>( dynamic_cast<GDatabox::XYCGraph*> (Glib::wrap_auto ((GObject*)(object), take_copy)) );
  //We use dynamic_cast<> in case of multiple inheritance.
}

} /* namespace Glib */


namespace GDatabox
{


/* The *_Class implementation: */

const Glib::Class& XYCGraph_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &XYCGraph_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(gtk_databox_xyc_graph_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:

  }

  return *this;
}


void XYCGraph_Class::class_init_function(void* g_class, void* class_data)
{
  BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);


}


Glib::ObjectBase* XYCGraph_Class::wrap_new(GObject* object)
{
  return new XYCGraph((GtkDataboxXYCGraph*)object);
}


/* The implementation: */

GtkDataboxXYCGraph* XYCGraph::gobj_copy()
{
  reference();
  return gobj();
}

XYCGraph::XYCGraph(const Glib::ConstructParams& construct_params)
:
  Graph(construct_params)
{

}

XYCGraph::XYCGraph(GtkDataboxXYCGraph* castitem)
:
  Graph((GtkDataboxGraph*)(castitem))
{}


XYCGraph::~XYCGraph()
{}


XYCGraph::CppClassType XYCGraph::xycgraph_class_; // initialize static member

GType XYCGraph::get_type()
{
  return xycgraph_class_.init().get_type();
}


GType XYCGraph::get_base_type()
{
  return gtk_databox_xyc_graph_get_type();
}


XYCGraph::XYCGraph()
:
  // Mark this class as non-derived to allow C++ vfuncs to be skipped.
  Glib::ObjectBase(0),
  Graph(Glib::ConstructParams(xycgraph_class_.init()))
{
  

}

unsigned int XYCGraph::get_length() const
{
  return gtk_databox_xyc_graph_get_length(const_cast<GtkDataboxXYCGraph*>(gobj()));
}

float* XYCGraph::get_X() const
{
  return const_cast<XYCGraph*>(this)->get_X();
}

float* XYCGraph::get_Y() const
{
  return const_cast<XYCGraph*>(this)->get_Y();
}


#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly< unsigned int > XYCGraph::property_length() const
{
  return Glib::PropertyProxy_ReadOnly< unsigned int >(this, "length");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly< float* > XYCGraph::property_X_Values() const
{
  return Glib::PropertyProxy_ReadOnly< float* >(this, "X-Values");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly< float* > XYCGraph::property_Y_Values() const
{
  return Glib::PropertyProxy_ReadOnly< float* >(this, "Y-Values");
}
#endif //GLIBMM_PROPERTIES_ENABLED


} // namespace GDatabox


