/*****************************************************************************/
/*  options.h - the global variables for the program                         */
/*  Copyright (C) 1998-2002 Brian Masney <masneyb@gftp.org>                  */
/*                                                                           */
/*  This program is free software; you can redistribute it and/or modify     */
/*  it under the terms of the GNU General Public License as published by     */
/*  the Free Software Foundation; either version 2 of the License, or        */
/*  (at your option) any later version.                                      */
/*                                                                           */
/*  This program is distributed in the hope that it will be useful,          */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/*  GNU General Public License for more details.                             */
/*                                                                           */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program; if not, write to the Free Software              */
/*  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111 USA      */
/*****************************************************************************/

/* $Id$ */

#include "gftp.h"

supported_gftp_protocols gftp_protocols[] =
{
  {"FTP", 	rfc959_init, 	"ftp",		1},
  {"HTTP", 	rfc2068_init, 	"http",		1},
  {"Local", 	local_init, 	"file",		1},
  {"SSH2",	sshv2_init,	"ssh2", 	1},
  {"Bookmark", 	bookmark_init, 	"bookmark", 	0},
  {NULL, 	NULL, 		NULL,		0}
};

gftp_proxy_type proxy_type[] = {
  {N_("none"), ""},
  {N_("SITE command"), "USER %pu\nPASS %pp\nSITE %hh\nUSER %hu\nPASS %hp\n"},
  {N_("user@host"), "USER %pu\nPASS %pp\nUSER %hu@%hh\nPASS %hp\n"},
  {N_("user@host:port"), "USER %hu@%hh:%ho\nPASS %hp\n"},
  {N_("AUTHENTICATE"), "USER %hu@%hh\nPASS %hp\nSITE AUTHENTICATE %pu\nSITE RESPONSE %pp\n"},
  {N_("user@host port"), "USER %hu@%hh %ho\nPASS %hp\n"},
  {N_("user@host NOAUTH"), "USER %hu@%hh\nPASS %hp\n"},
  {N_("HTTP Proxy"), "http"},
  {N_("Custom"), ""},
  {NULL, NULL}
};

/* Most of these should be self explanatory */
char version[] = "gFTP " VERSION,
     *emailaddr = NULL,			/* Email address for logging in
                                           anonymously */
     *default_protocol = NULL,
     *edit_program = NULL,
     *view_program = NULL,
     *firewall_host = NULL,
     *firewall_username = NULL,
     *firewall_password = NULL,
     *firewall_account = NULL,
     *proxy_config = NULL, 		/* The way to log into the proxy */
     *http_proxy_host = NULL,
     *http_proxy_username = NULL, 
     *http_proxy_password = NULL,
     *startup_directory = NULL,
     *ssh_prog_name = NULL,
     *ssh_extra_params = NULL,
     **ssh_extra_params_list = NULL,
     *ssh2_sftp_path = NULL;
int num_ssh_extra_params;

FILE * logfd = NULL;			/* Our fd to write logs to */

double maxkbs = 0.00;			/* Bandwidth throttling */
GList * proxy_hosts = NULL, 		/* Our local hosts that won't need to 
                                           use the proxy */
      * registered_exts = NULL,		/* Registered file extensions */
      * viewedit_processes = NULL,      /* View/Edit processes that are 
                                           running */
      * file_transfers = NULL,		/* File transfers in progress */
      * file_transfer_logs = NULL;	/* Logs generated by other threads */

gftp_bookmarks * bookmarks = NULL;
GHashTable * bookmarks_htable = NULL,
           * config_htable = NULL;

int do_one_transfer_at_a_time = 1, 	/* Only allow one transfer at a time. 
                                           The other transfers will be queued */
    start_file_transfers = 1, 		/* Shall we start the file transfers? */
    transfer_in_progress = 0, 		/* Any transfers transferring files? */
    passive_transfer = 1, 		/* Are we sending PASV or PORT to the 
					   server */
    sort_dirs_first = 1, 		/* Put the dirs first when sorting */
    show_hidden_files = 1, 		/* Show hidden files */
    refresh_files = 0, 			/* Refresh the listbox after each file 
                                           is done */
    listbox_local_width = 302, 		/* Width of the local listbox */
    listbox_remote_width = 302, 	/* Width of the remote listbox */
    listbox_file_height = 265, 		/* Height of the local/remote listbox */
    transfer_height = 80, 		/* Height of the transfer window */
    log_height = 105, 			/* Height of the logging window */
    retries = 3, 			/* Number of auto-retries */
    sleep_time = 30, 			/* Number of seconds to wait between 
					   retries */
    network_timeout = 120, 		/* Timeout on the read()s and write()s */
    use_http11 = 1, 			/* Use HTTP/1.1 or HTTP/1.0 */
    listbox_dblclick_action = 0, 	/* What happens when you double click in the
					   file listboxes. 0 = View, 1 = Edit,
					   2 = Download */
    file_trans_column = 100, 		/* The width of the File column in the 
					   listbox */
    local_columns[6] = {0, 85, 75, 76, 120, 75}, /* The width of the local
    	file, size, user, group, date and attribs column */
    remote_columns[6] = {0, 85, 75, 76, 120, 75}, /* The width of the remote
    	file, size, user, group, date and attribs column */
    resolve_symlinks = 1, 		/* Send LIST -L or LIST to the remote ftp 
					   server */
    firewall_port = 21, 		/* What port to connect to for ftp? */
    http_proxy_port = 80,		/* What port to connect to for http? */
    overwrite_by_default = 0,		/* Resume file transfers or set to
                                           overwrite by default */
    append_file_transfers = 1,		/* Append new file transfers onto 
                                           existing ones for the same 
                                           hostname */
    ssh_need_userpass = 0,		/* Require a user/pass for SSH
                                           connections */
    ssh_use_askpass = 0,		/* Use the ssh-askpass tool to
					   grab the password. I personally
					   don't like this, but some people
					   do */
    sshv2_use_sftp_subsys = 0,		/* Call ssh -s sftp. If you set this
					   it'll automatically use the askpass
					   utility above */
    local_sortcol = 1,			
    local_sortasds = 1,
    remote_sortcol = 1,
    remote_sortasds = 1;


guint max_log_window_size = 5000;	/* Max size of the log window for the 
                                           GTK port */

GList * host_history = NULL,
      * port_history = NULL,
      * user_history = NULL,
      * localhistory = NULL,
      * remotehistory = NULL;
      
unsigned int host_len = 0, 
             port_len = 0, 
             user_len = 0,
             localhistlen = 0,
             remotehistlen = 0;

volatile sig_atomic_t viewedit_process_done = 0;

gftp_color send_color, recv_color, error_color, misc_color;

