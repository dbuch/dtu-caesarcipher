/* dtu-caesarcipher-perspective.h
 *
 * Copyright (C) 2017 Daniel Buch <boogiewasthere@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DTU_CAESARCIPHER_PERSPECTIVE_H
#define DTU_CAESARCIPHER_PERSPECTIVE_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define DTU_TYPE_CAESARCIPHER_PERSPECTIVE (dtu_caesarcipher_perspective_get_type())

G_DECLARE_DERIVABLE_TYPE (DtuCaesarcipherPerspective, dtu_caesarcipher_perspective, DTU, CAESARCIPHER_PERSPECTIVE, GtkStack)

struct _DtuCaesarcipherPerspectiveClass
{
	GtkStackClass parent;

	void (*switch_to) (DtuCaesarcipherPerspective *self,
			   GtkWidget *page);

	gpointer padding[10];
};

DtuCaesarcipherPerspective *dtu_caesarcipher_perspective_new (void);
void dtu_caesarcipher_perspective_switch(DtuCaesarcipherPerspective *self, GtkWidget *page);

G_END_DECLS

#endif /* DTU_CAESARCIPHER_PERSPECTIVE_H */

