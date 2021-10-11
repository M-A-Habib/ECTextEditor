#pragma once

#include "ECTextView_Doc.h"
#include "ECTextView_View.h"
#include "ECTextViewImp.h"
#include "docMode.h"

class ECTextView_Control{
public:
	ECTextView_Control(ECTextView_Doc *document, ECTextView_View *window_view, ECTextViewImp *p):myDocument(document), myView(window_view), pp(p){
		myView->set_pages(myDocument->getPages());
		myView->view(myDocument->get_num_page());
		mode = new docMode();
		sI = "";
		sII = "";
	}

	void enter_Button_ctrl(){
		if(mode->getEditMode() == true){
			myView->save_cursor();
			myDocument->enter_Button();
			myView->enter_reset();
			myView->set_pages(myDocument->getPages());
			//myView->view(myDocument->get_num_page());
			myDocument->save_file();
		}
		else if(mode->getSearchMode() == true){
			myView->resetColor();
			myDocument->search(sI);
		}
		else if(mode->getReplaceMode() == true){
			myDocument->search_replace(sI, sII);
			//myView->docRefresh(myDocument->get_num_page());
			mode->setSearchMode();
			myView->resetColor();
			sI = sII;
			myDocument->save_file();
		}
	}

	void arrow_right_Button_ctrl(){
		int num_page_coord = myView->arrow_right_Button(myDocument->get_num_page());
		myDocument->set_num_page(num_page_coord);
	}

	void arrow_left_Button_ctrl(){
		int num_page_coord = myView->arrow_left_Button(myDocument->get_num_page());
		myDocument->set_num_page(num_page_coord);
	}

	void arrow_up_Button_ctrl(){
		int num_page_coord = myView->arrow_up_Button(myDocument->get_num_page());
		myDocument->set_num_page(num_page_coord);
	}

	void arrow_down_Button_ctrl(){
		int num_page_coord = myView->arrow_down_Button(myDocument->get_num_page());
		myDocument->set_num_page(num_page_coord);
	}

	void backspace_Button_ctrl(){
		if(mode->getEditMode() == true){
			myView->save_cursor();
			myDocument->backspace_Button();
			myView->backspace_reset(myDocument->get_num_page());
			myView->set_pages(myDocument->getPages());
			//myView->view(myDocument->get_num_page());
			myDocument->save_file();
		}
		else if(mode->getSearchMode() == true){
			sI = sI.substr(0, sI.size() - 1);
		}
		else if(mode->getReplaceMode() == true)
			sII = sII.substr(0, sII.size() - 1);
	}

	void type_Text_ctrl(){
		if(mode->getEditMode() == true){
			myView->save_cursor();
			myDocument->type_Text();
			myView->set_pages(myDocument->getPages());
			//myView->view(myDocument->get_num_page());
			myView->arrow_right_Button(myDocument->get_num_page());
			myDocument->save_file();
		}
		else if(mode->getSearchMode() == true){
			char i = pp->GetPressedKey();
			if(i == '/'){
				mode->setReplaceMode();
			}
			else{
				std::string s = std::string(1,i);
            	sI += s;
			}
		}
		else if(mode->getReplaceMode() == true){
			char i = pp->GetPressedKey();
			std::string s = std::string(1,i);
            sII += s;
		}
	}

	void view_control(){
		myView->set_pages(myDocument->getPages());
		if(mode->getEditMode() == true){
			myView->view(myDocument->get_num_page());
		}
		else if(mode->getSearchMode() == true){
			myView->searchStatusBar(sI, myDocument->get_num_page());
		}
		else if(mode->getReplaceMode() == true){
			myView->replaceStatusBar(sII, myDocument->get_num_page());
		}
	}

	void undo_ctrl(){
		myDocument->undo();
		myView->undo_Cursor();
		//myView->undo_redo_view_update(myDocument->get_num_page());
		myView->set_pages(myDocument->getPages());
		//myView->view(myDocument->get_num_page());
		myDocument->save_file();
	}

	void redo_ctrl(){
		myDocument->redo();
		myView->redo_Cursor();
		//myView->undo_redo_view_update(myDocument->get_num_page());
		myView->set_pages(myDocument->getPages());
		//myView->view(myDocument->get_num_page());
		myDocument->save_file();
	}

	void searchMode(){
		mode->setSearchMode();
	}

	void editMode(){
		mode->setEditMode();
		myView->resetColor();
	}

private:
	ECTextView_Doc *myDocument;
	ECTextView_View *myView;
	ECTextViewImp *pp;

	docMode *mode;
	std::string sI;
	std::string sII;

};