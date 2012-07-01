// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "RenderEffect.pypp.hpp"

namespace bp = boost::python;

struct RenderEffect_wrapper : CEGUI::RenderEffect, bp::wrapper< CEGUI::RenderEffect > {

    RenderEffect_wrapper()
    : CEGUI::RenderEffect()
      , bp::wrapper< CEGUI::RenderEffect >(){
        // null constructor
        
    }

    virtual int getPassCount(  ) const {
        bp::override func_getPassCount = this->get_override( "getPassCount" );
        return func_getPassCount(  );
    }

    virtual void performPostRenderFunctions(  ){
        bp::override func_performPostRenderFunctions = this->get_override( "performPostRenderFunctions" );
        func_performPostRenderFunctions(  );
    }

    virtual void performPreRenderFunctions( int const pass ){
        bp::override func_performPreRenderFunctions = this->get_override( "performPreRenderFunctions" );
        func_performPreRenderFunctions( pass );
    }

    virtual bool realiseGeometry( ::CEGUI::RenderingWindow & window, ::CEGUI::GeometryBuffer & geometry ){
        bp::override func_realiseGeometry = this->get_override( "realiseGeometry" );
        return func_realiseGeometry( boost::ref(window), boost::ref(geometry) );
    }

    virtual bool update( float const elapsed, ::CEGUI::RenderingWindow & window ){
        bp::override func_update = this->get_override( "update" );
        return func_update( elapsed, boost::ref(window) );
    }

};

void register_RenderEffect_class(){

    { //::CEGUI::RenderEffect
        typedef bp::class_< RenderEffect_wrapper, boost::noncopyable > RenderEffect_exposer_t;
        RenderEffect_exposer_t RenderEffect_exposer = RenderEffect_exposer_t( "RenderEffect" );
        bp::scope RenderEffect_scope( RenderEffect_exposer );
        { //::CEGUI::RenderEffect::getPassCount
        
            typedef int ( ::CEGUI::RenderEffect::*getPassCount_function_type )(  ) const;
            
            RenderEffect_exposer.def( 
                "getPassCount"
                , bp::pure_virtual( getPassCount_function_type(&::CEGUI::RenderEffect::getPassCount) )
                , "*!\n\
                \n\
                    Return the number of passes required by this effect.\n\
            \n\
                @return\n\
                    integer value indicating the number of rendering passes required to\n\
                    fully render this effect.\n\
                *\n" );
        
        }
        { //::CEGUI::RenderEffect::performPostRenderFunctions
        
            typedef void ( ::CEGUI::RenderEffect::*performPostRenderFunctions_function_type )(  ) ;
            
            RenderEffect_exposer.def( 
                "performPostRenderFunctions"
                , bp::pure_virtual( performPostRenderFunctions_function_type(&::CEGUI::RenderEffect::performPostRenderFunctions) )
                , "*!\n\
            \n\
                Function called after RenderingWindow.draw is called.  This is intended\n\
                to be used for any required cleanup  state restoration.  This function\n\
                is called <em>once only<em>, unlike performPreRenderFunctions which may\n\
                be called multiple times; once for each pass in the effect.\n\
            \note\n\
                Note that this function is called  e before any standard state\n\
                cleanup that might be peformed by the Renderer module.\n\
            *\n" );
        
        }
        { //::CEGUI::RenderEffect::performPreRenderFunctions
        
            typedef void ( ::CEGUI::RenderEffect::*performPreRenderFunctions_function_type )( int const ) ;
            
            RenderEffect_exposer.def( 
                "performPreRenderFunctions"
                , bp::pure_virtual( performPreRenderFunctions_function_type(&::CEGUI::RenderEffect::performPreRenderFunctions) )
                , ( bp::arg("pass") )
                , "*!\n\
                \n\
                    Function called prior to RenderingWindow.draw being called.  This is\n\
                    intended to be used for any required setup  state initialisation and is\n\
                    called once for each pass in the effect.\n\
            \n\
                @param pass\n\
                    Indicates the pass number to be initialised (starting at pass 0).\n\
            \n\
                \note\n\
                    Note that this function is called  e after any standard state\n\
                    initialisation that might be peformed by the Renderer module.\n\
                *\n" );
        
        }
        { //::CEGUI::RenderEffect::realiseGeometry
        
            typedef bool ( ::CEGUI::RenderEffect::*realiseGeometry_function_type )( ::CEGUI::RenderingWindow &,::CEGUI::GeometryBuffer & ) ;
            
            RenderEffect_exposer.def( 
                "realiseGeometry"
                , bp::pure_virtual( realiseGeometry_function_type(&::CEGUI::RenderEffect::realiseGeometry) )
                , ( bp::arg("window"), bp::arg("geometry") )
                , "*!\n\
                \n\
                    Function called to generate geometry for the RenderingWindow.\n\
            \n\
                    The geometry generated should be fully unclipped and window local.  The\n\
                    origin for the geometry is located at the top-left corner.\n\
            \n\
                @param window\n\
                    The RenderingWindow object that is being processed.\n\
            \n\
                @param geometry\n\
                    GeometryBuffer object where the generated geometry should be added.\n\
                    This object will be cleared before this function is invoked.\n\
            \n\
                @return\n\
                    boolean value indicating whether the RenderingWindow should generate\n\
                    it's own geometry.\n\
                    - true if the RenderingWindow should generate it's own geometry.  You\n\
                    will usually only return true if you do not need to use custom geometry.\n\
                    - false if you have added any required geometry needed to represent the\n\
                    RenderingWindow.\n\
                *\n" );
        
        }
        { //::CEGUI::RenderEffect::update
        
            typedef bool ( ::CEGUI::RenderEffect::*update_function_type )( float const,::CEGUI::RenderingWindow & ) ;
            
            RenderEffect_exposer.def( 
                "update"
                , bp::pure_virtual( update_function_type(&::CEGUI::RenderEffect::update) )
                , ( bp::arg("elapsed"), bp::arg("window") )
                , "*!\n\
                \n\
                    Function called to perform any time based updates on the RenderEffect\n\
                    state.\n\
            \n\
                \note\n\
                    This function should only affect the internal state of the RenderEffect\n\
                    object.  This function should definitely  e not be used to directly\n\
                    affect any render states of the underlying rendering API or engine.\n\
            \n\
                @param elapsed\n\
                    The number of seconds that have elapsed since the last time this\n\
                    function was called.\n\
            \n\
                @param window\n\
                    RenderingWindow object that the RenderEffect is being applied to.\n\
            \n\
                @return\n\
                    boolean that indicates whether the window geometry will still be valid\n\
                    after the update.\n\
                *\n" );
        
        }
    }

}
