/* dtu_caesarcipher.h
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

#ifndef DTU_CAESARCIPHER_H
#define DTU_CAESARCIPHER_H

#include <glib-object.h>

G_BEGIN_DECLS

#define DTU_TYPE_CAESARCIPHER (dtu_caesarcipher_get_type())

typedef enum
{
  Encrypt = 1,
  Decrypt = -1,
} CaesarcipherMode;

struct _DtuCaesarcipher
{
  GObject parent_instance;

  gchar *text;
  gint key;
  CaesarcipherMode mode;
  guint required_matches;
};

G_DECLARE_FINAL_TYPE (DtuCaesarcipher, dtu_caesarcipher, DTU, CAESARCIPHER, GObject)

DtuCaesarcipher *dtu_caesarcipher_new ();

void dtu_caesarcipher_set_mode(DtuCaesarcipher *self, CaesarcipherMode mode);

void
dtu_caesarcipher_crack_async(DtuCaesarcipher    *self,
                             GCancellable       *cancellable,
                             GAsyncReadyCallback callback,
                             gpointer            user_data);
gpointer
dtu_caesarcipher_crack_finish(GAsyncResult  *result,
                              GError       **error);
G_END_DECLS

#endif /* DTU_CAESARCIPHER_H */

