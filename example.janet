(import ./build/rtmidi :as rtmidi)
(def port (rtmidi/open-virtual-output "janet"))
(forever
 (rtmidi/note-on port 0 69 127)
 (ev/sleep 1)
 (rtmidi/note-off port 0 69 127)
 (ev/sleep 0.5))
