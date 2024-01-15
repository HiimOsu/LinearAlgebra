#include <iostream>
#include <SFML\Graphics.hpp>
#include <stdint.h>

#include "sources\VectorCollections\nVector.h"
#include "sources\Game\Game.h"

using namespace std;

int main(){
    cout << "Entering Main!\n";

    sf::Window window;
    Game game;

    while (game.isRunning())
    {
        game.CaptureInput();
        game.Update();
        game.LateUpdate();
        game.Draw();
        game.calculateDeltaTime();
    }

    // uint32_t bits = 1;
    // int pos = 1;
    // cout << "bits: " << bits << endl;
    // cout << "bits in bool : " << (bool) bits << endl;
    // cout << "(u_int32) (1 << pos) : " << (uint32_t) ((1 << pos)) << endl;
    // cout << "bits & (1 << pos) : " << (bool) (bits & (1 << pos) )<< endl;
}