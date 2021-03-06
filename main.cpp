#include <iostream>
#include "window.h"
#include "gui.h"
#include "file.h"

using namespace std;

Window *window = new Window;
Window *windowsettings = new Window;
File file;

LRESULT CALLBACK wndproc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
    switch(msg){
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        case WM_COMMAND:
            GUI *gui = window->getGUI();
            if(wparam == gui->getButtonID("newfile"))
            {
                cout<<"new"<<endl;
                gui->getEdit("editcode")->clear();
            }
            if(wparam == gui->getButtonID("openfile"))
            {
                cout<<"open"<<endl;
            }
            if(wparam == gui->getButtonID("savefile"))
            {
                cout<<"save"<<endl;
                char* path;
                if(!OpenFileDialog(window->getHWND(),path,"Save File","Assembly file(*.asm)\0*.asm\0\0"))
                    break;
                file.setname(path);
                file.setbuff(gui->getEdit("editcode")->getText());
                file.write();
                cout<<"file saved"<<endl;

            }
            if(wparam == gui->getButtonID("compilefile"))
            {
                cout<<file.getname()<<endl;
            }
    }
    return DefWindowProc(hwnd,msg,wparam,lparam);
}

int main()
{
    window = new Window(512,512,"ASMIDE 2020","asmide2020x64");
    window->createWindow(wndproc);
    window->show();

    GUI* gui = window->getGUI();
    GUIbutton *btnnew = gui->createButton("newfile","New",2,2,50,21);
    btnnew->setFontDefault();
    GUIbutton *btnopen = gui->createButton("openfile","Open",54,2,50,21);
    btnopen->setFontDefault();
    GUIbutton *btnsave = gui->createButton("savefile","Save",106,2,50,21);
    btnsave->setFontDefault();
    GUIbutton *btncompile = gui->createButton("compilefile","Compile",178,2,50,21);
    btncompile->setFontDefault();
    GUIbutton *btnsettings = gui->createButton("settings","Settings",window->getW()-68,2,50,21);
    btnsettings->setFontDefault();

    GUIedit *editcode = gui->createEdit("editcode","",2,27,window->getW()-3,window->getH()-68);
    editcode->setFontDefault();

    MSG msg = {};
    while(GetMessage(&msg,NULL,0,0)!=0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
