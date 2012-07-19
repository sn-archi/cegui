/***********************************************************************
filename:   WidgetDemo.cpp
created:    12/7/2012
author:     Lukas E Meindl
*************************************************************************/
/***************************************************************************
*   Copyright (C) 2004 - 2012 Paul D Turner & Thce CEGUI Development Team
*
*   Permission is hereby granted, free of charge, to any person obtaining
*   a copy of this software and associated documentation files (the
*   "Software"), to deal in the Software without restriction, including
*   without limitation the rights to use, copy, modify, merge, publish,
*   distribute, sublicense, and/or sell copies of the Software, and to
*   permit persons to whom the Software is furnished to do so, subject to
*   the following conditions:
*
*   The above copyright notice and this permission notice shall be
*   included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
*   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
*   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
*   OTHER DEALINGS IN THE SOFTWARE.
***************************************************************************/
#include "WidgetDemo.h"

#include "CEGUI/CEGUI.h"

#include <cmath>


using namespace CEGUI;

//----------------------------------------------------------------------------//
// Sample sub-class for ListboxTextItem that auto-sets the selection brush
// image.  This saves doing it manually every time in the code.
//----------------------------------------------------------------------------//

class MyListItem : public ListboxTextItem
{
public:
    MyListItem(const String& text, CEGUI::uint item_id = 0) :
      ListboxTextItem(text, item_id)
      {
          setSelectionBrushImage("Vanilla-Images/GenericBrush");
      }
};

//----------------------------------------------------------------------------//
// Helper class to deal with the different event names, used to output the name
// of the event for generic events
//----------------------------------------------------------------------------//
class EventHandlerObject
{
public: 
    EventHandlerObject(CEGUI::String eventName, WidgetDemo* owner);
    bool handleEvent(const CEGUI::EventArgs& args);
private:
    CEGUI::String d_eventName;
    WidgetDemo* d_owner;
};

EventHandlerObject::EventHandlerObject(CEGUI::String eventName, WidgetDemo* owner)
    : d_eventName(eventName),
    d_owner(owner)
{
}

bool EventHandlerObject::handleEvent(const CEGUI::EventArgs& args)
{
    d_owner->handleWidgetEventFired(d_eventName);

    return true;
}


//----------------------------------------------------------------------------//
// The following are for the main WidgetDemo class.
//----------------------------------------------------------------------------//

/*************************************************************************
Sample specific initialisation goes here.
*************************************************************************/
const CEGUI::String WidgetDemo::s_widgetDemoWindowPrefix = "WidgetDemoWindow_";

bool WidgetDemo::initialise(CEGUI::GUIContext* guiContext)
{
    using namespace CEGUI;

    d_usedFiles = CEGUI::String(__FILE__);
    d_guiContext = guiContext;

    // load scheme and set up defaults
    SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
    SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");
    SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
    SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
    d_guiContext->getMouseCursor().setDefaultImage("Vanilla-Images/MouseArrow");

    // load font and setup default if not loaded via scheme
    Font& defaultFont = FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
    FontManager::getSingleton().createFromFile("DejaVuSans-10.font");
    // Set default font for the gui context
    guiContext->setDefaultFont(&defaultFont);

    // load an image to use as a background
    if( !ImageManager::getSingleton().isDefined("SpaceBackgroundImage") )
        ImageManager::getSingleton().addFromImageFile("SpaceBackgroundImage", "SpaceBackground.jpg");

    // Retrieve the available widget types and save them inside a map
    initialiseAvailableWidgetsMap();
    initialiseEventHandlerObjects();

    d_currentlyDisplayedWidgetRoot = 0;
    //Create windows and initialise them 
    createLayout();

    d_guiContext->subscribeEvent(CEGUI::GUIContext::EventRenderQueueEnded, Event::Subscriber(&WidgetDemo::handleRenderingEnded, this));
    d_guiContext->getRootWindow()->subscribeEvent(CEGUI::Window::EventUpdated, Event::Subscriber(&WidgetDemo::handleRootWindowUpdate, this));

    // success!
    return true;
}

