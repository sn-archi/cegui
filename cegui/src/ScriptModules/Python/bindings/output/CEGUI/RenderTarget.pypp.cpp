// This file has been generated by Py++.

#include "boost/python.hpp"
#include "generators/include/python_CEGUI.h"
#include "RenderTarget.pypp.hpp"

namespace bp = boost::python;

struct RenderTarget_wrapper : CEGUI::RenderTarget, bp::wrapper< CEGUI::RenderTarget > {

    RenderTarget_wrapper()
    : CEGUI::RenderTarget()
      , bp::wrapper< CEGUI::RenderTarget >(){
        // null constructor
        
    }

    virtual void activate(  ){
        bp::override func_activate = this->get_override( "activate" );
        func_activate(  );
    }

    virtual void deactivate(  ){
        bp::override func_deactivate = this->get_override( "deactivate" );
        func_deactivate(  );
    }

    virtual void draw( ::CEGUI::GeometryBuffer const & buffer ){
        bp::override func_draw = this->get_override( "draw" );
        func_draw( boost::ref(buffer) );
    }

    virtual void draw( ::CEGUI::RenderQueue const & queue ){
        bp::override func_draw = this->get_override( "draw" );
        func_draw( boost::ref(queue) );
    }

    virtual ::CEGUI::Rectf const & getArea(  ) const {
        throw std::logic_error("warning W1049: This method could not be overriden in Python - method returns reference to local variable!");
    }

    virtual bool isImageryCache(  ) const {
        bp::override func_isImageryCache = this->get_override( "isImageryCache" );
        return func_isImageryCache(  );
    }

    virtual void setArea( ::CEGUI::Rectf const & area ){
        bp::override func_setArea = this->get_override( "setArea" );
        func_setArea( boost::ref(area) );
    }

    virtual void unprojectPoint( ::CEGUI::GeometryBuffer const & buff, ::CEGUI::Vector2f const & p_in, ::CEGUI::Vector2f & p_out ) const {
        bp::override func_unprojectPoint = this->get_override( "unprojectPoint" );
        func_unprojectPoint( boost::ref(buff), boost::ref(p_in), boost::ref(p_out) );
    }

    virtual void fireEvent( ::CEGUI::String const & name, ::CEGUI::EventArgs & args, ::CEGUI::String const & eventNamespace="" ) {
        if( bp::override func_fireEvent = this->get_override( "fireEvent" ) )
            func_fireEvent( boost::ref(name), boost::ref(args), boost::ref(eventNamespace) );
        else{
            this->CEGUI::EventSet::fireEvent( boost::ref(name), boost::ref(args), boost::ref(eventNamespace) );
        }
    }
    
    void default_fireEvent( ::CEGUI::String const & name, ::CEGUI::EventArgs & args, ::CEGUI::String const & eventNamespace="" ) {
        CEGUI::EventSet::fireEvent( boost::ref(name), boost::ref(args), boost::ref(eventNamespace) );
    }

    void fireEvent_impl( ::CEGUI::String const & name, ::CEGUI::EventArgs & args ){
        CEGUI::EventSet::fireEvent_impl( boost::ref(name), boost::ref(args) );
    }

    ::CEGUI::ScriptModule * getScriptModule(  ) const {
        return CEGUI::EventSet::getScriptModule(  );
    }

    virtual ::CEGUI::RefCounted< CEGUI::BoundSlot > subscribeScriptedEvent( ::CEGUI::String const & name, ::CEGUI::String const & subscriber_name ) {
        if( bp::override func_subscribeScriptedEvent = this->get_override( "subscribeScriptedEvent" ) )
            return func_subscribeScriptedEvent( boost::ref(name), boost::ref(subscriber_name) );
        else{
            return this->CEGUI::EventSet::subscribeScriptedEvent( boost::ref(name), boost::ref(subscriber_name) );
        }
    }
    
    ::CEGUI::RefCounted< CEGUI::BoundSlot > default_subscribeScriptedEvent( ::CEGUI::String const & name, ::CEGUI::String const & subscriber_name ) {
        return CEGUI::EventSet::subscribeScriptedEvent( boost::ref(name), boost::ref(subscriber_name) );
    }

    virtual ::CEGUI::RefCounted< CEGUI::BoundSlot > subscribeScriptedEvent( ::CEGUI::String const & name, unsigned int group, ::CEGUI::String const & subscriber_name ) {
        if( bp::override func_subscribeScriptedEvent = this->get_override( "subscribeScriptedEvent" ) )
            return func_subscribeScriptedEvent( boost::ref(name), group, boost::ref(subscriber_name) );
        else{
            return this->CEGUI::EventSet::subscribeScriptedEvent( boost::ref(name), group, boost::ref(subscriber_name) );
        }
    }
    
    ::CEGUI::RefCounted< CEGUI::BoundSlot > default_subscribeScriptedEvent( ::CEGUI::String const & name, unsigned int group, ::CEGUI::String const & subscriber_name ) {
        return CEGUI::EventSet::subscribeScriptedEvent( boost::ref(name), group, boost::ref(subscriber_name) );
    }

};

