#include <janet.h>
#include <rtmidi_c.h>

static Janet open_virtual_output_port(int32_t argc, Janet *argv) {
  RtMidiOutPtr out;
  janet_fixarity(argc, 1);
  out = rtmidi_out_create_default();
  if(!out->ok)
    janet_panic(out->msg);
  rtmidi_open_virtual_port(out, janet_getstring(argv, 0));
  if(!out->ok)
    janet_panic(out->msg);
  return janet_wrap_pointer(out);
}

static Janet open_output_port(int32_t argc, Janet *argv) {
  RtMidiOutPtr out;
  janet_fixarity(argc, 2);
  out = rtmidi_out_create_default();
  if(!out->ok)
    janet_panic(out->msg);
  rtmidi_open_port(out, janet_getinteger(argv, 0), janet_getstring(argv, 1));
  if(!out->ok)
    janet_panic(out->msg);
  return janet_wrap_pointer(out);
}

static Janet close_port(int32_t argc, Janet *argv) {
  RtMidiPtr dev;
  janet_fixarity(argc, 1);
  rtmidi_close_port(janet_getpointer(argv, 0));
  return janet_wrap_nil();
}

static Janet note_on(int32_t argc, Janet *argv) {
  RtMidiOutPtr out;
  uint8_t message[3] = {0};
  janet_fixarity(argc, 4);
  out = janet_getpointer(argv, 0);
  message[0] = janet_getinteger(argv, 1) & 0xf | 0x90;
  message[1] = janet_getinteger(argv, 2) & 0x7f;
  message[2] = janet_getinteger(argv, 3) & 0x7f;
  rtmidi_out_send_message(out, message, sizeof(message));
  if(!out->ok)
    janet_panic(out->msg);
  return janet_wrap_nil();
}

static Janet note_off(int32_t argc, Janet *argv) {
  RtMidiOutPtr out;
  uint8_t message[3] = {0};
  janet_fixarity(argc, 4);
  out = janet_getpointer(argv, 0);
  message[0] = janet_getinteger(argv, 1) & 0xf | 0x80;
  message[1] = janet_getinteger(argv, 2) & 0x7f;
  message[2] = janet_getinteger(argv, 3) & 0x7f;
  rtmidi_out_send_message(out, message, sizeof(message));
  if(!out->ok)
    janet_panic(out->msg);
  return janet_wrap_nil();
}



static const JanetReg cfuns[] = {
    {"open-virtual-output-port", open_virtual_output_port, "(rtmidi/open-virtual-output-port name)\n\nOpens a virtual output port"},
    {"open-output-port", open_output_port, "(rtmidi/open-output-port port-number name)\n\nOpens an output port"},
    {"close-port", close_port, "(rtmidi/close-port)\n\nCloses a port"},
    {"note-on", note_on, "(rtmidi/note-on port channel note velocity)\n\nSends a midi \"note on\" message"},
    {"note-off", note_off, "(rtmidi/note-off port channel note velocity)\n\nSends a midi \"note off\" message"},
    {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY(JanetTable *env) {
    janet_cfuns(env, "rtmidi", cfuns);
}
