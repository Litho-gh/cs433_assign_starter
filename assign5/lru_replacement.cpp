/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author ??? (TODO: your name)
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lru_replacement.h"


LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames){}


LRUReplacement::~LRUReplacement(){}

/*
// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{

}
*/

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    num_fault++;
    //greatest_frame++;
    page_table[page_num].frame_num = used_frames;	// used_frames doubles as a frame number recorder here
    page_table[page_num].valid = true;		// make the new page valid
    //need pr_table to push a pointer to this page
    pr_table.push(&page_table[page_num]);
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    num_fault++;
    num_replace++;
    PageEntry* temp = pr_table.top(); //temp holds the oldest page
    pr_table.pop(); // delete oldest page from queue
    temp->valid = false;
    int freed_frame = temp->frame_num;  // contains the frame just freed
    temp = nullptr; // drop temp
    
    page_table[page_num].valid = true;  // new page is valid
    page_table[page_num].frame_num = freed_frame;   // new page has freed frame number

    return 0;
}
