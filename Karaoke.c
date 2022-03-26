#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"

struct Song
{
    char* name;
    char* lyrics[500];
    Song* nextSong;
    Song* prevSong;
};

struct List
{
    Song* head;
    Song* tail;
};

Song* next(Song* curr)
{
    if (curr->nextSong == NULL)
    {
        return curr;
    }
    return curr->nextSong;
}

Song* prev(Song* curr)
{
    if (curr->prevSong == NULL)
    {
        return curr;
    }
    return curr->prevSong;
}

void add(List songList, Song* new)
{
    
    if (songList.head == NULL)
    {
        songList.head = new;
        songList.tail = new;
    }
    else 
    {
        Song* tracker = songList.head;
        while (tracker != NULL)
        {
            if (strcmp(tracker->name, new->name) > 0)
            {
                new->prevSong = tracker->prevSong;
                tracker->prevSong->nextSong = new;
                tracker->prevSong = new;
                new->nextSong =  tracker;
                return;
            }
            else if(strcmp(tracker.name, new->name) == 0)
            {
                return;
            }
            else
            {
                tracker = tracker->nextSong;
            }
        }
        songList.tail->nextSong = new;
        new->prevSong = songList.tail;
        new->nextSong = NULL;
        songList.tail = new;
    }  
}

Song* find(List songList, char* currName)
{
    Song* tracker = songList.head;
    while(tracker != NULL)
    {
        if (strcmp(tracker->name, currName) == 0)
        {
            return tracker;
        }
    }
    return NULL;
}

Song* remove(List songList, char* name)
{
    Song* remSong = find(songList, name);
    if (remSong == NULL)
    {
        lcd_moveto(0,0);
        lcd_stringout("Song no existo");
    }
    else
    {
        if (songList.head == songList.tail)
        {
            songList.head = NULL;
            songList.tail = NULL;
        }
        else if (remSong == songList.head)
        {
            songList.head = remSong->nextSong;
            remSong->nextSong->prevSong = NULL;
        }
        else if (remSong == songList.tail)
        {
            songList.tail = remSong->prevSong;
            remSomng->prevSong->nextSong = NULL;
        }
        else
        {
            Song* next = remSong->nextSong;
            Song* prev = remSong->prevSong;
            next->prevSong = prev;
            prev->nextSong = next;
        }
        delete remSong;
    }
}

void readFile(string fileName, List songList)
{
    FILE* ptr = fopen(fileName, "r");
    Song newSong;
    newSong.name = "";
    string temp = fgets(ptr);
    while (temp != "#")
    {
        newSong.name += temp;
        string temp = fgets(ptr);
    };
    int i = 0;
    string temp = fgets(ptr);
    while (temp != "#")
    {
        newSong.lyrics[i] = temp;
        i++;
        string temp = fgets(ptr);
    }
    fclose(fileName);
    add(songList, newSong);
    printf("%s\n", newSong.name);
    for(int i = 0; i < 500; i++)
    {
        if (newSong.lyrics[i] == "")
        {
            break;
        }
        printf("%s ", newSong.lyrics[i]);
    }
}

void runKaraoke()
{

}

int main(int argc, char* argv[])
{
    lcd_init();
    struct List songList;
    readFile("default.txt", songList);
    if (argc < 2)
    {
        runKaraoke();
    }
    else
    {
        for (int i = 0; i < argc; i++)
        {
            readFile(argv[i], songList);
        }
        runKaraoke();
    }

}



