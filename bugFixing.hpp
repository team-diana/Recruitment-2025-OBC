#include <iostream>
#include <thread>
#define MAX_ALTITUDE 100

class Circle {
    float centerX, centerY, radius;
public:
    Circle(float centerX, float centerY, float radius) : centerX(centerX), centerY(centerY), radius(radius) {}
    virtual ~Circle() = default;

    float getX() const { return centerX; }
    float getY() const { return centerY; }
    float getRadius() const { return radius; }
    float getArea() const { return M_PI * radius * radius; }
    void setCenter(float x, float y) { centerX = x; centerY = y; }
};

class Payload {
private:
    bool mounted = false;

public:
    void mount() {
        if (mounted) {
            throw std::logic_error("Payload already mounted");
        }
        std::cout << "Payload Mounted" << std::endl;
    }

    void unmount() {
        if (!mounted) { 
            throw std::logic_error("Payload already unmounted");
        }
        std::cout << "Payload unmounted" << std::endl;
    }

    virtual void use(Circle &circle, Rover &rover) = 0; // action to perform to use the payload
    
    ~Payload() {    // Automatically unmount the payload when it goes out of scope
        if (mounted) unmount();
    }

};

class Chair : public Circle {
    public:
    Chair(float centerX, float centerY, float radius) : Circle(centerX, centerY, radius) {}
};

class BeachUmbrella : public Circle {

    public:
    BeachUmbrella(float centerX, float centerY, float radius) : Circle(centerX, centerY, radius) {};
    
    bool contains(const Chair &chair) const {
        // Check if the chair is completely within the umbrella's radius
        float dx = chair.getX() - getX();
        float dy = chair.getY() - getY();
        float distance = sqrt(dx * dx + dy * dy);
        if (distance > this->getRadius()) {
            std::cout << "Chair is partially at the sun!" << std::endl;
            return false;
        }
        std::cout << "Chair is all in the umbrella's shade!" << std::endl;
        return true;
    }

}

class Spot : public Circle {
    private:
        float area;
        bool free = false;
    public:
        Spot(float centerX, float centerY, float radius, bool free) : Circle(centerX, centerY, radius), area(radius * radius * M_PI), free(free) {}
        bool isFree() const { return free; }
        void occupy() { 
            if (free) throw std::logic_error("Spot already occupied"); 
            free = true; }
        void vacate() { if (!free) 
            throw std::logic_error("Spot already free"); 
            free = false; }
};

class Rover {

private:
    const std::string name = "FORTUNA";
    Payload *payload = nullptr;   
    float x = 0, y = 0; // Rover position
    bool haveASpot = false;
public:
    
    void movTo(float newX, float newY) {
        std::cout << "Rover moved to (" << newX << ", " << newY << ")" << std::endl;
    }

    ~Rover() {
        if (payload != nullptr) unmountPayload();
    }

    void mountPayload(Payload &p) {
        if (this->payload != nullptr)
            throw std::logic_error("Payload already mounted");
        p.mount();
        this->payload = &p;
    }

    void unmountPayload() {
        if (this->payload == nullptr) throw std::logic_error("No payload mounted");
        this->payload->unmount();
        this->payload = nullptr;
    }

    void usePayload(Circle &circle) {
        if (payload == nullptr) throw std::logic_error("No payload mounted");
        payload->use(circle, *this);
    }

    int getX(){ return x; }
    int getY(){ return y; }
    bool getHaveASpot() const { return haveASpot; }
    void setHaveASpot(bool val) { haveASpot = val; }
};


class DIANArm : public Payload {
private:
    bool release = false;
    bool grabbing = false;
    Rover *rover;
    std::thread grabbingThread;
public:
    void use(Circle &circle, Rover &rover) override {
        this->rover = &rover;
        if (circle.getX() != rover.getX() || circle.getY() != rover.getY()) {
            throw std::logic_error("Rover must be on top of the object to grab it");
        }
        auto umbrella = dynamic_cast<Spot*>(&circle);
        if (umbrella == nullptr) {
            auto chair = dynamic_cast<Chair*>(&circle);
            if (chair == nullptr) {
                throw std::invalid_argument("DIANArm can only be used with BeachUmbrella or Chair objects");
            } else {
                std::cout << "Chair identified" << std::endl;
            }
        }
        else {
            std::cout << "Umbrella identified" << std::endl;
        }
        this->grabObject();
        this->grabbingThread = std::thread([this, &circle, &rover]() {
            while (!this->release) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            std::cout << "Object released in " << circle.getX() << ", " << circle.getY() << std::endl;
        });
    }
    void releaseObject() {
        if (!grabbing) throw std::logic_error("No object is being grabbed");
        if (this->grabbingThread.joinable()) {
            this->grabbingThread.join(); // Wait for the thread to finish
        }
        grabbing = false;
        release = true;
        std::cout << "Releasing object..." << std::endl;
    }
    void grabObject() {
        if (grabbing) throw std::logic_error("Already grabbing an object");
        grabbing = true;
        release = false;
        std::cout << "Grabbing object..." << std::endl;
    }
};

class Drone : public Payload {
    float altitude = 1000;
public:

    bool use(Circle &circle, Rover &rover) override {
        std::cout << "Drone Take off" << std::endl;
        if (altitude > MAX_ALTITUDE){
            throw std::logic_error("The Drone went too high and the wind made it crash (True Story)");
        }
        auto spot = dynamic_cast<Spot*>(&circle);
        if (spot == nullptr) {
            throw std::invalid_argument("Drone can only be used with Spot objects");
        }
        if (spot->isFree()) {
            if (rover.getHaveASpot()) {
                throw std::logic_error("Rover already has a target spot");
            }
            std::cout << "Spot is free, Rover is moving to the spot" << std::endl;
            rover.moveTo(spot->centerX, spot->centerY);
            spot->occupy();
            rover.setHaveASpot(true);
        } else {
            std::cout << "Spot is occupied, searching for another spot" << std::endl;
        }
        std::cout << "Drone Landed" << std::endl;
    }

    void setAltitude(float altitude) {
        altitude = altitude;
    }
};
