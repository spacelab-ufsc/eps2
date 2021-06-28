/* #include <stdio.h> */
#include <csp/csp.h>

#include <system/sys_log/sys_log.h>

void csp_hex_dump (const char *desc, void *addr, int len)
{
	int i;
	unsigned char buff[17];
	unsigned char *pc = (unsigned char*)addr;

	// Output description if given.
	if (desc != NULL) {
        /* printf ("%s:\r\n", desc); */
        sys_log_print_event_from_module(SYS_LOG_INFO, LIBCSP_MODULE_NAME, desc);
        sys_log_print_msg(":");
        sys_log_new_line();
    }

	if (len == 0) {
        /* printf("  ZERO LENGTH\r\n"); */
        sys_log_print_msg(" ZERO LENGTH");
        sys_log_new_line();
		return;
	}
	if (len < 0) {
        /* printf("  NEGATIVE LENGTH: %i\r\n",len); */
        sys_log_print_msg(" NEGATIVE LENGTH: ");
        sys_log_print_int(len);
        sys_log_new_line();
		return;
	}

	// Process every byte in the data.
	for (i = 0; i < len; i++) {
		// Multiple of 16 means new line (with line offset).

		if ((i % 16) == 0) {
			// Just don't print ASCII for the zeroth line.
			if (i != 0) {
                /* printf ("  %s\r\n", buff); */
                sys_log_print_msg(" ");
                sys_log_print_str(buff);
                sys_log_print_msg("\t");
                sys_log_new_line();
            }

			// Output the offset.
            /* printf ("  %p ", addr + i); */
            sys_log_print_hex(addr + i);
		}

		// Now the hex code for the specific character.
        /* printf (" %02x", pc[i]); */
        sys_log_print_msg(" ");
        sys_log_print_hex(pc[i]);

		// And store a printable ASCII character for later.
		if ((pc[i] < 0x20) || (pc[i] > 0x7e))
			buff[i % 16] = '.';
		else
			buff[i % 16] = pc[i];
		buff[(i % 16) + 1] = '\0';
	}

	// Pad out last line if not exactly 16 characters.
	while ((i % 16) != 0) {
        /* printf ("   "); */
        sys_log_print_msg("\t");
		i++;
	}

	// And print the final ASCII bit.
    /* printf ("  %s\r\n", buff); */
    sys_log_print_msg(" ");
    sys_log_print_str(buff);
    sys_log_new_line();
}
