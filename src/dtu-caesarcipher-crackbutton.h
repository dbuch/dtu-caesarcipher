/* dtu-caesarcipher-crackbutton.h
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

#ifndef DTU_CAESARCIPHER_CRACKBUTTON_H
#define DTU_CAESARCIPHER_CRACKBUTTON_H

#include <gtk/gtk.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define DTU_TYPE_CAESARCIPHER_CRACKBUTTON (dtu_caesarcipher_crackbutton_get_type())

G_DECLARE_FINAL_TYPE (DtuCaesarcipherCrackbutton, dtu_caesarcipher_crackbutton, DTU, CAESARCIPHER_CRACKBUTTON, GtkButton)

DtuCaesarcipherCrackbutton *dtu_caesarcipher_crackbutton_new (void);

G_END_DECLS

#endif /* DTU_CAESARCIPHER_CRACKBUTTON_H */

