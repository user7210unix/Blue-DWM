#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "get_data/disk_info.h"
#include "get_data/get_cpu.h"
#include "get_data/get_ram.h"
#include "get_data/get_sys.h"
#include "get_data/gpu_info.h"
#include "get_data/uptime.h"
#include "get_data/user_name.h"

#define RESET_BG "\033[0m"
#define BLACK_BG "\033[40m"
#define RED_BG "\033[41m"
#define GREEN_BG "\033[42m"
#define YELLOW_BG "\033[43m"
#define BLUE_BG "\033[44m"
#define MAGENTA_BG "\033[45m"
#define CYAN_BG "\033[46m"
#define WHITE_BG "\033[47m"

#define RESET "\033[0m"
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"

void wait_for_keypress() {
#ifdef _WIN32
  _getch();
#else
  getchar();
  printf("\033[?1049l");
  printf("\033[?25h");
#endif
}

void reset_term() {
  printf("\033[?1049l");
  printf("\033[?25h");
}

void clear_terminal() {
#ifdef _WIN32
  system("cls");
#else
  printf("\033[?1049h");
  printf("\033[?25l");
#endif
}

void print_centered(const char *str) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int width = w.ws_col;
  int len = strlen(str);
  int offset = (width - len) / 2;

  printf("%*s%s\n", offset, "", str);
}

char *create_repeated_string(char character, int count) {
  char *result = (char *)malloc((count + 1) * sizeof(char));
  if (result == NULL) {
    printf("Memory error\n");
    return NULL;
  }
  memset(result, character, count);
  result[count] = '\0';
  return result;
}

void print_centered_squares() {
  const char *squares = WHITE_BG
      "    " RESET_BG RED_BG "    " RESET_BG GREEN_BG "    " RESET_BG YELLOW_BG
      "    " RESET_BG BLUE_BG "    " RESET_BG MAGENTA_BG "    " RESET_BG CYAN_BG
      "    " RESET_BG WHITE_BG "    " RESET_BG;

  int padding = 4 * 8;
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int width = w.ws_col;
  int offset = (width - padding) / 2;

  printf("\n%*s%s\n", offset, "", squares);
}

void print_info(const char *label, const char *value, int *max_width) {
  char buffer[100];
  const char *color;
  const char *icon;
  const char *spacer;

  icon = "";

  spacer = "";
  // spacer = "│    ";

  // printf(WHITE "│ ");

  if (strstr(label, "Usage")) {
    label = "";
    color = MAGENTA;
    icon = "";
    spacer = "";

    printf(color, icon, label, WHITE, value, RESET);
  } else {
    if (strstr(label, "CPU")) {
      color = MAGENTA;
      icon = " ";
    } else if (strstr(label, "RAM")) {
      color = MAGENTA;
      icon = "󰍛 ";
    } else if (strstr(label, "Disk")) {
      color = MAGENTA;
      icon = " ";
    } else if (strstr(label, "Kernel")) {
      color = MAGENTA;
      icon = " ";
    } else if (strstr(label, "GPU")) {
      color = MAGENTA;
      icon = " ";
    } else if (strstr(label, "Uptime")) {
      color = MAGENTA;
      icon = " ";
    } else if (strstr(label, "OS")) {
      color = MAGENTA;
      icon = " ";
    } else if (strstr(label, "Host")) {
      color = MAGENTA;
      icon = "󰏔 ";
    } else if (strstr(label, "Shell")) {
      color = MAGENTA;
      icon = " ";
    } else if (strstr(label, "WM")) {
      color = MAGENTA;
      icon = " ";
    } else {
      color = RESET;
    }

    snprintf(buffer, sizeof(buffer), "%+27s%s%s ", color, icon, label);

    strncat(buffer, WHITE " ", sizeof(buffer) - strlen(buffer) - 1);
    strncat(buffer, spacer, sizeof(buffer) - strlen(buffer) - 1);
    strncat(buffer, value, sizeof(buffer) - strlen(buffer) - 1);
    strncat(buffer, RESET, sizeof(buffer) - strlen(buffer) - 1);

    print_centered(buffer);

    int current_width = strlen(buffer);

    if (current_width > *max_width) {
      *max_width = current_width;
    }
  }
}

void print_memory_info(const char *label, int used_memory, int full_memory,
                       int *max_width) {
  char buffer[100];
  snprintf(buffer, sizeof(buffer), "%.2f GB of %.2f GB",
           (float)used_memory / 1024, (float)full_memory / 1024);
  print_info(label, buffer, max_width);
}

void print_disk_info(disk_info_t *info, int *max_width) {
  if (get_disk_info("/", info) == 0) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Used: %-1llu GB, Total: %-1llu GB",
             info->used_space / (1024 * 1024 * 1024),
             info->total_space / (1024 * 1024 * 1024));
    print_info("Disk", buffer, max_width);
  } else {
    printf("Failed to get disk information.\n");
  }
}

