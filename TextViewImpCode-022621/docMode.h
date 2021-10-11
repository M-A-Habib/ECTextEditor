#pragma once
class docMode{
public:
	docMode(){editMode = true; searchMode = false; replaceMode = false;}
	void setEditMode(){editMode = true; searchMode = false; replaceMode = false;}
	void setSearchMode(){searchMode = true; editMode = false; replaceMode = false;}
	void setReplaceMode(){replaceMode = true; searchMode = false; editMode = false;}
	bool getEditMode(){return editMode;}
	bool getSearchMode(){return searchMode;}
	bool getReplaceMode(){return replaceMode;}
private:
	bool editMode;
	bool searchMode;
	bool replaceMode;
};