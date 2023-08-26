# MATB-YARP

Multi Attribute Task Battery for YARP.

MATB-YARP includes system monitoring task, tracking task, communications task, and resource management task. The basic structure is the same as MATB.
In conjunction with YARP, data can be recorded on MATB performance performed by participants with various external signals, such as the iCub.
#
MATB(Multi attribute task battery)

https://matb.larc.nasa.gov/

YARP(Yet Another Robot Platform)


https://github.com/robotology/yarp


icub-main is needed to use joystickCtrl.

icub-main

https://github.com/robotology/icub-main/tree/39a7e037e3d5dbdf94cdbd4046bd8c9a8cfb666d

#
###Edit MATB events

Using resource finder of YARP, you can specify the "event_json_file" to read a JSON file that defines the timings of the MATB events.
The event timings are described in the JSON file. JSON event files can be converted XML files with the format described in the MATB-II user manual.

##### MATB-II User manual

https://ntrs.nasa.gov/api/citations/20110014456/downloads/20110014456.pdf

To convert an XML file to a JSON file, for example, you can use the following website.

https://codebeautify.org/xmltojson

Of course, you may also create a JSON file directly by referring to a JSON file stored in the following folder.

https://github.com/motonobu-aoki/matb-yarp/tree/main/app/matb

#

### Important references
- Aoki, Motonobu, et al. "On the Influence of Social Robots in Cognitive Multitasking." International Journal of Humanoid Robotics 19.06 (2022): 2250022.

This is the paper in which MATB-YARP was used in the experiment and the details of its operation are described.