void print_uptime_info(uptime_t uptime, int *max_width) {
  char buffer[100];
  snprintf(buffer, sizeof(buffer), "%-1dd %-1dh %-1dm", uptime.days,
           uptime.hours, uptime.minutes);
  print_info("Uptime", buffer, max_width);
}

void print_window_manager(int *max_width) {
  char buffer[100];
  const char *wm =
      getenv("DESKTOP_SESSION") ? getenv("DESKTOP_SESSION") : "Unknown";
  print_info("WM", wm, max_width);
}

void print_usage(const char *program_name, int *max_width) {
  printf(RED "   ▄   ▄████  ▄███▄     ▄▄▄▄▀ ▄█▄     ▄  █ \n");
  printf("    █  █▀   ▀ █▀   ▀ ▀▀▀ █    █▀ ▀▄  █   █ \n");
  printf("██   █ █▀▀    ██▄▄       █    █   ▀  ██▀▀█ \n");
  printf("█ █  █ █      █▄   ▄▀   █     █▄  ▄▀ █   █ \n");
  printf("█  █ █  █     ▀███▀    ▀      ▀███▀     █  \n");
  printf("█   ██   ▀                             ▀   \n");
  printf("                                           \n");
  printf(YELLOW "Usage:\n\n--cpu --ram --gpu --disk --host --kernel --"
                "os --shell --uptime --colors --wm --user\n");
}

void print_os(int *max_width) {
  FILE *os_file = fopen("/etc/os-release", "r");
  char buffer[100];
  char os_name[100] = "Unknown OS";
  size_t linecap = 0;
  char *line = NULL;

  if (!os_file) {
    perror("Failed to open /etc/os-release");
    return;
  }

  while (getline(&line, &linecap, os_file) != -1) {
    if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
      snprintf(os_name, sizeof(os_name), "%s", line + 13);
      os_name[strcspn(os_name, "\"")] = '\0';
      break;
    }
  }

  free(line);
  fclose(os_file);

  print_info("OS", os_name, max_width);
}

int main(int argc, char *argv[]) {
  clear_terminal();
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int terminal_width = w.ws_col;
  int terminal_height = w.ws_row;
  int text_height = 0;

  CPUInfo cpu_info = get_cpu_info();
  SystemInfo sys_info = get_system_info();
  const char *gpu_model = get_gpu_model();
  disk_info_t info;
  uptime_t uptime = get_uptime();
  int used_memory = get_memory_usage();
  int full_memory = get_memory_total();

  int max_width = 0;
  int output_lines = 0;
  int empty_lines = 0;

  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      output_lines++;
    }
    empty_lines = (terminal_height - output_lines) / 2;
    for (int i = 0; i < empty_lines; i++) {
      printf("\n");
    }
  } else {
    output_lines += 8;
    empty_lines = (terminal_height - output_lines) / 2;
    for (int i = 0; i < empty_lines; i++) {
      printf("\n");
    }
    print_info("Kernel", sys_info.kernel, &max_width);
    print_info("Hostname", sys_info.device_name, &max_width);
    print_window_manager(&max_width);
    print_info("Shell", sys_info.shell, &max_width);
    print_uptime_info(uptime, &max_width);
    print_centered_squares();
  }

  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "--help") == 0) {
      print_usage("nfetch", &max_width);
    } else {
      if (strcmp(argv[i], "--cpu") == 0) {
        print_info("CPU", cpu_info.model, &max_width);
      } else if (strcmp(argv[i], "--ram") == 0) {
        print_memory_info("RAM", used_memory, full_memory, &max_width);
      } else if (strcmp(argv[i], "--gpu") == 0) {
        print_info("GPU", gpu_model, &max_width);
      } else if (strcmp(argv[i], "--disk") == 0) {
        print_disk_info(&info, &max_width);
      } else if (strcmp(argv[i], "--host") == 0) {
        print_info("Hostname", sys_info.device_name, &max_width);
      } else if (strcmp(argv[i], "--kernel") == 0) {
        print_info("Kernel", sys_info.kernel, &max_width);
      } else if (strcmp(argv[i], "--os") == 0) {
        print_os(&max_width);
      } else if (strcmp(argv[i], "--shell") == 0) {
        print_info("Shell", sys_info.shell, &max_width);
      } else if (strcmp(argv[i], "--uptime") == 0) {
        print_uptime_info(uptime, &max_width);
      } else if (strcmp(argv[i], "--colors") == 0) {
        print_centered_squares();
      } else if (strcmp(argv[i], "--wm") == 0) {
        print_window_manager(&max_width);
      } else if (strcmp(argv[i], "--user") == 0) {
        char *username = get_current_username();
        print_info("Hi, ", username, &max_width);
      }
    }
  }

  for (int i = 0; i < empty_lines; i++) {
    printf("\n");
  }

  wait_for_keypress();

  return 0;
}
