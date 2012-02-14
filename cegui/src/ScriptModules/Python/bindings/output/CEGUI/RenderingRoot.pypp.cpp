// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "RenderingRoot.pypp.hpp"

namespace bp = boost::python;

struct RenderingRoot_wrapper : CEGUI::RenderingRoot, bp::wrapper< CEGUI::RenderingRoot > {

    RenderingRoot_wrapper(::CEGUI::RenderTarget & target )
    : CEGUI::RenderingRoot( boost::ref(target) )
      , bp::wrapper< CEGUI::RenderingRoot >(){
        // constructor
    
    }

    void attachWindow( ::CEGUI::RenderingWindow & w ){
        CEGUI::RenderingSurface::attachWindow( boost::ref(w) );
    }

    virtual void destroyRenderingWindow( ::CEGUI::RenderingWindow & window ) {
        if( bp::override func_destroyRenderingWindow = this->get_override( "destroyRenderingWindow" ) )
            func_destroyRenderingWindow( boost::ref(window) );
        else{
            this->CEGUI::RenderingSurface::destroyRenderingWindow( boost::ref(window) );
        }
    }
    
    void default_destroyRenderingWindow( ::CEGUI::RenderingWindow & window ) {
        CEGUI::RenderingSurface::destroyRenderingWindow( boost::ref(window) );
    }

    void detatchWindow( ::CEGUI::RenderingWindow & w ){
        CEGUI::RenderingSurface::detatchWindow( boost::ref(w) );
    }

    virtual void draw(  ) {
        if( bp::override func_draw = this->get_override( "draw" ) )
            func_draw(  );
        else{
            this->CEGUI::RenderingSurface::draw(  );
        }
    }
    
    void default_draw(  ) {
        CEGUI::RenderingSurface::draw( );
    }