/*************************************************************************
Cleans up resources allocated in the initialiseSample call.
*************************************************************************/
void WidgetDemo::deinitialise()
{
    if(d_currentlyDisplayedWidgetRoot != 0)
        d_widgetDisplayWindowInnerWindow->removeChild(d_currentlyDisplayedWidgetRoot);

    destroyWidgetWindows();

    deinitWidgetListItems();
}

bool WidgetDemo::handleSkinSelectionAccepted(const CEGUI::EventArgs& args)
{
    const WindowEventArgs& winArgs = static_cast<const CEGUI::WindowEventArgs&>(args);

    CEGUI::Combobox* combobox = static_cast<CEGUI::Combobox*>(winArgs.window);
    CEGUI::String schemeName = combobox->getSelectedItem()->getText();

    WidgetListType& widgetsList = d_skinListItemsMap[schemeName];

    d_widgetSelectorListbox->resetList();

    for(unsigned int i = 0; i < widgetsList.size(); ++i)
    {
        MyListItem* item = widgetsList[i];
        d_widgetSelectorListbox->addItem(item);
    }

    // event was handled
    return true;
}

bool WidgetDemo::handleRenderingEnded(const CEGUI::EventArgs& args)
{
    d_windowLightMouseMoveEvent->disable();
    d_windowLightUpdatedEvent->disable();

    return true;
}

bool WidgetDemo::handleRootWindowUpdate(const CEGUI::EventArgs& args)
{
    const CEGUI::UpdateEventArgs& updateArgs = static_cast<const CEGUI::UpdateEventArgs&>(args);
    float passedTime = updateArgs.d_timeSinceLastFrame;

    if(d_currentlyDisplayedWidgetRoot == 0)
        return true;

    CEGUI::ProgressBar* progressBar = dynamic_cast<CEGUI::ProgressBar*>(d_currentlyDisplayedWidgetRoot);
    if(progressBar != 0)
    {
        float newProgress = progressBar->getProgress() + passedTime * 0.2f;
        if(newProgress < 1.f)
            progressBar->setProgress(newProgress);
    }


    return true;
}

bool WidgetDemo::handleWidgetSelectionChanged(const CEGUI::EventArgs& args)
{
    const WindowEventArgs& winArgs = static_cast<const CEGUI::WindowEventArgs&>(args);

    CEGUI::Listbox* listbox = static_cast<CEGUI::Listbox*>(winArgs.window);
    CEGUI::ListboxItem* skinListboxItem = d_skinSelectionCombobox->getSelectedItem();
    CEGUI::ListboxItem* widgetListboxItem = listbox->getFirstSelectedItem();

    if(!skinListboxItem || !widgetListboxItem)
        return true;

    d_widgetsEventsLog->setText("");

    //Recreate the widget's type
    CEGUI::String widgetTypeString;
    if(skinListboxItem->getText().compare("No Skin") != 0)
        widgetTypeString= skinListboxItem->getText() + "/";

    widgetTypeString += widgetListboxItem->getText();

    //Remove previous children window from the widget-display window
    if(d_currentlyDisplayedWidgetRoot)
        d_widgetDisplayWindowInnerWindow->removeChild(d_currentlyDisplayedWidgetRoot);


    CEGUI::Window* widgetWindowRoot;

    std::map<CEGUI::String, CEGUI::Window*>::iterator iter = d_widgetsMap.find(widgetTypeString);
    if(iter != d_widgetsMap.end())
    {
        widgetWindowRoot = iter->second;
    }
    else
    {
        widgetWindowRoot = createWidget(widgetTypeString, widgetListboxItem->getText());

        d_widgetsMap[widgetTypeString] = widgetWindowRoot;
    }

    d_widgetDisplayWindowInnerWindow->addChild(widgetWindowRoot);
    d_currentlyDisplayedWidgetRoot = widgetWindowRoot;

    d_widgetDisplayWindow->setText("Demo of widget: \"" + widgetTypeString + "\"");


    CEGUI::ProgressBar* progressBar = dynamic_cast<CEGUI::ProgressBar*>(d_currentlyDisplayedWidgetRoot);
    if(progressBar != 0)
        progressBar->setProgress(0.f);

    // event was handled
    return true;
}


