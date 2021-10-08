#include <plus.h>
#include <s7.h>
#include <stdbool.h>
#include <stdio.h>

#define HELP_plusone "(plusone x)"
s7_pointer scm_plusone(s7_scheme *sc, s7_pointer args) {
  return s7_make_integer(sc, plusone(s7_integer(s7_car(args))));
}

void bind_plusone(s7_scheme *sc, s7_pointer env) {
  s7_define(sc, env, s7_make_symbol(sc, "plusone"),
            s7_make_function(sc, "plusone", scm_plusone, 1, 0,
                             false, // req, opt, rest?
                             HELP_plusone));

  s7_define_safe_function(sc, "plusone-safe", scm_plusone, 1, 0, false, "(plusone-safe x)");
}

#define HELP_current_timestamp "(current-timestamp )"
s7_pointer scm_current_timestamp(s7_scheme *sc, s7_pointer args) {
  return s7_make_real(sc, (double)current_timestamp());
}

void bind_current_timestamp(s7_scheme *sc, s7_pointer env) {
  s7_define(sc, env, s7_make_symbol(sc, "current-timestamp"),
            s7_make_function(sc, "current-timestamp", scm_current_timestamp, 0,
                             0, false, // req, opt, rest?
                             HELP_current_timestamp));
}

s7_pointer scm_plusone_opt(s7_scheme *sc, s7_pointer args) {
  // printf("unopt called\n");
    
  return s7_make_integer(sc, plusone(s7_integer(s7_car(args))));
}

s7_int plus_one_opt(s7_int x) {
  // printf("opt called\n");
  return plusone(x);
}

void bind_plusone_opt(s7_scheme *sc, s7_pointer env) {
    // s7_define_safe_function(sc, "plusone-opt", scm_plusone_opt, 1, 0, false, "(plusone-opt x)");
    
  s7_pointer sig_ret = s7_make_symbol(sc, "integer?");
  s7_pointer sig_x = s7_make_symbol(sc, "integer?");
  s7_pointer sig = s7_make_signature(sc, 2, sig_ret, sig_x);
  s7_define_typed_function(sc, "plusone-opt", scm_plusone_opt, 1, 0, false, HELP_plusone, sig);
  s7_set_i_i_function(sc, s7_name_to_value(sc, "plusone-opt"), plus_one_opt);

}

int main(int argc, char **argv) {
  s7_scheme *sc = s7_init();

  bind_current_timestamp(sc, s7_nil(sc));
  bind_plusone(sc, s7_nil(sc));
  bind_plusone_opt(sc, s7_nil(sc));
  printf("hi there!\n");
  s7_pointer args = s7_make_list(sc, argc, s7_nil(sc));
  for (int i = 0; i < argc; i++) {
    s7_list_set(sc, args, i, s7_make_string(sc, argv[i]));
  }
  s7_define(sc, s7_nil(sc), s7_make_symbol(sc, "argv"), args);
  if (argc < 2) {
    printf("First arg is required \n");
  } else {
    s7_load(sc, argv[1]);
  }

  s7_free(sc);
}
