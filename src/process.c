#include "mruby.h"

#if defined(_WIN32) || defined(_WIN64)
typedef unsigned int uid_t;
typedef unsigned int gid_t;
uid_t getuid(void) { return 0; }
uid_t geteuid(void) { return 0; }
gid_t getgid(void) { return 0; }
gid_t getegid(void) { return 0; }
#else
#include <unistd.h>
#include <sys/types.h>
#endif

static mrb_value
process_getuid(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value((mrb_int)getuid());
}

static mrb_value
process_getgid(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value((mrb_int)getgid());
}

static mrb_value
process_geteuid(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value((mrb_int)geteuid());
}

static mrb_value
process_getegid(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value((mrb_int)getegid());
}

void
mrb_mruby_process_ext_gem_init(mrb_state *mrb)
{
  struct RClass *process = mrb_define_module(mrb, "Process");
  mrb_define_class_method(mrb, process, "uid", process_getuid, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, process, "gid", process_getgid, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, process, "euid", process_geteuid, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, process, "egid", process_getegid, MRB_ARGS_NONE());
}

void
mrb_mruby_process_ext_gem_final(mrb_state *mrb)
{
}