void WidgetDemo::initialiseAvailableWidgetsMap()
{
    //Retrieve the widget look types and add a Listboxitem for each widget, to the right scheme in the map
    CEGUI::WindowFactoryManager& windowFactorymanager = CEGUI::WindowFactoryManager::getSingleton();
    CEGUI::WindowFactoryManager::FalagardMappingIterator falMappingIter = windowFactorymanager.getFalagardMappingIterator();

    while(!falMappingIter.isAtEnd())
    {
        CEGUI::String falagardBaseType = falMappingIter.getCurrentValue().d_windowType;

        int slashPos = falagardBaseType.find_first_of('/');
        CEGUI::String group = falagardBaseType.substr(0, slashPos);
        CEGUI::String name = falagardBaseType.substr(slashPos + 1, falagardBaseType.size() - 1);

        if(group.compare("SampleBrowserSkin") != 0)
        {

            std::map<CEGUI::String, WidgetListType>::iterator iter = d_skinListItemsMap.find(group);
            if(iter == d_skinListItemsMap.end())
            {
                //Create new list
                d_skinListItemsMap[group];
            }

            WidgetListType& widgetList = d_skinListItemsMap.find(group)->second;
            addItemToWidgetList(name, widgetList);
        }

        ++falMappingIter;
    }

    //Add the default types as well
    d_skinListItemsMap["No Skin"];
    WidgetListType& defaultWidgetsList = d_skinListItemsMap["No Skin"];

    addItemToWidgetList("DefaultWindow", defaultWidgetsList);
    addItemToWidgetList("DragContainer", defaultWidgetsList);
    addItemToWidgetList("VerticalLayoutContainer", defaultWidgetsList);
    addItemToWidgetList("HorizontalLayoutContainer", defaultWidgetsList);
    addItemToWidgetList("GridLayoutContainer", defaultWidgetsList);
}


void WidgetDemo::createLayout()
{
    // we will use of the WindowManager.
    WindowManager& winMgr = WindowManager::getSingleton();

    // here we will use a StaticImage as the root, then we can use it to place a background image
    Window* background = winMgr.createWindow("TaharezLook/StaticImage", "BackgroundWindow");
    initialiseBackgroundWindow(background);
    // install this as the root GUI sheet
    d_guiContext->setRootWindow(background);

    d_skinSelectionCombobox = static_cast<CEGUI::Combobox*>(winMgr.createWindow("Vanilla/Combobox", "SkinSelectionCombobox"));
    initialiseSkinCombobox();
    background->addChild(d_skinSelectionCombobox);

    CEGUI::Window* widgetSelectorContainer = winMgr.createWindow("Vanilla/StaticText", "WidgetSelectorContainer");
    initialiseWidgetSelectorContainer(widgetSelectorContainer);
    background->addChild(widgetSelectorContainer);

    d_widgetsEventsLog = static_cast<CEGUI::MultiLineEditbox*>(winMgr.createWindow("Vanilla/MultiLineEditbox", "WidgetEventsLog"));
    initialiseWidgetsEventsLog();
    background->addChild(d_widgetsEventsLog);

    d_widgetSelectorListbox = static_cast<CEGUI::Listbox*>(winMgr.createWindow("Vanilla/Listbox", "WidgetSelectorListbox"));
    initialiseWidgetSelectorListbox();
    widgetSelectorContainer->addChild(d_widgetSelectorListbox);

    initialiseEventLights(background);


    d_widgetDisplayWindow = winMgr.createWindow("Vanilla/FrameWindow", "WidgetDisplayWindow");
    d_widgetDisplayWindow->setPosition(CEGUI::UVector2(cegui_reldim(0.085f), cegui_reldim(0.1f)));
    d_widgetDisplayWindow->setSize(CEGUI::USize(cegui_reldim(0.425f), cegui_reldim(0.55f)));
    d_widgetDisplayWindow->setText("Widget Demo");
    background->addChild(d_widgetDisplayWindow);

    d_widgetDisplayWindowInnerWindow =  winMgr.createWindow("DefaultWindow", "WidgetDisplayWindowInnerContainer");
    d_widgetDisplayWindowInnerWindow->setSize(CEGUI::USize(cegui_reldim(1.f), cegui_reldim(1.f)));
    d_widgetDisplayWindow->addChild(d_widgetDisplayWindowInnerWindow);
}

