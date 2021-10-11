#pragma once

#include "ECTextView_View.h"
#include "ECTextViewImp.h"
#include <fstream>
#include <string>

class ECTextView_Doc{
public:
	ECTextView_Doc(std::string file_name_Input, ECTextViewImp *p):myFile(file_name_Input), pp(p){
		num_Page = 0;
        edits.push_back("");//push back an empty string to begin the document. Otherwise you get seg fault for writing to an otherwise empty vector.
        pages.push_back(edits);
        if(same_Directory()){
            load_file();
        }
        else if(!same_Directory()){
        	pages[0][0] = " ";
            create_File();
            save_file();
        }
	}

    void reorganize_Vector(std::vector<std::string> &input_Vec){
        std::vector<std::string> temp_Edits;
        for(int i = 0; i < input_Vec.size(); i++)
            temp_Edits.push_back(input_Vec[i]);

        int count = 0;
        int index = 0;
        std::vector< std::vector<std::string> > temp_pages;
        std::vector<std::string> temp_vec;

        for(int i = 0; i < temp_Edits.size(); i++){
            if(count <= pp->GetRowNumInView() - 1){
                temp_vec.push_back(temp_Edits[i]);
                count++;
            }

            if(temp_pages.empty())
                temp_pages.push_back(temp_vec);
            else{
                temp_pages[index] = temp_vec;
            }

            if(count == pp->GetRowNumInView()){
                temp_vec.clear();
                count = 0;
                temp_pages.push_back(temp_vec);
                index++;
            }

        }

        if(temp_pages[temp_pages.size() - 1].empty())
        	temp_pages.erase(temp_pages.begin() + temp_pages.size() - 1);

        pages.clear();

        for(int i = 0; i < temp_pages.size(); i++)
            pages.push_back(temp_pages[i]);
    }

    void load_file(){
        //read the contents and loading them to vector
        std::vector<std::string> my_vec;
        newFile.open(myFile, std::ios::in);
        if(newFile.is_open()){
            std::string tp;
            while(getline(newFile, tp)){
                my_vec.push_back(tp);
            }

            newFile.close();
        }

        reorganize_Vector(my_vec);
    }

    void save_file(){
        newFile.open(myFile, std::ios::out | std::ios::trunc);
        if(newFile.is_open()){
            for(int i = 0; i < pages.size(); i++){
                for(int j = 0; j < pages[i].size(); j++){
                    newFile << pages[i][j] << "\n";
                }
            }

            newFile.close();
        }
    }

    void backspace_Button(){
    	undoStack.push(pages);
        if(pp->GetCursorX() == 0 && pp->GetCursorY() == 0){
            if (num_Page > 0 && pp->GetCursorY() == 0){
                pages[num_Page - 1][pp->GetRowNumInView() - 1] += pages[num_Page][pp->GetCursorY()];
                pages[num_Page].erase(pages[num_Page].begin() + pp->GetCursorY());
                if(pages[num_Page].empty())
                    pages.erase(pages.begin() + num_Page);
                num_Page--;
            }
        }
        else{
            if(pp->GetCursorX() == 0){
                if(pp->GetCursorY() > 0 && pages[num_Page][pp->GetCursorY()].empty()){
                    pages[num_Page].erase(pages[num_Page].begin() + pp->GetCursorY());
                }
                else if(pp->GetCursorY() > 0 && !pages[num_Page][pp->GetCursorY()].empty()){
                    pages[num_Page][pp->GetCursorY() - 1] = pages[num_Page][pp->GetCursorY() - 1] + pages[num_Page][pp->GetCursorY()];
                    pages[num_Page].erase(pages[num_Page].begin() + pp->GetCursorY());
                }
            }
            else{
                pages[num_Page][pp->GetCursorY()] = pages[num_Page][pp->GetCursorY()].substr(0, (pp->GetCursorX() - 1)) + pages[num_Page][pp->GetCursorY()].substr(pp->GetCursorX());
            }
        }

        reorganize_Vector();
    }

    void type_Text(){
    	undoStack.push(pages);
        char i = pp->GetPressedKey();//else add the character to the document
            std::string s = std::string(1,i);
            if(pp->GetCursorX() != pages[num_Page][pp->GetCursorY()].size()){//this is for inserting in the middle of a line
                std::string sI = "";
                sI += s;
                std::string curEdits = pages[num_Page][pp->GetCursorY()];
                pages[num_Page][pp->GetCursorY()] = curEdits.substr(0, pp->GetCursorX()) + sI + curEdits.substr(pp->GetCursorX());
            }
            else{
                pages[num_Page][pp->GetCursorY()] += s;
            }
            reorganize_Vector();
    }

