#include <lcom/lcf.h>

int main(int argc, char *argv[]) {
  lcf_set_language("PT-PT");

  lcf_trace_calls("/home/lcom/labs/proj/debug/trace.txt");

  lcf_log_output("/home/lcom/labs/proj/debug/output.txt");

  if (lcf_start(argc, argv))
    return 1;

  lcf_cleanup();

  return 0;
}

int(proj_main_loop)(int argc, char *argv[]) {
  return 0;
}
