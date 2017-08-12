TEMPLATE = app
CONFIG += console
CONFIG += qt

INCLUDEPATH += "/home/qgh/chassis_control_test/chassis_test_001/include"
INCLUDEPATH += "/opt/etherlab/include"
INCLUDEPATH += "/usr/include"


LIBS +="/opt/etherlab/lib/libethercat.a"
LIBS +="/usr/lib/x86_64-linux-gnu/libpthread.so"

SOURCES += \
    source/Bezier.cpp \
    source/class_mobile_chassis.cpp \
    source/class_servo_motor.cpp \
    source/speed_planning.cpp \
    source/PID.cpp \
    source/ethercat_init.cpp \
    chassis.cpp \
    chassis_display.cpp

HEADERS += \
    include/Bezier.h \
    include/class_mobile_chassis.h \
    include/class_servo_motor.h \
    include/my_chassis_init.h \
    include/MyTypedef.h \
    include/PID.h \
    include/speed_planning.h \
    include/ethercat_init.h \
    chassis_display.h

FORMS += \
    chassis_display.ui

