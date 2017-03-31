/* dtu-caesarcipher-app-win.c
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
#include "dtu-caesarcipher-app-win.h"

struct _DtuCaesarcipherAppWin
{
  GtkApplicationWindow parent_instance;
};

G_DEFINE_TYPE (DtuCaesarcipherAppWin, dtu_caesarcipher_app_win, GTK_TYPE_APPLICATION_WINDOW)

DtuCaesarcipherAppWin *
dtu_caesarcipher_app_win_new (GtkApplication *app)
{
  return g_object_new (DTU_TYPE_CAESARCIPHER_APP_WIN,
                       "application", app,
                        NULL);
}

static void
dtu_caesarcipher_app_win_finalize (GObject *object)
{
  DtuCaesarcipherAppWin *self = (DtuCaesarcipherAppWin *)object;

  G_OBJECT_CLASS (dtu_caesarcipher_app_win_parent_class)->finalize (object);
}

static void
dtu_caesarcipher_app_win_class_init (DtuCaesarcipherAppWinClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = dtu_caesarcipher_app_win_finalize;
}

static void
dtu_caesarcipher_app_win_init (DtuCaesarcipherAppWin *self)
{
}
