
#include <stdio.h>
#include <SerialStream.h>
using namespace LibSerial;

#include "robot.hh"

static SerialStream port;

RgRobot::RgRobot(int argc, char* argv[], void (*cb)(Robot*))
{
    port.Open("/dev/ttyUSB0");
    port.SetBaudRate(SerialStreamBuf::BAUD_9600);
    port.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
    port.SetParity(SerialStreamBuf::PARITY_NONE);
    port.SetNumOfStopBits(1);
}

RgRobot::~RgRobot()
{

}

float
RgRobot::get_range()
{
    return range;
}

void
RgRobot::set_vel(double lvel, double rvel)
{
    char temp[100];
    snprintf(temp, "%.02f,%.02f\n", lvel, rvel);
    port.write(temp, strlen(temp));
}

void
RgRobot::read_range()
{
    char temp[100];
    int ii = 0;

    for (; ii < 96; ++ii) {
        port.read(temp + ii, 1);
        if (temp[ii] == '\n') {
            break;
        }
    }

    temp[ii+1] = 0;

    this->range = atof(temp);
}

void
RgRobot::do_stuff()
{
    while (1) {
        this->read_range();
        this->on_update(this);
    }
}
