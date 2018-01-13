# React Glow - An Interactive Dance Performance

React Glow uses Kinect, Ableton, OSC and twitter to create a Dance performance where the dancer will interact with the Flock based system.

# Technical Features
**openGL 3.3 Shaders to create the orbs**

**openFrameworks along with the following addons:**
- ofxKinectForWindows2
- ofxDmx
- ofxOsc
- ofxXMLSettings

## Requirements
- OS: **Windows 10 ( Not a virtual machine )**
- SDK: **Microsoft Kinect (Version 2)**
- IDE: **Visual Studio Community 2015**

## How to Run
- Install the SDK  to check that the Kinect is compatible with your system
- Make sure you have installed the addons mentioned above
- Click the solution (.sln) in the root
- Build the project in visual studio
- The project should now successfully build

## Instructions
### Debugging Keys
- Press key 'p' - Pointcloud displayed
- Press key 's' - Scene is displayed with two lights
- Press key 'f' - Shader is displayed
- Press key 'j' - Joints are displayed
- Press key 'd' - Display boids

### Path Clearing
- Press key ' *spacebar* ' - Clears Path

### Pose
- Press keys 'z' to 'b' - Saves poses 1-5 to xml
- Press 'l' - Loads poses
