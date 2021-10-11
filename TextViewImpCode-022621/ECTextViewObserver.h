#pragma once

#include "ECTextViewImp.h"
#include <fstream>
#include "ECTextView_Control.h"
#include "ECTextView_View.h"
#include "ECTextView_Doc.h"


//***********************************************************
//          TextView version 0.0.1000 alpha
//                  April 01, 2021
//                  By Mohammad Habib (all rights reserved)
//    Disclaimer: the following code is largely a porting of
//              the Kilo editor in C to C++ with the help of professor
//***********************************************************

class ECTextViewObserver : public ECObserver{
public:
	ECTextViewObserver(ECTextViewImp *p, std::string file_name_Input): pp(p), myFile(file_name_Input){
        ECTextView_Doc *myDoc = new ECTextView_Doc(file_name_Input, p);
        ECTextView_View *myView = new ECTextView_View(myDoc->getPages(), p);
        myCtrl = new ECTextView_Control(myDoc, myView, p);
	}

	void Update(){
        if(pp->GetPressedKey() == ENTER){
            myCtrl->enter_Button_ctrl();
        }
        else if(pp->GetPressedKey() == ARROW_RIGHT){
            myCtrl->arrow_right_Button_ctrl();
        }
        else if(pp->GetPressedKey() == ARROW_LEFT){ //cursor to the left is constraint by 0
            myCtrl->arrow_left_Button_ctrl();
        }
        else if(pp->GetPressedKey() == ARROW_UP){ //constraint by 0
            myCtrl->arrow_up_Button_ctrl();
        }
        else if(pp->GetPressedKey() == ARROW_DOWN){
            myCtrl->arrow_down_Button_ctrl();
        }
        else if(pp->GetPressedKey() == BACKSPACE){
            myCtrl->backspace_Button_ctrl();
        }
        else if(pp->GetPressedKey() == CTRL_Z){
            myCtrl->undo_ctrl();
        }

        else if(pp->GetPressedKey() == CTRL_Y){
            myCtrl->redo_ctrl();
        }
        else if(pp->GetPressedKey() == CTRL_F){
            myCtrl->searchMode();
        }
        else if(pp->GetPressedKey() == ESC){
            myCtrl->editMode();
        }
        else{
            myCtrl->type_Text_ctrl();
        }
        myCtrl->view_control();
    }

private:
	ECTextViewImp *pp;
    std::string myFile;

    std::vector< std::vector<std::string> > pages;
    ECTextView_Control *myCtrl;
};