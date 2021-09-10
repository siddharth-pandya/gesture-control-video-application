# gesture-control-video-application:
Project uses the hand Gestures to perform functions on an application (mainly video playback application) on the system, which are being recognized by the ultrasonic sensors placed over the laptop which then converts hand signals to the keyboard or mouse shortcuts using the Python's PyAutoGUI library.
Step1- Ultrasonic sensors attached to top of laptop/PC captures the ultrasonic waves duration echoed back from the hand gesture made in front of it.
Step2-Arduino connected to ultrasonic sensors, reads the duration and type of hand gesture, processes it, and sends a output value to python application.
Step3-Python serially connects to arduino in real-time and processes input data coming from arduino using PyAutoGUI library into key pressing/mouse clicking actions, which then in turn mimic the physical hand movements on keyboard/mouse to perform an action on screen, which in turn is done just by hand gestures in air.
