#define NOB_IMPLEMENTATION
#include "nob.h"

#define CFLAGS "-Wall", "-Wextra", "-ggdb", "-pedantic", "-O2"

int main(int argc, char **argv)
{
	NOB_GO_REBUILD_URSELF(argc, argv);

	const char *program = nob_shift_args(&argc, &argv);

	Nob_Cmd cmd = {0};
	nob_cmd_append(&cmd, "cc");
	nob_cmd_append(&cmd, CFLAGS);
	nob_cmd_append(&cmd, "-o", "main");
	nob_cmd_append(&cmd, "main.c");
	if(!nob_cmd_run_sync(cmd)) return 1;

	if(argc > 0){
		const char *subcmd = nob_shift_args(&argc, &argv);

		if(strcmp(subcmd, "run") == 0){
			cmd.count = 0;
			nob_cmd_append(&cmd, "./main");
			nob_da_append_many(&cmd, argv, argc);
			if(!nob_cmd_run_sync(cmd)) return 1;
		} else {
			nob_log(NOB_ERROR, "Unknown subcommand %s", subcmd);
			return 1;
		}
	}

	return 0;
}
