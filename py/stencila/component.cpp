#include <vector>
#include <string>

#include <stencila/component.hpp>
using namespace Stencila;

#include "extension.hpp"

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Component_path_set_overloads,path,1,2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Component_destroy_overloads,destroy,0,0)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Component_create_overloads,create,1,2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Component_delete_overloads,delete_,1,1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Component_read_overloads,read,0,1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Component_write_overloads,write,0,1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Component_commit_overloads,commit,0,1)

void def_Component(void){
    class_<Component,bases<>>("Component",no_init)

        .def("title",static_cast<const std::string& (Component::*)(void) const>(&Component::title),return_value_policy<copy_const_reference>())
        .def("title",static_cast<Component& (Component::*)(const std::string&)>(&Component::title),return_self<>())

        .def("description",static_cast<const std::string& (Component::*)(void) const>(&Component::description),return_value_policy<copy_const_reference>())
        .def("description",static_cast<Component& (Component::*)(const std::string&)>(&Component::description),return_self<>())

        .def("keywords",static_cast<const std::vector<std::string>& (Component::*)(void) const>(&Component::keywords),return_value_policy<copy_const_reference>())
        .def("keywords",static_cast<Component& (Component::*)(const std::vector<std::string>&)>(&Component::keywords),return_self<>())

        .def("authors",static_cast<const std::vector<std::string>& (Component::*)(void) const>(&Component::authors),return_value_policy<copy_const_reference>())
        .def("authors",static_cast<Component& (Component::*)(const std::vector<std::string>&)>(&Component::authors),return_self<>())

        .def("path",static_cast<const std::string& (Component::*)(void) const>(&Component::path),return_value_policy<copy_const_reference>())
        .def("path",static_cast<Component& (Component::*)(const std::string&,bool)>(&Component::path),Component_path_set_overloads(
            (arg("path"),arg("force")),
            "Set the component's working directory"
        )[return_self<>()])

        .def("destroy",static_cast<Component& (Component::*)(void)>(&Component::destroy),Component_destroy_overloads(
            "Destroy the component's working directory"
        )[return_self<>()])

        .def("create",static_cast<Component& (Component::*)(const std::string&,const std::string&)>(&Component::create),Component_create_overloads(
            (arg("path"),arg("content")),
            "Create a file in the component's working directory"
        )[return_self<>()])
        
        .def("delete",static_cast<Component& (Component::*)(const std::string&)>(&Component::delete_),Component_delete_overloads(
            arg("path"),
            "Delete a file in the component's working directory"
        )[return_self<>()])

        .def("read",static_cast<Component& (Component::*)(const std::string&)>(&Component::read),Component_read_overloads(
            arg("path")="",
            "Read the component from a filesystem path"
        )[return_self<>()])

        .def("write",static_cast<Component& (Component::*)(const std::string&)>(&Component::write),Component_write_overloads(
            arg("path")="",
            "Write the component to a filesystem path"
        )[return_self<>()])

        .def("commit",&Component::commit,Component_commit_overloads(
            arg("message")="",
            "Commit the component"
        )[return_self<>()])
    ;
}