void WidgetDemo::initialiseSkinCombobox()
{
    d_skinSelectionCombobox->setPosition(CEGUI::UVector2(cegui_reldim(0.65f), cegui_reldim(0.165f)));
    d_skinSelectionCombobox->setSize(CEGUI::USize(cegui_reldim(0.24f), cegui_reldim(0.3f)));
    d_skinSelectionCombobox->setText("Select a Widget Skin");
    d_skinSelectionCombobox->setReadOnly(true);
    d_skinSelectionCombobox->setSortingEnabled(false);

    d_skinSelectionCombobox->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, Event::Subscriber(&WidgetDemo::handleSkinSelectionAccepted, this));

    std::map<CEGUI::String, WidgetListType>::iterator iter = d_skinListItemsMap.begin();
    while(iter != d_skinListItemsMap.end())
    {
        d_skinSelectionCombobox->addItem(new MyListItem(iter->first));

        ++iter;
    }
}

void WidgetDemo::initialiseBackgroundWindow(CEGUI::Window* background)
{
    background->setPosition(UVector2(cegui_reldim(0), cegui_reldim( 0)));
    background->setSize(USize(cegui_reldim(1), cegui_reldim( 1)));
    background->setProperty("FrameEnabled", "false");
    background->setProperty("BackgroundEnabled", "false");
    background->setProperty("Image", "SpaceBackgroundImage");
}

void WidgetDemo::initialiseWidgetSelectorListbox()
{
    d_widgetSelectorListbox->setPosition(CEGUI::UVector2(cegui_reldim(0.f), cegui_reldim(0.075f)));
    d_widgetSelectorListbox->setSize(CEGUI::USize(cegui_reldim(1.f), cegui_reldim(0.925f)));
    d_widgetSelectorListbox->setShowVertScrollbar(false);

    d_widgetSelectorListbox->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, Event::Subscriber(&WidgetDemo::handleWidgetSelectionChanged, this));   
}

void WidgetDemo::initialiseWidgetSelectorContainer(CEGUI::Window* widgetSelectorContainer)
{
    widgetSelectorContainer->setPosition(CEGUI::UVector2(cegui_reldim(0.6f), cegui_reldim(0.25f)));
    widgetSelectorContainer->setSize(CEGUI::USize(cegui_reldim(0.325f), cegui_reldim(0.56f)));
    widgetSelectorContainer->setText("Widget Selector");
    widgetSelectorContainer->setProperty("VertFormatting", "TopAligned");
    widgetSelectorContainer->setProperty("HorzFormatting", "CentreAligned");
}

void WidgetDemo::initialiseWidgetsEventsLog()
{
    d_widgetsEventsLog->setPosition(CEGUI::UVector2(cegui_reldim(0.085f), cegui_reldim(0.70f)));
    d_widgetsEventsLog->setSize(CEGUI::USize(cegui_reldim(0.425f), cegui_reldim(0.2f)));
    d_widgetsEventsLog->setReadOnly(true);
    d_widgetsEventsLog->setFont("DejaVuSans-10");
}

/*************************************************************************
Helper function to add MyListItem's to the widget list
*************************************************************************/
void WidgetDemo::addItemToWidgetList(const CEGUI::String& widgetName, WidgetListType &widgetList)
{
    MyListItem* widgetListItem = new MyListItem(widgetName);
    widgetListItem->setAutoDeleted(false);
    widgetList.push_back(widgetListItem);
}

void WidgetDemo::initialiseEventHandlerObjects()
{
#include "AllEvents.inc"

    std::set<String>::iterator iter = allEvents.begin();
    while(iter != allEvents.end())
    {
        addEventHandlerObjectToMap(*iter);

        ++iter;
    }
}

