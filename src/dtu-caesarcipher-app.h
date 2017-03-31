/* dtu-caesarcipher-app.h
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

#ifndef DTU_CAESARCIPHER_APP_H
#define DTU_CAESARCIPHER_APP_H

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define DTU_TYPE_CAESARCIPHER_APP (dtu_caesarcipher_app_get_type())

struct _DtuCaesarcipherApp
{
  GtkApplication parent_instance;
};

G_DECLARE_FINAL_TYPE (DtuCaesarcipherApp, dtu_caesarcipher_app, DTU, CAESARCIPHER_APP, GtkApplication)

DtuCaesarcipherApp *dtu_caesarcipher_app_new (void);

G_END_DECLS

#endif /* DTU_CAESARCIPHER_APP_H */

