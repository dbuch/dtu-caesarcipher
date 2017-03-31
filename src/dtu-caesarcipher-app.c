
/* dtu-caesarcipher-app.c
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
#include "dtu-caesarcipher-app.h"

typedef struct _DtuCaesarcipherAppPrivate
{
  DtuCaesarcipherAppWin *win;

} DtuCaesarcipherAppPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (DtuCaesarcipherApp, dtu_caesarcipher_app, GTK_TYPE_APPLICATION)

DtuCaesarcipherApp *
dtu_caesarcipher_app_new (void)
{
  return g_object_new (DTU_TYPE_CAESARCIPHER_APP,
                       "application-id", "org.gnome.DtuCaesarcipher",
                       "flags", G_APPLICATION_FLAGS_NONE,
                       NULL);
}

static void
dtu_caesarcipher_app_finalize (GObject *object)
{
  DtuCaesarcipherApp *self = (DtuCaesarcipherApp *)object;

  G_OBJECT_CLASS (dtu_caesarcipher_app_parent_class)->finalize (object);
}

static void
dtu_caesarcipher_app_activate(GApplication *app)
{
  DtuCaesarcipherAppWin *win = dtu_caesarcipher_app_win_new (GTK_APPLICATION(app));

  gtk_window_present (GTK_WINDOW(win));
}


static void
dtu_caesarcipher_app_class_init (DtuCaesarcipherAppClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

  object_class->finalize = dtu_caesarcipher_app_finalize;
  app_class->activate = dtu_caesarcipher_app_activate;
}

static void
dtu_caesarcipher_app_init (DtuCaesarcipherApp *self)
{

}