CEGUI::Window* WidgetDemo::createWidget(const CEGUI::String &widgetMapping, const CEGUI::String &widgetType)
{
    //Create default widget of the selected type
    CEGUI::WindowManager& windowManager = CEGUI::WindowManager::getSingleton();

    CEGUI::Window* widgetWindow = windowManager.createWindow(widgetMapping, s_widgetDemoWindowPrefix + widgetMapping);
    //Subscribe to all possible events the window could fire, the handler will output them to the log
    subscribeToAllEvents(widgetWindow);

    //Set a default text
    CEGUI::Spinner* spinner = dynamic_cast<CEGUI::Spinner*>(widgetWindow); // A spinner requires a number
    if(!spinner)
        widgetWindow->setText(widgetType);


    widgetWindow = initialiseSpecialWidgets(widgetWindow, widgetType);

    return widgetWindow;
}


void WidgetDemo::handleWidgetEventFired(CEGUI::String eventName)
{
    if(eventName == CEGUI::Window::EventMouseMove)
    {
        d_windowLightMouseMoveEvent->enable();
    }
    else if(eventName == CEGUI::Window::EventUpdated)
    {
        d_windowLightUpdatedEvent->enable();
    }
    else
    {
        logFiredEvent(eventName);
    }

}

void WidgetDemo::addEventHandlerObjectToMap(CEGUI::String eventName)
{
    d_eventHandlerObjectsMap[eventName] = new EventHandlerObject(eventName, this);
}

void WidgetDemo::deinitWidgetListItems()
{
    std::map<CEGUI::String, WidgetListType>::iterator iter = d_skinListItemsMap.begin();
    while(iter != d_skinListItemsMap.end())
    {
        WidgetListType& widgetsList = iter->second;

        while(widgetsList.size() > 0)
        {
            MyListItem* item = widgetsList.back();
            delete item;
            widgetsList.pop_back();
        }

        ++iter;
    }
}

void WidgetDemo::destroyWidgetWindows()
{
    CEGUI::WindowManager& winMan = CEGUI::WindowManager::getSingleton();
    std::map<CEGUI::String, CEGUI::Window*>::iterator iter = d_widgetsMap.begin();
    while(iter != d_widgetsMap.end())
    {
        winMan.destroyWindow(iter->second);

        ++iter;
    }
}

void WidgetDemo::initialiseEventLights(CEGUI::Window* background)
{
    CEGUI::WindowManager &winMgr = CEGUI::WindowManager::getSingleton();

    CEGUI::Window* horizontalLayout = winMgr.createWindow("HorizontalLayoutContainer", "EventLightsContainer");
    horizontalLayout->setPosition(CEGUI::UVector2(cegui_reldim(0.085f), cegui_reldim(0.91f)));
    background->addChild(horizontalLayout);


    d_windowLightUpdatedEvent = winMgr.createWindow("SampleBrowserSkin/Light");
    horizontalLayout->addChild(d_windowLightUpdatedEvent);
    d_windowLightUpdatedEvent->setSize(CEGUI::USize(cegui_reldim(0.f), cegui_reldim(0.04f)));
    d_windowLightUpdatedEvent->setAspectMode(CEGUI::AM_EXPAND);
    d_windowLightUpdatedEvent->setProperty("LightColour", "FF66FF66");

    CEGUI::Window* updateEventLabel = winMgr.createWindow("Vanilla/Label");
    horizontalLayout->addChild(updateEventLabel);
    updateEventLabel->setSize(CEGUI::USize(cegui_reldim(0.12f), cegui_reldim(0.04f)));
    updateEventLabel->setText("EventUpdated");
    updateEventLabel->setFont("DejaVuSans-12-NoScale");

    d_windowLightMouseMoveEvent = winMgr.createWindow("SampleBrowserSkin/Light");
    horizontalLayout->addChild(d_windowLightMouseMoveEvent);
    d_windowLightMouseMoveEvent->setSize(CEGUI::USize(cegui_reldim(0.f), cegui_reldim(0.04f)));
    d_windowLightMouseMoveEvent->setAspectMode(CEGUI::AM_EXPAND);
    d_windowLightMouseMoveEvent->setProperty("LightColour", "FF77BBFF");

    CEGUI::Window* mouseMoveEventLabel = winMgr.createWindow("Vanilla/Label");
    horizontalLayout->addChild(mouseMoveEventLabel);
    mouseMoveEventLabel->setSize(CEGUI::USize(cegui_reldim(0.12f), cegui_reldim(0.04f)));
    mouseMoveEventLabel->setText("EventMouseMove");
    mouseMoveEventLabel->setFont("DejaVuSans-12-NoScale");
}