void register_RenderTarget_class(){

    { //::CEGUI::RenderTarget
        typedef bp::class_< RenderTarget_wrapper, bp::bases< CEGUI::EventSet >, boost::noncopyable > RenderTarget_exposer_t;
        RenderTarget_exposer_t RenderTarget_exposer = RenderTarget_exposer_t( "RenderTarget" );
        bp::scope RenderTarget_scope( RenderTarget_exposer );
        { //::CEGUI::RenderTarget::activate
        
            typedef void ( ::CEGUI::RenderTarget::*activate_function_type )(  ) ;
            
            RenderTarget_exposer.def( 
                "activate"
                , bp::pure_virtual( activate_function_type(&::CEGUI::RenderTarget::activate) )
                , "*!\n\
                \n\
                    Activate the render target and put it in a state ready to be drawn to.\n\
            \n\
                \note\n\
                    You MUST call this before doing any rendering - if you do not call this,\n\
                    in the unlikely event that your application actually works, it will\n\
                    likely stop working in some future version.\n\
                *\n" );
        
        }
        { //::CEGUI::RenderTarget::deactivate
        
            typedef void ( ::CEGUI::RenderTarget::*deactivate_function_type )(  ) ;
            
            RenderTarget_exposer.def( 
                "deactivate"
                , bp::pure_virtual( deactivate_function_type(&::CEGUI::RenderTarget::deactivate) )
                , "*!\n\
                \n\
                    Deactivate the render target after having completed rendering.\n\
            \n\
                \note\n\
                    You MUST call this after you finish rendering to the target - if you do\n\
                    not call this, in the unlikely event that your application actually\n\
                    works, it will likely stop working in some future version.\n\
                *\n" );
        
        }
        { //::CEGUI::RenderTarget::draw
        
            typedef void ( ::CEGUI::RenderTarget::*draw_function_type )( ::CEGUI::GeometryBuffer const & ) ;
            
            RenderTarget_exposer.def( 
                "draw"
                , bp::pure_virtual( draw_function_type(&::CEGUI::RenderTarget::draw) )
                , ( bp::arg("buffer") )
                , "*!\n\
                \n\
                    Draw geometry from the given GeometryBuffer onto the surface that\n\
                    this RenderTarget represents.\n\
            \n\
                @param buffer\n\
                    GeometryBuffer object holding the geometry that should be drawn to the\n\
                    RenderTarget.\n\
                *\n" );
        
        }
        { //::CEGUI::RenderTarget::draw
        
            typedef void ( ::CEGUI::RenderTarget::*draw_function_type )( ::CEGUI::RenderQueue const & ) ;
            
            RenderTarget_exposer.def( 
                "draw"
                , bp::pure_virtual( draw_function_type(&::CEGUI::RenderTarget::draw) )
                , ( bp::arg("queue") )
                , "*!\n\
                \n\
                    Draw geometry from the given RenderQueue onto the surface that\n\
                    this RenderTarget represents.\n\
            \n\
                @param queue\n\
                    RenderQueue object holding the geometry that should be drawn to the\n\
                    RenderTarget.\n\
                *\n" );
        
        }
        { //::CEGUI::RenderTarget::getArea
        
            typedef ::CEGUI::Rectf const & ( ::CEGUI::RenderTarget::*getArea_function_type )(  ) const;
            
            RenderTarget_exposer.def( 
                "getArea"
                , bp::pure_virtual( getArea_function_type(&::CEGUI::RenderTarget::getArea) )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "*!\n\
                \n\
                    Return the area defined for this RenderTarget.\n\
            \n\
                @return\n\
                    Rect object describing the currently defined area for this RenderTarget.\n\
                *\n" );
        
        }
        { //::CEGUI::RenderTarget::isImageryCache
        
            typedef bool ( ::CEGUI::RenderTarget::*isImageryCache_function_type )(  ) const;
            
            RenderTarget_exposer.def( 
                "isImageryCache"
                , bp::pure_virtual( isImageryCache_function_type(&::CEGUI::RenderTarget::isImageryCache) )
                , "*!\n\
                \n\
                    Return whether the RenderTarget is an implementation that caches\n\
                    actual rendered imagery.\n\
            \n\
                    Typically it is expected that texture based RenderTargets would return\n\
                    true in response to this call.  Other types of RenderTarget, like\n\
                    view port based targets, will more likely return false.\n\
            \n\
                @return\n\
                    - true if the RenderTarget does cache rendered imagery.\n\
                    - false if the RenderTarget does not cache rendered imagery.\n\
                *\n" );
        
        }
        { //::CEGUI::RenderTarget::setArea
        
            typedef void ( ::CEGUI::RenderTarget::*setArea_function_type )( ::CEGUI::Rectf const & ) ;
            
            RenderTarget_exposer.def( 
                "setArea"
                , bp::pure_virtual( setArea_function_type(&::CEGUI::RenderTarget::setArea) )
                , ( bp::arg("area") )
                , "*!\n\
                \n\
                    Set the area for this RenderTarget.  The exact action this function\n\
                    will take depends upon what the concrete class is representing.  For\n\
                    example, with a 'view port' style RenderTarget, this should set the area\n\
                    that the view port occupies on the display (or rendering window).\n\
            \n\
                @param area\n\
                    Rect object describing the new area to be assigned to the RenderTarget.\n\
            \n\
                \note\n\
                    When implementing this function, you should be sure to fire the event\n\
                    RenderTarget.EventAreaChanged so that interested parties can know that\n\
                    the change has occurred.\n\
            \n\
                @exception InvalidRequestException\n\
                    May be thrown if the RenderTarget does not support setting or changing\n\
                    its area, or if the area change can not be satisfied for some reason.\n\
                *\n" );
        
        }
        { //::CEGUI::RenderTarget::unprojectPoint
        
            typedef void ( ::CEGUI::RenderTarget::*unprojectPoint_function_type )( ::CEGUI::GeometryBuffer const &,::CEGUI::Vector2f const &,::CEGUI::Vector2f & ) const;
            
            RenderTarget_exposer.def( 
                "unprojectPoint"
                , bp::pure_virtual( unprojectPoint_function_type(&::CEGUI::RenderTarget::unprojectPoint) )
                , ( bp::arg("buff"), bp::arg("p_in"), bp::arg("p_out") )
                , "*!\n\
            \n\
                Take point  p_in unproject it and put the result in  p_out.\n\
                Resulting point is local to GeometryBuffer  buff.\n\
            *\n" );
        
        }
        RenderTarget_exposer.add_static_property( "EventAreaChanged"
                        , bp::make_getter( &CEGUI::RenderTarget::EventAreaChanged
                                , bp::return_value_policy< bp::return_by_value >() ) );
        { //::CEGUI::EventSet::fireEvent
        
            typedef void ( ::CEGUI::EventSet::*fireEvent_function_type )( ::CEGUI::String const &,::CEGUI::EventArgs &,::CEGUI::String const & ) ;
            typedef void ( RenderTarget_wrapper::*default_fireEvent_function_type )( ::CEGUI::String const &,::CEGUI::EventArgs &,::CEGUI::String const & ) ;
            
            RenderTarget_exposer.def( 
                "fireEvent"
                , fireEvent_function_type(&::CEGUI::EventSet::fireEvent)
                , default_fireEvent_function_type(&RenderTarget_wrapper::default_fireEvent)
                , ( bp::arg("name"), bp::arg("args"), bp::arg("eventNamespace")="" ) );
        
        }
        { //::CEGUI::EventSet::fireEvent_impl
        
            typedef void ( RenderTarget_wrapper::*fireEvent_impl_function_type )( ::CEGUI::String const &,::CEGUI::EventArgs & ) ;
            
            RenderTarget_exposer.def( 
                "fireEvent_impl"
                , fireEvent_impl_function_type( &RenderTarget_wrapper::fireEvent_impl )
                , ( bp::arg("name"), bp::arg("args") )
                , "! Implementation event firing member\n" );
        
        }
        { //::CEGUI::EventSet::getScriptModule
        
            typedef ::CEGUI::ScriptModule * ( RenderTarget_wrapper::*getScriptModule_function_type )(  ) const;
            
            RenderTarget_exposer.def( 
                "getScriptModule"
                , getScriptModule_function_type( &RenderTarget_wrapper::getScriptModule )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "! Implementation event firing member\n\
            ! Helper to return the script module pointer or throw.\n" );
        
        }
        { //::CEGUI::EventSet::subscribeScriptedEvent
        
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( ::CEGUI::EventSet::*subscribeScriptedEvent_function_type )( ::CEGUI::String const &,::CEGUI::String const & ) ;
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( RenderTarget_wrapper::*default_subscribeScriptedEvent_function_type )( ::CEGUI::String const &,::CEGUI::String const & ) ;
            
            RenderTarget_exposer.def( 
                "subscribeScriptedEvent"
                , subscribeScriptedEvent_function_type(&::CEGUI::EventSet::subscribeScriptedEvent)
                , default_subscribeScriptedEvent_function_type(&RenderTarget_wrapper::default_subscribeScriptedEvent)
                , ( bp::arg("name"), bp::arg("subscriber_name") ) );
        
        }
        { //::CEGUI::EventSet::subscribeScriptedEvent
        
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( ::CEGUI::EventSet::*subscribeScriptedEvent_function_type )( ::CEGUI::String const &,unsigned int,::CEGUI::String const & ) ;
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( RenderTarget_wrapper::*default_subscribeScriptedEvent_function_type )( ::CEGUI::String const &,unsigned int,::CEGUI::String const & ) ;
            
            RenderTarget_exposer.def( 
                "subscribeScriptedEvent"
                , subscribeScriptedEvent_function_type(&::CEGUI::EventSet::subscribeScriptedEvent)
                , default_subscribeScriptedEvent_function_type(&RenderTarget_wrapper::default_subscribeScriptedEvent)
                , ( bp::arg("name"), bp::arg("group"), bp::arg("subscriber_name") ) );
        
        }
    }

}
