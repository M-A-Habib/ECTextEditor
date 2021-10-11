#pragma once

#include "ECTextViewImp.h"

class ECTextView_View{
public:
	ECTextView_View(std::vector< std::vector<std::string> > pages_input, ECTextViewImp *p) : pages(pages_input), pp(p){}
	int arrow_right_Button(int num_page_inp){
		int num_Page = num_page_inp;
        if(pp->GetCursorX() == pages[num_Page][pp->GetCursorY()].size() && pp->GetCursorY() < pages[num_Page].size() - 1){
            pp->SetCursorY(pp->GetCursorY() + 1);
            pp->SetCursorX(0);
        }
        else if(pp->GetCursorY() == pp->GetRowNumInView() - 1 && num_Page < pages.size() - 1 && pp->GetCursorX() == pages[num_Page][pp->GetCursorY()].size()){
            num_Page++;
            pp->SetCursorY(0);
            pp->SetCursorX(0);
        }
        else if(pp->GetCursorX() < pages[num_Page][pp->GetCursorY()].size()){
            pp->SetCursorX(pp->GetCursorX() + 1);
        }
        return num_Page;
    }

    int arrow_left_Button(int num_page_inp){
    	int num_Page = num_page_inp;
        if(pp->GetCursorX() == 0 && pp->GetCursorY() > 0){
            pp->SetCursorY(pp->GetCursorY() - 1);
            pp->SetCursorX(pages[num_Page][pp->GetCursorY()].size());
        }
        else if(pp->GetCursorY() == 0 && pp->GetCursorX() == 0 && num_Page > 0){
            num_Page--;
            pp->SetCursorY(pp->GetRowNumInView() - 1);
            pp->SetCursorX(pages[num_Page][pp->GetCursorY()].size());
        }
        else if(pp->GetCursorX() > 0)
            pp->SetCursorX(pp->GetCursorX() - 1);
        return num_Page;
    }

    int arrow_up_Button(int num_page_inp){
        int num_Page = num_page_inp;
        if(pp->GetCursorY() == 0 && num_Page > 0){
            num_Page--;
            pp->SetCursorY(pp->GetRowNumInView() - 1);
        }
        else if(pp->GetCursorY() > 0){
            pp->SetCursorY(pp->GetCursorY() - 1);
        }

        if(pp->GetCursorX() > pages[num_Page][pp->GetCursorY()].size())
            pp->SetCursorX(pages[num_Page][pp->GetCursorY()].size());

        return num_Page;
    }

    int arrow_down_Button(int num_page_inp){
        int num_Page = num_page_inp;
        if(pp->GetCursorY() == pp->GetRowNumInView() - 1 && num_Page < pages.size() - 1){
            num_Page++;
            pp->SetCursorY(0);
        }
        else if(pp->GetCursorY() < pages[num_Page].size() - 1 && num_Page < pages.size() && pp->GetCursorY() < pp->GetRowNumInView() - 1){
            pp->SetCursorY(pp->GetCursorY() + 1);
        }

        if(pp->GetCursorX() > pages[num_Page][pp->GetCursorY()].size())
            pp->SetCursorX(pages[num_Page][pp->GetCursorY()].size());
        
        return num_Page;
    }

	void view(int num_page_inp){
		int num_Page = num_page_inp;
        pp->InitRows(); //clear and rewrite the rows
        for(int b = 0; b < pages[num_Page].size(); b++){
        pp->AddRow(pages[num_Page][b]);//
        }

        pp->ClearStatusRows();
        pp->AddStatusRow("X: " + std::to_string(pp->GetCursorX()) + "Y: " + std::to_string(pp->GetCursorY()), "Page size(): " + std::to_string(pages.size()) + "Num Page: " + std::to_string(num_Page), true);
        pp->Refresh();
    }

    void searchStatusBar(std::string input, int num_page_inp){
        int num_Page = num_page_inp;
        pp->InitRows(); //clear and rewrite the rows
        for(int b = 0; b < pages[num_Page].size(); b++){
        pp->AddRow(pages[num_Page][b]);//
        }

        pp->ClearStatusRows();
        pp->AddStatusRow("Find: " + input, "", true);
        pp->Refresh();
    }