void WidgetDemo::logFiredEvent(const CEGUI::String& eventName)
{
    ListboxItem* item = d_widgetSelectorListbox->getFirstSelectedItem();
    if(!item)
        return;

    CEGUI::String eventsLog = d_widgetsEventsLog->getText();
    eventsLog += eventName + " event fired";

    //Remove line
    int pos = std::max<int>(static_cast<int>(eventsLog.length() - 512), 0);
    int len = std::min<int>(static_cast<int>(eventsLog.length()), 512);
    eventsLog = eventsLog.substr(pos, len);
    if(len == 512)
    {
        int newlinePos = eventsLog.find_first_of("\n");
        if(newlinePos != std::string::npos)
            eventsLog = eventsLog.substr(newlinePos, std::string::npos);
    }
    d_widgetsEventsLog->setText(eventsLog);

    //Scroll to end
    d_widgetsEventsLog->getVertScrollbar()->setScrollPosition(d_widgetsEventsLog->getVertScrollbar()->getDocumentSize() - d_widgetsEventsLog->getVertScrollbar()->getPageSize());
}

void WidgetDemo::subscribeToAllEvents(CEGUI::Window* widgetWindow)
{
    //Register all events for the widget window
    std::map<CEGUI::String, EventHandlerObject*>::iterator iter = d_eventHandlerObjectsMap.begin();
    while(iter != d_eventHandlerObjectsMap.end())
    {
        widgetWindow->subscribeEvent(iter->first, Event::Subscriber(&EventHandlerObject::handleEvent, iter->second));

        ++iter;
    }
}