    void draw( ::CEGUI::RenderQueue const & queue, ::CEGUI::RenderQueueEventArgs & args ){
        CEGUI::RenderingSurface::draw( boost::ref(queue), boost::ref(args) );
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

    virtual void invalidate(  ) {
        if( bp::override func_invalidate = this->get_override( "invalidate" ) )
            func_invalidate(  );
        else{
            this->CEGUI::RenderingSurface::invalidate(  );
        }
    }
    
    void default_invalidate(  ) {
        CEGUI::RenderingSurface::invalidate( );
    }

    virtual bool isRenderingWindow(  ) const  {
        if( bp::override func_isRenderingWindow = this->get_override( "isRenderingWindow" ) )
            return func_isRenderingWindow(  );
        else{
            return this->CEGUI::RenderingSurface::isRenderingWindow(  );
        }
    }
    
    bool default_isRenderingWindow(  ) const  {
        return CEGUI::RenderingSurface::isRenderingWindow( );
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

    virtual void transferRenderingWindow( ::CEGUI::RenderingWindow & window ) {
        if( bp::override func_transferRenderingWindow = this->get_override( "transferRenderingWindow" ) )
            func_transferRenderingWindow( boost::ref(window) );
        else{
            this->CEGUI::RenderingSurface::transferRenderingWindow( boost::ref(window) );
        }
    }
    
    void default_transferRenderingWindow( ::CEGUI::RenderingWindow & window ) {
        CEGUI::RenderingSurface::transferRenderingWindow( boost::ref(window) );
    }

};

void register_RenderingRoot_class(){

    { //::CEGUI::RenderingRoot
        typedef bp::class_< RenderingRoot_wrapper, bp::bases< CEGUI::RenderingSurface >, boost::noncopyable > RenderingRoot_exposer_t;
        RenderingRoot_exposer_t RenderingRoot_exposer = RenderingRoot_exposer_t( "RenderingRoot", bp::init< CEGUI::RenderTarget & >(( bp::arg("target") ), "! Constructor.\n") );
        bp::scope RenderingRoot_scope( RenderingRoot_exposer );
        bp::implicitly_convertible< CEGUI::RenderTarget &, CEGUI::RenderingRoot >();
        { //::CEGUI::RenderingSurface::attachWindow
        
            typedef void ( RenderingRoot_wrapper::*attachWindow_function_type )( ::CEGUI::RenderingWindow & ) ;
            
            RenderingRoot_exposer.def( 
                "attachWindow"
                , attachWindow_function_type( &RenderingRoot_wrapper::attachWindow )
                , ( bp::arg("w") )
                , "! attach ReneringWindow from this RenderingSurface\n" );
        
        }
        { //::CEGUI::RenderingSurface::createRenderingWindow
        
            typedef ::CEGUI::RenderingWindow & ( ::CEGUI::RenderingSurface::*createRenderingWindow_function_type )( ::CEGUI::TextureTarget & ) ;
            
            RenderingRoot_exposer.def( 
                "createRenderingWindow"
                , createRenderingWindow_function_type(&::CEGUI::RenderingSurface::createRenderingWindow)
                , ( bp::arg("target") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::CEGUI::RenderingSurface::destroyRenderingWindow
        
            typedef void ( ::CEGUI::RenderingSurface::*destroyRenderingWindow_function_type )( ::CEGUI::RenderingWindow & ) ;
            typedef void ( RenderingRoot_wrapper::*default_destroyRenderingWindow_function_type )( ::CEGUI::RenderingWindow & ) ;
            
            RenderingRoot_exposer.def( 
                "destroyRenderingWindow"
                , destroyRenderingWindow_function_type(&::CEGUI::RenderingSurface::destroyRenderingWindow)
                , default_destroyRenderingWindow_function_type(&RenderingRoot_wrapper::default_destroyRenderingWindow)
                , ( bp::arg("window") ) );
        
        }
        { //::CEGUI::RenderingSurface::detatchWindow
        
            typedef void ( RenderingRoot_wrapper::*detatchWindow_function_type )( ::CEGUI::RenderingWindow & ) ;
            
            RenderingRoot_exposer.def( 
                "detatchWindow"
                , detatchWindow_function_type( &RenderingRoot_wrapper::detatchWindow )
                , ( bp::arg("w") )
                , "! detatch ReneringWindow from this RenderingSurface\n" );
        
        }
        { //::CEGUI::RenderingSurface::draw
        
            typedef void ( ::CEGUI::RenderingSurface::*draw_function_type )(  ) ;
            typedef void ( RenderingRoot_wrapper::*default_draw_function_type )(  ) ;
            
            RenderingRoot_exposer.def( 
                "draw"
                , draw_function_type(&::CEGUI::RenderingSurface::draw)
                , default_draw_function_type(&RenderingRoot_wrapper::default_draw) );
        
        }
        { //::CEGUI::RenderingSurface::draw
        
            typedef void ( RenderingRoot_wrapper::*draw_function_type )( ::CEGUI::RenderQueue const &,::CEGUI::RenderQueueEventArgs & ) ;
            
            RenderingRoot_exposer.def( 
                "draw"
                , draw_function_type( &RenderingRoot_wrapper::draw )
                , ( bp::arg("queue"), bp::arg("args") )
                , "! draw a rendering queue, firing events before and after.\n" );
        
        }
        { //::CEGUI::EventSet::fireEvent
        
            typedef void ( ::CEGUI::EventSet::*fireEvent_function_type )( ::CEGUI::String const &,::CEGUI::EventArgs &,::CEGUI::String const & ) ;
            typedef void ( RenderingRoot_wrapper::*default_fireEvent_function_type )( ::CEGUI::String const &,::CEGUI::EventArgs &,::CEGUI::String const & ) ;
            
            RenderingRoot_exposer.def( 
                "fireEvent"
                , fireEvent_function_type(&::CEGUI::EventSet::fireEvent)
                , default_fireEvent_function_type(&RenderingRoot_wrapper::default_fireEvent)
                , ( bp::arg("name"), bp::arg("args"), bp::arg("eventNamespace")="" ) );
        
        }
        { //::CEGUI::EventSet::fireEvent_impl
        
            typedef void ( RenderingRoot_wrapper::*fireEvent_impl_function_type )( ::CEGUI::String const &,::CEGUI::EventArgs & ) ;
            
            RenderingRoot_exposer.def( 
                "fireEvent_impl"
                , fireEvent_impl_function_type( &RenderingRoot_wrapper::fireEvent_impl )
                , ( bp::arg("name"), bp::arg("args") )
                , "! Implementation event firing member\n" );
        
        }
        { //::CEGUI::EventSet::getScriptModule
        
            typedef ::CEGUI::ScriptModule * ( RenderingRoot_wrapper::*getScriptModule_function_type )(  ) const;
            
            RenderingRoot_exposer.def( 
                "getScriptModule"
                , getScriptModule_function_type( &RenderingRoot_wrapper::getScriptModule )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "! Implementation event firing member\n\
            ! Helper to return the script module pointer or throw.\n" );
        
        }
        { //::CEGUI::RenderingSurface::invalidate
        
            typedef void ( ::CEGUI::RenderingSurface::*invalidate_function_type )(  ) ;
            typedef void ( RenderingRoot_wrapper::*default_invalidate_function_type )(  ) ;
            
            RenderingRoot_exposer.def( 
                "invalidate"
                , invalidate_function_type(&::CEGUI::RenderingSurface::invalidate)
                , default_invalidate_function_type(&RenderingRoot_wrapper::default_invalidate) );
        
        }
        { //::CEGUI::RenderingSurface::isRenderingWindow
        
            typedef bool ( ::CEGUI::RenderingSurface::*isRenderingWindow_function_type )(  ) const;
            typedef bool ( RenderingRoot_wrapper::*default_isRenderingWindow_function_type )(  ) const;
            
            RenderingRoot_exposer.def( 
                "isRenderingWindow"
                , isRenderingWindow_function_type(&::CEGUI::RenderingSurface::isRenderingWindow)
                , default_isRenderingWindow_function_type(&RenderingRoot_wrapper::default_isRenderingWindow) );
        
        }
        { //::CEGUI::EventSet::subscribeScriptedEvent
        
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( ::CEGUI::EventSet::*subscribeScriptedEvent_function_type )( ::CEGUI::String const &,::CEGUI::String const & ) ;
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( RenderingRoot_wrapper::*default_subscribeScriptedEvent_function_type )( ::CEGUI::String const &,::CEGUI::String const & ) ;
            
            RenderingRoot_exposer.def( 
                "subscribeScriptedEvent"
                , subscribeScriptedEvent_function_type(&::CEGUI::EventSet::subscribeScriptedEvent)
                , default_subscribeScriptedEvent_function_type(&RenderingRoot_wrapper::default_subscribeScriptedEvent)
                , ( bp::arg("name"), bp::arg("subscriber_name") ) );
        
        }
        { //::CEGUI::EventSet::subscribeScriptedEvent
        
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( ::CEGUI::EventSet::*subscribeScriptedEvent_function_type )( ::CEGUI::String const &,unsigned int,::CEGUI::String const & ) ;
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( RenderingRoot_wrapper::*default_subscribeScriptedEvent_function_type )( ::CEGUI::String const &,unsigned int,::CEGUI::String const & ) ;
            
            RenderingRoot_exposer.def( 
                "subscribeScriptedEvent"
                , subscribeScriptedEvent_function_type(&::CEGUI::EventSet::subscribeScriptedEvent)
                , default_subscribeScriptedEvent_function_type(&RenderingRoot_wrapper::default_subscribeScriptedEvent)
                , ( bp::arg("name"), bp::arg("group"), bp::arg("subscriber_name") ) );
        
        }
        { //::CEGUI::RenderingSurface::transferRenderingWindow
        
            typedef void ( ::CEGUI::RenderingSurface::*transferRenderingWindow_function_type )( ::CEGUI::RenderingWindow & ) ;
            typedef void ( RenderingRoot_wrapper::*default_transferRenderingWindow_function_type )( ::CEGUI::RenderingWindow & ) ;
            
            RenderingRoot_exposer.def( 
                "transferRenderingWindow"
                , transferRenderingWindow_function_type(&::CEGUI::RenderingSurface::transferRenderingWindow)
                , default_transferRenderingWindow_function_type(&RenderingRoot_wrapper::default_transferRenderingWindow)
                , ( bp::arg("window") ) );
        
        }
    }

}
