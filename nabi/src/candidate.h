/* Nabi - X Input Method server for hangul
 * Copyright (C) 2003 Choe Hwanjin
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#ifndef _NABICANDIDATE_H_
#define _NABICANDIDATE_H_

#include <X11/Xlib.h>
#include <gtk/gtk.h>

typedef struct _NabiCandidate     NabiCandidate;
typedef struct _NabiCandidateItem NabiCandidateItem;

struct _NabiCandidateItem {
    unsigned short int ch;
    gchar *comment;
};

struct _NabiCandidate {
    GtkWidget *window;
    Window parent;
    gchar *label;
    GtkWidget **children;
    const NabiCandidateItem **data;
    int first;
    int n_per_window;
    int n_per_row;
    int n;
    int current;
};

NabiCandidate*     nabi_candidate_new(char *label_str,
		   	              int n_per_window,
			              const NabiCandidateItem **data,
			              Window parent);
void               nabi_candidate_prev(NabiCandidate *candidate);
void               nabi_candidate_next(NabiCandidate *candidate);
void               nabi_candidate_prev_row(NabiCandidate *candidate);
void               nabi_candidate_next_row(NabiCandidate *candidate);
unsigned short int nabi_candidate_get_current(NabiCandidate *candidate);
unsigned short int nabi_candidate_get_nth(NabiCandidate *candidate, int n);
void               nabi_candidate_delete(NabiCandidate *candidate);

NabiCandidateItem* nabi_candidate_item_new(unsigned short int ch,
					   const gchar *comment);
void               nabi_candidate_item_delete(NabiCandidateItem *item);

#endif /* _NABICANDIDATE_H_ */