    void replaceStatusBar(std::string input, int num_page_inp){
        int num_Page = num_page_inp;
        pp->InitRows(); //clear and rewrite the rows
        for(int b = 0; b < pages[num_Page].size(); b++){
        pp->AddRow(pages[num_Page][b]);//
        }

        pp->ClearStatusRows();
        pp->AddStatusRow("Replace: " + input, "", true);
        pp->Refresh();
    }

    void docRefresh(int num_page_inp){
        int num_Page = num_page_inp;
        pp->InitRows(); //clear and rewrite the rows
        for(int b = 0; b < pages[num_Page].size(); b++){
            pp->AddRow(pages[num_Page][b]);//
        }
    }

    void enter_reset(){
    	if(pp->GetCursorY() == pp->GetRowNumInView() - 1){
            pp->SetCursorY(0);
            pp->SetCursorX(0);
        }
        else{
    		pp->SetCursorX(0);
    		pp->SetCursorY(pp->GetCursorY() + 1);
    	}
    }

    void backspace_reset(int num_page_inp){
    	int num_Page = num_page_inp;
    	if(pp->GetCursorX() == 0 && pp->GetCursorY() == 0){
    		if(pages[num_Page].size() >= pp->GetRowNumInView() - 1)
    			num_Page = num_page_inp + 1;
    		if (num_Page > 0 && pp->GetCursorY() == 0){
    			pp->SetCursorY(pp->GetRowNumInView() - 1);
    			num_Page--;
    			pp->SetCursorX(pages[num_Page][pp->GetCursorY()].size());
    		}
    		else{
    			pp->SetCursorX(0);
                pp->SetCursorY(0);
    		}
    	}
    	else{
    		if(pp->GetCursorX() == 0){
    			if(pp->GetCursorY() > 0 && pages[num_Page][pp->GetCursorY()].empty()){
    				pp->SetCursorY(pp->GetCursorY() - 1);
                    pp->SetCursorX(pages[num_Page][pp->GetCursorY()].size());
    			}
    			else if(pp->GetCursorY() > 0 && !pages[num_Page][pp->GetCursorY()].empty()){
    				pp->SetCursorX(pages[num_Page][pp->GetCursorY() -1].size());
    				pp->SetCursorY(pp->GetCursorY() - 1);
    			}
    		}
    		else{
    			pp->SetCursorX(pp->GetCursorX() - 1);
    		}
    	}
    }

    void resetColor(){
        for(int i = 0; i < pp->GetRowNumInView(); i++){
            for(int j = 0; j < pp->GetColNumInView(); j++){
                pp->SetColor(i, j, j, TEXT_COLOR_DEF);
            }
        }
    }

    void set_pages(std::vector< std::vector<std::string> > pages_inp){
    	pages = pages_inp;
    }

    void undo_Cursor(){
        if(undoStack.empty() == 1)
            return;
        else{
            std::vector < int > coords;
            coords.push_back(pp->GetCursorX());
            coords.push_back(pp->GetCursorY());
            redoStack.push(coords);

            pp->SetCursorX(undoStack.top()[0]);
            pp->SetCursorY(undoStack.top()[1]);

            undoStack.pop();
        }
    }

    void redo_Cursor(){
        if(redoStack.empty() == 1)
            return;
        else{
            pp->SetCursorX(redoStack.top()[0]);
            pp->SetCursorY(redoStack.top()[1]);

            undoStack.push(redoStack.top());

            redoStack.pop();
        }
    }

    void save_cursor(){
        std::vector < int > coords;
        coords.push_back(pp->GetCursorX());
        coords.push_back(pp->GetCursorY());
        undoStack.push(coords);
    }
private:
	std::vector< std::vector<std::string> > pages;
	ECTextViewImp *pp;

    std::stack < std::vector < int > > undoStack;
    std::stack < std::vector < int > > redoStack;
};