#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <sys/time.h>
//#include <thread>

using namespace std;
class KeyBot
{
private:
    INPUT _buffer[1];

public:
    KeyBot();
    void KeyUp( char key );
    void KeyDown( char key );
    void KeyClick( char key );
};

KeyBot::KeyBot()
{
    _buffer->type = INPUT_KEYBOARD;
    _buffer->ki.wScan = 0;
    _buffer->ki.time = 0;
    _buffer->ki.dwExtraInfo = 0;
}

void KeyBot::KeyUp( char key )
{
    _buffer->ki.wVk = key;
    _buffer->ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput( 1, _buffer, sizeof( INPUT ) );
}

void KeyBot::KeyDown( char key )
{
    _buffer->ki.wVk = key;
    _buffer->ki.dwFlags = 0;
    SendInput( 1, _buffer, sizeof( INPUT ) );
}

void KeyBot::KeyClick( char key )
{
    KeyDown( key );
    Sleep( 10 );
    KeyUp( key );
}

void HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

string exec(string command) {
   char buffer[3];
   string result = "";

   // Open pipe to file
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {
        //Sleep(10);
      // use buffer to read and add to result
      if (fgets(buffer, 3, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   return result;
}
void *thread(void *k){
    //Sleep(1);
    cout << "thread start\n";
    int c = *((int *) &k);
    cout << "storage int\n";
    cout << c << "\n";
    KeyBot bot;
    cout << "created bot\n";
    bot.KeyDown(c);
    cout << "keydown\n";
    //Sleep(10);
    //cout << "sleep\n";
    //bot.KeyUp(c);
    //cout << "keyup\n";
    //for(int i=0;i<10;i++){
        //Sleep(1000*60*60*24);
        //cout << "hahaha";
    //}
    //pthread_exit(NULL);
    //return NULL;
}
long int timeToMil(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    return ms;
}
int prev = 0;
int start = 0;
void *openPort(void *p){

    int port = *((int *) &p);
    stringstream command;
    command << "ncat -l " << port;
    //cout << command.str() << "\n";
    while(true){
        cout << "waiting " << port << "\n";
        stringstream key;
        key << exec(command.str());

        int k;
        key >> k;
        KeyBot bot;
        cout << "ms:" <<(timeToMil()-start) << "\n";
        if(k != prev || (timeToMil()-start) > 10){
                bot.KeyUp(prev);
                prev = k;
        }
        start = timeToMil();
        pthread_create(NULL, NULL, thread, (void *) k);
        //start = timeToMil();
    }
    cout << "exiting\n";
    return 0;
}

int main(){
    /*while(true){
        cout << "waiting\n";
        stringstream key;
        key << exec("ncat -l 7171");
        int k;
        key >> k;
        KeyBot bot;
        cout << "ms:" <<(timeToMil()-start) << "\n";
        if(k != prev || (timeToMil()-start) > 125){
                bot.KeyUp(prev);
                prev = k;
        }
        pthread_create(NULL, NULL, thread, (void *) k);
        start = timeToMil();
    }
    cout << "exiting\n";
    return 0;*/
    int p = 7171;
    pthread_create(NULL, NULL, openPort, (void *) p++);
    Sleep(1);
    pthread_create(NULL, NULL, openPort, (void *) p++);
    Sleep(1);
    pthread_create(NULL, NULL, openPort, (void *) p++);
    Sleep(1);
    pthread_create(NULL, NULL, openPort, (void *) p++);
    Sleep(1);
    pthread_create(NULL, NULL, openPort, (void *) p++);
    while(true){
        sleep(60000*60*24);
    }
}