CEGUI::Window* WidgetDemo::initialiseSpecialWidgets(CEGUI::Window* widgetWindow, const CEGUI::String &widgetType)
{
   

    CEGUI::RadioButton* radioButton = dynamic_cast<CEGUI::RadioButton*>(widgetWindow);
    if(radioButton)
    {
        initRadioButtons(radioButton, widgetWindow);
    }

    CEGUI::MultiLineEditbox* multilineEditbox = dynamic_cast<CEGUI::MultiLineEditbox*>(widgetWindow);
    if(multilineEditbox || widgetType.compare("StaticText") == 0)
    {
        widgetWindow->setText("Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod tempor incidunt"
            "ut labore et dolore magna aliqua.Ut enim ad minim veniam, quis nostrud exercitation ullamco"
            "laboris nisi ut aliquid ex ea commodi consequat.Quis aute iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\n\n\n"
            "Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    }

    if(widgetType.compare("StaticImage") == 0)
    {
        widgetWindow->setProperty("Image", "SpaceBackgroundImage");
    }

    CEGUI::Listbox* listbox = dynamic_cast<CEGUI::Listbox*>(widgetWindow);
    if(listbox)
    {
        initListbox(listbox);
    }


    CEGUI::Combobox* combobox = dynamic_cast<CEGUI::Combobox*>(widgetWindow);
    if(combobox)
    {
        initCombobox(combobox);
    }

    CEGUI::MultiColumnList* multilineColumnList = dynamic_cast<CEGUI::MultiColumnList*>(widgetWindow);
    if(multilineColumnList)
    {
        initMultiColumnList(multilineColumnList);
    }

    return widgetWindow;
}

void WidgetDemo::initMultiColumnList(CEGUI::MultiColumnList* multilineColumnList)
{
    // Add some empty rows to the MCL
    multilineColumnList->addRow();
    multilineColumnList->addRow();
    multilineColumnList->addRow();
    multilineColumnList->addRow();
    multilineColumnList->addRow();

    // Set first row item texts for the MCL
    multilineColumnList->setItem(new MyListItem("Laggers World"), 0, 0);
    multilineColumnList->setItem(new MyListItem("yourgame.some-server.com"), 1, 0);
    multilineColumnList->setItem(new MyListItem("[colour='FFFF0000']1000ms"), 2, 0);

    // Set second row item texts for the MCL
    multilineColumnList->setItem(new MyListItem("Super-Server"), 0, 1);
    multilineColumnList->setItem(new MyListItem("whizzy.fakenames.net"), 1, 1);
    multilineColumnList->setItem(new MyListItem("[colour='FF00FF00']8ms"), 2, 1);

    // Set third row item texts for the MCL
    multilineColumnList->setItem(new MyListItem("Cray-Z-Eds"), 0, 2);
    multilineColumnList->setItem(new MyListItem("crayzeds.notarealserver.co.uk"), 1, 2);
    multilineColumnList->setItem(new MyListItem("[colour='FF00FF00']43ms"), 2, 2);

    // Set fourth row item texts for the MCL
    multilineColumnList->setItem(new MyListItem("Fake IPs"), 0, 3);
    multilineColumnList->setItem(new MyListItem("123.320.42.242"), 1, 3);
    multilineColumnList->setItem(new MyListItem("[colour='FFFFFF00']63ms"), 2, 3);

    // Set fifth row item texts for the MCL
    multilineColumnList->setItem(new MyListItem("Yet Another Game Server"), 0, 4);
    multilineColumnList->setItem(new MyListItem("abc.abcdefghijklmn.org"), 1, 4);
    multilineColumnList->setItem(new MyListItem("[colour='FFFF6600']284ms"), 2, 4);
}

void WidgetDemo::initCombobox(CEGUI::Combobox* combobox)
{
    combobox->addItem(new MyListItem("Combobox Item 1"));
    combobox->addItem(new MyListItem("Combobox Item 2"));

    MyListItem* item = new MyListItem("Combobox Item 3");
    item->setSelectionColours(CEGUI::Colour(0.3f, 0.7f, 1.0f, 1.f));
    combobox->addItem(item);

    item = new MyListItem("Combobox Item 4");
    item->setSelectionColours(CEGUI::Colour(0.3f, 1.0f, 0.7f, 1.f));
    combobox->addItem(item);
}

void WidgetDemo::initListbox(CEGUI::Listbox* listbox)
{
    listbox->addItem(new MyListItem("Listbox Item 1"));
    listbox->addItem(new MyListItem("Listbox Item 2"));

    MyListItem* item = new MyListItem("Listbox Item 3");
    item->setSelectionColours(CEGUI::Colour(0.3f, 0.7f, 1.0f, 1.f));
    listbox->addItem(item);

    item = new MyListItem("Listbox Item 4");
    item->setSelectionColours(CEGUI::Colour(0.3f, 1.0f, 0.7f, 1.f));
    listbox->addItem(item);
}

void WidgetDemo::initRadioButtons(CEGUI::RadioButton* radioButton, CEGUI::Window*& widgetWindow)
{
    CEGUI::WindowManager& windowManager = CEGUI::WindowManager::getSingleton();

    CEGUI::RadioButton* radioButton1 = radioButton;
    widgetWindow = windowManager.createWindow("DefaultWindow", "RadioButtonWidgetDemoRoot");
    widgetWindow->addChild(radioButton1);

    CEGUI::Window* radioButton2 = windowManager.createWindow(radioButton1->getType(), "WidgetDemoRadiobutton1");
    widgetWindow->addChild(radioButton2);
    radioButton2->setText("Additional Radiobutton1");
    radioButton2->setPosition(CEGUI::UVector2(cegui_reldim(0.f), cegui_reldim(0.17f)));

    CEGUI::Window* radioButton3 = windowManager.createWindow(radioButton1->getType(), "WidgetDemoRadiobutton2");
    widgetWindow->addChild(radioButton3);
    radioButton3->setText("Additional Radiobutton2");
    radioButton3->setPosition(CEGUI::UVector2(cegui_reldim(0.f), cegui_reldim(0.27f)));
}

/*************************************************************************
Define the module function that returns an instance of the sample
*************************************************************************/
extern "C" SAMPLE_EXPORT Sample& getSampleInstance()
{
    static WidgetDemo sample;
    return sample;
}