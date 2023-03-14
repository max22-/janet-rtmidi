(declare-project :name "rtmidi")
(declare-native
 :name "rtmidi"
 :source @["janet-rtmidi.c"]
 :cflags [;default-cflags "-I/usr/include/rtmidi"]
 :lflags [;default-lflags "-lrtmidi"])
