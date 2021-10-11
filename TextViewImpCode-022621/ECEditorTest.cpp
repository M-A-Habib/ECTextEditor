// Test code for editor
#include "ECTextViewObserver.h"
#include <iostream>

using namespace  std;

int myCounter = 0;

int main(int argc, char *argv[])
{
    //
    ECTextViewImp wndTest; //given code
    // ECTextDocument documentInput; //document text from 6.1
    // ECTextDocumentCtrl &docCtrl = documentInput.GetCtrl(); //control is used to control the commands from 6.1
    std::string file_Name;
    if(argc > 1)
        file_Name = argv[1];
    else
        file_Name = "";
    // wndTest.AddRow("CSE 3150");
    // wndTest.SetColor(0, 0, 0, TEXT_COLOR_RED);
    // wndTest.SetColor(0, 1, 1, TEXT_COLOR_GREEN);
    // wndTest.SetColor(0, 2, 2, TEXT_COLOR_BLUE);
    // wndTest.SetColor(0, 4, 4, TEXT_COLOR_RED);
    // wndTest.SetColor(0, 5, 5, TEXT_COLOR_GREEN);
    // wndTest.SetColor(0, 6, 6, TEXT_COLOR_BLUE);
    // wndTest.SetColor(0, 7, 7, TEXT_COLOR_MAGENTA);
    // wndTest.AddRow("This is a very simple demo of the ECTextViewImp functionalities.");
    // wndTest.SetColor(1, 10, 13, TEXT_COLOR_GREEN);
    // wndTest.AddRow("Press ctrl-q to quit");
    // wndTest.SetColor(2, 0, 1, TEXT_COLOR_GREEN);
    // wndTest.SetColor(2, 0, 1, TEXT_COLOR_DEF);

    // add a status bar


    wndTest.AddStatusRow("Editor", "For demo only", true);

    ECTextViewImp* test = &wndTest; //dereferencing the given window to make modification to the view

    
    
    ECTextViewObserver *somethingnew = new ECTextViewObserver(test, file_Name);//somethingnew runs the user input and controls
    //somethingnew->set_myFile(file_Name);
    wndTest.Attach(somethingnew);


    wndTest.Show();//show permanently display the final view. Cannot modify anything after this line
    
    return 0;
}