    void enter_Button(){
    	undoStack.push(pages);
    	if(pp->GetCursorY() == pp->GetRowNumInView() - 1){
    		if(pp->GetCursorX() != pages[num_Page][pp->GetCursorY()].size()){
    			std::string part1 = ""; //the beginning part of the string
                std::string part2 = ""; //the ending part of the string
                for(int x = 0; x < pp->GetCursorX(); x++){
                    part1 += pages[num_Page][pp->GetCursorY()][x];//copy the beginning to the part 1
                }
                for(int x = pp->GetCursorX(); x < pages[num_Page][pp->GetCursorY()].size(); x++){
                    part2 += pages[num_Page][pp->GetCursorY()][x]; //copy the ending to part2
                }

                pages[num_Page][pp->GetCursorY()] = part1; //make the current index into the first part
                pages[num_Page].insert(pages[num_Page].begin() + (pp->GetCursorY() + 1), part2); //insert the second part after
    		}
    		else{
	    		std::vector<std::string> edits;
	    		edits.clear();
	    		edits.push_back("");
	    		pages.push_back(edits);
	    	}
	    	num_Page++;
    	}
    	else{
    		if(pp->GetCursorX() != (pages[num_Page][pp->GetCursorY()].size())){
                std::string part1 = ""; //the beginning part of the string
                std::string part2 = ""; //the ending part of the string
                for(int x = 0; x < pp->GetCursorX(); x++){
                    part1 += pages[num_Page][pp->GetCursorY()][x];//copy the beginning to the part 1
                }
                for(int x = pp->GetCursorX(); x < pages[num_Page][pp->GetCursorY()].size(); x++){
                    part2 += pages[num_Page][pp->GetCursorY()][x]; //copy the ending to part2
                }

                pages[num_Page][pp->GetCursorY()] = part1; //make the current index into the first part
                pages[num_Page].insert(pages[num_Page].begin() + (pp->GetCursorY() + 1), part2); //insert the second part after
            }
            else if(pp->GetCursorX() == pages[num_Page][pp->GetCursorY()].size() && pages[num_Page].size() > pp->GetCursorY()){
            	std::string newstring = "";
            	pages[num_Page].insert(pages[num_Page].begin() + (pp->GetCursorY() + 1), newstring);
            }
            else{
            pages[num_Page].push_back("");
            }
        }
            reorganize_Vector();
    }

    std::vector< std::vector<std::string> > getPages(){
    	return pages;
    }

    int get_num_page(){
    	return num_Page;
    }

    void set_num_page(int num_page_inp){
    	num_Page = num_page_inp;
    }

    void undo(){
    	if(undoStack.empty() == 1)
            return;
        else{
            redoStack.push(pages);
            pages = undoStack.top();
            undoStack.pop();
        }
    }

    void redo(){
    	if(redoStack.empty() == 1)
            return;
        else{
            pages = redoStack.top();
            undoStack.push(redoStack.top());
            redoStack.pop();
        }
    }

    void search(std::string text){
        std::vector< std::vector<std::string> > tempPage = pages;
        for(int i = 0; i < tempPage.size(); i++){
            for(int j = 0; j < tempPage[i].size(); j++){
                std::string tempstr = tempPage[i][j];
                int cur = 0;
                while(tempstr.length() >= text.length()){
                    int substr = isSubstring(text, tempstr);
                    if(substr != -1){
                        pp->SetColor(j, cur + substr, cur + substr + text.length()-1, TEXT_COLOR_RED);
                        tempstr = tempstr.substr(substr + text.length(), tempstr.length() - 1);
                        cur += text.length() + substr;
                    }
                    else
                        break;
                }
            }
        }
    }

    void search_replace(std::string text, std::string replace){
        undoStack.push(pages);
        for(int i = 0; i < pages[num_Page].size(); i++){
            size_t pos = pages[num_Page][i].find(text);
            // Repeat till end is reached
            while( pos != std::string::npos)
            {
                // Replace this occurrence of Sub String
                pages[num_Page][i].replace(pos, text.size(), replace);
                // Get the next occurrence from the current position
                pos =pages[num_Page][i].find(text, pos + replace.size());
            }
        }
    }
private:
	int num_Page;
	std::string myFile;
	std::vector< std::vector<std::string> > pages;
    std::fstream newFile;
    ECTextViewImp *pp;
    std::vector<std::string> edits;

    std::stack< std::vector< std::vector<std::string> > > undoStack;
    std::stack< std::vector< std::vector<std::string> > > redoStack;

    void reorganize_Vector(){
        std::vector<std::string> temp_Edits;
        for(int i = 0; i < pages.size(); i++){
            for(int j = 0; j < pages[i].size(); j++){
                temp_Edits.push_back(pages[i][j]);
            }
        }
        int count = 0;
        int index = 0;
        std::vector< std::vector<std::string> > temp_pages;
        std::vector<std::string> temp_vec;

        for(int i = 0; i < temp_Edits.size(); i++){
            if(count <= pp->GetRowNumInView() - 1){
                temp_vec.push_back(temp_Edits[i]);
                count++;
            }

            if(temp_pages.empty())
                temp_pages.push_back(temp_vec);
            else{
                temp_pages[index] = temp_vec;
            }

            if(count == pp->GetRowNumInView()){
                temp_vec.clear();
                count = 0;
                temp_pages.push_back(temp_vec);
                index++;
            }

        }

        pages.clear();

        for(int i = 0; i < temp_pages.size(); i++)
            pages.push_back(temp_pages[i]);
    }

    bool same_Directory(){
        std::ifstream infile(myFile);
        return infile.good();
    }

    void create_File(){
        newFile.open(myFile, std::ios::out);
        newFile.close();
    }

    int isSubstring(std::string s1, std::string s2){
        int M = s1.length();
        int N = s2.length();

        for(int i = 0; i <= N - M; i++){ //0 -> 13
            int j;
            for(j = 0; j < M; j++){ //0 -> 3
                if(s2[i + j] != s1[j])
                    break;
            }

            if(j == M)
                return i;
        }
        return -1;
    }
};