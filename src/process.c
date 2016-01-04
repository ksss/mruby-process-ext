/*
original: https://github.com/ruby/ruby/blob/trunk/process.c
*/

#include "mruby.h"
#include "mruby/error.h"

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

#include "extconf.h"

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

static mrb_value
process_setuid(mrb_state *mrb, mrb_value mod)
{
  mrb_int uid;

  /* TODO support username string */
  mrb_get_args(mrb, "i", &uid);
#if defined(HAVE_SETRESUID)
  if (setresuid(uid, -1, -1) < 0) mrb_sys_fail(mrb, 0);
#elif defined HAVE_SETREUID
  if (setreuid(uid, -1) < 0) mrb_sys_fail(mrb, 0);
#elif defined HAVE_SETRUID
  if (setruid(uid) < 0) mrb_sys_fail(mrb, 0);
#elif defined HAVE_SETUID
  {
    if (geteuid() == uid) {
      if (setuid(uid) < 0) mrb_sys_fail(mrb, 0);
    }
    else {
      mrb_notimplement(mrb);
    }
  }
#endif
  return mrb_fixnum_value(uid);
}

#if defined HAVE_SETUID
static mrb_value
process_sys_setuid(mrb_state *mrb, mrb_value mod)
{
  mrb_int uid;
  mrb_get_args(mrb, "i", &uid);
  if (setuid(uid) < 0)
    mrb_sys_fail(mrb, 0);
  return mrb_nil_value();
}
#else
#  define process_sys_setuid mrb_notimplement_m
#endif

#if defined HAVE_SETRUID
static mrb_value
process_sys_setruid(mrb_state *mrb, mrb_value mod)
{
  mrb_int uid;
  mrb_get_args(mrb, "i", &uid);
  if (setruid(uid) < 0)
    mrb_sys_fail(mrb, 0);
  return mrb_nil_value();
}
#else
#  define process_sys_setruid mrb_notimplement_m
#endif

#if defined HAVE_SETREUID
static mrb_value
process_sys_setreuid(mrb_state *mrb, mrb_value mod)
{
  mrb_int rid, eid;
  mrb_get_args(mrb, "ii", &rid, &eid);
  if (setreuid(rid, eid) < 0)
    mrb_sys_fail(mrb, 0);
  return mrb_nil_value();
}
#else
#  define process_sys_setreuid mrb_notimplement_m
#endif

#if defined HAVE_SETRESUID
static mrb_value
process_sys_setresuid(mrb_state *mrb, mrb_value mod)
{
  mrb_int rid, eid, sid;
  mrb_get_args(mrb, "iii", &rid, &eid, &sid);
  if (setresuid(rid, eid, sid) < 0)
    mrb_sys_fail(mrb, 0);
  return mrb_nil_value();
}
#else
#  define process_sys_setresuid mrb_notimplement_m
#endif

void
mrb_mruby_process_ext_gem_init(mrb_state *mrb)
{
  struct RClass *process = mrb_define_module(mrb, "Process");
  mrb_define_class_method(mrb, process, "uid", process_getuid, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, process, "gid", process_getgid, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, process, "euid", process_geteuid, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, process, "egid", process_getegid, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, process, "uid=", process_setuid, MRB_ARGS_REQ(1));

  struct RClass *process_sys = mrb_define_module_under(mrb, process, "Sys");
  mrb_define_class_method(mrb, process_sys, "setuid", process_sys_setuid, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, process_sys, "setruid", process_sys_setruid, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, process_sys, "setreuid", process_sys_setreuid, MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, process_sys, "setresuid", process_sys_setresuid, MRB_ARGS_REQ(3));
}

void
mrb_mruby_process_ext_gem_final(mrb_state *mrb)
{
}
