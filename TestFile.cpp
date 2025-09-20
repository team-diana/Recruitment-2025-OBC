#include <iostream>
#include <unistd.h>
#include <cassert>


int main() {
    //Declaration part
    Rover rover;
    Drone drone;
    DIANArm arm;
    drone.setAltitude(50);
    
    // The rover must use the drone to find a free spot
    Spot spotOccupied(10, 12, 5, false);
    Spot spotFree(5, 5, 5, true);
    rover.mountPayload(drone);
    rover.usePayload(spotOccupied);
    rover.usePayload(spotFree);
    rover.unmountPayload();

    // The rover must use the arm to grab the umbrella, move to the center of the free spot and release it there
    BeachUmbrella umbrella(0, 0, 5);
    rover.mountPayload(arm);
    rover.moveTo(0, 0);
    rover.usePayload(umbrella); // Move to the spot
    rover.moveTo(5, 5);
    arm.releaseObject();

    // The rover must use the arm to grab the chair, move it to be completely in the shade of the umbrella and release it there
    Chair chair(6, 7, 1);
    rover.moveTo(6, 7);
    rover.usePayload(chair);
    rover.moveTo(6, 5);
    arm.releaseObject();
    assert(umbrella.contains(chair));
    rover.unmountPayload();
    std::cout << "Test completed successfully!" << std::endl;
    return 0;
}